#include "complexActionDialog.h"
#include "ui_complexActionDialog.h"

#include "userAction/complexUserAction/complexUserActionGenerator.h"
#include "propertiesDialog.h"

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

ComplexActionDialog::ComplexActionDialog(QWidget *parent, BaseUserActionList baseUserActions, ComplexUserActionList complexUserActions) :
	QDialog(parent)
	, ui(new Ui::ComplexActionDialog)
	, mBaseUserActions(baseUserActions)
	, mComplexUserActions(complexUserActions)
{
	ui->setupUi(this);

	initButtonsState();
	mPropertiesDialog = new PropertiesDialog(this);
	mPropertiesDialog->move(this->geometry().center() - mPropertiesDialog->geometry().center());

	mComplexActionNameDialog = new ComplexActionNameDialog();
	mOpenedRuleItem = new QTreeWidgetItem();
	QStringList reservedNames;

	reservedNames << initBaseActionListWidget();
	reservedNames << initComplexActionTreeWidget();

	mComplexActionNameDialog->initReservedNames(reservedNames);
	mComplexUserActionGenerator = new ComplexUserActionGenerator(mBaseUserActions, mComplexUserActions);

	connect(ui->addPushButton, &QPushButton::clicked, this, &ComplexActionDialog::addActionToRuleList);
	connect(ui->baseActionListWidget, &QListWidget::itemDoubleClicked, this, &ComplexActionDialog::addActionToRuleList);
	connect(ui->deletePushButton, &QPushButton::clicked, this, &ComplexActionDialog::deleteActionFromRuleList);
	connect(ui->ruleTreeWidget, &QTreeWidget::itemDoubleClicked, this, &ComplexActionDialog::openProperties);
	connect(mPropertiesDialog, &QDialog::accepted, this, &ComplexActionDialog::updateCustomProperties);
	connect(ui->savePushButton, &QPushButton::clicked, this, &ComplexActionDialog::openNameDialogComplexAction);
	connect(mComplexActionNameDialog, &ComplexActionNameDialog::accepted, this, &ComplexActionDialog::saveComplexAction);
	connect(mComplexUserActionGenerator, &ComplexUserActionGenerator::newComplexActionCreated, this, &ComplexActionDialog::addNewComplexAction);
	connect(ui->complexActionTreeWidget, &QTreeWidget::itemClicked, this, &ComplexActionDialog::clearBaseListSelection);
	connect(ui->baseActionListWidget, &QListWidget::itemClicked, this, &ComplexActionDialog::clearComplexTreeSelection);

	connect(ui->startGroupPushButton, &QPushButton::clicked, this, &ComplexActionDialog::startGroupInRuleList);
	connect(ui->finishGroupPushButton, &QPushButton::clicked, this, &ComplexActionDialog::finishGroupInRuleList);
	connect(ui->orPushButton, &QPushButton::clicked, this, &ComplexActionDialog::orInRuleList);

	connect(ui->startSetPushButton, &QPushButton::clicked, this, &ComplexActionDialog::startSetInRuleList);
	connect(ui->finishSetPushButton, &QPushButton::clicked, this, &ComplexActionDialog::finishSetInRuleList);
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
	for (QListWidgetItem *selectedItem: selectedItems) {
		addBaseActionToRuleWidget(nullptr, selectedItem->text(), QMap<QString, QString>());
	}
	ui->baseActionListWidget->clearSelection();
	// add complex action, if some of them selected
	QList<QTreeWidgetItem *> selectedTreeItems = ui->complexActionTreeWidget->selectedItems();
	for (QTreeWidgetItem *selectedTreeItem: selectedTreeItems) {
		if (selectedTreeItem->parent()) {
			continue;
		}
		int column = 0;
		addComplexActionToRuleWidget(nullptr, mComplexUserActions.complexUserActionByName(selectedTreeItem->text(column)), nullptr);
	}
	ui->complexActionTreeWidget->clearSelection();
}

void ComplexActionDialog::deleteActionFromRuleList()
{
	QList<QTreeWidgetItem *> selectedItems = ui->ruleTreeWidget->selectedItems();
	ui->ruleTreeWidget->clearSelection();
	for (QTreeWidgetItem * selectedItem: selectedItems) {
		if (!selectedItem->parent()) {
			if (mOpenedRuleItem == selectedItem) {
				mOpenedRuleItem = nullptr;
			}
			mWidgetItemCustomPropertyList.removePropertiesWithParent(selectedItem);
			delete selectedItem;
		}
	}
}

