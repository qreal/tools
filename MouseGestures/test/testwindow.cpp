#include "testwindow.h"
#include "ui_testwindow.h"
#include "multistrokeRecognizers/multistrokeGesturesManagers.h"
#include "multistrokeRecognizers/rectanglegesturesmanager.h"
#include "multistrokeRecognizers/sumMultistrokeGesturesManager.h"
#include "multistrokeRecognizers/nearestposgridgesturesmanager.h"
#include "multistrokeRecognizers/rectangleClassifier.h"
#include "multistrokeRecognizers/mixedgesturesmanager.h"
#include "recognizerInterface.h"
#include "multistrokeRecognizers/adaBoostManager.h"
#include "xmlparser.h"
#include "adopter.h"
#include "testThread.h"
#include <QFileDialog>
#include <QApplication>

//const QString pathToTestFile = "usersGestures.xml";
const QString pathToTrainingFile = "NeuralNetwork/learnGestures/learn_gestures1.xml";
const QString levXYSortAlgorithm = "levenshtein distance square and sorting by XY coordinates";
const QString levDistHullAlgorithm = "levenshtein distance and hull sorting";
const QString sortXYAlgorithm = "one size keys and sorting by XY";
const QString hullSortAlgorithm = "one size keys and hull sorting";
const QString squaresCurvesAlgorithm = "distance between nearest squares";
const QString trainingGesturesManagerAlgorithm = "training algorithm";
const QString sumGesturesRecognizeAlgorithm = "sum positions algorithm";
const QString rectangleGesturesAlgorithm = "rectangle gestures algorithm";
const QString nearestPosGridAlgorithm = "distance grid algorithm";
const QString sumGesturesTrainingAlgorithm = "sum positions training algorithm";
const QString rectangleGesturesTrainingAlgorithm = "rectangle gestures training algorithm";
const QString nearestPosGridTrainingAlgorithm = "distance grid training algorithm";
const QString mixedGridAlgorithm = "combination of rectangle and nesrest squares algorithm";
const QString mixedTrainingAlgorithm = "mixed training algorithm";
const QString adaBoostAlgorithm = "adaboost";

