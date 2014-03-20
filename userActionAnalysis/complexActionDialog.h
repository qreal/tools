#pragma once

#include <QtWidgets/QDialog>
#include <QListWidgetItem>
#include <QTreeWidgetItem>

#include "userAction/complexUserAction/complexUserActionGenerator.h"
#include "propertiesDialog.h"
#include "complexActionNameDialog.h"
#include "widgetItemProperty/widgetItemCustomPropertyList.h"

namespace Ui {
class ComplexActionDialog;
}

class ComplexActionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ComplexActionDialog(QWidget *parent = 0
			, BaseUserActionList baseUserActions = BaseUserActionList()
			, QList<ComplexUserAction *> complexUserActions = QList<ComplexUserAction *>());
	~ComplexActionDialog();

	QStringList initComplexActionTreeWidget();
public slots:
	void addActionToRuleList();
	void deleteActionFromRuleList();
	void openProperties(QTreeWidgetItem *item);
	void updateCustomProperties();
	void openNameDialogComplexAction();
	void saveComplexAction();
	void addNewComplexAction(ComplexUserAction *action);

signals:
	void newComplexActionCreated(ComplexUserAction *complexUserAction);

private:
	QStringList initBaseActionListWidget();
	void initComplexAction(ComplexUserAction *complexUserAction, QTreeWidgetItem *item, int const &column);

	Ui::ComplexActionDialog *ui;

	BaseUserActionList mBaseUserActions;
	QList<ComplexUserAction *> mComplexUserActions;

	PropertiesDialog *mPropertiesDialog;
	ComplexActionNameDialog *mComplexActionNameDialog;
	WidgetItemCustomPropertyList mWidgetItemCustomPropertyList;
	QTreeWidgetItem *mOpenedRuleItem;
	ComplexUserActionGenerator *mComplexUserActionGenerator;
};
