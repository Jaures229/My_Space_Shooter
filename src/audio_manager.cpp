#include "../include/AudioManager.hpp"

AudioManager::AudioManager()
{
    if (!shootBuffer.loadFromFile("assets/audio/songs/laser.mp3"))
    {
        std::cerr << "Error loading shoot song\n";
    }
    if(!explosionBuffer.loadFromFile("assets/audio/songs/explosion.mp3"))
    {
        std::cerr << "Error loading explosion song\n";
    }
    
    shootSound.setBuffer(shootBuffer);
    explosionSound.setBuffer(explosionBuffer);
    
    if (backgroundMusic.openFromFile("assets/audio/music/music.mp3")) {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(30.f);
        backgroundMusic.play();
    }
}
