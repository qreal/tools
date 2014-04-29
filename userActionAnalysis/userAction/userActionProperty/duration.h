#pragma once

class Duration
{
public:
    Duration(int from = 0, int to = 0, int exact = 0);
	~Duration();

	int from() const;
	int to() const;
    int exact() const;

	void setFrom(int from);
	void setTo(int to);
    void setExact(int exact);

private:
	int mFrom; //ms
	int mTo; //ms
    int mExact; //ms
};
