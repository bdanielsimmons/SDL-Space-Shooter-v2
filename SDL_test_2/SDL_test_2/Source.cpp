#include <string>
#include <iostream>
#include <SDL.h>
#include <ctime>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Constants.h"
#include "Projectiles.h"
#include "Box.h"
bool running = true;
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
SDL_Event e;


int main(int, char**) {
	int bW, bH, now=0, timePass=0, gap = 10;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Galaga", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture *background = loadTexture("space.bmp", renderer);
	SDL_Texture *image = loadTexture("spaceship.bmp", renderer);
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
	
	Player GUNNER(100,100, image);
		
	while(running){
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_RenderClear(renderer);

		renderTexture(background, renderer, 0, 0);
		auto keys = SDL_GetKeyboardState(NULL);
		now = SDL_GetTicks();
			if (now > timePass + ((rand() % 51)+16)) {
				Enemy::createEnemy(SCREEN_WIDTH, (rand() % (SCREEN_HEIGHT-100)) + 100);
			}
		timePass = now; 
		Enemy::Update();
		Enemy::Draw(renderer);
		GUNNER.Update(keys);
		GUNNER.Draw(renderer);
		Projectile::Draw(renderer);
		Projectile::Update();
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}


SDL_Quit();
	return 0;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	texture = SDL_CreateTextureFromSurface(ren, loadedImage);
	SDL_FreeSurface(loadedImage);
	return texture;
}