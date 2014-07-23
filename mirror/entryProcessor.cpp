#include "entryProcessor.h"

#include <QtCore/QRegExp>
#include <QtCore/QPoint>
#include <QtCore/QSize>

#include <QtCore/QStringList>
#include "os.h"

LogEntry::Level const userActionsLogLevel = LogEntry::trace;

EntryProcessor::EntryProcessor(LogEntry const &entry)
	: mEntry(entry)
{
}

void EntryProcessor::process()
{
	if (mEntry.level() != userActionsLogLevel) {
		// Got message of the other level
		return;
	}

	if (mEntry.message().startsWith("Mouse")) {
		processMouseEntry();
	} else if (mEntry.message().startsWith("Key")) {
		processKeyEntry();
	}

	// Else it is not user action message, ignoring it
}

#include"defines.h"
void EntryProcessor::processMouseEntry()
{
	QRegExp const regexp("Mouse (\\w+) in QPoint\\((\\d+),(\\d+)\\) with (\\d+) target \"(.*)\" QSize\\((\\d+), (\\d+)\\)");
	if (!regexp.exactMatch(mEntry.message())) {
		return;
	}

//	PRINT(regexp.capturedTexts().join("; "));
	QString const action = regexp.cap(1);

	int const x = regexp.cap(2).toInt();
	int const y = regexp.cap(3).toInt();

	Qt::MouseButton const button = static_cast<Qt::MouseButton>(regexp.cap(4).toInt());

	QString const title = regexp.cap(5);

	int const width = regexp.cap(6).toInt();
	int const height = regexp.cap(7).toInt();

	if (action == "press") {
//		Os::pressMouse(QPoint(x, y), button, title, QSize(width, height));
	} else if (action == "release") {
//		Os::releaseMouse(QPoint(x, y), button, title, QSize(width, height));
	}
}

void EntryProcessor::processKeyEntry()
{
	QRegExp const regexp("Key (\\w+) with (\\d+) modifiers QFlags\\(0x(\\d+)\\)");
	if (!regexp.exactMatch(mEntry.message())) {
		return;
	}

	QString const action = regexp.cap(1);

	Qt::Key const key = static_cast<Qt::Key>(regexp.cap(2).toInt());
	Qt::KeyboardModifiers const modifiers = static_cast<Qt::KeyboardModifiers>(regexp.cap(3).toInt(0, 16));

	if (action == "press") {
//		Os::pressKey(key, modifiers);
	} else if (action == "release") {
//		Os::releaseKey(key, modifiers);
	}
}
