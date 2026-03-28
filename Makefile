# VERSION CONSOLE

console: mainconsole.o Jeu.o Joueur.o Ennemi.o Projectile.o Rectangle.o
	g++ -Wall mainconsole.o Jeu.o Joueur.o Ennemi.o Projectile.o Rectangle.o -o bin/console.exe

mainconsole.o: src/mainconsole.cpp
	g++ -Wall -c src/mainconsole.cpp

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

# VERSION SDL

sdl: mainsdl.o Jeu.o Joueur.o Ennemi.o Projectile.o Rectangle.o
	g++ -Wall mainsdl.o Jeu.o Joueur.o Ennemi.o Projectile.o Rectangle.o -o bin/sdl.exe -lSDL2

mainsdl.o: src/mainsdl.cpp
	g++ -Wall -c src/mainsdl.cpp

# TESTS DE REGRESSION

tests: testRegression.o Joueur.o Ennemi.o Projectile.o Rectangle.o
	g++ -Wall testRegression.o Joueur.o Ennemi.o Projectile.o Rectangle.o -o bin/tests.exe

testRegression.o: src/testRegression.cpp
	g++ -Wall -c src/testRegression.cpp


clean:
	rm -f *.o
	rm -f bin/*.exe