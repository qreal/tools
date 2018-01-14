#pragma once
#include "server/server.h"

#include <QWidget>

namespace Ui {
class Widget;
}

/// Class of window configuration server.
class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

	/// Initialize widget.
	void init();

private slots:
	/// Slot of connect new client.
	void addNewClient(QString const &newClient);

	/// Slot of delete client.
	void deleteClient(QString const &clientsIP);

private:
	Ui::Widget *mUi;
	Server *mServer;
};

