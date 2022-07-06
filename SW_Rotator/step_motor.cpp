#include "step_motor.h"

int step_motor::get_deg() {
  return (int) this->current;
}

void step_motor::set_target(int deg) {
  this->target = (deg + this->offset > this->max_deg) ? this->max_deg : deg + this->offset;
}

bool step_motor::step() {
  if (abs(this->current - this->target) > DEG_TOLERANCE) {

     float steps = abs(this->current - this->target) / this->step2deg;
    
     if (this->current < this->target) {
        if (this->current >= this->max_deg) return false; 
        
        this->motor_down(steps);
        this->current += steps * this->step2deg;
      } else {
        if (this->current <= 0) return false;
          
        this->motor_up(steps);
        this->current -= steps * this->step2deg;
      }

      return true;
   }

   return false;
}
  
void step_motor::motor_down(float steps) {
  this->stepper.setCurrentPosition(0);
  this->stepper.setSpeed(-this->step_speed);
  while(stepper.currentPosition() > -steps) {
    this->stepper.runSpeed();
  }
}
  
void step_motor::motor_up(float steps) {
  this->stepper.setCurrentPosition(0);
  this->stepper.setSpeed(this->step_speed);
  while(stepper.currentPosition() < steps) {
    this->stepper.runSpeed();
  }
}
  
void step_motor::home() {
  this->motor_up(this->step_count);
  this->current = 0;
  this->target = 0;
}
