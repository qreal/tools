#pragma once

#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtCore/QString>

namespace GestEditor {

class Parser
{

public:
	/// Converts list of points into a string
	/// @param path amount of points which represents figure
	/// @return string of points
	static QString pathToString(QList<QList<QPoint> > const &path);

private:
	/// Converst point to string
	/// @return point as a string
	static QString pointToString(QPoint const &p);
};

}
