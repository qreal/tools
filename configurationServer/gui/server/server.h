#pragma once

#include <QDialog>
#include <QtNetwork>

#include "qrkernel/settingsManager.h"

class Server : public QDialog
{
	Q_OBJECT

public:
	explicit Server(QWidget *parent = 0);
	QString getIP();
	quint16 getAdress();

private slots:
	void sessionOpened();
	void acceptClientConnection();
	void clientDisconnectedSlot(QString clientsID);

signals:
	void newClient(QString clientName);
	void clientDisconnectedSignal(QString clientsIP);

private:
	void sendSettings();
	QMap<int,QTcpSocket *> SClients;
	QTcpServer *tcpServer;
	QNetworkSession *networkSession;
	quint16 blockSize;
	QSignalMapper *mapper;
};

