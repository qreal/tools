#pragma once

#include "userAction/complexUserAction/complexUserAction.h"

class ComplexUserActionList : public QList<ComplexUserAction *>
{
public:
	ComplexUserActionList();
	ComplexUserAction *complexUserActionByName(QString const &name);
};
