#include "mainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QHostAddress const &server, int updateInterval, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, mCommunicator(server)
{
	ui->setupUi(this);
	connect(&mUpdateTimer, SIGNAL(timeout()), this, SLOT(updateValues()));
	connect(&mCommunicator, SIGNAL(newMessage(QString)), this, SLOT(setValues(QString)));
	mUpdateTimer.start(updateInterval);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updateValues()
{
	mCommunicator.getNewValues();
}

void MainWindow::setValues(const QString &values)
{
	ui->values->setText(values);
}
