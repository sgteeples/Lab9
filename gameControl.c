#include "gameControl.h"
#include "display.h"
#include "settings.h"

//Declarations
// missile_t missiles[CONFIG_MAX_TOTAL_MISSILES];
// missile_t *duck_eggs = &(missiles[0]);
// missile_t *player_shots = &(missiles[CONFIG_MAX_ENEMY_MISSILES + CONFIG_MAX_PLANE_MISSILES]);

//Draws fortress
void drawFortress(){
    display_fillRect(140,220,40,20,DISPLAY_GRAY);
    display_fillRect(150,200,20,20,DISPLAY_GRAY);
}
// Initialize the game control logic
// This function will initialize los ducks, projectiles, and more
void gameControl_init(){
// Draw the fortress that shoots the ducks
    display_fillScreen(DISPLAY_CYAN);
    drawFortress();

}

// Tick the game control logic
//
// This function should tick duckos, projectiles, and more
void gameControl_tick(){

}