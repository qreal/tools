#pragma once

#include <QtCore/QTimer>
#include <QtWidgets/QMainWindow>

#include "communicator.h"

namespace Ui {
class MainWindow;
}

/// MainWindow class coordinates a work of robot communicator and widgets that show current sensors data.
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/// Configures sensors widgets with current robot's ports info, starts update timer.
	explicit MainWindow(QHostAddress const &server, int updateInterval, QWidget *parent = 0);
	~MainWindow();

public slots:
	void setValues(SensorData const &values);
	void reportError(QString const &message);
	void configure(QStringList const &analog, QStringList const &digital, QStringList const &special
			, QStringList const &encoders);

signals:
	void configurationFinished();

private:
	void init3dSensorsWidget();

	Ui::MainWindow *ui;

	Communicator mCommunicator;
	QTimer mUpdateTimer;
};
