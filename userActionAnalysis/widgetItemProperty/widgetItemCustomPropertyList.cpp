#include "widgetItemProperty/widgetItemCustomPropertyList.h"


WidgetItemCustomPropertyList::WidgetItemCustomPropertyList()
{
}

WidgetItemCustomPropertyList::~WidgetItemCustomPropertyList()
{

}

void WidgetItemCustomPropertyList::removePropertiesWithParent(QTreeWidgetItem *parent)
{
	WidgetItemCustomPropertyList listToDelete;
	for (int i = 0; i < length(); ++i) {
		if (at(i)->parent() == parent) {
			listToDelete.append(at(i));
		}
	}
	for (int i = 0; i < listToDelete.length(); ++i) {
		removeAll(listToDelete.at(i));
	}
}

QMap<QString, QString> WidgetItemCustomPropertyList::customPropertiesByItem(QTreeWidgetItem *item) const
{
	for (int i = 0; i < length(); ++i) {
		if (item == at(i)->item()) {
			return at(i)->properties();
		}
	}
	return QMap<QString, QString>();
}

void WidgetItemCustomPropertyList::replaceProperties(QTreeWidgetItem *item, QMap<QString, QString> newProperties)
{
	for (int i = 0; i < length(); ++i) {
		if (at(i)->item() == item) {
			at(i)->replaceProperties(newProperties);
		}
	}
}

void WidgetItemCustomPropertyList::updateOtherProperties(QTreeWidgetItem *item, const int &repeatCount, bool isKeyAction, const Duration &duration)
{
	for (int i = 0; i < length(); ++i) {
		WidgetItemCustomProperty *property = at(i);
		if (property->item() == item) {
			property->setIsKeyAction(isKeyAction);
			property->setRepeatCount(repeatCount);
			property->setDuration(duration);
		}
	}
}

int WidgetItemCustomPropertyList::repeatCountByItem(QTreeWidgetItem *item) const
{
	int const defaultRepeatCount = 1;
	for (int i = 0; i < length(); ++i) {
		WidgetItemCustomProperty *property = at(i);
		if (property->item() == item) {
			return property->repeatCount();
		}
	}
	return defaultRepeatCount;
}

bool WidgetItemCustomPropertyList::isKeyActionByItem(QTreeWidgetItem *item) const
{
	bool const defaultIsKeyAction = true;
	for (int i = 0; i < length(); ++i) {
		WidgetItemCustomProperty *property = at(i);
		if (property->item() == item) {
			return property->isKeyAction();
		}
	}
	return defaultIsKeyAction;
}

Duration *WidgetItemCustomPropertyList::durationByItem(QTreeWidgetItem *item) const
{
	Duration *defaultDuration = new Duration(0, 0);
	for (int i = 0; i < length(); ++i) {
		WidgetItemCustomProperty *property = at(i);
		if (property->item() == item) {
			return property->duration();
		}
	}
	return defaultDuration;
}
