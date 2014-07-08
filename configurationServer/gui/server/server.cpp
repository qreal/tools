#include <QMessageBox>
#include "server.h"

Server::Server(QWidget *parent) :
	QDialog(parent),
	tcpServer(0),
	networkSession(0)
	//blockSize(0),
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

	mapper = new QSignalMapper;
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptClientConnection()));
	connect(mapper, SIGNAL(mapped(QString)), this, SLOT(clientDisconnectedSlot(QString)));
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
	if (!tcpServer->listen(QHostAddress::AnyIPv4, 55555))
	{
		QMessageBox::critical(this, tr("qReal Server"),
							  tr("Unable to start the server: %1.")
							  .arg(tcpServer->errorString()));
		close();
		return;
	}
}

void Server::acceptClientConnection()
{
	QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
	emit newClient(clientSocket->peerAddress().toString());
	int idusersocs = clientSocket->socketDescriptor();
	SClients[idusersocs] = clientSocket;
	connect(SClients[idusersocs], SIGNAL(disconnected()), mapper, SLOT(map()));
	mapper->setMapping(SClients[idusersocs], SClients[idusersocs]->peerAddress().toString());
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
		foreach(int i, SClients.keys())
		{
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
	QList<QNetworkInterface> adressList = QNetworkInterface::allInterfaces();
	QString address;
	for (int j = 0; j < adressList.size(); j++)
	{
		QList<QNetworkAddressEntry> addressEntry = adressList[j].addressEntries();
		for (int i = 0; i < addressEntry.size(); i++)
			address += addressEntry[i].ip().toString() + "\n";
		address += "\n";
	}

	return address;
}

void Server::clientDisconnectedSlot(QString clientsID)
{
	emit clientDisconnectedSignal(clientsID);
}
