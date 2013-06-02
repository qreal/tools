#include <QtGui/QApplication>
#include "diagramRecognizer.h"
#include <field.h>
#include <iostream>
#include <cstdio>
#include <graph.h>
#include <segmentator.h>
#include <link.h>
#include "recognizers/mixedGesturesManager.h"
#include "simpleFormsInitializer.h"
#include <QString>

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	DiagramRecognizer widget;
	widget.setGeometry(100, 100, 500, 355);
	widget.show();

	return a.exec();
}
