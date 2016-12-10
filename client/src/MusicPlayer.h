#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SFML/Audio.hpp>

#include "Identifiers.h"

#include <map>
#include <string>

class MusicPlayer : private sf::NonCopyable
{
public:
                MusicPlayer();

    void        play(Music::ID music);
//    void        stop();

//    void        setPaused(bool paused);
//    void        setVolume(float volume);

//private:
    typedef std::map<Music::ID, std::string, EnumClassHashMusic> MusicMap;

private:
    //sf::Music	mMusic;
    MusicMap    mFilenames;
//    float		mVolume;
};

#endif // MUSICPLAYER_H
