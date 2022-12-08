#include "gameControl.h"
#include "display.h"
#include "settings.h"
#include "interrupts.h"
#include "intervalTimer.h"
#include "duck.h"
#include "touchscreen.h"
#include "projectiles.h"
#include <stdio.h>

// Define
#define HALF 2
#define DUCK_X_ADJUSTMENT 10
#define DUCK_Y_ADJUSTMENT 5
#define RADIUS 25

//Declarations
projectile_t projectiles[SETTING_MAX_TOTAL_PROJECTILES];
projectile_t *duck_eggs = &(projectiles[0]);
projectile_t *player_shots = &(projectiles[SETTING_MAX_DUCK_EGGS]);

// Display point for player
display_point_t playerTouch;

// Bool variables
bool firstHalf;
bool projectileFired;


//Draws fortress
void drawFortress(){
    display_fillRect(140,220,40,20,DISPLAY_GRAY);
    display_fillRect(150,200,20,20,DISPLAY_GRAY);
}

void initProjectilesAndDuck(){
     // for loop to initialize missiles
  for (uint16_t i = 0; i < SETTING_MAX_TOTAL_PROJECTILES; i++) {
    projectile_init_dead(&projectiles[i]);
  } 
  duck_init(&projectiles[0]);
  firstHalf = true;
  projectileFired = false;
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
    initProjectilesAndDuck();

}

// Tick the game control logic
//
// This function should tick duckos, projectiles, and more
void gameControl_tick(){
    // Tick duck state machine
    duck_tick();
    // Tick first half of missiles for optimization, then second half
    if(firstHalf){
        for (uint16_t i = 0; i < SETTING_MAX_TOTAL_PROJECTILES / HALF; i++) {
            projectile_tick(&projectiles[i]);
    }
        firstHalf = false;
    }
    else {
        for (uint16_t i = SETTING_MAX_TOTAL_PROJECTILES / HALF;i < SETTING_MAX_TOTAL_PROJECTILES; i++) {
            projectile_tick(&projectiles[i]);
    }
        firstHalf = true;
  }

    // We need to get the duck's location in order to specify when it can drop the egg
    display_point_t duckLocation = duck_getXY();
    printf("%d\n duckLocation ", duckLocation.x);
    if(projectile_is_dead(&projectiles[0]) && (duckLocation.x < 165) && (duckLocation.x > 155) ){
        projectile_init_egg(&projectiles[0], duckLocation.x, duckLocation.y);
        
     }


       // for loop that gets player location and fires
    for (uint16_t i = 4; i < 4 + SETTING_MAX_PLAYER_SHOTS; i++) {
    // checks if screen is touched
        if ((touchscreen_get_status() == TOUCHSCREEN_RELEASED) &&
        (projectile_is_dead(&projectiles[i]))) {
            playerTouch = touchscreen_get_location();
            projectile_init_gun(&projectiles[i], playerTouch.x, playerTouch.y);
            touchscreen_ack_touch();
            
    }
  }
  touchscreen_ack_touch();
    // Have to get the duck location to compare it to the 
    // For loop to see if the gunshot kills the ducks
    for (uint8_t projCounter = 0; projCounter < SETTING_MAX_TOTAL_PROJECTILES; projCounter++) {
    // if statement that checks if the delta's are inside the radius
      double deltaDuckX = (duckLocation.x + DUCK_X_ADJUSTMENT) - projectiles[projCounter].x_current;
      double deltaDuckY = (duckLocation.y + DUCK_Y_ADJUSTMENT) - projectiles[projCounter].y_current;
      double deltaDuckX2 = deltaDuckX * deltaDuckX;
      double deltaDuckY2 = deltaDuckY * deltaDuckY;
      // If statement checks if the plance is within blast radius
      if ((deltaDuckX2 + deltaDuckY2) < RADIUS) {
        duck_die();
      }
    
  }

     

}