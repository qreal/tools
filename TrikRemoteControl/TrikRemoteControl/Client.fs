namespace TrikRemoteControl

module Constants =
    [<Literal>]
    let ConnectionTimeout = 2000
    [<Literal>]
    let SendTimeout = 2000

type ConnectionState =
    abstract Send : string -> unit
    abstract DisconnectedEvent : IEvent<unit>

type ConnectedState (client : System.Net.Sockets.TcpClient, syncContext : System.Threading.SynchronizationContext) as this =

    let disconnectedEvent = Event<_> ()

    let keepAliveTimer = new System.Timers.Timer (1000.0, AutoReset = true)
    do keepAliveTimer.Elapsed.Add (fun _ -> (this :> ConnectionState).Send "keepalive")
    do keepAliveTimer.Start ()

    /// Network data stream.
    let stream = client.GetStream ()

    /// Writer for network stream.
    let writer = new System.IO.StreamWriter (stream, AutoFlush = true)

    interface ConnectionState with
        member x.Send (str : string) = 
            let postEvent (event : Event<_>) = syncContext.Post (System.Threading.SendOrPostCallback (fun _ -> event.Trigger ()), null)
            async {
                do! Async.AwaitIAsyncResult (writer.WriteLineAsync str, Constants.SendTimeout) |> Async.Ignore
                if not client.Connected then
                    postEvent disconnectedEvent
                    
            } |> Async.Start

        member this.DisconnectedEvent = disconnectedEvent.Publish

type DisconnectedState () =
    let disconnectedEvent = Event<_> ()

    interface ConnectionState with
        member x.Send (str : string) = ()
        member this.DisconnectedEvent = disconnectedEvent.Publish

/// Network client. Can connect to some endpoint, send and receive string data.
type Client (host : string, port) =

    /// TCP client that is used for communication.
    let client = new System.Net.Sockets.TcpClient ()
    let mutable connectionState : ConnectionState = DisconnectedState () :> _
    let syncContext = System.Threading.SynchronizationContext.Current

    let connectedEvent = Event<_> ()
    let connectionFailedEvent = Event<_> ()
    let disconnectedEvent = Event<_> ()

    member this.ConnectedEvent = connectedEvent.Publish
    member this.ConnectionFailedEvent = connectionFailedEvent.Publish
    member this.DisconnectedEvent = disconnectedEvent.Publish

    member this.Connect () =
        let postEvent (event : Event<_>) = syncContext.Post (System.Threading.SendOrPostCallback (fun _ -> event.Trigger ()), null)

        async {
            let! result = Async.AwaitIAsyncResult (client.ConnectAsync(host, port), Constants.ConnectionTimeout)
            if result && client.Connected then
                postEvent connectedEvent
                connectionState <- ConnectedState (client, syncContext) :> ConnectionState
                connectionState.DisconnectedEvent.Add (fun () -> disconnectedEvent.Trigger ())
            else
                postEvent connectionFailedEvent
        } |> Async.Start

    /// Send given string to a server.
    member this.Send (str : string) = connectionState.Send str

    member this.Dispose () = (client :> System.IDisposable).Dispose ()

    interface System.IDisposable with
        member this.Dispose () = this.Dispose ()
