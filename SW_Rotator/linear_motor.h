#pragma ones

#include <Arduino.h>

#define DEG_TOLERANCE 5
#define MOT_ON        LOW
#define MOT_OFF       HIGH

struct linear_motor_ports {
  int n;
  int p;
};

class linear_motor {
  private:
    struct linear_motor_ports ports;
    int                       full_milis;
    int                       max_deg;
    int                       target;
    int                       current;
    float                     restart_deg_count;
    float                     trevled_deg;

    int                       step_deg;
    int                       step_time;

  public:
    linear_motor(int port_positive, int port_negative, int full_milis, int max_deg, float restart_deg_count) {
      this->ports.p = port_positive;
      this->ports.n = port_negative;

      pinMode(this->ports.p,      OUTPUT);
      pinMode(this->ports.n,      OUTPUT);
      digitalWrite(this->ports.p, MOT_OFF);
      digitalWrite(this->ports.n, MOT_OFF);
      
      this->full_milis = full_milis;
      this->max_deg    = max_deg;

      this->restart_deg_count = restart_deg_count;
  
      this->home();
    }

    int get_deg();
    void set_step(int deg, int times);
    void set_target(int deg);
    void step();
    void motor_down(int times);
    void motor_up(int times);
    void home();

  
};
