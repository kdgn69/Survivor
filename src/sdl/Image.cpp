#include "Image.h"
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

Image::Image() {
    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

Image::~Image() {
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    if (m_surface != nullptr) {
        SDL_FreeSurface(m_surface);
        m_surface = nullptr;
    }
}

void Image::setSurface(SDL_Surface* surface) {
    if (m_surface != nullptr) {
        SDL_FreeSurface(m_surface);
        m_surface = nullptr;
    }

    m_surface = surface;
    m_hasChanged = true;
}

bool Image::loadFromCurrentSurface(SDL_Renderer* renderer) {
    if (m_surface == nullptr || renderer == nullptr) {
        return false;
    }

    // si la surface a changé, on recrée la texture
    if (m_hasChanged) {
        if (m_texture != nullptr) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }

        m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
        m_hasChanged = false;
    }

    return m_texture != nullptr;
}

bool Image::loadFromFile(const string& filename, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filename.c_str());

    if (surface == nullptr) {
        cout << "Erreur chargement image : " << filename << " | " << IMG_GetError() << endl;
        return false;
    }

    setSurface(surface);
    return loadFromCurrentSurface(renderer);
}

void Image::draw(SDL_Renderer* renderer, float x, float y, float w, float h) const {
    if (renderer == nullptr || m_texture == nullptr) {
        return;
    }

    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopyF(renderer, m_texture, nullptr, &rect);
}