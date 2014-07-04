#include <QMessageBox>
#include "server.h"

Server::Server(QWidget *parent) :
	QDialog(parent),
	tcpServer(0),
	//clientSocket(0),
	networkSession(0),
	blockSize(0)
{
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

		networkSession->open();
	}
	else
	{
		sessionOpened();
	}

	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptClientConnection()));
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
		 QMessageBox::critical(this, tr("qReal Server"),
							   tr("Unable to start the server: %1.")
							   .arg(tcpServer->errorString()));
		 close();
		 return;
	 }

	//statusLabel->setText(tr("The server is running on\n\nIP-adress: %1\nPort: %2\n\n"
	//						 "Run the Chat Client now.")
	//					  .arg(tcpServer->serverAddress().toString()).arg(tcpServer->serverPort()));
 }

void Server::acceptClientConnection()
{
	QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
	emit newClient(clientSocket->localAddress().toString());
	int idusersocs = clientSocket->socketDescriptor();
	SClients[idusersocs] = clientSocket;
	//connect(SClients[idusersocs], SIGNAL(readyRead()), this, SLOT(sendSettings()));
	connect(SClients[idusersocs], SIGNAL(disconnected()), this, SLOT(disconnectedFromClient()));
	connect(SClients[idusersocs], SIGNAL(disconnected()), SClients[idusersocs], SLOT(deleteLater()));
	sendSettings();
}

void Server::sendSettings()
{
	if(!SClients.isEmpty())
	{
		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);

		out << (quint16)qReal::SettingsManager::instance()->convertToString().length();
		out << qReal::SettingsManager::instance()->convertToString();
		foreach(int i, SClients.keys()) {
			SClients[i]->write(block);
		}
	}
}

quint16 Server::getAdress()
{
	return tcpServer->serverPort();
}

QString Server::getIP()
{
	return tcpServer->serverAddress().toString();
}

void Server::clientDisconnected()
{
	QMessageBox::information(this, tr("qReal Server"),
							 tr("Client disconnected!"));
}
