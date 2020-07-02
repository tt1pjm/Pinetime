#pragma once

#include <cstdint>

namespace Pinetime {
  class HeartRateTask;
  namespace Controllers {
    class HeartRateController {
      public:
        enum class States { NotEnoughData, NoTouch, Running};
        explicit HeartRateController(Pinetime::HeartRateTask& heartRateTask);

        void Start();
        void Stop();
        void Update(States newState, uint8_t heartRate);

        States State() const { return state; }
        uint8_t HeartRate() const { return heartRate; }

      private:
        Pinetime::HeartRateTask& heartRateTask;
        States state = States::NotEnoughData;
        uint8_t heartRate = 0;
    };
  }
}