#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

class Communicator : public QObject
{
	Q_OBJECT

public:
	explicit Communicator(QHostAddress const &serverAddress);
	~Communicator();

	void getNewValues();

signals:
	void newMessage(QString const &message);

private slots:
	void onIncomingData();
	void processIncomingMessage(QString const &message);

private:
	/// Establishes connection and initializes socket. If connection fails, leaves socket
	/// in invalid state.
	void connect();

	/// Disconnects from robot.
	void disconnect();

	/// Sends message using message length protocol (message is in form "<data length in bytes>:<data>").
	void send(QString const &data);

	/// Socket that holds connection.
	QTcpSocket mSocket;

	/// Buffer to accumulate parts of a message.
	QByteArray mBuffer;

	QHostAddress mServerAddress;

	/// Declared size of a current message.
	int mExpectedBytes = 0;
};
