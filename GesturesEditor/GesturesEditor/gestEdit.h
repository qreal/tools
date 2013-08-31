#pragma once

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtWidgets/QAbstractButton>
#include <QtCore/QMap>
#include <QtWidgets/QFileDialog>

#include "xmlLoader.h"
#include "scene.h"
#include "parser.h"
#include <outFile.h>


namespace Ui {
class GestEdit;
}

typedef QList< QList<QPoint> > PathVector;
typedef QPair<PathVector, QStringList> UsersGestures;

/// Main class, which connects all components
class GestEdit : public QWidget
{
	Q_OBJECT

public:
	explicit GestEdit(QWidget *parent = 0);
	~GestEdit();

private:
	/// Sets headers to the file, where figure is saved as points
	/// @param fileName name of the file
	QDomElement getFirstDomElement(const QString &fileName);

	/// Watches all item-figures on a Scene and generates information about every element
	/// @return list of element's properties
	QList<QDomElement> generateGraphics();

	/// Sets header tag and writes information about all item-figures in XML (as object file)
	void generateDom();

	/// Writes formal XML file, where item-figures represented as objects
	/// @param fileName name of XML file
	void exportToXml(QString const &fileName);

	/// Writes formal XML file, where item-figures represented as amount of points
	/// @param fileName name of XML file
	void exportInPoints(QString const &fileName);

	/// Union buttons in group
	void initButtonGroup();

	/// Higlights only one button
	void setHighlightOneButton(QAbstractButton *oneButton);

	/// Creates pair of
	///	first list of paths of item-figures (amount of points)
	/// second list of item-figures names
	UsersGestures createGest();

	/// Makes top left point from coordinates of all item-figures
	/// @return top left point, where x - the most left(small) coordinate, y - most top(small) coordinate
	QPoint getTopLeftPoint() const;

	/// Sets header tag and writes information about all item-figures in XML (as amount of points)
	/// @param gesture pair of: first list of paths of item-figures (amount of points), second list of item-figures names
	/// @param doc document representation
	/// @param fileName name of file
	void saveDocument(const UsersGestures &gesture, QDomDocument doc,
								 QString const & fileName);
	Ui::GestEdit *mUi;
	GestEditor::Scene *mScene;
	QList<QAbstractButton*> mButtonGroup;
	qreal mX1;
	qreal mX2;
	qreal mY1;
	qreal mY2;
	QDomDocument mDocument;
	QDomElement mDomElement;

private slots:
	/// Calls Scene's drawLine method
	void drawLine();

	/// Calls Scene's drawRect method
	void drawRect();

	/// Calls Scene's drawEllipse method
	void drawEllipse();

	/// Calls Scene's drawCurve method
	void drawCurve();

	/// Calls Scene's deleteSelectedItem method
	void deleteItem();

	/// Calls Scene's refresh method
	void clear();

	/// Opens XML file and Adds figures from file
	void open();

	/// Saves figures in XML file as objects
	void saveToXml();

	/// Saves figures in XML file as points
	void saveInPoints();

	/// Resrts higlight from buttons
	void resetHighlightAllButtons();
};

