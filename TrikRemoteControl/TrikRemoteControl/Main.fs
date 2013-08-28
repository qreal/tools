open System
open System.Windows
open System.Windows.Controls
open System.Windows.Controls.Primitives
open System.Windows.Markup

open TrikRemoteControl

let port = 8888

type MainWindow (mainWindow : Window) =

    let button name = mainWindow.FindName name :?> Button

    let ipTextBox = mainWindow.FindName "ipTextBox" :?> TextBox
    let connectButton = mainWindow.FindName "connect" :?> ToggleButton
    let connectionFailedLabel = mainWindow.FindName "connectionFailedLabel" :?> Label
    let upButton = button "up"
    let downButton = button "down"
    let leftButton = button "left"
    let rightButton = button "right"
    let stopButton = button "stop"
    let buttons = [upButton; downButton; leftButton; rightButton; stopButton]

    let settings = TrikSettings ()

    let mutable client : Client option = None

    let setButtonsEnabled enabled = for button in buttons do button.IsEnabled <- enabled

    let noConnection reason = 
        client <- None
        connectButton.IsChecked <- Nullable false
        connectButton.IsEnabled <- true
        connectionFailedLabel.Content <- reason
        connectionFailedLabel.Visibility <- Visibility.Visible
        setButtonsEnabled false

    let connectionFailed () =
        noConnection "Подключение не удалось"

    let disconnected () =
        noConnection "Соединение потеряно"

    let connectionSucceed () =
        setButtonsEnabled true
        connectionFailedLabel.Visibility <- Visibility.Hidden
        connectButton.IsEnabled <- false

    let connect ip =
        if client.IsNone then
            client <- Some <| Client (ip, port)
            client.Value.ConnectedEvent |> Event.add (fun _ -> connectionSucceed ())
            client.Value.ConnectionFailedEvent |> Event.add (fun _ -> connectionFailed ())
            client.Value.DisconnectedEvent |> Event.add (fun _ -> disconnected ())
            client.Value.Connect ()

    let sendCommand command =
        if client.IsSome then
            let command = "direct:" + command
            client.Value.Send command

    let init () =
        let registerButtonHandler buttonName handler =
            let button = mainWindow.FindName buttonName :?> ButtonBase
            Event.add handler button.Click

        let registerCommand button key =
            let commandScriptFileName = "scripts/" + button + ".qts"
            let command _ = sendCommand <| System.IO.File.ReadAllText commandScriptFileName
            registerButtonHandler button command 
            mainWindow.KeyDown 
            |> Event.filter (fun event -> event.Key = key) 
            |> Event.add command

        registerButtonHandler "connect" 
            (fun _ -> 
                connect <| ipTextBox.Text
                settings.IpAddress <- ipTextBox.Text
            )

        registerCommand "up" Input.Key.Up
        registerCommand "down" Input.Key.Down
        registerCommand "left" Input.Key.Left
        registerCommand "right" Input.Key.Right
        registerCommand "stop" Input.Key.Back

        setButtonsEnabled false

        ipTextBox.Text <- settings.IpAddress

    do init ()

[<STAThread>]
[<EntryPoint>]
let main _ = 
    let application = Application.LoadComponent (new Uri ("App.xaml", UriKind.Relative)) :?> Application

    let mainWindow = ref None

    application.Activated
    |> Event.add (fun _ -> if (!mainWindow).IsNone then mainWindow := Some <| MainWindow(application.MainWindow))

    application.Run ()
