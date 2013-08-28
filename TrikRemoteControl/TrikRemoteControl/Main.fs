open System
open System.Windows
open System.Windows.Controls
open System.Windows.Markup

open TrikRemoteControl

let port = 8888

type MainWindow (mainWindow : Window) =

    let button name = mainWindow.FindName name :?> Button

    let ipTextBox = mainWindow.FindName "ipTextBox" :?> TextBox
    let connectButton = button "connect"
    let upButton = button "up"
    let downButton = button "down"
    let leftButton = button "left"
    let rightButton = button "right"
    let stopButton = button "stop"
    let buttons = [upButton; downButton; leftButton; rightButton; stopButton]

    let mutable client : Client option = None

    let setButtonsEnabled enabled = for button in buttons do button.IsEnabled <- enabled

    let connect ip =
        if client.IsNone then
            client <- Some <| Client (ip, port)
            client.Value.ConnectedEvent |> Event.add (fun _ -> setButtonsEnabled true)
            client.Value.ConnectionFailedEvent |> Event.add (fun _ -> client <- None)
            client.Value.Connect ()

    let sendCommand command =
        if client.IsSome then
            client.Value.Send command

    let init () =
        let registerButtonHandler buttonName handler =
            let button = mainWindow.FindName buttonName :?> Button
            Event.add handler button.Click

        let registerCommand button =
            let commandScriptFileName = "scripts/" + button + ".qts"
            registerButtonHandler button (fun _ -> sendCommand <| System.IO.File.ReadAllText commandScriptFileName)

        registerButtonHandler "connect" (fun _ -> connect <| ipTextBox.Text)

        registerCommand "up"
        registerCommand "down"
        registerCommand "left"
        registerCommand "right"
        registerCommand "stop"

        setButtonsEnabled false

    do init ()

[<STAThread>]
[<EntryPoint>]
let main _ = 
    let application = Application.LoadComponent (new Uri ("App.xaml", UriKind.Relative)) :?> Application

    let mainWindow = ref None

    application.Activated
    |> Event.add (fun _ -> if (!mainWindow).IsNone then mainWindow := Some <| MainWindow(application.MainWindow))

    application.Run ()
