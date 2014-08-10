
template <typename RessType>
RessType& Ressource<RessType>::GetRessource(const std::string& ress_name)
{
    if(_ress_lib.find(ress_name) == _ress_lib.end())
        if(!_ress_lib[ress_name].loadFromFile(ress_name))
            exit(EXIT_FAILURE);

    return _ress_lib[ress_name];
}

template <typename RessType>
RessType& Ressource<RessType>::operator[](const std::string& ress_name)
{
    return GetRessource(ress_name);
}

template <typename RessType>
void Ressource<RessType>::Unload(const std::string& ress_name)
{
    if(_ress_lib.count(ress_name))
        _ress_lib.erase(ress_name);
}

template <typename RessType>
void Ressource<RessType>::FreeRessources()
{
    typename std::map<std::string, RessType>::iterator ressourcesIterator = _ress_lib.begin();
    while(ressourcesIterator != _ress_lib.end())
    {
        _ress_lib.erase(ressourcesIterator);
        ressourcesIterator = _ress_lib.begin();
    }
}
