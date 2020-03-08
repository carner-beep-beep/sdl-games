#include "game.h"
#include <stdbool.h>

void run_game(){
	SDL_Window* window = SDL_CreateWindow("Hello SDL2",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			800,
			600,
			SDL_WINDOW_OPENGL);

	SDL_Renderer* renderer = SDL_CreateRenderer(window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Vec2 paddle_pos = { 100.0, 300.0 };
	int paddle_width = 20;
	int paddle_height = 50;
	int moving = 0;
	bool running = true;
	SDL_Rect paddle_rect = { paddle_pos.x, paddle_pos.y, paddle_width,
		paddle_height };

	Vec2 ball_pos = { 400.0, 300.0 };
	Vec2 ball_vel = { 10.0, 10.0 };
	SDL_Rect ball_rect = { ball_pos.x, ball_pos.y, 20, 20};

	Uint32 tick_count = 0;
	SDL_Event event;

	while(running){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				running = false;
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if(state[SDL_SCANCODE_ESCAPE]){
			running = false;
		}
		
		float delta_time = (SDL_GetTicks() - tick_count) / 1000.0f;

		if(delta_time > 0.05f)
			delta_time = 0.05f;

		// Update
		moving = 0;
		if(state[SDL_SCANCODE_W]){
			moving = -1;
		}else if(state[SDL_SCANCODE_S]){
			moving = 1;
		}

		if(moving != 0){
			paddle_pos.y += moving * 300.0f * delta_time;
		}

		if(paddle_pos.y < 0){
			paddle_pos.y = 0;
		}else if(paddle_pos.y + paddle_height > 600){
			paddle_pos.y = 600 - paddle_height;
		}

		ball_pos.x += ball_vel.x * delta_time;
		ball_pos.y += ball_vel.y * delta_time;

		if(ball_pos.x < 0){
			ball_pos.x = 0;
			ball_vel.x = ball_vel.x * -1;
		}else if(ball_pos.x + 20 > 800){
			ball_pos.x = 800 - 20;
			ball_vel.x = ball_vel.x * -1;
		}

		if(ball_pos.y < 0){
			ball_pos.y = 0;
			ball_vel.y *= -1;
		}else if(ball_pos.y + 20 > 600){
			ball_pos.y = 600 - 20;
			ball_vel.y *= -1;
		}

		ball_rect.x = ball_pos.x;
		ball_rect.y = ball_pos.y;
		
		paddle_rect.y = paddle_pos.y;
		// Draw

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &paddle_rect);

		SDL_RenderFillRect(renderer, &ball_rect);

		SDL_RenderPresent(renderer);
	}
}
