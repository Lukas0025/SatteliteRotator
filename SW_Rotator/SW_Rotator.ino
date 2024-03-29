#include "easycomm.h"
#include "librespace_rotator_pins.h"
#include "linear_motor.h"
#include "step_motor.h"

#define USE_AZ_NOTIFY_RELAY
#define RELAY_ON LOW
#define RELAY_OFF HIGH
#define NOTIF_RELAY RELAY_2

#define AZ_DIR_PIN MOTOR_DIR
#define AZ_STEP_PIN MOTOR_STEP
#define AZ_STEP_SPEED 40
#define AZ_STEPS_PER_DEG 137
#define AZ_MAX_DEG 360
#define AZ_RESTART_DEG_COUNT 360 * 2

#define AZ_OFFSET 180

#define EL_POS_PIN RELAY_3
#define EL_NEG_PIN RELAY_4
#define EL_STEP_COUNT_MAX 29000
#define EL_MAX_DEG 81
#define EL_TIME_PER_DEG_COUNT 358
#define EL_DEG_COUNT_PER_TIME 1
#define EL_RESTART_DEG_COUNT 90 * 4

#define EL_OFFSET 15

linear_motor *el;
step_motor *az;
easycomm *easycom;

bool last_az_step = false;

void setup() {
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  digitalWrite(RELAY_1, RELAY_OFF);
  digitalWrite(RELAY_2, RELAY_OFF);
  digitalWrite(RELAY_3, RELAY_OFF);
  digitalWrite(RELAY_4, RELAY_OFF);

  el = new linear_motor(EL_POS_PIN, EL_NEG_PIN, EL_STEP_COUNT_MAX, EL_MAX_DEG,
                        EL_RESTART_DEG_COUNT);
  el->set_step(EL_DEG_COUNT_PER_TIME, EL_TIME_PER_DEG_COUNT);

  az = new step_motor(AZ_STEP_PIN, AZ_DIR_PIN, AZ_STEP_SPEED, AZ_STEPS_PER_DEG,
                      AZ_MAX_DEG, AZ_RESTART_DEG_COUNT);

  Serial.begin(9600);
  Serial.setTimeout(50);

  easycom = new easycomm(&Serial);
}

void loop() {
  easycom->parse((az->get_deg() + AZ_OFFSET) % AZ_MAX_DEG,
                 el->get_deg() - EL_OFFSET);

  el->set_target(easycom->ComElev + EL_OFFSET);
  el->step();

  az->set_target((easycom->ComAzim + AZ_OFFSET) % AZ_MAX_DEG);
  bool az_step = az->step();

#ifdef USE_AZ_NOTIFY_RELAY
  if (az_step) {
    // notify
    digitalWrite(NOTIF_RELAY, RELAY_ON);
    delay(200);
    digitalWrite(NOTIF_RELAY, RELAY_OFF);
  }

  last_az_step = az_step;
#endif
}
