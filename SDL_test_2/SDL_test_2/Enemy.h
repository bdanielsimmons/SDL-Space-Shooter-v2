#pragma once
#include "Constants.h"
#include "Player.h"
#include "Projectiles.h"
#include <SDL.h>
#include <vector>
#include "Box.h"
int ran = SDL_GetTicks();

class Enemy{
private:
	static std::vector<Enemy> Enemies;
	int x, y, w, h;
public:
	Enemy(int x, int y, int w = ENEMY_W, int h = ENEMY_H) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	static void createEnemy(int, int, int, int);
	static void Draw(SDL_Renderer*);
	static void Update();
	
};

std::vector<Enemy> Enemy::Enemies;

void Enemy::createEnemy(int x, int y, int w = ENEMY_W, int h = ENEMY_H) {
	Enemies.push_back(Enemy(x, y, w, h));
}

void Enemy::Draw(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, (rand() % 256), (rand() % 256), (rand() % 256), 255);
	for (Enemy &p : Enemies) {
		SDL_Rect recta;
		recta.x = p.x;
		recta.y = p.y;
		recta.w = p.w;
		recta.h = p.h;
		SDL_RenderFillRect(ren, &recta);
	}
}

void Enemy::Update() {
	std::vector<Enemy>present;
	for (Enemy &a : Enemies) {
		a.x += ENEMY_S;
		bool c = false;
		for (Projectile &p : Projectile::Bullets) {
			c = c || (CheckCollision(a.x, a.y, a.w, a.h, p.x, p.y, p.w, p.h));
			if (c) {
				Projectile::Bullets.pop_back();
				break;
			}
		}
		if (a.x + a.w > 0 && !c) {
			present.push_back(a);
		}
		break;
	}
	Enemies = present;
}
