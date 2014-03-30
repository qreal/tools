#pragma once

#include <QtWidgets/QDialog>
#include <QListWidgetItem>
#include <QTreeWidgetItem>

#include "userAction/complexUserAction/complexUserActionGenerator.h"
#include "propertiesDialog.h"
#include "complexActionNameDialog.h"
#include "widgetItemProperty/widgetItemCustomPropertyList.h"
#include "userAction/complexUserAction/complexUserActionList.h"
#include "ruleElement.h"

namespace Ui {
class ComplexActionDialog;
}

class ComplexActionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ComplexActionDialog(QWidget *parent = 0
			, BaseUserActionList baseUserActions = BaseUserActionList()
			, ComplexUserActionList complexUserActions = ComplexUserActionList()
			, ComplexUserActionList scenarios = ComplexUserActionList());
	~ComplexActionDialog();

	void prepareForComplexAction();
	void prepareForScenarios();

public slots:
	void addActionToRuleList();
	void deleteActionFromRuleList();
	void openProperties(QTreeWidgetItem *item);
	void updateCustomProperties();
	void openNameDialogComplexAction();
	void openNameDialogScenario();
	void saveComplexAction();
	void addNewComplexAction(ComplexUserAction *action);
	void addNewScenario(ComplexUserAction *scenario);
	void clearBaseListSelection();
	void clearComplexTreeSelection();

	void startGroupInRuleList();
	void finishGroupInRuleList();
	void orInRuleList();

	void startSetInRuleList();
	void finishSetInRuleList();

signals:
	void newComplexActionCreated(ComplexUserAction *complexUserAction);
	void newScenarioCreated(ComplexUserAction *scenario);

private:
	QStringList initComplexActionTreeWidget();
	QStringList initBaseActionListWidget();
	QStringList initScenarioWidget();
	void initComplexAction(ComplexUserAction *complexUserAction, QTreeWidgetItem *item, int const &column);
	void addBaseActionToRuleWidget(QTreeWidgetItem *parent
			, const QString &name
			, const QMap<QString, QString> &disabledProperties
			, int const &repeatCountValue = 1
			, bool const &isKeyActionValue = true
			, Duration const &durationValue = Duration(0, 0)
			, QTreeWidgetItem *topLevelParent = nullptr);
	void addComplexActionToRuleWidget(QTreeWidgetItem *parent, ComplexUserAction *complexUserAction, QTreeWidgetItem *topLevelParent);
	RuleElement *parseRuleTreeItem(QTreeWidgetItem *item);
	void printRuleElements(QList<RuleElement *> ruleElements);
	bool isTopLevelItemInRuleTree(QTreeWidgetItem *item);
	void initButtonsState();
	void openNameDialog(bool isScenario);

	Ui::ComplexActionDialog *ui;

	BaseUserActionList mBaseUserActions;
	ComplexUserActionList mComplexUserActions;
	ComplexUserActionList mScenarios;

	PropertiesDialog *mPropertiesDialog;
	ComplexActionNameDialog *mComplexActionNameDialog;
	WidgetItemCustomPropertyList mWidgetItemCustomPropertyList;
	QTreeWidgetItem *mOpenedRuleItem;
	ComplexUserActionGenerator *mComplexUserActionGenerator;

	QMap<QTreeWidgetItem *, QMap<QString, QString>> mDisabledProperties;
};
