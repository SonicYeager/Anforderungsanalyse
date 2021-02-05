#pragma once

#include <QtCore/qglobal.h>
#include <QtNetwork/qhostinfo.h>

#ifndef BUILD_STATIC
# if defined(QTLIB_LIB)
#  define QTLIB_EXPORT Q_DECL_EXPORT
# else
#  define QTLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTLIB_EXPORT
#endif
