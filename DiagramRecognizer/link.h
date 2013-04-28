#pragma once;
#include <eLink.h>

class Link : public ELink
{
public:
	Link() : ELink() { }
	Link(Component *component) : ELink (component) { }
	Link(ELink *eLink) : ELink (eLink) { }
	Link(Link *link) : ELink ((ELink *)link) { }
};