TestWindow::TestWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::TestWindow)
{
	ui->setupUi(this);
	ui->cbAlgorithm->addItem(squaresCurvesAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(trainingGesturesManagerAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(levXYSortAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(levDistHullAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(sortXYAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(hullSortAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(sumGesturesRecognizeAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(rectangleGesturesAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(nearestPosGridAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(sumGesturesTrainingAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(rectangleGesturesTrainingAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(nearestPosGridTrainingAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(mixedGridAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(mixedTrainingAlgorithm,  QVariant());
	ui->cbAlgorithm->addItem("adaboost", QVariant()); //TODO: add constant
	connect(ui->bTest, SIGNAL(clicked()), this, SLOT(test()));
	ui->pbTested->setValue(0);
}

void TestWindow::test()
{
	ui->pbTested->setValue(1);
	RecognizerInterface * gesturesManager = getGesturesManager();
	TestThread * thread = new TestThread(gesturesManager, this);
	connect(thread, SIGNAL(tested(int, int, int)), this, SLOT(printData(int,int,int)));
	ui->pbTested->setValue(5);
	thread->run();
}

void TestWindow::printData(int percent, int all, int recognized)
{
	ui->pbTested->setValue(percent);
	ui->teAll->setText(QString::number(all));
	ui->teRecognized->setText(QString::number(recognized));
	ui->teNotRecognized->setText(QString::number(all - recognized));
}

RecognizerInterface * TestWindow::getGesturesManager()
{
	QString name = ui->cbAlgorithm->currentText();
	if (name == adaBoostAlgorithm) {
		AdaBoostManager * adaBoostManager = new AdaBoostManager();
		train(adaBoostManager);
		return adaBoostManager;
	}
	if (name ==  levXYSortAlgorithm) {
		return new AbstractRecognizer(new LevenshteinXYSortGesturesManager());
	}
	else if (name == levDistHullAlgorithm) {
		return new AbstractRecognizer(new LevenshteinHullGesturesManager());
	}
	else if (name == sortXYAlgorithm) {
		return new AbstractRecognizer(new OneSizeXYSortGesturesManager());
	}
	else if (name == squaresCurvesAlgorithm) {
		return new AbstractRecognizer(new SquaresCurveGesturesManager());
	}
	else if (name == trainingGesturesManagerAlgorithm)
	{
		TrainingGesturesManager<GridClassifier> * trainingGesturesManager
				= new TrainingGesturesManager<GridClassifier>();
		return new AbstractRecognizer(getTrainingGesturesManager(trainingGesturesManager));
	}
	else if (name == sumGesturesRecognizeAlgorithm)
	{
		qDebug() << "try to initialize";
		return new AbstractRecognizer(new SumGesturesManager());
	}
	else if (name == rectangleGesturesAlgorithm) {
		return new AbstractRecognizer(new RectangleGesturesManager());
	}
	else if (name == nearestPosGridAlgorithm) {
		return new AbstractRecognizer(new NearestPosGridGesturesManager());
	}
	else if (name == mixedGridAlgorithm) {
		return new AbstractRecognizer(new MixedGesturesManager());
	}
	else if (name == sumGesturesTrainingAlgorithm)
	{
		TrainingGesturesManager<RectangleClassifier<SumGesturesManager> > * trainingGM =
				new TrainingGesturesManager<RectangleClassifier<SumGesturesManager> >();
		return new AbstractRecognizer(getTrainingGesturesManager(trainingGM));
	}
	else if (name == rectangleGesturesTrainingAlgorithm)
	{
		TrainingGesturesManager<RectangleClassifier<RectangleGesturesManager> > * trainingGM =
				new TrainingGesturesManager<RectangleClassifier<RectangleGesturesManager> >();
		return new AbstractRecognizer(getTrainingGesturesManager(trainingGM));
	}
	else if (name == nearestPosGridTrainingAlgorithm)
	{
		TrainingGesturesManager<RectangleClassifier<NearestPosGridGesturesManager> > * trainingGM =
				new TrainingGesturesManager<RectangleClassifier<NearestPosGridGesturesManager> >();
		return new AbstractRecognizer(getTrainingGesturesManager(trainingGM));
	}
	else if (name == mixedTrainingAlgorithm)
	{
		TrainingGesturesManager<MixedClassifier> * trainingGM =
				new TrainingGesturesManager<MixedClassifier>();
		return new AbstractRecognizer(getTrainingGesturesManager(trainingGM));
	}
	else {
		return new AbstractRecognizer(new OneSizeHullGesturesManager());
	}
}
template <typename T>
		GesturesManager * TestWindow::getTrainingGesturesManager
		(TrainingGesturesManager<T> *const & trainingGesturesManager)
{
	QString trainingFile = QFileDialog::getOpenFileName(this, tr("Open Xml"), "",
														tr("Xml files (*.xml)"));
	QMap<QString, UsersGestures> gestures = XmlParser::parseXml(trainingFile);
	foreach (QString object, gestures.keys())
	{
		UsersGestures paths = gestures[object];
		trainingGesturesManager->learn(object, paths.first);
		foreach (QString path, paths.second)
		{
			QApplication::processEvents();
			qDebug() << "new gesture";
			PathVector gesture = Parser::stringToPath(path);
			//if (!trainingGesturesManager->belong(object, gesture))
			trainingGesturesManager->learn(object, gesture);
		}
	}
	qDebug() << "learnt";
	return trainingGesturesManager;
}


void TestWindow::train(AdaBoostManager *const & trainingGesturesManager)
{
	QString trainingFile = QFileDialog::getOpenFileName(this, tr("Open Xml"), "",
														tr("Xml files (*.xml)"));
	QMap<QString, UsersGestures> gestures = XmlParser::parseXml(trainingFile);
	QList<Entity> trainingSet;
	QList<Entity> idealGestures;
	foreach(QString name, gestures.keys()) {
		Entity ideal;
		ideal.first = name;
		ideal.second = gestures[name].first;
		idealGestures.append(ideal);
		foreach(QString pathStr, gestures[name].second) {
			Parser parser;
			PathVector path = parser.stringToPath(pathStr);
			Entity newElement;
			newElement.first = name;
			newElement.second = path;
			trainingSet.append(newElement);
		}
	}

	trainingGesturesManager->setIdealGestures(idealGestures);
	trainingGesturesManager->learn(trainingSet);
	qDebug() << "learnt";
}

TestWindow::~TestWindow()
{
	delete ui;
}
