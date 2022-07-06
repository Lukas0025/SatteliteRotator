#pragma ones

#include <Arduino.h>
#include <AccelStepper.h>

#define DEG_TOLERANCE 5
#define MOTORINTERFACETYPE 1
#define DIRECTION -1
#define MAXSPEED 1000

struct step_motor_ports {
  int dir;
  int step;
};

class step_motor {
  private:
    struct step_motor_ports     ports;
    float                       target;
    float                       current;
    float                       step2deg;

    int                         step_speed;
    int                         step_count;
    int                         offset;
    int                         max_deg;

    AccelStepper                stepper;

  public:
    step_motor(int port_step, int port_dir, int step_speed, int step_count, int max_deg) {
      this->ports.dir  = port_dir;
      this->ports.step = port_step;

      this->stepper = AccelStepper(MOTORINTERFACETYPE, this->ports.step, this->ports.dir);
      this->stepper.setMaxSpeed(MAXSPEED);
      
      this->step_speed    = step_speed;
      this->step_count    = step_count;
      this->step2deg      = (float) max_deg / step_count;
      this->max_deg       = max_deg;
      this->offset        = 0;
      
      this->home();
    }

    void set_offset(int offset);
    int get_deg();
    void set_target(int deg);
    bool step();
    void motor_down(float steps);
    void motor_up(float steps);
    void home();

  
};
