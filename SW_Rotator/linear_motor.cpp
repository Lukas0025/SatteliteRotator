#include "linear_motor.h"

int linear_motor::get_deg() {
  return this->current;
}
  
void linear_motor::set_step(int deg, int times) {
  this->step_deg = deg;
  this->step_time = times;
}

void linear_motor::set_target(int deg) {
  this->target = (deg > this->max_deg) ? this->max_deg : deg;
}

void linear_motor::step() {
  if (abs(this->current - this->target) > DEG_TOLERANCE) {
     if (this->current < this->target) {
        if (this->current >= this->max_deg) return; 
        this->motor_up(this->step_time);
        this->current += this->step_deg;
      } else {
        if (this->current <= 0) return;
          
        this->motor_down(this->step_time);
        this->current -= this->step_deg;
      }
   }
}
  
void linear_motor::motor_down(int times) {
  digitalWrite(this->ports.p, MOT_ON);
  digitalWrite(this->ports.n, MOT_OFF);
  delay(times);
  digitalWrite(this->ports.p, MOT_OFF);
  digitalWrite(this->ports.n, MOT_OFF);
}
  
void linear_motor::motor_up(int times) {
  digitalWrite(this->ports.p, MOT_OFF);
  digitalWrite(this->ports.n, MOT_ON);
  delay(times);
  digitalWrite(this->ports.p, MOT_OFF);
  digitalWrite(this->ports.n, MOT_OFF);
}
  
void linear_motor::home() {
  this->motor_down(full_milis * 2);
  this->current = 0;
  this->target = 0;
}
