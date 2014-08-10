
#ifndef _HPP_RESSOURCEMANAGER_
#define _HPP_RESSOURCEMANAGER_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ressource.hpp"

#define SOUND_BASE_FOLDER "Data/Sound/"
#define TEXTURE_BASE_FOLDER "Data/Image/"
#define FONT_BASE_FOLDER "Data/Font/"

Ressource<sf::SoundBuffer>& SoundBuf();
Ressource<sf::Texture>& Texture();
Ressource<sf::Font>& Font();

#endif //_HPP_RESSOURCEMANAGER_
