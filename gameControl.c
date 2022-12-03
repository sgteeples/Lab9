#include "gameControl.h"
#include "display.h"
#include "settings.h"
#include "interrupts.h"
#include "intervalTimer.h"
#include "duck.h"
#include "touchscreen.h"
#include "projectiles.h"
#include <stdio.h>

//Declarations
projectile_t projectiles[SETTING_MAX_TOTAL_PROJECTILES];
projectile_t *duck_eggs = &(projectiles[0]);
projectile_t *player_shots = &(projectiles[SETTING_MAX_DUCK_EGGS]);

//Draws fortress
void drawFortress(){
    display_fillRect(140,220,40,20,DISPLAY_GRAY);
    display_fillRect(150,200,20,20,DISPLAY_GRAY);
}

void drawHealthBar(uint16_t lives){
    display_drawRect(240,20,62,20,DISPLAY_BLACK);
    if(lives >= 3){
        display_fillRect(241,21,60,18,DISPLAY_GREEN);
    }
    if(lives == 2) {
        display_fillRect(241,21,40,18,DISPLAY_GREEN);
    }
    if(lives == 1) {
        display_fillRect(241,21,20,18,DISPLAY_GREEN);
    }
    if(lives == 0){
       display_setCursor(65, 110);
       display_setTextColor(DISPLAY_RED);
       display_setTextSize(3);
       display_print("GAME OVER!!!");
    }
}
   
// Initialize the game control logic
// This function will initialize los ducks, projectiles, and more
void gameControl_init(){
// Draw the fortress that shoots the ducks
    display_fillScreen(DISPLAY_CYAN);
    drawFortress();
    drawHealthBar(3);

}

// Tick the game control logic
//
// This function should tick duckos, projectiles, and more
void gameControl_tick(){
    
}