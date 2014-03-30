#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userAction/baseUserAction/baseUserAction.h"
#include "userAction/complexUserAction/complexUserActionParser.h"

#include "propertiesDialog.h"

#include <QtWidgets/QMessageBox>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtWidgets/QFileDialog>
#include <QtGui/QColor>

QStringList const reserveRuleItems = (QStringList() << QString::fromUtf8("Начать группу {")
									  << QString::fromUtf8("} Завершить группу")
									  << QString::fromUtf8("или")
									  << QString::fromUtf8("Начать множество [")
									  << QString::fromUtf8("] Завершить множество"));

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	mBaseUserActionsParser = new BaseUserActionsParser();
	mBaseUserActions = mBaseUserActionsParser->parse();

	for (BaseUserAction *baseUserAction: mBaseUserActions) {
		QString const baseUserActionName = baseUserAction->userActionName();
		QListWidgetItem *item = new QListWidgetItem(baseUserActionName);
		ui->actionListWidget->addItem(item);
	}

	ComplexUserActionParser *complexUserActionParser = new ComplexUserActionParser(mBaseUserActions);
	mComplexUserActions = complexUserActionParser->parse();
	for (ComplexUserAction *complexUserAction: mComplexUserActions) {
		addComplexAction(complexUserAction);
	}

	mScenarios = complexUserActionParser->parseScenarios();
	for (ComplexUserAction *scenario: mScenarios) {
		addScenario(scenario);
	}

	mComplexActionDialog = new ComplexActionDialog(this, mBaseUserActions, mComplexUserActions);
	mComplexActionDialog->setWindowTitle(tr("Complex action dialog"));
	mFindDialog = new FindDialog(this);

	setWindowTitle(tr("User interaction analysis"));

	mAddComplexAction = new QAction(tr("Создать новое действие"), nullptr);
	connect(mAddComplexAction, &QAction::triggered, this, &MainWindow::openComplexActionDialog);
	ui->mainToolBar->addAction(mAddComplexAction);

	mAddScenarioAction = new QAction(tr("Создать новый сценарий"), nullptr);
	connect(mAddScenarioAction, &QAction::triggered, this, &MainWindow::openScenariosDialog);
	ui->mainToolBar->addAction(mAddScenarioAction);

	connect(mComplexActionDialog, &ComplexActionDialog::newComplexActionCreated, this, &MainWindow::addComplexAction);
	connect(mComplexActionDialog, &ComplexActionDialog::newScenarioCreated, this, &MainWindow::addScenario);
	connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
	connect(ui->actionListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::openFindDialog);
	connect(mFindDialog, &FindDialog::actionToFind, this, &MainWindow::findAction);
	connect(ui->complexActionTreeWidget, &QTreeWidget::itemDoubleClicked, this, &MainWindow::findComplexAction);
}

MainWindow::~MainWindow()
{
	delete mFindDialog;
	delete mAddScenarioAction;
	delete mAddComplexAction;
	delete mComplexActionDialog;
	delete mBaseUserActionsParser;
	delete ui;
}

void MainWindow::openComplexActionDialog()
{
	mComplexActionDialog->prepareForComplexAction();
	mComplexActionDialog->show();
}

void MainWindow::openScenariosDialog()
{
	mComplexActionDialog->prepareForScenarios();
	mComplexActionDialog->show();
}

void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this);
	if (!fileName.isEmpty()) {
		loadFile(fileName);
	}
}

void MainWindow::addComplexAction(ComplexUserAction *action)
{
	int const column = 0;
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->complexActionTreeWidget);
	item->setText(column, action->userActionName());
	initComplexAction(action, item, column);
	if (!mComplexUserActions.contains(action)) {
		mComplexUserActions << action;
	}
}

void MainWindow::addScenario(ComplexUserAction *scenario)
{
	int const column = 0;
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->scenarioTreeWidget);
	item->setText(column, scenario->userActionName());
	initComplexAction(scenario, item, column);
	if (!mScenarios.contains(scenario)) {
		mScenarios << scenario;
	}
}

void MainWindow::openFindDialog(QListWidgetItem *item)
{
	mFindDialog->setWindowTitle(item->text());
	mFindDialog->open(mBaseUserActions.baseUserActionByName(item->text()));
	mFindDialog->show();
}

void MainWindow::findAction(const QString &actionToFind)
{
	int allActionCount = 0;
	int rightActionCount = 0;
	QList<QListWidgetItem *> items = ui->ruleListWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
	if (items.isEmpty()) {
		QMessageBox::information(this, QString::fromUtf8("Информация")
										, QString::fromUtf8("Не загружен файл с действиями пользователя")
										, QMessageBox::Ok);
		return;
	}
	for (QListWidgetItem *item: items) {
		item->setBackgroundColor(QColor(255, 255, 255));
	}
	QRegExp regExp(actionToFind);
	qDebug() << actionToFind;
	regExp.setPatternSyntax(QRegExp::Wildcard);
	for (QListWidgetItem *item: items) {
		allActionCount++;
		if (regExp.exactMatch(item->text()) || actionToFind == item->text()) {
			rightActionCount++;
			item->setBackgroundColor(QColor(0, 255, 0, 127));
			ui->ruleListWidget->setCurrentItem(item);
		}
	}
	QString textMessage;
	if (rightActionCount == 0) {
		textMessage = "Совпадений не найдено.";
	}
	else {
		textMessage = "Совпадения обнаружены: " + QString::number(rightActionCount) + " из " + QString::number(allActionCount) + " действий.";
	}
	QMessageBox::information(this, "Результат поиска", textMessage, QMessageBox::Ok);
}

