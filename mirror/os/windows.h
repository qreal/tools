#pragma once

#include <windows.h>

#include <QtCore/QPoint>
#include <QtCore/QSize>

/// Windows API communicator.
class Os
{
public:
	/// Simulates mouse press using Windows API.
	static void pressMouse(QPoint const &point, Qt::MouseButton button
			, QString const &windowTitle, QSize const &windowSize);

	/// Simulates mouse release using Windows API.
	static void releaseMouse(QPoint const &point, Qt::MouseButton button
			, QString const &windowTitle, QSize const &windowSize);

	/// Simulates key press using Windows API.
	static void pressKey(Qt::Key key, Qt::KeyboardModifiers modifiers);

	/// Simulates key release using Windows API.
	static void releaseKey(Qt::Key key, Qt::KeyboardModifiers modifiers);

private:
	static void moveMouse(QPoint const &point, QString const &windowTitle);
	static void resizeWindow(QString const &windowTitle, QSize const &windowSize);

	static void pressKey(Qt::Key key);
	static void releaseKey(Qt::Key key);
};
