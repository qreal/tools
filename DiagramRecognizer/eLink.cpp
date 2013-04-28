#pragma once;
#include <eLink.h>

ELink::ELink()
{
	mComponent = new Component();
	mFigure1 = mFigure2 = 0;  //null
}
ELink::ELink(Component *component)
{
	mComponent = component;
	mFigure1 = mFigure2 = 0;  //null
}
ELink::ELink(Component *component, EFigure *figure1, EFigure *figure2)
{
	mComponent = component;
	mFigure1 = figure1;
	mFigure2 = figure2;
}
ELink::ELink(Component *component, EFigure *figure)
{
	mComponent = component;
	mFigure1 = figure;
	mFigure2 = 0;
}
ELink::ELink(ELink *eLink)
{
	mComponent = eLink->getComponent();
	mFigure1 = eLink->getFigure1();
	mFigure2 = eLink->getFigure2();
}

ELink::~ELink()
{
	//no actions
}

Component *ELink::getComponent() const { return mComponent; }
EFigure *ELink::getFigure1() const { return mFigure1; }
EFigure *ELink::getFigure2() const { return mFigure2; }
