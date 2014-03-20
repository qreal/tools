#pragma once

#include "widgetItemProperty/widgetItemCustomProperty.h"

class WidgetItemCustomPropertyList : public QList<WidgetItemCustomProperty *>
{
public:
	WidgetItemCustomPropertyList();
	~WidgetItemCustomPropertyList();

	void removePropertiesWithParent(QTreeWidgetItem *parent);
	QMap<QString, QString> customPropertiesByItem(QTreeWidgetItem *item);
	void replaceProperties(QTreeWidgetItem *item, QMap<QString, QString> newProperties);
};
