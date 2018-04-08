#ifndef RESOURCEMANGER_H
#define RESOURCEMANGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

/** A ResourceManager singleton class */
class ResourceManager {
public:
	/** Returns the instance of the ResourceManager */
    static ResourceManager& instance() {
        if (inst_ == NULL) {
			inst_ = new ResourceManager();
		}
        return *inst_;
    }

	/** Get the dimensions (width, height) of a given resource's Surface. */
	SDL_Point getIMGDimensions(/** The string pointing to the surface */ std::string resource) {
		SDL_Surface* surface = IMG_Load(resource.c_str());

		if (surface == NULL) {
			SDL_Log("Failed to allocate surface");
		}

		SDL_Point dimensions = { surface->w, surface->h };
		return dimensions;
	}

	/** Returns a SDL_Texture that is scaled to the width and height from the given surface. */
	SDL_Texture* getScaledTexture(SDL_Renderer* ren, std::string resource, Uint16 width, Uint16 height) {
		std::string sized_resource = resource + std::to_string(width) + std::to_string(height);
		if (textures_.count(sized_resource) > 0) {
			return textures_[sized_resource];
		}

		SDL_Surface* sprite = IMG_Load(resource.c_str());

		if (sprite == NULL) {
			SDL_Log("Failed to allocate surface");
		}
		else {
			SDL_Log("Allocated surface successfully");

			SDL_Surface* scaled = SDL_CreateRGBSurface(sprite->flags, width, height, sprite->format->BitsPerPixel,
				sprite->format->Rmask, sprite->format->Gmask, sprite->format->Bmask, sprite->format->Amask);

			SDL_Rect src = { 0, 0, sprite->w, sprite->h };
			SDL_Rect dst = { 0, 0, width, height };
			SDL_BlitScaled(sprite, &src, scaled, &dst);

			SDL_Texture* scaledTexture = SDL_CreateTextureFromSurface(ren, scaled);
			textures_.insert(std::pair<std::string, SDL_Texture*>(sized_resource, scaledTexture));
			SDL_FreeSurface(sprite);
			SDL_FreeSurface(scaled);
			return scaledTexture;
		}
		return NULL;
	}

	/** Returns a SDL_Texture.
		Any source with pure green (0, 255, 0) will have those pixels rendered transparently as if on a green screen. */
    SDL_Texture* getTexture(/** The string pointing to the resource */std::string resource,
		/** The SDL_Renderer to render the Texture with */ SDL_Renderer* ren) {
        if (textures_.count(resource) > 0) {
            return textures_[resource];
        }

        SDL_Surface* spriteSheet = IMG_Load(resource.c_str());

        if (spriteSheet==NULL){
            SDL_Log("Failed to allocate surface");
        } else {
            SDL_Log("Allocating memory for texture");
		    // Create a texture from our surface
            // Textures run faster and take advantage of hardware acceleration
			SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 255, 0));
            SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
            textures_.insert(std::pair<std::string, SDL_Texture*>(resource, texture));
            SDL_FreeSurface(spriteSheet);
            return texture;
        }

        return NULL;
    }

	/** Returns the true-type font at the given path */
	TTF_Font* getFont(/** The resource path */ std::string resource,
		/** The size of the font */ int size) {
		if (fonts_.count(resource) > 0) {
			return fonts_[resource];
		}

		TTF_Font* font = TTF_OpenFont(resource.c_str(), size);

		if (font == NULL) {
			SDL_Log("Failed to allocate font");
		}
		else {
			SDL_Log("Allocating font");
			fonts_.insert(std::pair<std::string, TTF_Font*>(resource, font));
			return font;
		}

		return NULL;
	}

	/** Returns a Mix_Music loaded using the given path */
	Mix_Music* getMusic(/** The path for the music */ std::string resource) {
		if (music_.count(resource) > 0) {
			return music_[resource];
		}

		Mix_Music* music = Mix_LoadMUS(resource.c_str());

		if (music == NULL) {
			SDL_Log("Failed to allocate music");
		}
		else {
			SDL_Log("Allocating music");
			music_.insert(std::pair<std::string, Mix_Music*>(resource, music));
			return music;
		}

		return NULL;
	}

	/** Returns a playable sound chunk from the given resource path */
	Mix_Chunk* getSFX(/** The resource path */std::string resource) {
		if (sounds_.count(resource) > 0) {
			return sounds_[resource];
		}

		Mix_Chunk* sfx = Mix_LoadWAV(resource.c_str());

		if (sfx == NULL) {
			SDL_Log("Failed to allocate sfx");
		}
		else {
			SDL_Log("Allocating sfx");
			sounds_.insert(std::pair<std::string, Mix_Chunk*>(resource, sfx));
			return sfx;
		}

		return NULL;
	}

    static void reset() {
        delete inst_;
        inst_ = NULL;
    }

private:
	/** Private constructor */
    ResourceManager() {}

	/** Private destructor */
    ~ResourceManager() {
        for (auto it=textures_.begin(); it!=textures_.end(); ++it) {
            SDL_DestroyTexture(it->second);
            //SDL_Log("Freed Texture: %s", it->first);
        }

		for (auto it = music_.begin(); it != music_.end(); ++it) {
			Mix_FreeMusic(it->second);
			//SDL_Log("Freed Music: %s", it->first);
		}

		for (auto it = sounds_.begin(); it != sounds_.end(); ++it) {
			Mix_FreeChunk(it->second);
			//SDL_Log("Freed SFX: %s", it->first);
		}

		for (auto it = fonts_.begin(); it != fonts_.end(); ++it) {
			TTF_CloseFont(it->second);
			//SDL_Log("Freed Font: %s", it->first);
		}
    }

	/** The singleton instance */
	static ResourceManager* inst_;

	/** Mapping of cached SDL_Textures */
    std::map<std::string, SDL_Texture*> textures_;
	/** Mapping of cached Mix_Music */
	std::map<std::string, Mix_Music*> music_;
	/** Mapping of cached Mix_Chunk */
	std::map<std::string, Mix_Chunk*> sounds_;
	/** Mapping of cached TTF_Font */
	std::map<std::string, TTF_Font*> fonts_;
};

#endif
