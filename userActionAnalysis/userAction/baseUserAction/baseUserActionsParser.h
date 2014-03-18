#pragma once

#include <QtCore/QObject>
#include <QtXml/QDomDocument>

#include "userAction/baseUserAction/baseUserAction.h"
#include "userAction/baseUserAction/baseUserActionList.h"

class BaseUserActionsParser : public QObject
{
	Q_OBJECT

public:
	BaseUserActionsParser();
	~BaseUserActionsParser();
	BaseUserActionList parse();
	QList<BaseUserAction *> parseUserLog(QStringList const &userLog);

private:
	BaseUserAction *parseUserActionFromLog(QString const &userAction);
	QDomDocument loadDocument(const QString &fileName);
	BaseUserActionList mBaseUserActions;
};
