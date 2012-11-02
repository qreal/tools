#pragma once

class Edge : public Component
{
public:
	Edge()
		: figure1(NULL), figure2 : (NULL)
	{}
	Edge(Figure *fig1, Figure *fig2)
		: figure1(fig1), figure2(fig2)
	{}
private:
	Figure *figure1, *figure2;
};
