#pragma once

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtXml/QDomDocument>

#include "userAction/baseUserAction/baseUserAction.h"
#include "userAction/baseUserAction/baseUserActionList.h"
#include "userAction/complexUserAction/complexUserAction.h"

class ComplexUserActionGenerator : public QObject
{
	Q_OBJECT

public:
	ComplexUserActionGenerator(BaseUserActionList const &baseUserActionList);
	~ComplexUserActionGenerator();

	void generateComplexAction(QString const &name, QStringList const &userActions);

signals:
	void newComplexActionCreated(ComplexUserAction *action);

private:
	QDomElement userActionElement(QString const &userAction, QDomDocument &document);
	QMap<QString, QString> userActionPropertiesMap(QString const &userActionProperties);

	BaseUserActionList mBaseUserActions;
	int mComplexActionsCount;
	QDir mComplexActionsDir;

	QMap<QString, QStringList> mProperties;
	QMap<QString, QString> mCustomProperties;
	QList<UserAction *> mUserActions;
};
