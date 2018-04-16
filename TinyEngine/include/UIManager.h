#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ResourceManager.h"

/** A manager for UI Rendering */
class UIManager {
public:
	/** Gets the instance of the SFXManager */
	static UIManager& instance() {
		if (uiInstance == nullptr) {
			uiInstance = new UIManager();
			// if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			// {
			// 	SDL_Log("Error opening mixer in SFXManager");
			// }
		}
		return *uiInstance;
	}

	void renderText(SDL_Renderer* gRenderer, std::string text,
		std::string fontStyle, int fontSize,
		SDL_Color color, int x, int y) {

		TTF_Font* font = ResourceManager::instance().getFont(fontStyle, fontSize);
		SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
		SDL_Texture * texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

		SDL_Rect rect = { x, y, texW, texH };

		SDL_RenderCopy(gRenderer, texture, NULL, &rect);

		SDL_FreeSurface(text_surface);
		SDL_DestroyTexture(texture);
	}

	void renderCenteredText(SDL_Renderer* gRenderer, std::string text,
		std::string fontStyle, int fontSize,
		SDL_Color color, int y, int screenWidth) {

		TTF_Font* font = ResourceManager::instance().getFont(fontStyle, fontSize);
		SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
		SDL_Texture * texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH); //textH -> NULL TODO

		int x = (screenWidth - texW) / 2;

		SDL_Rect rect = { x, y, texW, texH };

		SDL_RenderCopy(gRenderer, texture, NULL, &rect);

		SDL_FreeSurface(text_surface);
		SDL_DestroyTexture(texture);
	}

private:
	/** The Private constructor for the SFXManager */
	UIManager() {}
	/** The Private destructor for the SFXManager */
	~UIManager() {}

	/** The current instance of the SFXManager */
	static UIManager* uiInstance;
};

#endif
