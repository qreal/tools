open System
open System.Windows
open System.Windows.Controls
open System.Windows.Markup

open TrikRemoteControl

let port = 8888

type MainWindow () =

    let mutable client : Client option = None
    let mutable controlsRegistered = false

    let connect ip =
        if client.IsNone then
            client <- Some <| Client (ip, port)

    let sendCommand command =
        if client.IsSome then
            client.Value.Send command

    member x.RegisterControls (mainWindow : Window) =
        if not controlsRegistered then

            let registerButtonHandler buttonName handler =
                let button = mainWindow.FindName buttonName :?> Button
                Event.add handler button.Click

            let ipTextBox = mainWindow.FindName "ipTextBox" :?> TextBox

            registerButtonHandler "connect" (fun _ -> connect <| ipTextBox.Text)

            let registerCommand button =
                let commandScriptFileName = "scripts/" + button + ".qts"
                registerButtonHandler button (fun _ -> sendCommand <| System.IO.File.ReadAllText commandScriptFileName)

            registerCommand "up"
            registerCommand "down"
            registerCommand "left"
            registerCommand "right"
            registerCommand "stop"

            controlsRegistered <- true

[<STAThread>]
[<EntryPoint>]
let main _ = 
    let application = Application.LoadComponent (new Uri ("App.xaml", UriKind.Relative)) :?> Application

    let mainWindow = MainWindow () 

    application.Activated
    |> Event.add (fun _ -> mainWindow.RegisterControls (application.MainWindow))

    application.Run ()
