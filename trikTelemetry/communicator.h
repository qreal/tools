#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include "sensorData.h"

/// Communicator class handles connection to a robot - sends requests for new sensors data and ports configuration,
/// reports when gets responses to those requests.
class Communicator : public QObject
{
	Q_OBJECT

public:
	explicit Communicator(QHostAddress const &serverAddress);

	~Communicator() override;

signals:
	void error(QString const &message);

	/// Emitted when Communicator gets a response to the data request.
	void newData(SensorData const &message);

	/// Emitted when Communicator gets a responce to the ports info request.
	void portsInfo(QStringList const &analog, QStringList const &digital, QStringList const &special
			, QStringList const &encoders);

public slots:
	/// Sends data request to a telemetry server.
	void getNewValues();

	/// Sends ports request to a telemetry server.
	void getPortsInfo();

private slots:
	void onIncomingData();

	/// Parses a message from a telemetry server, emits either newData signal or portsInfo signal
	/// depending on type of the message.
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

	/// Address of a telemetry server on a robot.
	QHostAddress mServerAddress;

	/// Declared size of a current message.
	int mExpectedBytes = 0;
};
