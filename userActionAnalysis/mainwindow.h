#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMap>

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
	void open();
	void addComplexAction(ComplexUserAction *action);
	void openFindDialog(QListWidgetItem *item);
	void findAction(QString const &actionToFind);

private:
	Ui::MainWindow *ui;
	BaseUserActionsParser *mBaseUserActionsParser;
	BaseUserActionList mBaseUserActions;
	ComplexUserActionList mComplexUserActions;
	ComplexActionDialog *mComplexActionDialog;
	QAction *mAddComplexAction;
	FindDialog *mFindDialog;


	void loadFile(const QString &fileName);
	void initComplexAction(ComplexUserAction *complexUserAction, QTreeWidgetItem *item, const int &column);
};
