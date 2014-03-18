#pragma once

#include <QtCore/QObject>
#include <QtXml/QDomDocument>

#include "userAction/complexUserAction/complexUserAction.h"
#include "userAction/baseUserAction/baseUserActionList.h"

class ComplexUserActionParser : public QObject
{
	Q_OBJECT

public:
	ComplexUserActionParser(BaseUserActionList baseUserActions);
	~ComplexUserActionParser();
	QList<ComplexUserAction*> parse();

private:
	QDomDocument loadDocument(const QString &fileName);
	ComplexUserAction *parseAction(QString const &fileName);

	BaseUserActionList mBaseUserActions;
	QList<ComplexUserAction *> mComplexUserActions;
};
