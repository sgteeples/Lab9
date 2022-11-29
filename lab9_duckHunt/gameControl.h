#ifndef GAMECONTROL
#define GAMECONTROL

#include <stdbool.h>

// Initialize the game control logic
// This function will initialize los ducks, projectiles, and more
void gameControl_init();

// Tick the game control logic
//
// This function should tick duckos, projectiles, and more
void gameControl_tick();

#endif /* GAMECONTROL */
