#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/qtimer.h>
#include <QtNetwork/qhostinfo.h>
#include <QtNetwork/qnetworkinterface.h>

//SLFGAMEBACKENDQT_EXPORT -> export 

#ifndef BUILD_STATIC
# if defined(SLFGAMEBACKENDQT_LIB)
#  define SLFGAMEBACKENDQT_EXPORT Q_DECL_EXPORT
# else
#  define SLFGAMEBACKENDQT_EXPORT Q_DECL_IMPORT
# endif
#else
# define SLFGAMEBACKENDQT_EXPORT
#endif
