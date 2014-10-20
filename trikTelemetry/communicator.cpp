#include "communicator.h"

#include <QtCore/QFileInfo>

static uint const telemetryServerPort = 9000;

Communicator::Communicator(QHostAddress const &serverAddress)
	: mServerAddress(serverAddress)
{
	QObject::connect(&mSocket, SIGNAL(readyRead()), this, SLOT(onIncomingData()), Qt::DirectConnection);
	connect();
}

Communicator::~Communicator()
{
	disconnect();
}

void Communicator::getNewValues()
{
	send("data");
}

void Communicator::getPortsInfo()
{
	send("ports");
}

void Communicator::onIncomingData()
{
	if (!mSocket.isValid()) {
		return;
	}

	QByteArray const &data = mSocket.readAll();
	mBuffer.append(data);

	while (!mBuffer.isEmpty()) {
		if (mExpectedBytes == 0) {
			// Determining the length of a message.
			int const delimiterIndex = mBuffer.indexOf(':');
			if (delimiterIndex == -1) {
				// We did not receive full message length yet.
				return;
			} else {
				QByteArray const length = mBuffer.left(delimiterIndex);
				mBuffer = mBuffer.mid(delimiterIndex + 1);
				bool ok;
				mExpectedBytes = length.toInt(&ok);
				if (!ok) {
					qDebug() << "Malformed message, can not determine message length from this:" << length;
					mExpectedBytes = 0;
				}
			}
		} else {
			if (mBuffer.size() >= mExpectedBytes) {
				QByteArray const message = mBuffer.left(mExpectedBytes);
				mBuffer = mBuffer.mid(mExpectedBytes);

				processIncomingMessage(message);

				mExpectedBytes = 0;
			} else {
				// We don't have all message yet.
				return;
			}
		}
	}
}

void Communicator::processIncomingMessage(QString const &message)
{
	QString dataLabel("data:");
	QString portsLabel("ports:");

	if (message.startsWith(dataLabel)) {
		SensorData data;

		for (QString const &value : message.right(message.length() - dataLabel.length()).split(";")) {
			if (value.startsWith("analog:")) {
				QStringList sensors = value.right(value.length() - QString("analog:").length()).split(",");
				for (QString const &sensor : sensors) {
					QString port = sensor.split("=")[0];
					QStringList values = sensor.split("=")[1].split(":");
					data.analog[port] = values[0].toInt();
					data.analogRaw[port] = values[1].toInt();
				}
			} else if (value.startsWith("digital:")) {
				QStringList sensors = value.right(value.length() - QString("digital:").length()).split(",");
				for (QString const &sensor : sensors) {
					QString port = sensor.split("=")[0];
					QStringList values = sensor.split("=")[1].split(":");
					data.digital[port] = values[0].toInt();
					data.digitalRaw[port] = values[1].toInt();
				}
			} else if (value.startsWith("special:")) {
				QStringList sensors = value.right(value.length() - QString("special:").length()).split(",");
				for (QString const &sensor : sensors) {
					QString port = sensor.split("=")[0];
					QStringList values = sensor.split("=")[1].split(":");
					data.special[port] = values[0].toInt();
					data.specialRaw[port] = values[1].toInt();
				}
			} else if (value.startsWith("accelerometer:")) {
				int const labelLength = QString("accelerometer:").length();
				QStringList values = value.mid(labelLength + 1, value.length() - labelLength - 2).split(",");
				data.accelerometer = QVector<int>({ values[0].toInt(), values[1].toInt(), values[2].toInt() });
			} else if (value.startsWith("gyroscope:")) {
				int const labelLength = QString("gyroscope:").length();
				QStringList values = value.mid(labelLength + 1, value.length() - labelLength - 2).split(",");
				data.gyroscope = QVector<int>({ values[0].toInt(), values[1].toInt(), values[2].toInt() });
			}
		}

		emit newData(data);
	} else if (message.startsWith(portsLabel)) {
		QStringList types = message.right(message.length() - portsLabel.length()).split(";");
		QStringList analog;
		QStringList digital;
		QStringList special;

		for (QString const &typeSection : types) {
			if (typeSection.startsWith("analog:")) {
				analog = typeSection.right(typeSection.length() - QString("analog:").length())
						.split(",", QString::SkipEmptyParts);
			} else if (typeSection.startsWith("digital:")) {
				digital = typeSection.right(typeSection.length() - QString("digital:").length())
						.split(",", QString::SkipEmptyParts);
			} else if (typeSection.startsWith("special:")) {
				special = typeSection.right(typeSection.length() - QString("special:").length())
						.split(",", QString::SkipEmptyParts);
			}
		}

		emit portsInfo(analog, digital, special);
	}
}

void Communicator::connect()
{
	if (mSocket.state() == QTcpSocket::ConnectedState || mSocket.state() == QTcpSocket::ConnectingState) {
		return;
	}

	mSocket.connectToHost(mServerAddress, static_cast<quint16>(telemetryServerPort));
	bool const result = mSocket.waitForConnected(5000);
	if (!result) {
		qDebug() << mSocket.errorString();
	}

	mBuffer.clear();
	mExpectedBytes = 0;
}

void Communicator::disconnect()
{
	if (mSocket.state() == QTcpSocket::ConnectedState) {
		mSocket.disconnectFromHost();
		mSocket.waitForDisconnected(3000);
	}
}

void Communicator::send(QString const &data)
{
	if (mSocket.state() != QTcpSocket::ConnectedState) {
		emit error(tr("no connection"));
		return;
	}

	QByteArray dataByteArray = data.toUtf8();
	dataByteArray = QByteArray::number(dataByteArray.size()) + ':' + dataByteArray;
	mSocket.write(dataByteArray);
	if (!mSocket.waitForBytesWritten(3000)) {
		qDebug() << "Unable to send data" << data << "to" << mSocket.peerAddress();
	}
}
