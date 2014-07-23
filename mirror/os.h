#pragma once

#ifdef Q_OS_WIN
#include "os/windows.h"
#endif

#ifdef Q_OS_LINUX
#include "os/linux.h"
#endif

#ifdef Q_OS_MAC
#pragma message ("Mac OS is not needed, use Windows or Linux instead")
#include "os/mac.h"
#endif
