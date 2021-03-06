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
	ComplexUserActionGenerator(BaseUserActionList const &baseUserActionList
			, ComplexUserActionList const &complexUserActionList
			, ComplexUserActionList const &scenarios);
	~ComplexUserActionGenerator();

	void generateComplexAction(QString const &name, QList<RuleElement *> const &userActions);

	void generateScenario(const QString &name, const QList<RuleElement *> &userActions, const QMap<QString, ActionStatus> &actionStatus);
signals:
	void newComplexActionCreated(ComplexUserAction *action);
	void newScenarioCreated(ComplexUserAction *scenario);

private:
	QDomElement userActionElement(RuleElement *userAction, QDomDocument &document, QList<UserAction *> &userActionList);
	QDomElement baseUserActionElement(RuleElement *userAction, QDomDocument &document, QList<UserAction *> &userActionList);
	QDomElement redTapeInstructionElement(QString const &instructionName, QDomDocument &document, QList<UserAction *> &userActionList);
	void addComplexAction(RuleElement *userAction, QDomDocument &document, QDomElement &complexUserActionElement);
	QMap<QString, QString> userActionPropertiesMap(QString const &userActionProperties);

	BaseUserActionList mBaseUserActions;
	ComplexUserActionList mComplexUserActions;
	ComplexUserActionList mScenarios;
	int mComplexActionsCount;
	QDir mComplexActionsDir;

	int mScenariosCount;
	QDir mScenariosDir;
	QMap<QString, ActionStatus> mActionStatus;

	QMap<QString, QStringList> mProperties;
	QMap<QString, QString> mCustomProperties;
	QList<UserAction *> mUserActions;
};
