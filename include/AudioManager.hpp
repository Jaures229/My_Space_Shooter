
#ifndef AUDIOMANAGER_HPP_
    #define AUDIOMANAGER_HPP_
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <iostream>

    class AudioManager
    {
        private:
            sf::SoundBuffer shootBuffer;
            sf::SoundBuffer explosionBuffer;
            
            sf::Sound shootSound;
            sf::Sound explosionSound;

            sf::Music backgroundMusic;

        public:
            AudioManager();

            void playShoot() { shootSound.play(); }
            void playExplosion() { explosionSound.play(); }

            ~AudioManager() {}
    };
#endif /* !AUDIOMANAGER_HPP_ */
