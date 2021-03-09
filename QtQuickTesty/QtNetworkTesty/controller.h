#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "qmladapter.h"
#include "interactor.h"
#include "datatypes.h"

class controller
{
public:
    explicit controller(QmlAdapter*, Interactor*);
    void Run();

private:
    //keep ptr of both
    QmlAdapter* ui;
    Interactor* interactor;
};

#endif // CONTROLLER_H
