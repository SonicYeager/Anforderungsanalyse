#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/qthread.h>
#include <QtNetwork/qhostinfo.h>
#include <QtNetwork/qnetworkinterface.h>
#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>

#ifndef BUILD_STATIC
# if defined(BACKEND_LIB)
#  define BACKEND_EXPORT Q_DECL_EXPORT
# else
#  define BACKEND_EXPORT Q_DECL_IMPORT
# endif
#else
# define BACKEND_EXPORT
#endif
