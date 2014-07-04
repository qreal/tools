#pragma once

#include <QDialog>
#include <QtNetwork>

#include "qrkernel/settingsManager.h"

namespace Ui {
class Server;
}

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
	void clientDisconnected();

signals:
	void newClient(QString clientName);

private:
	void sendSettings();
	QMap<int,QTcpSocket *> SClients;
	QTcpServer *tcpServer;
	QNetworkSession *networkSession;
	quint16 blockSize;
};

