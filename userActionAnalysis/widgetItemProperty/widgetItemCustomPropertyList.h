#pragma once

#include "widgetItemProperty/widgetItemCustomProperty.h"

class WidgetItemCustomPropertyList : public QList<WidgetItemCustomProperty *>
{
public:
	WidgetItemCustomPropertyList();
	~WidgetItemCustomPropertyList();

	void removePropertiesWithParent(QTreeWidgetItem *parent);
	QMap<QString, QString> customPropertiesByItem(QTreeWidgetItem *item) const;
	void replaceProperties(QTreeWidgetItem *item, QMap<QString, QString> newProperties);
	void updateOtherProperties(QTreeWidgetItem *item, int const &repeatCount, bool isKeyAction, Duration const &duration);

	int repeatCountByItem(QTreeWidgetItem *item) const;
	bool isKeyActionByItem(QTreeWidgetItem *item) const;
	Duration *durationByItem(QTreeWidgetItem *item) const;
};
