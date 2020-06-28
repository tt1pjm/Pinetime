#include "HeartRateController.h"
using namespace Pinetime::Controllers;

void HeartRateController::Update(HeartRateController::States newState, uint8_t heartRate) {
  this->state = newState;
  this->heartRate = heartRate;
}

void HeartRateController::Start() {
  // TODO : request a new measurement (start the sensor, wait for data, wait for stabilisation, stop the sensor)
  // + Timeout (once the sensor found some touch, it tries to measure no matther what, and find erroneous values
}
