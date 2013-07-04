#include "gestEdit.h"
#include "ui_gestEdit.h"

using namespace GestEditor;

const QString gestureKeyWord = "gesture";
const QString idealPathKeyWord = "idealPath";
const QString nameKeyWord = "name";
const QString userPathKeyWord = "userPath";
const QString pathKeyWord = "path";
static const int widthGW = 3000;
static const int heightGW = 4000;

GestEdit::GestEdit(QWidget *parent) :
	QWidget(parent),
	mUi(new Ui::GestEdit)
{
	mUi->setupUi(this);
	mScene = new Scene(mUi->graphicsView);
	mScene->setSceneRect(0,0, widthGW, heightGW);
	mUi->graphicsView->setScene(mScene);
	mUi->graphicsView->setAlignment(Qt::AlignLeft);
	mUi->graphicsView->setRenderHint(QPainter::Antialiasing, true);
	initButtonGroup();

	connect(mUi->drawLineButton, SIGNAL(clicked()), this, SLOT(drawLine()));
	connect(mUi->drawRectButton, SIGNAL(clicked()), this, SLOT(drawRect()));
	connect(mUi->drawEllipseButton, SIGNAL(clicked()), this, SLOT(drawEllipse()));
	connect(mUi->drawCurveButton, SIGNAL(clicked()), this, SLOT(drawCurve()));
	connect(mUi->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	connect(mUi->deleteItemButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
	connect(mUi->openButton, SIGNAL(clicked()), this, SLOT(open()));
	connect(mUi->saveButton, SIGNAL(clicked()), this, SLOT(saveToXml()));
	connect(mUi->savePointButtonS, SIGNAL(clicked()), this, SLOT(saveInPoints()));
	connect(mScene, SIGNAL(resetHighlightAllButtons()), this, SLOT(resetHighlightAllButtons()));
}

void GestEdit::initButtonGroup()
{
	mButtonGroup.append(mUi->drawCurveButton);
	mButtonGroup.append(mUi->drawLineButton);
	mButtonGroup.append(mUi->drawEllipseButton);
	mButtonGroup.append(mUi->drawRectButton);
}

void GestEdit::setHighlightOneButton(QAbstractButton *oneButton)
{
	foreach (QAbstractButton *button, mButtonGroup) {
		if (button != oneButton) {
			button->setChecked(false);
		}
	}
}

void GestEdit::resetHighlightAllButtons()
{
	foreach (QAbstractButton *button, mButtonGroup) {
		button->setChecked(false);
	}
	mScene->addNone();
}

void GestEdit::drawLine()
{
	mScene->drawLine();
	setHighlightOneButton(mUi->drawLineButton);
}

void GestEdit::drawRect()
{
	mScene->drawRect();
	setHighlightOneButton(mUi->drawRectButton);
}

void GestEdit::drawEllipse()
{
	mScene->drawEllipse();
	setHighlightOneButton(mUi->drawEllipseButton);
}

void GestEdit::drawCurve()
{
	mScene->drawCurve();
	setHighlightOneButton(mUi->drawCurveButton);
}

void GestEdit::clear()
{
	mScene->refresh();
	resetHighlightAllButtons();
	mScene->invalidate();
}

void GestEdit::deleteItem()
{
	mScene->deleteSelectedItem();
	resetHighlightAllButtons();
	mScene->invalidate();
}

void GestEdit::open()
{
	mDocument.clear();
	QString fileName = QFileDialog::getOpenFileName(this);
	if (fileName.isEmpty()) {
		return;
	}
	XmlLoader loader(mScene);
	loader.readFile(fileName);
}

void GestEdit::saveToXml()
{
	mDocument.clear();
	// get's file's name from the window
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty()) {
		return;
	}
	exportToXml(fileName);
}

void GestEdit::saveInPoints()
{
	mDocument.clear();
	// get's file's name from the window
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty()) {
		return;
	}
	mDomElement = getFirstDomElement(fileName);
	exportInPoints(fileName);
}

QList<QDomElement> GestEdit::generateGraphics()
{
	QDomElement picture = mDocument.createElement("picture");
	QRect sceneBoundingRect = mScene->itemsBoundingRect().toRect();

	QList<QGraphicsItem *> list = mScene->items();
	foreach (QGraphicsItem *graphicsItem, list) {
		Item* item = dynamic_cast<Item*>(graphicsItem);
		if (item != NULL) {
			QDomElement domItem = item->generateItem(mDocument); // write figure properties in XML
			picture.appendChild(domItem);
		}
	}
	picture.setAttribute("sizex", static_cast<int>(sceneBoundingRect.width()));
	picture.setAttribute("sizey", static_cast<int>(sceneBoundingRect.height()));
	QList<QDomElement> domList;
	domList.push_back(picture);
	return domList;
}

void GestEdit::generateDom()
{
	QDomElement graphics = mDocument.createElement("graphics");
	mDocument.appendChild(graphics);
	QList<QDomElement> list = generateGraphics();
	foreach (QDomElement const &domItem, list) {
		graphics.appendChild(domItem);
	}
}

void GestEdit::exportToXml(QString const &fileName)
{
	utils::OutFile file(fileName);
	generateDom();
	file() << "<?xml version='1.0' encoding='utf-8'?>\n";
	file() << mDocument.toString(4);
	file() << "\n";
}

QDomElement GestEdit::getFirstDomElement(const QString &fileName)
{
	QFile file(fileName);
	QDomDocument doc("document");
	if (file.open(QIODevice::ReadWrite)) {
		doc.setContent(&file);
		file.close();
	}
	return doc.documentElement();
}

void GestEdit::exportInPoints(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadWrite)) {
		return;
	}
	QDomDocument doc;
	QDomElement root = doc.createElement("usersGestures");
	doc.appendChild(root);
	saveDocument(createGest(), doc, fileName);
}

UsersGestures GestEdit::createGest()
{
	QStringList names;
	PathVector paths;
	QPoint topLeftPoint = getTopLeftPoint();
	QList<QGraphicsItem *> list = mScene->items();
	foreach (QGraphicsItem *graphicsItem, list) {
		Item* item = dynamic_cast<Item*>(graphicsItem);
		paths.append(item->getCurve(topLeftPoint));
		names.append(item->getName());
	}
	UsersGestures gestures;
	gestures.first = paths;
	gestures.second = names;
	return gestures;
}

void GestEdit::saveDocument(const UsersGestures &gesture, QDomDocument doc,
							 QString const & fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadWrite)) {
		return;
	}
	QTextStream textStream(&file);
	QDomElement element = doc.createElement(gestureKeyWord);
	element.setAttribute(idealPathKeyWord, Parser::pathToString(gesture.first));
	element.setAttribute(nameKeyWord, "NewGesture");
	doc.documentElement().appendChild(element);
	doc.save(textStream, 2);
	file.close();
}

QPoint GestEdit::getTopLeftPoint() const
{
	qreal minX = widthGW;
	qreal minY = heightGW;
	foreach (QGraphicsItem *graphicsItem, mScene->items()) {
		Item *item = dynamic_cast<Item*>(graphicsItem);
		qreal x = item->sceneBoundingRect().topLeft().x();
		qreal y = item->sceneBoundingRect().topLeft().y();
		if (minX > x) {
			minX = x;
		}
		if (minY > y) {
			minY = y;
		}
	}
	QPointF topLeftPoint = QPointF(minX, minY);
	return topLeftPoint.toPoint();
}

GestEdit::~GestEdit()
{
	delete mUi;
}
