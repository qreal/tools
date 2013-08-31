#include <xmlLoader.h>
#include <scene.h>

#include <QtXml/QDomDocument>

using namespace GestEditor;

XmlLoader::XmlLoader(Scene *scene)
{
	mScene = scene;
	mReadFile = true;
}

void XmlLoader::readFile(const QString &fileName)
{
	mReadFile = true;
	mDocument = utils::xmlUtils::loadDocument(fileName);
	readDocument();
}

void XmlLoader::readDocument()
{
	QDomNodeList const graphics = mDocument.elementsByTagName("graphics");
	for (int i = 0; i < graphics.length(); ++i) {
		QDomElement graphic = graphics.at(i).toElement();
		readGraphics(graphic);
	}
	mScene->centerView();
}

void XmlLoader::readGraphics(QDomElement const &graphic)
{
	QDomNodeList graphicAttributes = graphic.childNodes();
	for (int i = 0; i < graphicAttributes.length(); ++i) {
		QDomElement type = graphicAttributes.at(i).toElement();
		if (type.tagName() == "picture") {
			readPicture(type);
		}
	}
}

void XmlLoader::readPicture(QDomElement const &picture)
{
	QDomNodeList pictureAttributes = picture.childNodes();

	for (int i = 0; i < pictureAttributes.length(); ++i) {
		QDomElement type = pictureAttributes.at(i).toElement();
		if (type.tagName() == "line") {
			readLine(type);
		} else if (type.tagName() == "ellipse") {
			readEllipse(type);
		} else if (type.tagName() == "curve") {
			readCurve(type);
		} else if (type.tagName() == "rectangle") {
			readRectangle(type);}
	}
}

void XmlLoader::readLine(QDomElement const &line)
{
	QPair<QPointF, QPointF> rect = readLineOfXandY(line);
	Line* item = new Line(rect.first.x(), rect.first.y(), rect.second.x(), rect.second.y(), NULL);
	mScene->addItem(item);
	mScene->setLastAdded(item);
}

QPair<QPointF, QPointF> XmlLoader::readLineOfXandY(QDomElement const &docItem)
{
	QPair<QString, bool> pointX1 = readScaleCoord("x1", docItem);
	QPair<QString, bool> pointX2 = readScaleCoord("x2", docItem);
	QPair<QString, bool> pointY1 = readScaleCoord("y1", docItem);
	QPair<QString, bool> pointY2 = readScaleCoord("y2", docItem);

	qreal x1 = pointX1.first.toDouble();
	qreal x2 = pointX2.first.toDouble();
	qreal y1 = pointY1.first.toDouble();
	qreal y2 = pointY2.first.toDouble();

	return QPair<QPointF, QPointF>(QPointF(x1, y1), QPointF(x2, y2));
}

QPair<QString, bool> XmlLoader::readScaleCoord(QString point, QDomElement const &docItem)
{
	QString text = docItem.attribute(point, "0");
	if (text.endsWith("a")) {
		text.truncate(text.size() - 1);
		return QPair<QString, bool>(text, true);
	}
	return QPair<QString, bool>(text, false);
}

void XmlLoader::readEllipse(QDomElement const &ellipse)
{
	QRectF rect = readRectOfXandY(ellipse);
	Ellipse *item = new Ellipse(rect.left(), rect.top(), rect.right(), rect.bottom(), NULL);
	mScene->addItem(item);
	mScene->setLastAdded(item);
}

QRectF XmlLoader::readRectOfXandY(QDomElement const &docItem)
{
	QPair<QString, bool> pointX1 = readScaleCoord("x1", docItem);
	QPair<QString, bool> pointX2 = readScaleCoord("x2", docItem);
	QPair<QString, bool> pointY1 = readScaleCoord("y1", docItem);
	QPair<QString, bool> pointY2 = readScaleCoord("y2", docItem);

	qreal x1 = pointX1.first.toDouble();
	qreal x2 = pointX2.first.toDouble();
	qreal y1 = pointY1.first.toDouble();
	qreal y2 = pointY2.first.toDouble();

	return QRectF(x1, y1, x2 - x1, y2 - y1);
}

void XmlLoader::readRectangle(QDomElement const &rectangle)
{
	QRectF rect = readRectOfXandY(rectangle);
	Rectangle *item = new Rectangle(rect.left(), rect.top(), rect.right(), rect.bottom(), NULL);
	mScene->addItem(item);
	mScene->setLastAdded(item);
}

void XmlLoader::readCurve(QDomElement const &arch)
{
	QRectF rect = readRectOfXandY(arch);
	Curve* item = new Curve(rect.topLeft().x(), rect.topLeft().y(), rect.bottomRight().x(), rect.bottomRight().y());
	mScene->addItem(item);
	mScene->setLastAdded(item);
}
