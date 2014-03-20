#include "complexActionDialog.h"
#include "ui_complexActionDialog.h"

#include "userAction/complexUserAction/complexUserActionGenerator.h"
#include "propertiesDialog.h"

#include <QMessageBox>
#include <QtCore/QDebug>

ComplexActionDialog::ComplexActionDialog(QWidget *parent, BaseUserActionList baseUserActions, QList<ComplexUserAction *> complexUserActions) :
	QDialog(parent)
	, ui(new Ui::ComplexActionDialog)
	, mBaseUserActions(baseUserActions)
	, mComplexUserActions(complexUserActions)
{
	ui->setupUi(this);
	mPropertiesDialog = new PropertiesDialog();
	mComplexActionNameDialog = new ComplexActionNameDialog();
	mOpenedRuleItem = new QTreeWidgetItem();
	QStringList reservedNames;

	reservedNames << initBaseActionListWidget();
	reservedNames << initComplexActionTreeWidget();

	mComplexActionNameDialog->initReservedNames(reservedNames);
	mComplexUserActionGenerator = new ComplexUserActionGenerator(mBaseUserActions);

	connect(ui->addPushButton, &QPushButton::clicked, this, &ComplexActionDialog::addActionToRuleList);
	connect(ui->baseActionListWidget, &QListWidget::itemDoubleClicked, this, &ComplexActionDialog::addActionToRuleList);
	connect(ui->deletePushButton, &QPushButton::clicked, this, &ComplexActionDialog::deleteActionFromRuleList);
	connect(ui->ruleTreeWidget, &QTreeWidget::itemDoubleClicked, this, &ComplexActionDialog::openProperties);
	connect(mPropertiesDialog, &QDialog::accepted, this, &ComplexActionDialog::updateCustomProperties);
	connect(ui->savePushButton, &QPushButton::clicked, this, &ComplexActionDialog::openNameDialogComplexAction);
	connect(mComplexActionNameDialog, &ComplexActionNameDialog::accepted, this, &ComplexActionDialog::saveComplexAction);
	connect(mComplexUserActionGenerator, &ComplexUserActionGenerator::newComplexActionCreated, this, &ComplexActionDialog::addNewComplexAction);
}

QStringList ComplexActionDialog::initBaseActionListWidget()
{
	QStringList reservedNames;
	for (BaseUserAction *baseUserAction: mBaseUserActions) {
		QString const baseUserActionName = baseUserAction->userActionName();
		reservedNames << baseUserActionName;
		QListWidgetItem *item = new QListWidgetItem(baseUserActionName);
		ui->baseActionListWidget->addItem(item);
	}
	return reservedNames;
}

QStringList ComplexActionDialog::initComplexActionTreeWidget()
{
	QStringList reservedNames;
	for (ComplexUserAction *complexUserAction: mComplexUserActions) {
		QString const complexUserActionName = complexUserAction->userActionName();
		reservedNames << complexUserActionName;
		QTreeWidgetItem *item = new QTreeWidgetItem(ui->complexActionTreeWidget);
		int column = 0;
		item->setText(column, complexUserActionName);
		initComplexAction(complexUserAction, item, column);
	}
	return reservedNames;
}

void ComplexActionDialog::addActionToRuleList()
{
	// add base action, if some of them selected
	QList<QListWidgetItem *> selectedItems = ui->baseActionListWidget->selectedItems();
	for (QListWidgetItem * selectedItem: selectedItems) {
		QTreeWidgetItem *ruleItem = new QTreeWidgetItem(ui->ruleTreeWidget);
		if (ruleItem) {
			QString const name = selectedItem->text();
			QMap<QString, QString> mapProperties;
			QMap<QString, QStringList> properties = mBaseUserActions.propertiesByBaseUserActionName(name);

			QMap<QString, QStringList>::const_iterator i = properties.constBegin();
			QString ruleProperties = " — ";
			while (i != properties.constEnd()) {
				QStringList const values = i.value();
				QString const value = (!values.isEmpty()) ? values.at(0) : "";
				mapProperties.insert(i.key(), value);
				ruleProperties += i.key() + ": " + value + "|";
				++i;
			}
			mWidgetItemCustomPropertyList.append(new WidgetItemCustomProperty(ruleItem, ruleItem, mapProperties));
			int column = 0;
			ruleItem->setText(column, name + ruleProperties);
		}
	}
	ui->baseActionListWidget->clearSelection();

}

