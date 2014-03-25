#include "widgetItemProperty/widgetItemCustomProperty.h"

WidgetItemCustomProperty::WidgetItemCustomProperty(QTreeWidgetItem *topLevelParent
		, QTreeWidgetItem *item, const QMap<QString, QString> &customProperties
		, const int &repeatCount, bool isKeyAction, const Duration &duration)
		: mTopLevelParent(topLevelParent)
		, mItem(item)
		, mCustomProperties(customProperties)
		, mRepeatCount(repeatCount)
		, mIsKeyAction(isKeyAction)
		, mDuration(new Duration(duration.from(), duration.to()))
{

}

WidgetItemCustomProperty::~WidgetItemCustomProperty()
{
	delete mDuration;
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

void WidgetItemCustomProperty::setRepeatCount(const int &repeatCount)
{
	mRepeatCount = repeatCount;
}

void WidgetItemCustomProperty::setIsKeyAction(bool isKeyAction)
{
	mIsKeyAction = isKeyAction;
}

void WidgetItemCustomProperty::setDuration(const Duration &duration)
{
	mDuration->setFrom(duration.from());
	mDuration->setTo(duration.to());
}

int WidgetItemCustomProperty::repeatCount()
{
	return mRepeatCount;
}

bool WidgetItemCustomProperty::isKeyAction()
{
	return mIsKeyAction;
}

Duration *WidgetItemCustomProperty::duration()
{
	return mDuration;
}
