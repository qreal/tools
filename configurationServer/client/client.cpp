#include "client.h"

Client::Client(QWidget *parent) :
	QDialog(parent),
	networkSession(0),
	blockSize(0)
{

	setWindowTitle(tr("Chat client"));

	/// creating buttons and text:
	hostLabel = new QLabel(tr("Server IP-adress:"));

	portLabel = new QLabel(tr("Server port:"));

	portLineEdit = new QLineEdit;
	portLineEdit->setValidator(new QIntValidator(1, 65535));

	messageText = new QLineEdit;

	sendButton = new QPushButton(tr("Send"));
	sendButton->setDisabled(true);

	connectButton = new QPushButton(tr("Connect"));

	quitButton = new QPushButton(tr("Quit"));
	quitButton->setAutoDefault(false);

	chatText = new QTextEdit;
	chatText->setReadOnly(true);

	/// adding adresses to combo box
	hostAdress = new QComboBox;
	QList<QHostAddress> adressList = QNetworkInterface::allAddresses();

	for (int i = 0; i < adressList.size(); ++i)
	{
		hostAdress->addItem(adressList.at(i).toString());
	}

	serverSocket = new QTcpSocket;

	///adding operation to buttons:
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
	connect(serverSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
	connect(connectButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
	connect(serverSocket, SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));
	connect(serverSocket, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(displayError(QAbstractSocket::SocketError)));

	/// adding widgets into the window:
	QGridLayout *connectionLayout = new QGridLayout;
	connectionLayout->addWidget(hostLabel, 0, 0);
	connectionLayout->addWidget(hostAdress, 0, 1);
	connectionLayout->addWidget(portLabel, 1, 0);
	connectionLayout->addWidget(portLineEdit, 1, 1);

	QHBoxLayout *messageLayout = new QHBoxLayout;
	messageLayout->addWidget(messageText);
	messageLayout->addWidget(sendButton);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(connectButton);
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(quitButton);
	buttonLayout->addStretch(1);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(connectionLayout);
	mainLayout->addWidget(chatText);
	mainLayout->addLayout(messageLayout);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	portLineEdit->setFocus();

	QNetworkConfigurationManager manager;
	if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
	{
		// Get saved network configuration
		QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
		settings.beginGroup(QLatin1String("QtNetwork"));
		const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
		settings.endGroup();

		// If the saved network configuration is not currently discovered use the system default
		QNetworkConfiguration config = manager.configurationFromIdentifier(id);
		if ((config.state() & QNetworkConfiguration::Discovered) !=
				QNetworkConfiguration::Discovered)
		{
			config = manager.defaultConfiguration();
		}

		networkSession = new QNetworkSession(config, this);
		connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

		networkSession->open();
	}
}

void Client::receiveMessage()
{
	QDataStream in(serverSocket);
	in.setVersion(QDataStream::Qt_5_2);

	if (blockSize == 0)
	{
		if (serverSocket->bytesAvailable() < (int)sizeof(quint16))
			return;

		in >> blockSize;
	}

	if (serverSocket->bytesAvailable() < blockSize)
			 return;

	blockSize = 0;
	QString newMessage;
	in >> newMessage;
	chatText->textCursor().insertText("Server: " + newMessage + '\n');
}

void Client::sendMessage()
{
	if (messageText->text().isEmpty())
		return;
	sendButton->setEnabled(false);

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out << (quint16)messageText->text().length();
	out << messageText->text();
	serverSocket->write(block);

	chatText->textCursor().insertText("You: " + messageText->text() + '\n');

	messageText->clear();

	sendButton->setEnabled(true);
}

void Client::sessionOpened()
{
	// Save the used configuration
	QNetworkConfiguration config = networkSession->configuration();
	QString id;
	if (config.type() == QNetworkConfiguration::UserChoice)
		id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
	else
		id = config.identifier();

	QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
	settings.beginGroup(QLatin1String("QtNetwork"));
	settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
	settings.endGroup();


	sendButton->setEnabled(true);
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
	serverSocket->close();
	switch (socketError)
	{
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information(this, tr("Chat client"),
								 tr("The host was not found. Please check the "
									"host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::information(this, tr("Chat client"),
								 tr("The connection was refused by the peer. "
									"Make sure the fortune server is running, "
									"and check that the host name and port "
									"settings are correct."));
		break;
	default:
		QMessageBox::information(this, tr("Chat client"),
								 tr("The following error occurred: %1.")
								 .arg(serverSocket->errorString()));
	}
	hostAdress->setEnabled(true);
	portLineEdit->setEnabled(true);
}

void Client::connectToServer()
{
	serverSocket->connectToHost(hostAdress->currentText(), portLineEdit->text().toInt());

	if (serverSocket->waitForConnected(5000))
	{
		chatText->clear();
		chatText->textCursor().insertText("Server connected!\n");
		hostAdress->setDisabled(true);
		portLineEdit->setDisabled(true);
		connectButton->setDisabled(true);
		sendButton->setEnabled(true);
	}
	else
	{
		hostAdress->setEnabled(true);
		portLineEdit->setEnabled(true);
	}
}

void Client::disconnectedFromServer()
{
	hostAdress->setDisabled(true);
	portLineEdit->setDisabled(true);
	connectButton->setEnabled(true);
	sendButton->setDisabled(true);

	QMessageBox::information(this, tr("Chat Client"),
							 tr("Server disconnected!"));
}
