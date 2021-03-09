#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "qmladapter.h"
#include "interactor.h"
#include "ServerInteractor.h"
#include "datatypes.h"

class controller
{
public:
    explicit controller(QmlAdapter*, Interactor*, ServerInteractor*);
    void Run();

private:
    //keep ptr of both
    QmlAdapter* ui;
    Interactor* interactor;
    ServerInteractor* serverInteractor;
};

#endif // CONTROLLER_H
