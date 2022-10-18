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
    if (this->trevled_deg + abs(this->current - this->target) > this->restart_deg_count) this->home();

     if (this->current < this->target) {
        if (this->current >= this->max_deg) return; 
        this->motor_up(this->step_time);
        this->current += this->step_deg;
      } else {
        if (this->current <= 0) return;
          
        this->motor_down(this->step_time);
        this->current -= this->step_deg;
      }

      this->trevled_deg += this->step_deg;
   }
}
  
void linear_motor::motor_down(int times) {
  digitalWrite(this->ports.n, MOT_OFF);
  digitalWrite(this->ports.p, MOT_ON);
  delay(times);
  digitalWrite(this->ports.p, MOT_OFF);
  digitalWrite(this->ports.n, MOT_OFF);
  delay(times);
}
  
void linear_motor::motor_up(int times) {
  digitalWrite(this->ports.p, MOT_OFF);
  digitalWrite(this->ports.n, MOT_ON);
  delay(times);
  digitalWrite(this->ports.n, MOT_OFF);
  digitalWrite(this->ports.p, MOT_OFF);
  delay(times);
}
  
void linear_motor::home() {
  for (int i = 0; i < full_milis; i += 1000) {
    this->motor_down(1000);
  }
  
  this->trevled_deg = 0;
  this->current = 0;
  this->target = 0;
}
