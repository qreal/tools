#pragma once

#include <QtXml/QDomDocument>

#include "scene.h"
#include "item.h"
#include <xmlUtils.h>

namespace GestEditor {

/// Class provides reading from XML file
/// Were figures are written as elementary figures
class XmlLoader
{
public:
	XmlLoader(GestEditor::Scene *scene);

	/// Loads document and starts reading
	/// @param fileName name of XML file
	void readFile(const QString &fileName);

private:
	QDomDocument mDocument;
	GestEditor::Scene *mScene;
	bool mReadFile;

	/// Reads elements by tag graphics
	void readDocument();

	/// Reads elements by tag picture
	void readGraphics(QDomElement const &graphic);

	/// Determines picture on types
	void readPicture(QDomElement const &picture);

	/// Reads & Creates Line
	void readLine(QDomElement const &line);

	/// Reads & Creates Ellipse
	void readEllipse(QDomElement const &ellipse);

	/// Reads & Creates Curve
	void readCurve(QDomElement const &arch);

	/// Reads & Creates Rectangle
	void readRectangle(QDomElement const &rectangle);

	/// Line coordinates parse
	QPair<QPointF, QPointF> readLineOfXandY(QDomElement const &docItem);

	/// Helps in parse
	/// @param point name of current coordinate
	QPair<QString, bool> readScaleCoord(QString point, QDomElement const &docItem);

	/// Rectangle coordinates parse
	QRectF readRectOfXandY(QDomElement const &docItem);
};

}
