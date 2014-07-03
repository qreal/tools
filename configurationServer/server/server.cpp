#include <QLayout>
#include <QMessageBox>
#include "server.h"

Server::Server(QWidget *parent) :
	QDialog(parent),
	tcpServer(0),
	clientSocket(0),
	networkSession(0),
	blockSize(0)
{
	/// creating widgets:
	statusLabel = new QLabel;

	allText	 = new QTextEdit;
	allText	->setReadOnly(true);

	messageText = new QLineEdit;

	sendButton = new QPushButton(tr("Send"));
	sendButton->setDisabled(true);

	quitButton = new QPushButton(tr("Quit"));
	quitButton->setAutoDefault(false);

	QNetworkConfigurationManager manager;
	if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
	{
		// Get saved network configuration
		QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
		settings.beginGroup(QLatin1String("QtNetwork"));
		const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
		settings.endGroup();

		// If the saved network configuration is not currently discovered use the system default
		QNetworkConfiguration config = manager.configurationFromIdentifier(id);
		if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered)
		{
			config = manager.defaultConfiguration();
		}

		networkSession = new QNetworkSession(config, this);
		connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

		statusLabel->setText(tr("Opening network session."));
		networkSession->open();
	}
	else
	{
		sessionOpened();
	}

	/// connecting widgets:
	connect(sendButton, SIGNAL(clicked()), this, SLOT(sendSettings()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptClientConnection()));

	/// adding widgets into the window:
	QHBoxLayout *messageLayout = new QHBoxLayout;
	messageLayout->addWidget(messageText);
	messageLayout->addWidget(sendButton);

	QHBoxLayout *quitLayout = new QHBoxLayout;
	quitLayout->addStretch(1);
	quitLayout->addWidget(quitButton);
	quitLayout->addStretch(1);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(statusLabel);
	mainLayout->addWidget(allText);
	mainLayout->addLayout(messageLayout);
	mainLayout->addLayout(quitLayout);
	setLayout(mainLayout);

	setWindowTitle(tr("Chat Server"));
}

void Server::sessionOpened()
 {
	 // Save the used configuration
	 if (networkSession)
	 {
		 QNetworkConfiguration config = networkSession->configuration();
		 QString id;
		 if (config.type() == QNetworkConfiguration::UserChoice)
			 id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
		 else
			 id = config.identifier();

		 QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
		 settings.beginGroup(QLatin1String("QtNetwork"));
		 settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
		 settings.endGroup();
	 }

	 tcpServer = new QTcpServer(this);
	 if (!tcpServer->listen(QHostAddress::LocalHost, tcpServer->serverPort()))
	 {
		 QMessageBox::critical(this, tr("Chat Server"),
							   tr("Unable to start the server: %1.")
							   .arg(tcpServer->errorString()));
		 close();
		 return;
	 }

	 statusLabel->setText(tr("The server is running on\n\nIP-adress: %1\nPort: %2\n\n"
							 "Run the Chat Client now.")
						  .arg(tcpServer->serverAddress().toString()).arg(tcpServer->serverPort()));
 }

void Server::acceptClientConnection()
{
	clientSocket = tcpServer->nextPendingConnection();

	connect(clientSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
	connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnectedFromClient()));
	connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));

	allText->clear();
	allText->textCursor().insertText("Client connected!\n");

	sendButton->setEnabled(true);
}

//void Server::receiveMessage()
//{
//	QDataStream in(clientSocket);
//	in.setVersion(QDataStream::Qt_5_2);

//	if (blockSize == 0)
//	{
//		if (clientSocket->bytesAvailable() < (int)sizeof(quint16))
//			return;

//		in >> blockSize;
//	}

//	if (clientSocket->bytesAvailable() < blockSize)
//		return;

//	blockSize = 0;
//	QString newMessage;
//	in >> newMessage;
//	allText	->textCursor().insertText("Client: " + newMessage + '\n');
//}

//void Server::sendMessage()
//{
//	if(clientSocket)
//	{
//		if (messageText->text().isEmpty())
//			return;
//		sendButton->setDisabled(true);

//		QByteArray block;
//		QDataStream out(&block, QIODevice::WriteOnly);

//		out << (quint16)messageText->text().length();
//		out << messageText->text();
//		clientSocket->write(block);

//		allText	->textCursor().insertText("You: " + messageText->text() + '\n');

//		messageText->clear();

//		sendButton->setEnabled(true);
//	}
//}

void Server::sendSettings()
{

}

void Server::clientDisconnected()
{
	sendButton->setDisabled(true);
	QMessageBox::information(this, tr("Chat Server"),
							 tr("Client disconnected!"));
}
