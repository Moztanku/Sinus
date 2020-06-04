#include<SDL.h>
#include<iostream>
#include<cmath>
#define pi 3.14159265359
#define RtP(X) ((X*pi)/180)
#define _wWidth 1600
#define _wHeight 900

inline void drawLine(SDL_Renderer* _renderer,SDL_Point P1, SDL_Point P2) {
	SDL_RenderDrawLine(_renderer, P1.x, P1.y, P2.x, P2.y);
};
void drawAxes(int, int,SDL_Renderer*);

int main(int argc, char *argv[]) {
	// Variables
	bool nend = true;
	int AxisX = 5;	int aCellX = 0;
	int AxisY = 5; int aCellY = 0;
	double _sum = 0;
	// SDL Initiation
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* _window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,_wWidth,_wHeight,0);
	SDL_Renderer* _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event _event;
	// Background
	SDL_SetRenderDrawColor(_renderer,0xE0,0xE5,0xF5,0xFF);
	SDL_RenderClear(_renderer);
	// Points
	SDL_Point Pt1{ 0,_wHeight / 2 };
	SDL_Point Pt2{ 1,_wHeight / 2 };
	// Drawing Function
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0x55, 0x55, 0xFF);
	for (int i = 1 - (_wWidth / 2); i < (_wWidth / 2) + 1; i++) {
		Pt1.y = (_wHeight / 2) - sin(RtP(i)) * 100;
		Pt2.y = (_wHeight / 2) - sin(RtP(i)) * 100;
		Pt1.x++; Pt2.x++;
		drawLine(_renderer, Pt1, Pt2);
	}
	// Drawing Axes
	drawAxes(AxisX, AxisY, _renderer);
	// Presenting Drawing
	SDL_RenderPresent(_renderer);
	while (nend) {
		SDL_PollEvent(&_event);
		switch (_event.type) {
		case SDL_QUIT:
			nend = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			aCellX = (_event.motion.x - _wWidth / 2) / AxisX;
			if (_event.motion.x < _wWidth / 2) aCellX -= 1;
			aCellY = (_event.motion.y - _wHeight / 2) / AxisY;
			if (_event.motion.y < _wHeight / 2) aCellY -= 1;
			_sum = 0;
			for (int n = AxisX * aCellX; n <= AxisX * (aCellX+1); n++) {
				_sum += sin(RtP(n));
				std::cout << n << std::endl;
			}
			std::cout << "X - " << aCellX << " | Y - " << aCellY << " | _sum - " << _sum << std::endl;
			_sum = 0;
			std::cout << _sum << std::endl;
			SDL_Delay(100);
			break;
		}
	}
	SDL_Quit();
	return 0;
}

void drawAxes(int sX, int sY, SDL_Renderer* _renderer) {
	SDL_SetRenderDrawColor(_renderer, 0x55, 0x55, 0x55, 0xFF);
	drawLine(_renderer, { 0,_wHeight / 2 }, { _wWidth,_wHeight / 2 });
	drawLine(_renderer, { _wWidth / 2,0 }, { _wWidth / 2,_wHeight });
	for (int i = 0; i < _wWidth/2; i+=sX)
			drawLine(_renderer, { i+_wWidth/2,_wHeight / 2 + 100 }, { i + _wWidth / 2,_wHeight / 2 -100 });
	for (int i = _wWidth / 2; i > 0; i-=sX)
		drawLine(_renderer, { i,_wHeight / 2 + 100 }, { i,_wHeight / 2 - 100 });
	for (int i = _wHeight / 2 - 100; i < _wHeight / 2 + 101; i += sY)
		drawLine(_renderer, { 0,i }, { _wWidth,i });
}
