# VERSION CONSOLE

console: mainconsole.o JeuConsole.o Jeu.o Joueur.o Ennemi.o Projectile.o Rectangle.o Arme.o Vague.o
	g++ -Wall mainconsole.o JeuConsole.o Jeu.o Joueur.o Ennemi.o Projectile.o Rectangle.o Arme.o Vague.o -o bin/console.exe

mainconsole.o: src/txt/mainconsole.cpp
	g++ -Wall -c src/txt/mainconsole.cpp

JeuConsole.o: src/txt/JeuConsole.cpp
	g++ -Wall -c src/txt/JeuConsole.cpp

Jeu.o: src/Jeu.cpp
	g++ -Wall -c src/Jeu.cpp

Joueur.o: src/Joueur.cpp
	g++ -Wall -c src/Joueur.cpp

Ennemi.o: src/Ennemi.cpp
	g++ -Wall -c src/Ennemi.cpp

Projectile.o: src/Projectile.cpp
	g++ -Wall -c src/Projectile.cpp

Rectangle.o: src/Rectangle.cpp
	g++ -Wall -c src/Rectangle.cpp

Arme.o: src/Arme.cpp
	g++ -Wall -c src/Arme.cpp

Vague.o: src/Vague.cpp
	g++ -Wall -c src/Vague.cpp

# VERSION SDL

sdl: mainsdl.o JeuSDL.o Jeu.o Joueur.o Ennemi.o Projectile.o Rectangle.o Arme.o Vague.o
	g++ -Wall mainsdl.o JeuSDL.o Jeu.o Joueur.o Ennemi.o Projectile.o Rectangle.o Arme.o Vague.o -o bin/sdl.exe -lSDL2 -lSDL2_ttf -lSDL2_image

mainsdl.o: src/sdl/mainsdl.cpp
	g++ -Wall -c src/sdl/mainsdl.cpp

JeuSDL.o: src/sdl/JeuSDL.cpp
	g++ -Wall -c src/sdl/JeuSDL.cpp

# TESTS DE REGRESSION

tests: testRegression.o Joueur.o Ennemi.o Projectile.o Rectangle.o Arme.o
	g++ -Wall testRegression.o Joueur.o Ennemi.o Projectile.o Rectangle.o Arme.o -o bin/tests.exe

testRegression.o: src/testRegression.cpp
	g++ -Wall -c src/testRegression.cpp


clean:
	rm -f *.o
	rm -f bin/*.exe