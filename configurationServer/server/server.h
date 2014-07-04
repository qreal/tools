#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QtNetwork>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

#include "settingsManager.h"

namespace Ui {
class Server;
}

class Server : public QDialog
{
	Q_OBJECT

public:
	explicit Server(QWidget *parent = 0);

private slots:
	void sessionOpened();
	void acceptClientConnection();
	void sendSettings();
	void receiveMessage();
	void clientDisconnected();

private:
	/// labels:
	QLabel *statusLabel;

	/// text widgets:
	QLineEdit *messageText;
	QTextEdit *allText;

	/// buttons:
	QPushButton *sendButton;
	QPushButton *quitButton;


	QTcpServer *tcpServer;
	QNetworkSession *networkSession;
	QMap<int,QTcpSocket *> SClients;
	//qReal::SettingsManager *Qmanager;

	quint16 blockSize;
};

#endif // SERVER_H
