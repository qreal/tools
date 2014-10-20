#include "mainWindow.h"
#include "ui_mainwindow.h"
#include "sensorsValue.h"

MainWindow::MainWindow(QHostAddress const &server, int updateInterval, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, mCommunicator(server)
{
	ui->setupUi(this);
	setWindowTitle(tr("TRIK Telemetry"));

	mUpdateTimer.setInterval(updateInterval);
	connect(&mUpdateTimer, SIGNAL(timeout()), &mCommunicator, SLOT(getNewValues()));

	connect(&mCommunicator, SIGNAL(newData(SensorData)), this, SLOT(setValues(SensorData)));
	connect(&mCommunicator, SIGNAL(error(QString)), this, SLOT(reportError(QString)));

	connect(&mCommunicator, SIGNAL(portsInfo(QStringList,QStringList,QStringList))
			, this, SLOT(configure(QStringList,QStringList,QStringList)));
	connect(this, SIGNAL(configurationFinished()), &mUpdateTimer, SLOT(start()));
	mCommunicator.getPortsInfo();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setValues(SensorData const &values)
{
	for (QString const &analogPort : values.analog.keys()) {
		ui->analogSensors->setNormalized(analogPort, values.analog[analogPort]);
	}

	for (QString const &analogPort : values.analogRaw.keys()) {
		ui->analogSensors->setRaw(analogPort, values.analogRaw[analogPort]);
	}

	for (QString const &digitalPort : values.digital.keys()) {
		ui->digitalSensors->setNormalized(digitalPort, values.digital[digitalPort]);
	}

	for (QString const &digitalPort : values.digitalRaw.keys()) {
		ui->digitalSensors->setRaw(digitalPort, values.digitalRaw[digitalPort]);
	}

	for (QString const &specialPort : values.special.keys()) {
		ui->specialSensors->setNormalized(specialPort, values.special[specialPort]);
	}

	for (QString const &specialPort : values.specialRaw.keys()) {
		ui->specialSensors->setRaw(specialPort, values.specialRaw[specialPort]);
	}

	ui->sensors3d->item(0, 1)->setText(QString::number(values.accelerometer[0]));
	ui->sensors3d->item(1, 1)->setText(QString::number(values.accelerometer[1]));
	ui->sensors3d->item(2, 1)->setText(QString::number(values.accelerometer[2]));

	ui->sensors3d->item(3, 1)->setText(QString::number(values.gyroscope[0]));
	ui->sensors3d->item(4, 1)->setText(QString::number(values.gyroscope[1]));
	ui->sensors3d->item(5, 1)->setText(QString::number(values.gyroscope[2]));
}

void MainWindow::reportError(QString const &message)
{
	statusBar()->showMessage(tr("Error: ") + message);
}

void MainWindow::configure(QStringList const &analog, QStringList const &digital, QStringList const &special)
{
	for (QString const &analogPort : analog) {
		ui->analogSensors->addPort(analogPort);
	}

	for (QString const &digitalPort : digital) {
		ui->digitalSensors->addPort(digitalPort);
	}

	for (QString const &specialPort : special) {
		ui->specialSensors->addPort(specialPort);
	}

	init3dSensorsWidget();

	emit configurationFinished();
}

void MainWindow::init3dSensorsWidget()
{
	ui->sensors3d->setColumnCount(2);
	ui->sensors3d->setRowCount(6);
	ui->sensors3d->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Port")));
	ui->sensors3d->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Value")));
	ui->sensors3d->verticalHeader()->setVisible(false);
	ui->sensors3d->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->sensors3d->setColumnWidth(1, 80);
	for (int row = 0; row < 6; ++row) {
		ui->sensors3d->setRowHeight(row, 20);
	}

	ui->sensors3d->setItem(0, 0, new QTableWidgetItem(tr("AccelerometerX")));
	ui->sensors3d->setItem(1, 0, new QTableWidgetItem(tr("AccelerometerY")));
	ui->sensors3d->setItem(2, 0, new QTableWidgetItem(tr("AccelerometerZ")));

	ui->sensors3d->setItem(0, 1, new QTableWidgetItem(tr("N/A")));
	ui->sensors3d->setItem(1, 1, new QTableWidgetItem(tr("N/A")));
	ui->sensors3d->setItem(2, 1, new QTableWidgetItem(tr("N/A")));

	ui->sensors3d->setItem(3, 0, new QTableWidgetItem(tr("GyroscopeX")));
	ui->sensors3d->setItem(4, 0, new QTableWidgetItem(tr("GyroscopeY")));
	ui->sensors3d->setItem(5, 0, new QTableWidgetItem(tr("GyroscopeZ")));

	ui->sensors3d->setItem(3, 1, new QTableWidgetItem(tr("N/A")));
	ui->sensors3d->setItem(4, 1, new QTableWidgetItem(tr("N/A")));
	ui->sensors3d->setItem(5, 1, new QTableWidgetItem(tr("N/A")));
}
