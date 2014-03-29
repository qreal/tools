#pragma once

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include "userAction/userActionProperty/duration.h"

class RuleElement : public QObject
{
	Q_OBJECT

public:
	RuleElement();
	RuleElement(QString const &content, QList<RuleElement *> const &list
			, int repeatCount = 1
			, bool isKeyAction = true
			, Duration *duration = new Duration(0, 0));
	~RuleElement();

	void setContent(QString const &content);
	void setList(const QList<RuleElement *> &list);
	void addList(QList<RuleElement *> const &list);
	void addElementToList(RuleElement *element);
	bool isBaseAction();
	bool isRedTapeInstruction();
	QList<RuleElement *> list() const;
	QString content() const;

	int repeatCount() const;
	bool isKeyAction() const;
	Duration *duration() const;

private:
	QString mContent;
	QList<RuleElement *> mList;

	int mRepeatCount;
	bool mIsKeyAction;
	Duration *mDuration;
};
