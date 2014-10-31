#include "mainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QHostAddress const &server, int updateInterval, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, mCommunicator(server)
{
	ui->setupUi(this);
	setWindowTitle(tr("TRIK Telemetry"));

	mUpdateTimer.setInterval(updateInterval);
	QObject::connect(&mUpdateTimer, &QTimer::timeout, &mCommunicator, &Communicator::getNewValues);

	QObject::connect(&mCommunicator, &Communicator::newData, this, &MainWindow::setValues);
	QObject::connect(&mCommunicator, &Communicator::error, this, &MainWindow::reportError);

	QObject::connect(&mCommunicator, &Communicator::portsInfo, this, &MainWindow::configure);
	QObject::connect(this, SIGNAL(configurationFinished()), &mUpdateTimer, SLOT(start()));
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

	for (QString const &encoderPort : values.encoders.keys()) {
		ui->encoders->setNormalized(encoderPort, values.encoders[encoderPort]);
	}

	for (QString const &encoderPort : values.encodersRaw.keys()) {
		ui->encoders->setRaw(encoderPort, values.encodersRaw[encoderPort]);
	}

	ui->sensors3d->setValues("accelerometer", values.accelerometer);
	ui->sensors3d->setValues("gyroscope", values.gyroscope);
}

void MainWindow::reportError(QString const &message)
{
	statusBar()->showMessage(tr("Error: ") + message);
}

void MainWindow::configure(QStringList const &analog, QStringList const &digital, QStringList const &special
		, QStringList const &encoders)
{
	ui->analogSensors->configurePorts(analog);
	ui->digitalSensors->configurePorts(digital);
	ui->specialSensors->configurePorts(special);
	ui->encoders->configurePorts(encoders);

	emit configurationFinished();
}
