
#ifndef _HPP_RESSOURCE_
#define _HPP_RESSOURCE_

#include <string>
#include <vector>

#include <iostream>

template <typename RessType>
class Ressource
{
public:
    Ressource() {}
    virtual ~Ressource() {}

	RessType& GetRessource(const std::string& ress_name);
	void Unload(const std::string& ress_name);
	void FreeRessources();

	RessType& operator[](const std::string& ress_name);

protected:

	std::map<std::string, RessType> _ress_lib;
};

#include "ressource.tpp"

#endif // _HPP_RESSOURCE_

