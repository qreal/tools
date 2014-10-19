#include "communicator.h"

#include <QtCore/QFileInfo>

static uint const telemetryServerPort = 9000;

QString const errorMarker = "error: ";
QString const infoMarker = "info: ";

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
	if (mSocket.state() != QTcpSocket::ConnectedState) {
		emit newMessage("error");
		return;
	}

	send("everything");
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
	emit newMessage(message);
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
	QByteArray dataByteArray = data.toUtf8();
	dataByteArray = QByteArray::number(dataByteArray.size()) + ':' + dataByteArray;
	mSocket.write(dataByteArray);
	if (!mSocket.waitForBytesWritten(3000)) {
		qDebug() << "Unable to send data" << data << "to" << mSocket.peerAddress();
	}
}
