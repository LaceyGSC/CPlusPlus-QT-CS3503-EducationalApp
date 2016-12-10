#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
    //: mMusic()
    : mFilenames()
//    , mVolume(100.f)
{
    // Load music paths
    //mFilenames.insert(std::make_pair(Music::ID::Login, "qrc:/../media/Music/The_Happy_Troll_song_-_by_D1ofAquavibe.ogg"));
    //mFilenames.insert(std::make_pair(Music::ID::Game, "qrc:/../media/Music/Sneaky_Adventure_-_Vanoss_Gaming_Background_Music_.ogg"));

    mFilenames[Music::ID::Login] = "qrc:/../media/Music/The_Happy_Troll_song_-_by_D1ofAquavibe.ogg";
    mFilenames[Music::ID::Game] = "qrc:/../media/Music/Sneaky_Adventure_-_Vanoss_Gaming_Background_Music_.ogg";
}

void MusicPlayer::play(Music::ID music)
{
    std::string filename = mFilenames[music];

    //if (!mMusic.openFromFile(filename));
        //throw std::runtime_error("Music " + filename + " could not be loaded.");

//    mMusic.setVolume(mVolume);
//    mMusic.setLoop(true);
//    mMusic.play();
}

//void MusicPlayer::stop()
//{
//    mMusic.stop();
//}

//void MusicPlayer::setVolume(float volume)
//{
//    mVolume = volume;
//}

//void MusicPlayer::setPaused(bool paused)
//{
//    if (paused)
//        mMusic.pause();
//    else
//        mMusic.play();
//}
