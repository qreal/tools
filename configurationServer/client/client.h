#include <QDialog>
#include <QtNetwork>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>

class Client : public QDialog
{
	Q_OBJECT

public:
	explicit Client(QWidget *parent = 0);

private slots:
	void sessionOpened();
	void displayError(QAbstractSocket::SocketError socketError);

	/// sends message
	void sendMessage();

	/// receives message
	void receiveMessage();

	void connectToServer();
	void disconnectedFromServer();

private:
	/// buttons:
	QPushButton *quitButton;
	QPushButton *sendButton;
	QPushButton *connectButton;

	/// labels:
	QLabel *hostLabel;
	QLabel *portLabel;

	/// combo box:
	QComboBox *hostAdress;

	/// text widgets:
	QLineEdit *portLineEdit;
	QTextEdit *chatText;
	QLineEdit *messageText;


	QTcpSocket *serverSocket;
	QNetworkSession *networkSession;
	quint16 blockSize;
};