void ComplexActionDialog::openProperties(QTreeWidgetItem *item)
{
	mOpenedRuleItem = item;
	int column = 0;
	bool isTopLevelItem = isTopLevelItemInRuleTree(item);
	bool isComplexAction = false;
	QString itemName = item->text(column).section(" — ", 0, 0);
	mPropertiesDialog->setWindowTitle(itemName);
	QMap<QString, QStringList> const map = mBaseUserActions.propertiesByBaseUserActionName(itemName);
	isComplexAction = map.isEmpty();

	mPropertiesDialog->setLabelsAndProperties(map, mWidgetItemCustomPropertyList.customPropertiesByItem(item)
			, mWidgetItemCustomPropertyList.repeatCountByItem(item)
			, mWidgetItemCustomPropertyList.isKeyActionByItem(item)
			, mWidgetItemCustomPropertyList.durationByItem(item)
			, mDisabledProperties.value(mOpenedRuleItem).keys()
			, isTopLevelItem
			, isComplexAction);

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
	if (ruleProperties == " — ") {
		ruleProperties = "";
	}
	mOpenedRuleItem->setText(column, itemName + ruleProperties);
	mWidgetItemCustomPropertyList.replaceProperties(mOpenedRuleItem, customProperties);
	mWidgetItemCustomPropertyList.updateOtherProperties(mOpenedRuleItem
			, mPropertiesDialog->repeatCount()
			, mPropertiesDialog->isKeyAction()
			, *(mPropertiesDialog->duration()));
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

	QList<RuleElement *> ruleElements;
	int column = 0;
	for (int i = 0; i < ui->ruleTreeWidget->topLevelItemCount(); ++i) {
		QTreeWidgetItem *item = ui->ruleTreeWidget->topLevelItem(i);
		if (item->childCount() > 0) {
			ruleElements.append(parseRuleTreeItem(item));
		}
		else {
			ruleElements.append(new RuleElement(item->text(column), QList<RuleElement *>()
					, mWidgetItemCustomPropertyList.repeatCountByItem(item)
					, mWidgetItemCustomPropertyList.isKeyActionByItem(item)
					, mWidgetItemCustomPropertyList.durationByItem(item)));
		}
	}
	//printRuleElements(ruleElements);
	mComplexUserActionGenerator->generateComplexAction(mComplexActionNameDialog->complexActionName(), ruleElements);
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

void ComplexActionDialog::clearBaseListSelection()
{
	ui->baseActionListWidget->clearSelection();
	ui->ruleTreeWidget->clearSelection();
}

void ComplexActionDialog::clearComplexTreeSelection()
{
	ui->complexActionTreeWidget->clearSelection();
	ui->ruleTreeWidget->clearSelection();
}

void ComplexActionDialog::startGroupInRuleList()
{
	int const column = 0;
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->ruleTreeWidget);
	item->setText(column, QString::fromUtf8("Начать группу {"));
	item->setTextColor(column, QColor(100, 100, 100));

	ui->finishGroupPushButton->setEnabled(true);
}

void ComplexActionDialog::finishGroupInRuleList()
{
	int const column = 0;
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->ruleTreeWidget);
	item->setText(column, QString::fromUtf8("} Завершить группу"));
	item->setTextColor(column, QColor(100, 100, 100));
}

void ComplexActionDialog::orInRuleList()
{
	int const column = 0;
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->ruleTreeWidget);
	item->setText(column, QString::fromUtf8("или"));
	item->setTextColor(column, QColor(100, 100, 255));
}

void ComplexActionDialog::startSetInRuleList()
{
	int const column = 0;
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->ruleTreeWidget);
	item->setText(column, QString::fromUtf8("Начать множество ["));
	item->setTextColor(column, QColor(100, 100, 100));

	ui->finishSetPushButton->setEnabled(true);
}

void ComplexActionDialog::finishSetInRuleList()
{
	int const column = 0;
	QTreeWidgetItem *item = new QTreeWidgetItem(ui->ruleTreeWidget);
	item->setText(column, QString::fromUtf8("] Завершить множество"));
	item->setTextColor(column, QColor(100, 100, 100));
}

void ComplexActionDialog::initComplexAction(ComplexUserAction *complexUserAction, QTreeWidgetItem *item, const int &column)
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
		}
	}
}

