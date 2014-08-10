
#include "RessourceManager.hpp"

Ressource<sf::SoundBuffer>& SoundBuf()
{
    static Ressource<sf::SoundBuffer> soundBuf;
    return soundBuf;
}

Ressource<sf::Texture>& Texture()
{
    static Ressource<sf::Texture> texture;
    return texture;
}

Ressource<sf::Font>& Font()
{
    static Ressource<sf::Font> font;
    return font;
}