void ComplexActionDialog::deleteActionFromRuleList()
{
	QList<QTreeWidgetItem *> selectedItems = ui->ruleTreeWidget->selectedItems();
	ui->ruleTreeWidget->clearSelection();
	for (QTreeWidgetItem * selectedItem: selectedItems) {
		if (!selectedItem->parent()) {
			mWidgetItemCustomPropertyList.removePropertiesWithParent(selectedItem);
			delete selectedItem;
		}
	}
}

void ComplexActionDialog::openProperties(QTreeWidgetItem *item)
{
	mOpenedRuleItem = item;
	int column = 0;
	QString itemName = item->text(column).section(" — ", 0, 0);
	mPropertiesDialog->setWindowTitle(itemName);
	QMap<QString, QStringList> const map = mBaseUserActions.propertiesByBaseUserActionName(itemName);
	if (map.isEmpty()) {
		return;
	}
	mPropertiesDialog->setLabelsAndProperties(map, mWidgetItemCustomPropertyList.customPropertiesByItem(item));
	mPropertiesDialog->show();
}

void ComplexActionDialog::updateCustomProperties()
{
	QMap<QString, QString> const customProperties = mPropertiesDialog->conProperties();
	QMap<QString, QString>::const_iterator i = customProperties.constBegin();
	QString ruleProperties = " — ";
	int column = 0;
	QString itemName = mOpenedRuleItem->text(column).section(" — ", 0, 0);
	while (i != customProperties.constEnd()) {
		ruleProperties += i.key() + ": " + i.value() + "|";
		++i;
	}
	mOpenedRuleItem->setText(column, itemName + ruleProperties);
	mWidgetItemCustomPropertyList.replaceProperties(mOpenedRuleItem, customProperties);
}

void ComplexActionDialog::openNameDialogComplexAction()
{
	QList<QTreeWidgetItem *> items = ui->ruleTreeWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
	if (items.isEmpty()) {
		QMessageBox::information(this, QString::fromUtf8("Информация")
										, QString::fromUtf8("Составное действие не содержит ни одного действия.")
										, QMessageBox::Ok);
		return;
	}
	mComplexActionNameDialog->openDialog();
}

void ComplexActionDialog::saveComplexAction()
{
	QList<QTreeWidgetItem *> items = ui->ruleTreeWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
	if (items.isEmpty()) {
		return;
	}
	QStringList ruleList;
	int column = 0;
	for (QTreeWidgetItem *item: items) {
		ruleList.append(item->text(column));
	}
	mComplexUserActionGenerator->generateComplexAction(mComplexActionNameDialog->complexActionName(), ruleList);
}

void ComplexActionDialog::addNewComplexAction(ComplexUserAction *action)
{
	int const column = 0;
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->complexActionTreeWidget);
	item->setText(column, action->userActionName());
	initComplexAction(action, item, column);
	mComplexActionNameDialog->addReservedName(action->userActionName());
	mComplexUserActions << action;
	emit newComplexActionCreated(action);
}

void ComplexActionDialog::initComplexAction(ComplexUserAction *complexUserAction, QTreeWidgetItem *item, const int &column)
{
	int const currentColumn = column + 1;
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
		}
	}
}

ComplexActionDialog::~ComplexActionDialog()
{
	delete mComplexUserActionGenerator;
	delete mOpenedRuleItem;
	delete mComplexActionNameDialog;
	delete mPropertiesDialog;
	delete ui;
}