void MainWindow::findComplexAction(QTreeWidgetItem *item)
{
	if (item->parent()) {
		return;
	}
	QList<QListWidgetItem *> items = ui->ruleListWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
	if (items.isEmpty()) {
		QMessageBox::information(this, QString::fromUtf8("Информация")
										, QString::fromUtf8("Не загружен файл с действиями пользователя")
										, QMessageBox::Ok);
		return;
	}

	int const column = 0;
	int allActionCount = 0;
	int rightActionCount = 0;

	QStringList const actionsToFind = mComplexUserActions.complexUserActionByName(item->text(column))->toStringList();
	QStringList userItems;
	for (QListWidgetItem *item: items) {
		userItems.append(item->text());
		allActionCount++;
		item->setBackgroundColor(QColor(255, 255, 255));
	}
	QStringList currentList;
	int startIndex = 0;
	for (int i = 0; i < actionsToFind.length(); ++i) {
		currentList << userItems.at(i);
	}
	int finishIndex = actionsToFind.length() - 1;

	if (matchComplexAction(currentList, actionsToFind)) {
		highlightMatch(startIndex, finishIndex);
		rightActionCount++;
	}

	startIndex++;
	finishIndex++;

	do {
		currentList.removeFirst();
		currentList << userItems.at(finishIndex);

		if (matchComplexAction(currentList, actionsToFind)) {
			highlightMatch(startIndex, finishIndex);
			rightActionCount++;
		}

		startIndex++;
		finishIndex++;
	} while (finishIndex < userItems.length());

	QString textMessage;
	if (rightActionCount == 0) {
		textMessage = "Совпадений не найдено.";
	}
	else {
		textMessage = "Совпадения обнаружены: " + QString::number(rightActionCount) + " из " + QString::number(allActionCount) + " действий.";
	}
	QMessageBox::information(this, "Результат поиска", textMessage, QMessageBox::Ok);
}

void MainWindow::initComplexAction(ComplexUserAction *complexUserAction, QTreeWidgetItem *item, const int &column)
{
	int const currentColumn = column;
	QList<UserAction *> userActions = complexUserAction->userActions();
	for (UserAction *userAction: userActions) {
		BaseUserAction *baseUserAction = dynamic_cast<BaseUserAction *>(userAction);
		if (baseUserAction != nullptr) {
			QTreeWidgetItem *baseActionItem = new QTreeWidgetItem(item);
			QString const userActionName = baseUserAction->userActionName();
			baseActionItem->setText(column, userActionName);
		}
		else {
			ComplexUserAction *newComplexUserAction = dynamic_cast<ComplexUserAction *>(userAction);
			if (newComplexUserAction != nullptr) {
				QTreeWidgetItem *complexActionItem = new QTreeWidgetItem(item);
				complexActionItem->setText(currentColumn, newComplexUserAction->userActionName());
				initComplexAction(newComplexUserAction, complexActionItem, currentColumn);
			}
			else if (reserveRuleItems.contains(userAction->userActionName())) {
				int blue = 100;
				if (userAction->userActionName() == QString::fromUtf8("или")) {
					blue = 255;
				}
				QTreeWidgetItem *redTapeInstructionItem = new QTreeWidgetItem(item);
				redTapeInstructionItem->setText(currentColumn, userAction->userActionName());
				redTapeInstructionItem->setTextColor(currentColumn, QColor(100, 100, blue));
			}
		} 
	}
}

bool MainWindow::matchComplexAction(const QStringList &currentList, const QStringList &ruleList)
{
	if (currentList.length() != ruleList.length()) {
		return false;
	}
	for (int i = 0; i < currentList.length(); ++i) {
		QString actionToFind = ruleList.at(i);
		QRegExp regExp(actionToFind);
		regExp.setPatternSyntax(QRegExp::Wildcard);
		if (!regExp.exactMatch(currentList.at(i))) {
			return false;
		}
	}
	return true;
}

void MainWindow::highlightMatch(int startIndex, int finishIndex)
{
	for (int i = startIndex; i <= finishIndex; ++i) {
		ui->ruleListWidget->item(i)->setBackgroundColor(QColor(0, 255, 0, 127));
	}
	ui->ruleListWidget->setCurrentRow(finishIndex);
}

void MainWindow::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
	QStringList userActionsLog;
	QString userAction;
	do {
		userAction = in.readLine();
		if (!userAction.isEmpty()) {
			userActionsLog << userAction;
		}
	}
	while (!userAction.isNull());
	QList<BaseUserAction *> userActions = mBaseUserActionsParser->parseUserLog(userActionsLog);
	int i = 1;
	for (BaseUserAction *action: userActions) {
		ui->ruleListWidget->addItem(action->actionToString());
		++i;
	}
}
