#include "HeartRateController.h"
#include <HeartRateTask/HeartRateTask.h>

using namespace Pinetime::Controllers;

HeartRateController::HeartRateController(Pinetime::HeartRateTask &heartRateTask) : heartRateTask{heartRateTask} {

}

void HeartRateController::Update(HeartRateController::States newState, uint8_t heartRate) {
  this->state = newState;
  this->heartRate = heartRate;
}

void HeartRateController::Start() {
  heartRateTask.PushMessage(HeartRateTask::Messages::StartMeasurement);
}

void HeartRateController::Stop() {
  heartRateTask.PushMessage(HeartRateTask::Messages::StopMeasurement);
}
