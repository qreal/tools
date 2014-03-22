#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QTreeWidgetItem>
#include <QtCore/QMap>

#include "userAction/userActionProperty/duration.h"

class WidgetItemCustomProperty : public QObject
{
	Q_OBJECT

public:
	WidgetItemCustomProperty(QTreeWidgetItem *topLevelParent
			, QTreeWidgetItem *item, QMap<QString, QString> const &customProperties
			, int const &repeatCount, bool isKeyAction, Duration const &duration);
	~WidgetItemCustomProperty();

	void addProperty(QString const &name, QString const &value);
	void setProperty(QString const &name);
	QTreeWidgetItem *parent() const;
	QTreeWidgetItem *item() const;
	QMap<QString, QString> properties() const;
	void replaceProperties(QMap<QString, QString> const &properties);

	void setRepeatCount(int const &repeatCount);
	void setIsKeyAction(bool isKeyAction);
	void setDuration(Duration const &duration);

	int repeatCount();
	bool isKeyAction();
	Duration *duration();

private:
	QTreeWidgetItem *mTopLevelParent;
	QTreeWidgetItem *mItem;
	QMap<QString, QString> mCustomProperties;
	int mRepeatCount;
	bool mIsKeyAction;
	Duration *mDuration;

};
