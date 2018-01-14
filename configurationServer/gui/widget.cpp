#include "widget.h"
#include "ui_widget.h"

#include "preferencesDialog.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	mUi(new Ui::Widget)
{
	mUi->setupUi(this);
}

Widget::~Widget()
{
	delete mUi;
}

void Widget::init()
{
	mServer = new Server;
	PreferencesDialog * dialog = new PreferencesDialog();
	dialog->init(new QAction(dialog), new QAction(dialog), new QAction(dialog), new QAction(dialog));

	mUi->widgetSettings->layout()->addWidget(dialog);
	dialog->setParent(mUi->widgetSettings);

	connect(mServer, SIGNAL(newClient(QString)), this, SLOT(addNewClient(QString)));
	connect(mServer, SIGNAL(clientDisconnected(QString)), this, SLOT(deleteClient(QString)));

	setWindowTitle("Port: " + QString::number(mServer->getPort()));

	QString allIP = mServer->getIP();
	for(int i = 0; i < allIP.count("\n"); i++) {
		QString temp = allIP;
		mUi->widgetListOfIP->addItem(temp.remove(temp.indexOf('\n'), temp.length() - temp.indexOf('\n')));
		allIP = allIP.remove(0, allIP.indexOf('\n') + 1);
	}

	mUi->widgetListOfIP->addItem(allIP.remove(allIP.length() - 1, 1));
}

void Widget::addNewClient(const QString &newClient)
{
	mUi->widgetListOfNames->addItem(newClient);
}

void Widget::deleteClient(const QString &clientsIP)
{
	for (int i = 0; i < mUi->widgetListOfNames->count(); i++) {
		if (mUi->widgetListOfNames->item(i)->text() == clientsIP) {
			delete mUi->widgetListOfNames->item(i);
			return;
		}
	}
}
