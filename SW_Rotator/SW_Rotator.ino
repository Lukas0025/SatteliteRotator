#include "linear_motor.h"
#include "step_motor.h"
#include "easycomm.h"

#define RELAY_ON        LOW
#define RELAY_OFF       HIGH
#define NOTIF_RELAY     4

linear_motor* el;
step_motor*   az;
easycomm*     easycom;

bool last_az_step = false;
int offset_az = 20;
int offset_el = 15;

void setup() {
  pinMode(NOTIF_RELAY, OUTPUT);
   digitalWrite(NOTIF_RELAY, RELAY_OFF);
  
  el = new linear_motor(15, 2, 29000, 81);
  el->set_step(3, 1074);

  az = new step_motor(13, 12, 40, 137, 360);

  Serial.begin(9600);
  Serial.setTimeout(50);
  
  easycom = new easycomm(&Serial);
}

void loop() {
  easycom->parse((az->get_deg() + 180 - offset_az) % 360, el->get_deg() - offset_el);
  
  el->set_target(easycom->ComElev + offset_el);
  el->step();

  az->set_target((easycom->ComAzim + 180 + offset_az) % 360);
  bool az_step = az->step();
    
  if (az_step) {
    //notify
    digitalWrite(NOTIF_RELAY, RELAY_ON);
    delay(200);
    digitalWrite(NOTIF_RELAY, RELAY_OFF);
  }

  last_az_step = az_step;
}
