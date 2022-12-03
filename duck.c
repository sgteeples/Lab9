#include <stdio.h>
#include "duck.h"
#include "display.h"
#include "settings.h"

#define LEFT 0
#define TRIANGLE_SIZE 10

// State machine enum
static enum duck_st_t { MOVING_ST, DEAD_ST } DUMMY;

static duck_t myDuck;

//init ducks
void duck_init(projectile_t *egg){
  // set x and y origins
  myDuck.x_origin = DISPLAY_WIDTH;
  myDuck.y_origin = (rand() % 120) + 60;
  // set x and y currents
  myDuck.x_current = myDuck.x_origin;
  myDuck.y_current = myDuck.y_origin;
  // set x and y dest
  myDuck.x_dest = LEFT;
  myDuck.y_dest = (rand() % 120)+ 60;
  // set missile and state

  myDuck.egg = *egg;

  myDuck.currentState = MOVING_ST;
}

// State machine tick function
void duck_tick(){
  // Transitions
  switch (myDuck.currentState) {
  case MOVING_ST:
    // draw duck
    if (myDuck.duck_die || (myDuck.x_current <= myDuck.x_dest)) {
      display_fillTriangle(myDuck.x_current + TRIANGLE_SIZE,
                           myDuck.y_current + TRIANGLE_SIZE,
                           myDuck.x_current - TRIANGLE_SIZE, myDuck.y_current,
                           myDuck.x_current + TRIANGLE_SIZE,
                           myDuck.y_current - TRIANGLE_SIZE, DISPLAY_CYAN);
      // update state
      myDuck.currentState = DEAD_ST;
    }
    break;
  case DEAD_ST:
    // update state
    myDuck.currentState = MOVING_ST;
    break;
  default:
    // Error Message
    printf("Transition State Problem");
    break;
  }

  // State action
  switch (myDuck.currentState) {
  case MOVING_ST:
    // draw cyan plane
    display_fillTriangle(myDuck.x_current + TRIANGLE_SIZE,
                         myDuck.y_current + TRIANGLE_SIZE,
                         myDuck.x_current - TRIANGLE_SIZE, myDuck.y_current,
                         myDuck.x_current + TRIANGLE_SIZE,
                         myDuck.y_current - TRIANGLE_SIZE, DISPLAY_CYAN);
    // update plane drawing
    if (myDuck.x_current > myDuck.x_dest) {
      myDuck.x_current -= SETTING_DUCK_DISTANCE_PER_TICK;
      // draw the plane again
      display_fillTriangle(myDuck.x_current + TRIANGLE_SIZE,
                           myDuck.y_current + TRIANGLE_SIZE,
                           myDuck.x_current - TRIANGLE_SIZE, myDuck.y_current,
                           myDuck.x_current + TRIANGLE_SIZE,
                           myDuck.y_current - TRIANGLE_SIZE, DISPLAY_WHITE);
    }
    break;
  // Dead state
  case DEAD_ST:
    duck_init(&myDuck.egg);
    break;
  default:
    // Error Message
    printf("Action State Problem");
    break;
  }
}

// Trigger the duck to la muerte
void duck_die(){
    // update state
  myDuck.currentState = DEAD_ST;
  // draw plane in black
  display_fillTriangle(myDuck.x_current + TRIANGLE_SIZE,
                       myDuck.y_current + TRIANGLE_SIZE,
                       myDuck.x_current - TRIANGLE_SIZE, myDuck.y_current,
                       myDuck.x_current + TRIANGLE_SIZE,
                       myDuck.y_current - TRIANGLE_SIZE, DISPLAY_CYAN);
}

// Get the XY location of the duck
display_point_t duck_getXY(){
    // create planepoint
  display_point_t duckPoint;
  // set x and y
  duckPoint.x = myDuck.x_current;
  duckPoint.y = myDuck.y_current;
  return duckPoint;

}