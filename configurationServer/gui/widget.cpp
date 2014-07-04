#include "widget.h"
#include "ui_widget.h"

#include "preferencesDialog.h"

#include <QAction>

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
	setWindowTitle("IP: " + server->getIP()
		+ " Adress: " + QString::number(server->getAdress()));
}

void Widget::addNewClient(QString newClient)
{
	ui->widgetListOfNames->addItem("client's IP: " + newClient);
}
