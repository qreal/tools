namespace TrikRemoteControl
open System

module Constants =
    [<Literal>]
    let ConnectionTimeout = 2000
    [<Literal>]
    let SendTimeout = 2000

/// Network client. Can connect to some endpoint, send and receive string data.
type Client (host : string, port: int) =

    /// TCP client that is used for communication.
    let client = new System.Net.Sockets.TcpClient()
    let mutable connectionState = None
    let syncContext = System.Threading.SynchronizationContext.Current
    
    let connectedEvent = Event<_> ()
    let connectionFailedEvent = Event<_> ()
    let disconnectedEvent = Event<_> ()    
    let postEvent (event : Event<_>) = syncContext.Post (System.Threading.SendOrPostCallback (fun _ -> event.Trigger ()), null)

    member this.ConnectedEvent = connectedEvent.Publish
    member this.ConnectionFailedEvent = connectionFailedEvent.Publish
    member this.DisconnectedEvent = disconnectedEvent.Publish
    
    member this.Connect () =        
        this.Disconnect()
        async {
            let! _ = Async.AwaitIAsyncResult (client.ConnectAsync(host, port), Constants.ConnectionTimeout)
            if client.Connected then
                postEvent connectedEvent
                let keepAliveTimer = new System.Timers.Timer (1000.0, AutoReset = true)
                keepAliveTimer.Elapsed.Add (fun _ -> this.Send "keepalive")
                keepAliveTimer.Start ()
                connectionState <-  Some (new System.IO.StreamWriter (client.GetStream (), AutoFlush = true), keepAliveTimer)                
            else
                postEvent connectionFailedEvent
        } |> Async.Start

    member this.Send (str : string) = 
           connectionState |> Option.iter (fun (writer, timer) ->
               async {
                   do! Async.AwaitIAsyncResult (writer.WriteLineAsync str, Constants.SendTimeout) |> Async.Ignore
                   if not client.Connected then
                       this.Disconnect()
                } |> Async.Start)
                    
    member this.Disconnect () = 
        match connectionState with
          | None -> ()
          | Some (writer, timer) -> 
              writer.Close()
              timer.Dispose()
              connectionState <- None
              postEvent disconnectedEvent
              
        
    member this.Dispose () = this.Disconnect(); (client :> System.IDisposable).Dispose ()

    interface System.IDisposable with
        member this.Dispose () = this.Dispose ()
