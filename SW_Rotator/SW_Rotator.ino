#include "linear_motor.h"
#include "step_motor.h"
#include "easycomm.h"
#include "librespace_rotator_pins.h"

#define USE_AZ_NOTIFY_RELAY
#define RELAY_ON         LOW
#define RELAY_OFF        HIGH
#define NOTIF_RELAY      RELAY_3

#define AZ_DIR_PIN        MOTOR_DIR 
#define AZ_STEP_PIN       MOTOR_STEP
#define AZ_STEP_SPEED     40
#define AZ_STEPS_PER_DEG  137
#define AZ_MAX_DEG        360

#define AZ_OFFSET 180

#define EL_POS_PIN            RELAY_1
#define EL_NEG_PIN            RELAY_2
#define EL_STEP_COUNT_MAX     29000
#define EL_MAX_DEG            81
#define EL_TIME_PER_DEG_COUNT 1074
#define EL_DEG_COUNT_PER_TIME 3

#define EL_OFFSET 15

linear_motor* el;
step_motor*   az;
easycomm*     easycom;

bool last_az_step = false;

void setup() {
  #ifdef USE_AZ_NOTIFY_RELAY
  pinMode(NOTIF_RELAY, OUTPUT);
  digitalWrite(NOTIF_RELAY, RELAY_OFF);
  #endif
  
  el = new linear_motor(EL_POS_PIN, EL_NEG_PIN, EL_STEP_COUNT_MAX, EL_MAX_DEG);
  el->set_step(EL_DEG_COUNT_PER_TIME, EL_TIME_PER_DEG_COUNT);

  az = new step_motor(AZ_DIR_PIN, AZ_STEP_PIN, AZ_STEP_SPEED, AZ_STEPS_PER_DEG, AZ_MAX_DEG);

  Serial.begin(9600);
  Serial.setTimeout(50);
  
  easycom = new easycomm(&Serial);
}

void loop() {
  easycom->parse((az->get_deg() + AZ_OFFSET) % AZ_MAX_DEG, el->get_deg() - EL_OFFSET);
  
  el->set_target(easycom->ComElev + EL_OFFSET);
  el->step();

  az->set_target((easycom->ComAzim + AZ_OFFSET) % AZ_MAX_DEG);
  bool az_step = az->step();
  
  #ifdef USE_AZ_NOTIFY_RELAY
  if (az_step) {
    //notify
    digitalWrite(NOTIF_RELAY, RELAY_ON);
    delay(200);
    digitalWrite(NOTIF_RELAY, RELAY_OFF);
  }

  last_az_step = az_step;
  #endif
}