void ComplexActionDialog::addComplexActionToRuleWidget(QTreeWidgetItem *parent, ComplexUserAction *complexUserAction, QTreeWidgetItem *topLevelParent)
{
	QTreeWidgetItem *ruleItem = nullptr;
	if (parent == nullptr) {
		ruleItem = new QTreeWidgetItem(ui->ruleTreeWidget);
	} else {
		ruleItem = new QTreeWidgetItem(parent);
	}
	if (ruleItem) {
		QTreeWidgetItem *topLevelParentItem = new QTreeWidgetItem();
		if (topLevelParent == nullptr) {
			topLevelParentItem = ruleItem;
		}
		else {
			topLevelParentItem = topLevelParent;
		}
		int column = 0;
		ruleItem->setText(column, complexUserAction->userActionName());
		for (UserAction *userAction: complexUserAction->userActions()) {
			ComplexUserAction *complexAction = dynamic_cast<ComplexUserAction *>(userAction);
			if (complexAction) {
				addComplexActionToRuleWidget(ruleItem, complexAction, topLevelParentItem);
			}
			else {
				BaseUserAction *baseAction = dynamic_cast<BaseUserAction *>(userAction);
				if (baseAction) {
					addBaseActionToRuleWidget(ruleItem, baseAction->userActionName(),
							baseAction->customActionProperties()
							, baseAction->repeatCount()
							, baseAction->isKeyAction()
							, *(baseAction->duration())
							, topLevelParentItem);
				}
			}
		}
		mWidgetItemCustomPropertyList.append(new WidgetItemCustomProperty(topLevelParentItem
				, ruleItem
				, QMap<QString, QString>()
				, complexUserAction->repeatCount()
				, complexUserAction->isKeyAction()
				, *(complexUserAction->duration())));
		mDisabledProperties.insert(ruleItem, QMap<QString, QString>());
	}
}

RuleElement *ComplexActionDialog::parseRuleTreeItem(QTreeWidgetItem *item)
{
	int column = 0;
	RuleElement *ruleElement = new RuleElement(item->text(column), QList<RuleElement *>()
			, mWidgetItemCustomPropertyList.repeatCountByItem(item)
			, mWidgetItemCustomPropertyList.isKeyActionByItem(item)
			, mWidgetItemCustomPropertyList.durationByItem(item));
	for (int i = 0; i < item->childCount(); ++i) {
		ruleElement->addElementToList(parseRuleTreeItem(item->child(i)));
	}
	return ruleElement;
}

void ComplexActionDialog::printRuleElements(QList<RuleElement *> ruleElements)
{
	for (RuleElement *element: ruleElements) {
		qDebug() << element->content() << element->repeatCount() << element->isKeyAction();
		qDebug() << element->duration()->from() << element->duration()->to();
		printRuleElements(element->list());
	}
}

bool ComplexActionDialog::isTopLevelItemInRuleTree(QTreeWidgetItem *item)
{
	for (int i = 0; i < ui->ruleTreeWidget->topLevelItemCount(); ++i) {
		if (item == ui->ruleTreeWidget->topLevelItem(i)) {
			return true;
		}
	}
	return false;
}

void ComplexActionDialog::initButtonsState()
{
	ui->startGroupPushButton->setEnabled(true);
	ui->startSetPushButton->setEnabled(true);
	ui->orPushButton->setEnabled(true);

	ui->finishGroupPushButton->setEnabled(false);
	ui->finishSetPushButton->setEnabled(false);
}

void ComplexActionDialog::addBaseActionToRuleWidget(QTreeWidgetItem *parent
		, QString const &name, QMap<QString, QString> const &disabledProperties
		, const int &repeatCountValue
		, const bool &isKeyActionValue
		, const Duration &durationValue
		, QTreeWidgetItem *topLevelParent
		)
{
	QTreeWidgetItem *ruleItem = nullptr;
	if (parent == nullptr) {
		ruleItem = new QTreeWidgetItem(ui->ruleTreeWidget);
	} else {
		ruleItem = new QTreeWidgetItem(parent);
	}
	if (ruleItem) {
		QMap<QString, QString> mapProperties;
		QMap<QString, QStringList> properties = mBaseUserActions.propertiesByBaseUserActionName(name);

		QMap<QString, QStringList>::const_iterator i = properties.constBegin();
		QString ruleProperties = " — ";
		while (i != properties.constEnd()) {
			QStringList const values = i.value();
			QString value = (!values.isEmpty()) ? values.at(0) : "";
			if (disabledProperties.keys().contains(i.key())) {
				value = disabledProperties.value(i.key());
			}
			mapProperties.insert(i.key(), value);
			ruleProperties += i.key() + ": " + value + "|";
			++i;
		}
		QTreeWidgetItem *topLevelParentItem = new QTreeWidgetItem();
		if (topLevelParent == nullptr) {
			topLevelParentItem = ruleItem;
		}
		else {
			topLevelParentItem = topLevelParent;
		}
		mWidgetItemCustomPropertyList.append(new WidgetItemCustomProperty(topLevelParentItem, ruleItem, mapProperties
				, repeatCountValue, isKeyActionValue, durationValue));
		mDisabledProperties.insert(ruleItem, disabledProperties);
		int column = 0;
		ruleItem->setText(column, name + ruleProperties);
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
