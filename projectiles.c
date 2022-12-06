#include "projectiles.h"
#include "settings.h"
#include "display.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

//Declarations
#define DEAD_COORDINATE_X 0
#define DEAD_COORDINATE_Y 0
#define SQUARED 2
#define SPEED_MULTIPLIER 2
double percentage = 0;
// Helper function
void init_helper(projectile_t *projectile);

// Enum for our state machine
enum projectileState_t {INIT, MOVING, DEAD};
static enum projectileState_t currentState;

// Initializes projectiles as dead
void projectile_init_dead(projectile_t *projectile) { 
  // function takes a pointer to a projectile, no return makes sure it is dead
  projectile->x_origin = DEAD_COORDINATE_X;
  projectile->y_origin = DEAD_COORDINATE_Y;
  projectile->x_current = DEAD_COORDINATE_X;
  projectile->y_current = DEAD_COORDINATE_Y;
  init_helper(projectile);
  projectile->currentState = DEAD;
  projectile->radius = 15.0;
}
// Initialize the fortress' gun
void projectile_init_gun(projectile_t *projectile, uint16_t x_dest, uint16_t y_dest){
  projectile->type = PROJECTILE_TYPE_GUN;
  projectile->x_origin = 160;
  projectile->y_origin = 200;
  projectile->currentState = INIT;
  projectile->y_dest = y_dest;
  projectile->x_dest = x_dest;
  projectile->radius = 15.0;
  init_helper(projectile);
}
void projectile_init_egg(projectile_t *projectile, int16_t duck_x, int16_t duck_y){
  projectile->type = PROJECTILE_TYPE_GUN;
  projectile->y_dest = 200;
  projectile->x_dest = DISPLAY_WIDTH / 2;
  projectile->y_origin = duck_y;
  projectile->x_origin = duck_x;
  projectile->currentState = INIT;
  init_helper(projectile);

}

////////// State Machine TICK Function //////////
void projectile_tick(projectile_t *projectile){
  switch(projectile->currentState){
    case INIT:
    projectile->currentState = MOVING;
    break;
    case MOVING:
    if(projectile->length > projectile->total_length){
      projectile->currentState = DEAD;
      projectile->die_me = true;
      display_drawLine(projectile->x_origin, projectile->y_origin, projectile->x_current, projectile->y_current, DISPLAY_BLACK);
      display_drawLine(projectile->x_origin, projectile->y_origin, projectile->x_dest, projectile->y_dest, DISPLAY_BLACK);
    }
    else if(((projectile->type == PROJECTILE_TYPE_GUN) && (projectile->length >= projectile->total_length)) || (projectile->die_me == true)){
      projectile->die_me = true;
      display_drawLine(projectile->x_origin, projectile->y_origin, projectile->x_current, projectile->y_current, DISPLAY_BLACK);
      projectile->x_current = projectile->x_dest;
      projectile->y_current = projectile->y_dest;
      display_drawLine(projectile->x_origin, projectile->y_origin, projectile->x_dest, projectile->y_dest, DISPLAY_BLACK);
    }
    else{
      projectile->currentState = MOVING;
    }
    break;
    case DEAD:
    break;
    default:
    printf("YOU GOOFED, in the default case for the switch \n");
    break;

  }
  switch(projectile->currentState){
    case INIT:
    break;
    case MOVING:
    // This is the case if the projectile is the player's
    if (projectile->type == PROJECTILE_TYPE_GUN) {
      display_drawLine(projectile->x_origin, projectile->y_origin, projectile->x_current,projectile->y_current, DISPLAY_BLACK);
      percentage = projectile->length / projectile->total_length;
      projectile->length = (SETTING_PLAYER_SHOT_DISTANCE_PER_TICK * SPEED_MULTIPLIER) + projectile->length;
      projectile->x_current = projectile->x_origin + percentage * (projectile->x_dest - projectile->x_origin);
      projectile->y_current = projectile->y_origin + percentage * (projectile->y_dest - projectile->y_origin);
      display_drawLine(projectile->x_origin, projectile->y_origin, projectile->x_current,projectile->y_current, DISPLAY_YELLOW);

    }
    else if (projectile->type == PROJECTILE_TYPE_EGG) {
      display_drawLine(projectile->x_origin, projectile->y_origin, projectile->x_current, projectile->y_current, DISPLAY_BLACK);
      percentage = projectile->length / projectile->total_length;
      projectile->length = (SETTING_DUCK_EGG_DISTANCE_PER_TICK * SPEED_MULTIPLIER) + projectile->length;
      projectile->x_current = projectile->x_origin + percentage * (projectile->x_dest - projectile->x_origin);
      projectile->y_current = projectile->y_origin + percentage * (projectile->y_dest - projectile->y_origin);
      display_drawLine(projectile->x_origin, projectile->y_origin, projectile->x_current, projectile->y_current, DISPLAY_DARK_BLUE);
    }

    break;
    case DEAD:


    break;
    default:
    printf("YOU GOOFED, in the default case for the switch \n");
  }
}
// Return whether the given projectile is dead.
bool projectile_is_dead(projectile_t *projectile){
  // Need to check what state in the state machine we're in
  if (projectile->currentState == DEAD) {
    return true;
  }
  // not true
  else {
    return false;
  }
    return false;
  }   



// This function takes in a missle and it sets the values that were not set
void init_helper(projectile_t *projectile) {
    projectile->x_current = projectile->x_origin;
    projectile->y_current = projectile->y_origin;
    projectile->radius = 15;
    projectile->length = 0.0;
    projectile->die_me = false;
    projectile->egged = false;
    projectile->total_length = sqrt(pow((projectile->y_dest - projectile->y_origin), SQUARED) +
    pow((projectile->x_dest - projectile->x_origin), SQUARED));
}
