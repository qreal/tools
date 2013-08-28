namespace TrikRemoteControl

module Constants =
    let connectionTimeout = 2000
    let sendTimeout = 2000

type ConnectionState =
    abstract Send : string -> unit

type ConnectedState (client : System.Net.Sockets.TcpClient) =
    /// Network data stream.
    let stream = client.GetStream ()

    /// Writer for network stream.
    let writer = new System.IO.StreamWriter (stream)
    do writer.AutoFlush <- true

    interface ConnectionState with
        member x.Send (str : string) = 
            async {
                do! Async.AwaitIAsyncResult (writer.WriteLineAsync str, Constants.sendTimeout) |> Async.Ignore
            } |> Async.Start

type DisconnectedState () =
    interface ConnectionState with
        member x.Send (str : string) = ()

/// Network client. Can connect to some endpoint, send and receive string data.
type Client (host : string, port) =
    
    /// TCP client that is used for communication.
    let client = new System.Net.Sockets.TcpClient ()
    let mutable connectionState : ConnectionState = DisconnectedState () :> _

    let connectedEvent = Event<_> ()
    let connectionFailedEvent = Event<_> ()

    member x.ConnectedEvent = connectedEvent.Publish
    member x.ConnectionFailedEvent = connectionFailedEvent.Publish

    member x.Connect () =
        let syncContext = System.Threading.SynchronizationContext.Current
        let postEvent (event : Event<_>) = syncContext.Post (System.Threading.SendOrPostCallback (fun _ -> event.Trigger ()), null)

        async {
            let! result = Async.AwaitIAsyncResult (client.ConnectAsync(host, port), Constants.connectionTimeout)
            if result && client.Connected then
                postEvent connectedEvent
                connectionState <- ConnectedState client :> ConnectionState
            else
                postEvent connectionFailedEvent
        } |> Async.Start

    /// Send given string to a server.
    member this.Send (str : string) = connectionState.Send str

