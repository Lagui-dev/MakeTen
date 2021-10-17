#include "maketenglobal.h"

MakeTenGlobal *MakeTenGlobal::currentInstance = nullptr;

MakeTenGlobal::MakeTenGlobal()
{
}

MakeTenGlobal::~MakeTenGlobal()
{

}

MakeTenGlobal *MakeTenGlobal::getInstance()
{
    if (!currentInstance)
        currentInstance = new MakeTenGlobal();
    return currentInstance;
}

bool MakeTenGlobal::removeInstance()
{
    if (currentInstance) {
        delete currentInstance;
        currentInstance = NULL;
        return true;
    }
    return false;
}

