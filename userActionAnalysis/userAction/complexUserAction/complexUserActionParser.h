#pragma once

#include <QtCore/QObject>
#include <QtXml/QDomDocument>

#include "userAction/complexUserAction/complexUserAction.h"
#include "userAction/baseUserAction/baseUserActionList.h"
#include "userAction/complexUserAction/complexUserActionList.h"

class ComplexUserActionParser : public QObject
{
	Q_OBJECT

public:
	ComplexUserActionParser(BaseUserActionList baseUserActions);
	~ComplexUserActionParser();
	ComplexUserActionList parse();
	ComplexUserActionList parseScenarios();
private:
	QDomDocument loadDocument(const QString &fileName);
	ComplexUserAction *parseAction(QString const &fileName, bool isScenario = false);
	BaseUserAction *parseBaseUserAction(const QDomElement &element);
	ComplexUserAction *parseComplexUserAction(const QDomElement &element);
	UserAction *parseRedTapeInstruction(const QDomElement &element);

	BaseUserActionList mBaseUserActions;
	ComplexUserActionList mComplexUserActions;
};
