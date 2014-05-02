#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMap>

#include <RInside.h>

#include "complexActionNameDialog.h"
#include "userAction/complexUserAction/complexUserActionGenerator.h"
#include "userAction/baseUserAction/baseUserActionsParser.h"
#include "propertiesDialog.h"
#include "complexActionDialog.h"
#include "findDialog.h"

#include "userAction/baseUserAction/baseUserActionList.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void openComplexActionDialog();
	void openScenariosDialog();
	void open();
	void addComplexAction(ComplexUserAction *action);
	void addScenario(ComplexUserAction *scenario);
	void openFindDialog(QListWidgetItem *item);
	void findAction(QString const &actionToFind);
	void findComplexAction(QTreeWidgetItem *item);

private:
	Ui::MainWindow *ui;
	BaseUserActionsParser *mBaseUserActionsParser;
	BaseUserActionList mBaseUserActions;
	ComplexUserActionList mComplexUserActions;
	ComplexUserActionList mScenarios;
	ComplexActionDialog *mComplexActionDialog;
	QAction *mAddComplexAction;
	QAction *mAddScenarioAction;
	FindDialog *mFindDialog;
	QString mWhereToFind;


	void loadFile(const QString &fileName);
	void initComplexAction(ComplexUserAction *complexUserAction, QTreeWidgetItem *item, const int &column);
	bool matchComplexAction(QStringList const &currentList, QStringList const &ruleList);
	void highlightMatch(int startIndex, int finishIndex);
};
