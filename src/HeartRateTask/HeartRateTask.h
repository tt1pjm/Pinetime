#pragma once

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <drivers/Hrs3300.h>
#include <Components/HeartRate/HeartRateController.h>

namespace Pinetime {
  class HeartRateTask {
    public:
      enum class Messages : uint8_t {GoToSleep, WakeUp, StartMeasurement, StopMeasurement };
      enum class States {Idle, Running};

      explicit HeartRateTask(Drivers::Hrs3300& heartRateSensor);
      void Start();
      void Work();
      void PushMessage(Messages msg);

      Pinetime::Controllers::HeartRateController& HeartRateController() { return heartRateController; }

    private:
      TaskHandle_t taskHandle;
      QueueHandle_t messageQueue;
      States state = States::Running;
      Drivers::Hrs3300& heartRateSensor;
      Pinetime::Controllers::HeartRateController heartRateController;
      bool measurementStarted = false;

      static void Process(void* instance);

      void StartMeasurement();

      void StopMeasurement();
  };
}



