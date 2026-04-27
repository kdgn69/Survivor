/**
 * @file Image.h
 * Gère le chargement et l’affichage des images avec SDL.
 */

/**
 * @class Image
 * Permet de charger une image et de l’afficher à l’écran.
 */
class Image {
private:
    SDL_Surface* m_surface;  /**< Surface SDL */
    SDL_Texture* m_texture;  /**< Texture SDL */
    bool m_hasChanged;       /**< Indique si la texture doit être recréée */

public:
    /**
     * Initialise une image vide.
     */
    Image();

    /**
     * Libère les ressources.
     */
    ~Image();

    /**
     * Définit la surface.
     */
    void setSurface(SDL_Surface* surface);

    /**
     * Crée la texture à partir de la surface.
     */
    bool loadFromCurrentSurface(SDL_Renderer* renderer);

    /**
     * Charge une image depuis un fichier.
     */
    bool loadFromFile(const std::string& filename, SDL_Renderer* renderer);

    /**
     * Affiche l’image à l’écran.
     */
    void draw(SDL_Renderer* renderer, float x, float y, float w, float h) const;
};