
#ifndef _HPP_SINGLETON_
#define _HPP_SINGLETON_

template <typename T>
class Singleton
{
public:
    static T& getInstance();
    static T* getPointerToInstance();
    static void kill();

protected :
    Singleton() {}
    virtual ~Singleton() {}

    static T instance;
};

#include "Singleton.tpp"

#endif
