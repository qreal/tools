#pragma once

#include <QtCore/QMap>
#include <QtCore/QStringList>

class UserAction : public QObject
{
	Q_OBJECT

public:
	UserAction(QString const &name);
	virtual ~UserAction();
	virtual QString userActionName() const;

private:
	QString mName;
};
