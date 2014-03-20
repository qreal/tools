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

QMap<QString, QString> WidgetItemCustomPropertyList::customPropertiesByItem(QTreeWidgetItem *item)
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
