
template <typename T>
T Singleton<T>::instance;

template <typename T>
T& Singleton<T>::getInstance()
{
    return instance;
}

template <typename T>
T* Singleton<T>::getPointerToInstance()
{
    return &instance;
}

template <typename T>
void Singleton<T>::kill()
{
    instance.~Singleton<T>();
}
