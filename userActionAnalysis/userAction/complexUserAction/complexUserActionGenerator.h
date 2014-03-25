#pragma once

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtXml/QDomDocument>

#include "userAction/baseUserAction/baseUserAction.h"
#include "userAction/baseUserAction/baseUserActionList.h"
#include "userAction/complexUserAction/complexUserAction.h"
#include "userAction/complexUserAction/complexUserActionList.h"
#include "ruleElement.h"

class ComplexUserActionGenerator : public QObject
{
	Q_OBJECT

public:
	ComplexUserActionGenerator(BaseUserActionList const &baseUserActionList, ComplexUserActionList const &complexUserActionList);
	~ComplexUserActionGenerator();

	void generateComplexAction(QString const &name, QList<RuleElement *> const &userActions);

signals:
	void newComplexActionCreated(ComplexUserAction *action);

private:
	QDomElement userActionElement(RuleElement *userAction, QDomDocument &document, QList<UserAction *> &userActionList);
	QDomElement baseUserActionElement(RuleElement *userAction, QDomDocument &document, QList<UserAction *> &userActionList);
	void addComplexAction(RuleElement *userAction, QDomDocument &document, QDomElement &complexUserActionElement);
	QMap<QString, QString> userActionPropertiesMap(QString const &userActionProperties);

	BaseUserActionList mBaseUserActions;
	ComplexUserActionList mComplexUserActions;
	int mComplexActionsCount;
	QDir mComplexActionsDir;

	QMap<QString, QStringList> mProperties;
	QMap<QString, QString> mCustomProperties;
	QList<UserAction *> mUserActions;
};
