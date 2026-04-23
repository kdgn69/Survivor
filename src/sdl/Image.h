#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Image {
private:
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    bool m_hasChanged;

public:
    Image();
    ~Image();

    void setSurface(SDL_Surface* surface);
    bool loadFromCurrentSurface(SDL_Renderer* renderer);
    bool loadFromFile(const string& filename, SDL_Renderer* renderer);

    void draw(SDL_Renderer* renderer, float x, float y, float w, float h) const;
};

#endif 