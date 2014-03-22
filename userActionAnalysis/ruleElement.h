#pragma once

#include <QtCore/QObject>

#include "userAction/userActionProperty/duration.h"

class RuleElement : public QObject
{
	Q_OBJECT

public:
	RuleElement();
	RuleElement(QString const &content, QList<RuleElement *> const &list
			, int const &repeatCount = 1
			, bool const &isKeyAction = true
			, Duration const &duration = Duration(0, 0));
	~RuleElement();

	void setContent(QString const &content);
	void setList(const QList<RuleElement *> &list);
	void addList(QList<RuleElement *> const &list);
	void addElementToList(RuleElement const &element);
	bool isBaseAction();
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
