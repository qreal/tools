#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include "sensorData.h"

class Communicator : public QObject
{
	Q_OBJECT

public:
	explicit Communicator(QHostAddress const &serverAddress);
	~Communicator();

signals:
	void error(QString const &message);
	void newData(SensorData const &message);
	void portsInfo(QStringList const &analog, QStringList const &digital, QStringList const &special
			, QStringList const &encoders);

public slots:
	void getNewValues();
	void getPortsInfo();

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
