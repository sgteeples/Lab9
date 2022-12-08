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
#define RADIUS 225

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

    intervalTimer_ackInterrupt(INTERVAL_TIMER_0);
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
    //printf("%d\n duckLocation ", duckLocation.x);
    
    if(projectile_is_dead(&projectiles[0]) && (duckLocation.x < 165) && (duckLocation.x > 155)){
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
    for (uint8_t projCounter = 4; projCounter < SETTING_MAX_TOTAL_PROJECTILES; projCounter++) {
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
    for(uint8_t eggCounter = 0; eggCounter < SETTING_MAX_DUCK_EGGS; eggCounter++){
        for(uint8_t projCounter = 4; projCounter < 4 + SETTING_MAX_TOTAL_PROJECTILES;
         projCounter++){
            if(projectile_is_flying(&projectiles[eggCounter]) == false){
                continue;
            }
            if(projectile_is_dead(&projectiles[eggCounter])){
                continue;
            }
                double deltaX = projectiles[eggCounter].x_current - projectiles[projCounter].x_current;
                double deltaY = projectiles[eggCounter].y_current - projectiles[projCounter].y_current;
                double deltaX2 = deltaX * deltaX;
                double deltaY2 = deltaY * deltaY;
                double radius = projectiles[projCounter].radius * projectiles[projCounter].radius;            
                if ((deltaX2 + deltaY2) < radius) {
                    egg_trigger_death(&projectiles[eggCounter]);
      }
         
         
         }
    }
  

//     // Double for loops for collisions
//   for (int16_t i = 4; i < 4+ SETTING_MAX_DUCK_EGGS; ++i) {
//     // total missiles
//     for (int16_t j = 0; j < SETTING_MAX_TOTAL_PROJECTILES; ++j) {
//         if (projectile_is_flying(&projectiles[i]) == false){
//          continue;
//         }
//       // calc the distance
//       double dist = (((projectiles[i].y_current - projectiles[j].y_current) * (projectiles[i].y_current - projectiles[j].y_current)) +
//                     ((projectiles[i].x_current - projectiles[j].x_current) * (projectiles[i].x_current - projectiles[j].x_current)));
//       // if dist < radius then trigger explosion
//       if (dist < RADIUS) {
//         egg_trigger_death(&projectiles[i]);
//       }

//       // get plane point
//       display_point_t duckPoint = duck_getXY();
//       // calc dist
//       dist = (((duckPoint.y - projectiles[j].y_current) * (duckPoint.y - projectiles[j].y_current)) + 
//              ((duckPoint.x - projectiles[j].x_current) * (duckPoint.x - projectiles[j].x_current)));
//       // if smaller than radius then explode
//       if (dist < RADIUS) {
//         duck_die();
//        // duck_init(duck_eggs);
//       }
//     }
//   }

     

}