#pragma once;
#include <component.h>
#include <eFigure.h>

class ELink
{
public:
	ELink();
	ELink(Component *component);
	ELink(Component *component, EFigure *figure1, EFigure *figure2);
	ELink(Component *component, EFigure *figure);
	ELink(ELink *eLink);
	~ELink();
	Component *getComponent() const;
	EFigure *getFigure1() const;
	EFigure *getFigure2() const;
private:
	Component *mComponent;
	EFigure *mFigure1, *mFigure2;
};
