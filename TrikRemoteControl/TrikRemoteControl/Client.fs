namespace TrikRemoteControl

/// Network client. Can connect to some endpoint, send and receive string data.
type Client (host, port) =
    
    /// TCP client that is used for communication.
    let client = new System.Net.Sockets.TcpClient (host, port)

    /// Network data stream.
    let stream = client.GetStream ()

    /// Writer for network stream.
    let writer = new System.IO.StreamWriter (stream)
    do writer.AutoFlush <- true

    /// Loop that waits for connection to a server to be opened.
    let rec waitForConnection () =
        if not client.Connected then 
            waitForConnection ()
        else
            System.Threading.Thread.Sleep 100
    do waitForConnection ()

    /// Send given string to a server.
    member this.Send (str : string) = writer.WriteLine str
