#ifndef PROHLEDAVAC_H
#define PROHLEDAVAC_H

#include "Bludiste.h"

#include <string>

// Tuto tridu nemente
// Obsahuje abstraktni tridu - interface, ktery musi trida vaseho robota implementovat

class Prohledavac {
public:
    virtual bool start(Bludiste & map) = 0;
    virtual bool start(BludisteOdkryte & map) = 0;
    virtual bool stop() = 0;
    virtual void krok(Bludiste & map) = 0;
    virtual void krok(BludisteOdkryte & map) = 0;
    virtual std::string jmeno() = 0;
};

#endif