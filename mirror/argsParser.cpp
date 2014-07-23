#include "argsParser.h"

QString const logKey = "log";
QString const applicationKey = "app";
QString const speedKey = "speed";

ArgsParser::ArgsParser(QStringList const &args)
	: mHelpMode(false)
	, mSpeed(original)
{
	int const startupArgsSeparatorIndex = args.indexOf("--");
	int const startupArgsBegin = startupArgsSeparatorIndex > 0 ? startupArgsSeparatorIndex : args.length();

	mStartupArgs = args.mid(startupArgsBegin + 1);

	for (int i = 1; i < startupArgsBegin; ++i) {
		QString const arg = args[i];
		if (arg == "--help" || !parseArg(arg)) {
			mHelpMode = true;
			return;
		}
	}

	if (mLogPath.isEmpty() || mApplicationPath.isEmpty()) {
		mHelpMode = true;
	}
}

bool ArgsParser::helpMode() const
{
	return mHelpMode;
}

QString ArgsParser::helpText() const
{
	return "usage: mirror [--help] [log=<log file path> app=<application path>] [speed=<speed>] [-- <startup args>]\n"\
			"\n"\
			"This tool reproduces user actions by the given log file on the given application.\n"\
			"The log file name must have strict format (see "\
			/// @todo: url
			"github.com/qreal/qreal/tree/master/qrgui/QRealApplication.cpp for details).\n"\
			"The speed may be varied between 'fastest', 'fast' and 'original'\n"\
			"At the moment this tool works only on Windows platforms, porting on X-server planned.\n";
}

QString ArgsParser::logFilePath() const
{
	return mLogPath;
}

Speed ArgsParser::speed() const
{
	return mSpeed;
}

QString ArgsParser::applicationPath() const
{
	return mApplicationPath;
}

QStringList ArgsParser::startupArgs() const
{
	return mStartupArgs;
}

bool ArgsParser::parseArg(QString const &arg)
{
	QStringList const parts = arg.split('=', QString::SkipEmptyParts);
	if (parts.count() != 2) {
		return false;
	}

	QString const key = parts[0].toLower().trimmed();
	QString const value = parts[1].toLower().trimmed();

	if (key == logKey) {
		mLogPath = value;
		return true;
	}

	if (key == applicationKey) {
		mApplicationPath = value;
		return true;
	}

	if (key == speedKey) {
		bool ok = false;
		mSpeed = stringToSpeed(value, ok);
		return ok;
	}

	return false;
}

Speed ArgsParser::stringToSpeed(QString const &rawSpeed, bool &ok) const
{
	ok = true;

	QString const speed = rawSpeed.toLower().trimmed();
	if (speed == "original") {
		return original;
	}

	if (speed == "fast") {
		return fast;
	}

	if (speed == "fastest") {
		return fastest;
	}

	ok = false;
	return original;
}
