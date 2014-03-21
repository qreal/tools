#pragma once

#include <QtCore/QObject>

class RuleElement : public QObject
{
	Q_OBJECT

public:
	RuleElement();
	RuleElement(QString const &content, QList<RuleElement *> const &list);
	~RuleElement();

	void setContent(QString const &content);
	void setList(const QList<RuleElement *> &list);
	void addList(QList<RuleElement *> const &list);
	void addElementToList(RuleElement const &element);
	bool isBaseAction();
	QList<RuleElement *> list() const;
	QString content() const;

private:
	QString mContent;
	QList<RuleElement *> mList;
};
