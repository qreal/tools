#include "widgetItemProperty/widgetItemCustomProperty.h"

WidgetItemCustomProperty::WidgetItemCustomProperty(QTreeWidgetItem *topLevelParent
		, QTreeWidgetItem *item, const QMap<QString, QString> &customProperties)
		: mTopLevelParent(topLevelParent)
		, mItem(item)
		, mCustomProperties(customProperties)
{

}

WidgetItemCustomProperty::~WidgetItemCustomProperty()
{
	delete mItem;
	delete mTopLevelParent;
}

void WidgetItemCustomProperty::addProperty(const QString &name, const QString &value)
{
	mCustomProperties.insert(name, value);
}

void WidgetItemCustomProperty::setProperty(const QString &name)
{
	mCustomProperties.remove(name);
}

QTreeWidgetItem *WidgetItemCustomProperty::parent() const
{
	return mTopLevelParent;
}

QTreeWidgetItem *WidgetItemCustomProperty::item() const
{
	return mItem;
}

QMap<QString, QString> WidgetItemCustomProperty::properties() const
{
	return mCustomProperties;
}

void WidgetItemCustomProperty::replaceProperties(const QMap<QString, QString> &properties)
{
	mCustomProperties.clear();
	QMap<QString, QString>::const_iterator i = properties.constBegin();
	while (i != properties.constEnd()) {
		mCustomProperties.insert(i.key(), i.value());
		++i;
	}
}
