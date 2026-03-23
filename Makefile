SRC	=	src/game.cpp	\
		src/main.cpp	\
		src/enemy.cpp	\
		src/projectile.cpp	\
		src/simple_enemy.cpp	\
		src/zigzagenemy.cpp	\
		src/enemy_manager.cpp	\
		src/explosion.cpp	\
		src/shooter_enemy.cpp	\
		src/audio_manager.cpp	\
		src/player.cpp

OBJ	=	${SRC}

NAME	=	SpaceShooter

all:	${NAME}

SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

${NAME}:
	g++ -o ${NAME} -std=c++20 ${SRC} -g3 $(SFML)

clean:
	rm -f *~
	rm -f ${NAME}

fclean: clean

re: fclean all
