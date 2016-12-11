#include "SoundPlayer.h"

#include <cmath>

namespace
{
// Sound coordinate system, point of view of a player in front of the screen:
// X = left; Y = up; Z = back (out of the screen)
const float ListenerZ = 300.f;
const float Attenuation = 8.f;
const float MinDistance2D = 200.f;
const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

SoundPlayer::SoundPlayer()
    : mSoundBuffers()
    , mSounds()
{
    mSoundBuffers.load(Sounds::ID::Pickup, "qrc:/../media/Sounds/327894__kreastricon62__bush-cut.wav");
    mSoundBuffers.load(Sounds::ID::MainQuest, "qrc:/../media/Sounds/171671__fins__success-1.wav");
    mSoundBuffers.load(Sounds::ID::OptionalQuest, "qrc:/../media/Sounds/274183__littlerobotsoundfactory__jingle-win-synth-04.wav");

    // Listener points towards the screen (default in SFML)
    sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::play(Sounds::ID effect, float volume)
{
    play(effect, getListenerPosition(), volume);
}

void SoundPlayer::play(Sounds::ID effect, sf::Vector2f position, float volume)
{
    mSounds.push_back(sf::Sound());
    sf::Sound& sound = mSounds.back();

    sound.setBuffer(mSoundBuffers.get(effect));
    sound.setPosition(position.x, -position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);

    sound.setVolume(volume);
    sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([] (const sf::Sound& s)
    {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
    sf::Vector3f position = sf::Listener::getPosition();
    return sf::Vector2f(position.x, -position.y);
}
