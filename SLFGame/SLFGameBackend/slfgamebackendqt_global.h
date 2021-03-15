#pragma once

//#include "../SLFGameBackend_Tests/Dependencys//QtCore/qglobal.h"
//#include "../SLFGameBackend_Tests/Dependencys//QtNetwork/qhostinfo.h"
//#include "../SLFGameBackend_Tests/Dependencys//QtNetwork/qnetworkinterface.h"
//#include "../SLFGameBackend_Tests/Dependencys//QtNetwork/qtcpserver.h"
//#include "../SLFGameBackend_Tests/Dependencys//QtNetwork/qtcpsocket.h"
//#include "../SLFGameBackend_Tests/Dependencys//QtCore/qthread.h"
//#include "../SLFGameBackend_Tests/Dependencys//QtCore/qtimer.h"
 
#include <QtCore/qglobal.h>
#include <QtCore/qtimer.h>
#include <QtNetwork/qhostinfo.h>
#include <QtNetwork/qnetworkinterface.h>
#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>
#include <QtCore/qthread.h>


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
