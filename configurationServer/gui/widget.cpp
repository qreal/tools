#include "widget.h"
#include "ui_widget.h"

#include "preferencesDialog.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::init()
{
	server = new Server;
	PreferencesDialog * dialog = new PreferencesDialog();
	dialog->init(new QAction(dialog), new QAction(dialog), new QAction(dialog), new QAction(dialog));
	ui->widgetSettings->layout()->addWidget(dialog);
	dialog->setParent(ui->widgetSettings);
	connect(server, SIGNAL(newClient(QString)), this, SLOT(addNewClient(QString)));
	connect(server, SIGNAL(clientDisconnectedSignal(QString)), this, SLOT(deleteClient(QString)));
	setWindowTitle(" Adress: " + QString::number(server->getAdress()));
	ui->widgetListOfIP->setText(server->getIP());
}

void Widget::addNewClient(QString newClient)
{
	ui->widgetListOfNames->addItem(newClient);
}

void Widget::deleteClient(QString clientsIP)
{
	for (int i = 0; i < ui->widgetListOfNames->count(); i++)
		if (ui->widgetListOfNames->item(i)->text() == clientsIP)
		{
			delete ui->widgetListOfNames->item(i);
			return;
		}
}
