#include <stdio.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <unistd.h>
using namespace std;

#if defined(_WIN32) | (_WIN64)
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/Code/images/";
#endif

#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/Code/images/";
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/Code/images/";
#endif

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char* argv[]) {

#if defined(__APPLE__)
	cout << images_dir << endl;
#endif

	// GAME LOOP Variable
	bool inGame = true;

	//SDL Event handler
	SDL_Event event;

	// ******************* Create the SDL Window - START *******************
	// Start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create a SDL Window reference - pointer
	SDL_Window *window = nullptr;

	// Create a SDL RenderTarget - pointer
	SDL_Renderer *renderTarget = nullptr;

	// Create a SDL Window in the middle of the screen
	window = SDL_CreateWindow("Hello World!",
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	// Create an SDL RenderTarget
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// ******************* Create the SDL Window - END *******************

	// ******************* Create the player texture - START ******************

	// Load Room BITMAP to a SDL Texture
	SDL_Texture *player = IMG_LoadTexture(renderTarget,
			(images_dir + "player.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect playerPos;

	// Set the x, y, width and height SDL Rectangle values
	playerPos.x = 100;
	playerPos.y = 100;
	playerPos.w = 42;
	playerPos.h = 42;

	// Set the maximum velocity of the player
	const int PLAYER_VEL = 5;

	// The velocity of the player
	int pVelX = 0;
	int pVelY = 0;

	// ******************* Create the player texture - END *******************

	// ******************* Create the turret texture - START ******************

		// Load Room BITMAP to a SDL Texture
		SDL_Texture *ranged = IMG_LoadTexture(renderTarget,
				(images_dir + "enemyRanged.png").c_str());

		// Create a SDL Rectangle for the roomTexture's position and size
		SDL_Rect ranged0Pos;

		// Set the x, y, width and height SDL Rectangle values
		ranged0Pos.x = 512;
		ranged0Pos.y = 550;
		ranged0Pos.w = 31;
		ranged0Pos.h = 124;

		// ******************* Create the turret texture - END *******************

	// ******************* Create the room (background) texture - START *******************

	// load the surface into the texture
	SDL_Texture *bkgd = IMG_LoadTexture(renderTarget,
			(images_dir + "bkgd1.png").c_str());

	// load the surface into the texture
	SDL_Texture *bkgd1 = IMG_LoadTexture(renderTarget,
			(images_dir + "bkgd2.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect roomPos;
	SDL_Rect roomPos1;
	SDL_Rect roomPos2;
	SDL_Rect roomPos3;
	SDL_Rect roomPos4;

	// Set the x, y, width and height SDL Rectangle values
	roomPos.x = 0;
	roomPos.y = 0;
	roomPos1.x = 1024;
	roomPos1.y = 0;
	roomPos2.x = 2048;
	roomPos2.y = 0;
	roomPos3.x = 2048;
	roomPos3.y = -768;
	roomPos4.x = 2048;
	roomPos4.y = 768;

	// Use SDL_QueryTexture to get the W and H of the player's texture
	int w, h;
	SDL_QueryTexture(bkgd, NULL, NULL, &w, &h);
	roomPos.w = w;
	roomPos.h = h;
	roomPos1.w = w;
	roomPos1.h = h;
	roomPos2.w = w;
	roomPos2.h = h;
	roomPos3.w = w;
	roomPos3.h = h;

	int w1, h1;
	SDL_QueryTexture(bkgd1, NULL, NULL, &w1, &h1);
	roomPos4.w = w1;
	roomPos4.h = h1;

	// ******************* Create the room walls - START *******************
	// Create a SDL Rectangle for the Wall1's position and size
	SDL_Rect Wall1;

	// Set the x, y, width and height SDL Rectangle values
	Wall1.x = 0;
	Wall1.y = -768;
	Wall1.w = 3072;
	Wall1.h = 40;

	// Create a SDL Rectangle for the Wall2's position and size
	SDL_Rect Wall2;

	// Set the x, y, width and height SDL Rectangle values
	Wall2.x = 0;
	Wall2.y = -768;
	Wall2.w = 40;
	Wall2.h = 1536;

	// ******************* Create the room walls - END *******************

	// ******************* Create the Health Bar Background  texture - START *******************

	// load the surface into the texture
	SDL_Texture *healthBKGD = IMG_LoadTexture(renderTarget,
			(images_dir + "healthBack.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect healthBKGDPos;

	// Set the x, y, width and height SDL Rectangle values
	healthBKGDPos.x = 30;
	healthBKGDPos.y = 30;

	int w3, h3;
	SDL_QueryTexture(healthBKGD, NULL, NULL, &w3, &h3);
	healthBKGDPos.w = w3;
	healthBKGDPos.h = h3;

	// ******************* Create the Health Bar Background  texture - END *******************

	// ******************* Create the Health Bar texture - START *******************

	SDL_Texture *healthBar = IMG_LoadTexture(renderTarget,
			(images_dir + "healthBar.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect healthBarPos;

	// Set the x, y, width and height SDL Rectangle values
	healthBarPos.x = 30;
	healthBarPos.y = 30;
	SDL_QueryTexture(healthBKGD, NULL, NULL, &w3, &h3);
	healthBarPos.w = w3;
	healthBarPos.h = h3;

	// ******************* Create the Health Bar texture - END *******************

	// ******************* Create the Health Bar Front texture - START *******************
	SDL_Texture *healthFront = IMG_LoadTexture(renderTarget,
			(images_dir + "healthFront.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect healthFrontPos;

	// Set the x, y, width and height SDL Rectangle values
	healthFrontPos.x = 30;
	healthFrontPos.y = 30;
	SDL_QueryTexture(healthBKGD, NULL, NULL, &w3, &h3);
	healthFrontPos.w = w3;
	healthFrontPos.h = h3;

	// ******************* Create the Health Bar Front texture - END *******************

	// ******************* Create the HUD Frame texture - START *******************

	SDL_Texture *hudFrame = IMG_LoadTexture(renderTarget,
			(images_dir + "HUDFrame.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect hudFramePos;

	// Set the x, y, width and height SDL Rectangle values
	hudFramePos.x = 685;
	hudFramePos.y = 30;
	SDL_QueryTexture(hudFrame, NULL, NULL, &w3, &h3);
	hudFramePos.w = w3;
	hudFramePos.h = h3;
	// ******************* Create the HUD Frame texture - END *******************

	// ******************* Create the HUD Frame texture - START *******************
	SDL_Texture *hudKey1 = IMG_LoadTexture(renderTarget,
			(images_dir + "HUDkey1.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect hudKey1Pos;

	// Set the x, y, width and height SDL Rectangle values
	hudKey1Pos.x = 685;
	hudKey1Pos.y = 30;
	SDL_QueryTexture(hudKey1, NULL, NULL, &w3, &h3);
	hudKey1Pos.w = w3;
	hudKey1Pos.h = h3;
	// ******************* Create the HUD Frame texture - END *******************

	// ******************* Create the HUD Frame texture - START *******************
	SDL_Texture *hudKey2 = IMG_LoadTexture(renderTarget,
			(images_dir + "HUDkey2.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect hudKey2Pos;

	// Set the x, y, width and height SDL Rectangle values
	hudKey2Pos.x = 685;
	hudKey2Pos.y = 30;
	SDL_QueryTexture(hudKey1, NULL, NULL, &w3, &h3);
	hudKey2Pos.w = w3;
	hudKey2Pos.h = h3;
	// ******************* Create the HUD Frame texture - END *******************

	// ******************* Create the HUD Frame texture - START *******************
	SDL_Texture *hudKey3 = IMG_LoadTexture(renderTarget,
			(images_dir + "HUDkey3.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect hudKey3Pos;

	// Set the x, y, width and height SDL Rectangle values
	hudKey3Pos.x = 685;
	hudKey3Pos.y = 30;
	SDL_QueryTexture(hudKey1, NULL, NULL, &w3, &h3);
	hudKey3Pos.w = w3;
	hudKey3Pos.h = h3;
	// ******************* Create the HUD Frame texture - END *******************

	// ******************* Create the HUD Frame texture - START *******************
	SDL_Texture *daggerIcon = IMG_LoadTexture(renderTarget,
			(images_dir + "daggerIcon.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect daggerIconPos;

	// Set the x, y, width and height SDL Rectangle values
	daggerIconPos.x = 30;
	daggerIconPos.y = 565;
	SDL_QueryTexture(daggerIcon, NULL, NULL, &w3, &h3);
	daggerIconPos.w = w3;
	daggerIconPos.h = h3;
	// ******************* Create the HUD Frame texture - END *******************

	// ******************* Create the HUD Frame texture - START *******************
	SDL_Texture *ammoBar = IMG_LoadTexture(renderTarget,
			(images_dir + "ammoBar.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect ammoBarPos;

	// Set the x, y, width and height SDL Rectangle values
	ammoBarPos.x = 100;
	ammoBarPos.y = 565;
	SDL_QueryTexture(ammoBar, NULL, NULL, &w3, &h3);
	ammoBarPos.w = w3;
	ammoBarPos.h = h3;
	// ******************* Create the HUD Frame texture - END *******************

	// ******************* Create the HUD Frame texture - START *******************
	SDL_Texture *ammoFrame = IMG_LoadTexture(renderTarget,
			(images_dir + "ammoFrame.png").c_str());

	// Create a SDL Rectangle for the roomTexture's position and size
	SDL_Rect ammoFramePos;

	// Set the x, y, width and height SDL Rectangle values
	ammoFramePos.x = 100;
	ammoFramePos.y = 565;
	SDL_QueryTexture(ammoFrame, NULL, NULL, &w3, &h3);
	ammoFramePos.w = w3;
	ammoFramePos.h = h3;
	// ******************* Create the HUD Frame texture - END *******************

	// ******************* GAME LOOP - START *******************

	// While the loop is running
	while (inGame) {

		// ******************* INPUT - START *******************
		// Check for Keyboard Input using SDL_Event event
		while (SDL_PollEvent(&event) != 0) {

			//Player wants to quit
			if (event.type == SDL_QUIT) {
				inGame = false;
			} else {
				//Player wants to move
				//Check if a key was pressed
				if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {

					//Adjust the velocity based on which key was pressed
					switch (event.key.keysym.sym) {

					case SDLK_UP:
						pVelY -= PLAYER_VEL;
						break;
					case SDLK_DOWN:
						pVelY += PLAYER_VEL;
						break;
					case SDLK_LEFT:
						pVelX -= PLAYER_VEL;
						break;
					case SDLK_RIGHT:
						pVelX += PLAYER_VEL;
						break;

					}
				} //Check if a key was released
				else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
					//Adjust the player's velocity
					switch (event.key.keysym.sym) {

					case SDLK_UP:
						pVelY += PLAYER_VEL;
						break;
					case SDLK_DOWN:
						pVelY -= PLAYER_VEL;
						break;
					case SDLK_LEFT:
						pVelX += PLAYER_VEL;
						break;
					case SDLK_RIGHT:
						pVelX -= PLAYER_VEL;
						break;
					}

				}
			}
		}
		// ******************* INPUT -END *******************

		// ******************* UPDATE Player - START *******************

		//Move the player left or right
		playerPos.x += pVelX;

		if (playerPos.x > (1024 - (playerPos.w * 2))) {

			playerPos.x = 1024 - (playerPos.w * 2);

			roomPos.x -= pVelX;
			roomPos1.x -= pVelX;
			roomPos2.x -= pVelX;
			roomPos3.x -= pVelX;
			roomPos4.x -= pVelX;
			ranged0Pos.x -= pVelX;
//			Wall1.x -= pVelX;
//			Wall2.x -= pVelX;

		}

		if (playerPos.x < (0 + (playerPos.w * 2))) {

			playerPos.x = 0 + (playerPos.w * 2);

			roomPos.x -= pVelX;
			roomPos1.x -= pVelX;
			roomPos2.x -= pVelX;
			roomPos3.x -= pVelX;
			roomPos4.x -= pVelX;
			ranged0Pos.x -= pVelX;
//			Wall1.x -= pVelX;
//			Wall2.x -= pVelX;

		}

		// Check for wall collisions - left or right
//		if (SDL_HasIntersection(&playerPos, &Wall1)
//				|| SDL_HasIntersection(&playerPos, &Wall2)) {
//
//			//Move back
//			playerPos.x -= pVelX;
//		}
		//Move the player up or down
		playerPos.y += pVelY;

		if (playerPos.y < (0 + (playerPos.h * 2))) {

			playerPos.y = (0 + (playerPos.h * 2));

			roomPos.y -= pVelY;
			roomPos1.y -= pVelY;
			roomPos2.y -= pVelY;
			roomPos3.y -= pVelY;
			roomPos4.y -= pVelY;
			ranged0Pos.y -= pVelY;
//			Wall1.y -= pVelY;
//			Wall2.y -= pVelY;

		}

		if (playerPos.y > (768 - (playerPos.h * 2))) {

			playerPos.y = 768 - (playerPos.h * 2);

			roomPos.y -= pVelY;
			roomPos1.y -= pVelY;
			roomPos2.y -= pVelY;
			roomPos3.y -= pVelY;
			roomPos4.y -= pVelY;
			ranged0Pos.y -= pVelY;
//			Wall1.y -= pVelY;
//			Wall2.y -= pVelY;

		}

		// Check for wall collisions - left or right
//		if (SDL_HasIntersection(&playerPos, &Wall1)
//				|| SDL_HasIntersection(&playerPos, &Wall2)) {
//
//			//Move back
//			playerPos.y -= pVelY;
//		}

		// ******************* UPDATE Player - END *******************

		// ******************* Start the SDL Draw Process *******************

		// Clear the SDL RenderTarget
		SDL_RenderClear(renderTarget);

		// Copy the roomTexture to the RenderTarget using the roomPos to place it in position
		SDL_RenderCopy(renderTarget, bkgd, NULL, &roomPos);
		SDL_RenderCopy(renderTarget, bkgd, NULL, &roomPos1);
		SDL_RenderCopy(renderTarget, bkgd, NULL, &roomPos2);
		SDL_RenderCopy(renderTarget, bkgd, NULL, &roomPos3);
		SDL_RenderCopy(renderTarget, bkgd1, NULL, &roomPos4);

		// Copy the roomTexture to the RenderTarget using the roomPos to place it in position
		SDL_RenderCopy(renderTarget, player, NULL, &playerPos);

		// Copy the roomTexture to the RenderTarget using the roomPos to place it in position
		SDL_RenderCopy(renderTarget, ranged, NULL, &ranged0Pos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, healthBKGD, NULL, &healthBKGDPos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, healthBar, NULL, &healthBarPos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, healthFront, NULL, &healthFrontPos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, hudFrame, NULL, &hudFramePos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, hudKey1, NULL, &hudKey1Pos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, hudKey2, NULL, &hudKey2Pos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, hudKey3, NULL, &hudKey3Pos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, daggerIcon, NULL, &daggerIconPos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, ammoBar, NULL, &ammoBarPos);

		// Copy the healthBKGD to the RenderTarget using the healthBKGDPos to place it in position
		//SDL_RenderCopy(renderTarget, ammoFrame, NULL, &ammoFramePos);

		// Draw "Present" the SDL RenderTarget to the user
		SDL_RenderPresent(renderTarget);

		// ******************* End the SDL Draw Process *******************

		// Delay so that we are at 60 FPS
		SDL_Delay(16);

	}

	// ******************* GAME LOOP - END *******************

	// Cleanup and Quit
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
