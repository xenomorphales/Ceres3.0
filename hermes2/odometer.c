#include "odometer.h"

#define __BSD_VISIBLE 1
#include <math.h>

int odometer_init(odometer_t * odo, encoder_t * encoder_left, encoder_t * encoder_right, const odometer_cfg_t * config) {
  odo->config = *config;

  odo->encoder_left = encoder_left;
  odo->encoder_right = encoder_right;

  odo->distance_offset = 0;
  odo->angle_offset = 0;

  return 0;
}

void odometer_reset(odometer_t * odo);

float odometer_read_distance(odometer_t * odo) {
  const float dist_left = encoder_read_distance(odo->encoder_left);
  const float dist_right = encoder_read_distance(odo->encoder_right);
  return odo->distance_offset + (dist_right + dist_left) / 2;
}

float odometer_read_speed(odometer_t * odo) {
  const float speed_left = encoder_read_speed(odo->encoder_left);
  const float speed_right = encoder_read_speed(odo->encoder_right);
  return (speed_right + speed_left) / 2;
}

float odometer_read_angle(odometer_t * odo) {
  const float dist_left = encoder_read_distance(odo->encoder_left);
  const float dist_right = encoder_read_distance(odo->encoder_right);
  return odo->angle_offset + (dist_right - dist_left) / odo->config.wheels_distance;
}