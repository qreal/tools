#pragma once

#include <QMainWindow>
#include "abstractRecognizer.h"
#include "NeuralNetwork/neuralNetwork.h"
#include "multistrokeRecognizers/adaBoostManager.h"

namespace Ui {
	class TestWindow;
}

class TestWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit TestWindow(QWidget *parent = 0);
	~TestWindow();

private:
	Ui::TestWindow *ui;
	RecognizerInterface * getGesturesManager();
	template <typename T>
			GesturesManager * getTrainingGesturesManager(TrainingGesturesManager<T> * const &trainingGM);
	void train(AdaBoostManager *const & trainingGesturesManager);

private slots:
	void test();
	void printData(int, int, int);
};

