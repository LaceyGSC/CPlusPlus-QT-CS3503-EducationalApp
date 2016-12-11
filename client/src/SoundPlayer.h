#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <SFML/Audio.hpp>

#include "ResourceManager.h"
#include "Identifiers.h"

#include <list>

class SoundPlayer : private sf::NonCopyable
{
public:
    SoundPlayer();

    void                    play(Sounds::ID effect, float volume);
    void                    play(Sounds::ID effect, sf::Vector2f position, float volume);

    void                    removeStoppedSounds();
    void                    setListenerPosition(sf::Vector2f position);
    sf::Vector2f            getListenerPosition() const;

private:
    SoundBufferManager      mSoundBuffers;
    std::list<sf::Sound>    mSounds;
};

#endif // SOUNDPLAYER_H
