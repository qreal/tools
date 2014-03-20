#include "complexUserActionList.h"

ComplexUserActionList::ComplexUserActionList()
{
}

ComplexUserAction *ComplexUserActionList::complexUserActionByName(const QString &name)
{
	ComplexUserActionList result;
	for (int i = 0; i < length(); ++i) {
		ComplexUserAction *complexUserAction = at(i);
		if (complexUserAction->userActionName() == name) {
			result << complexUserAction;
		}
	}
	if (result.length() == 1) {
		return result.first();
	}
	else {
		return nullptr;
	}
}
