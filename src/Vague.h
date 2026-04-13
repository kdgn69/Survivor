#ifndef VAGUE_H
#define VAGUE_H

using namespace std;

class Vague {
private:
    int niveau;
    int numero;

public:
    Vague();

    void passerSuivante();

    int getNumero() const;
    int getNiveau() const;

    int getNombreEnnemis() const;
};

#endif