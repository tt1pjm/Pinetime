#pragma once

#include <cstdint>

namespace Pinetime {
  namespace Controllers {
    class HeartRateController {
      public:
        enum class States { NotEnoughData, NoTouch, Running};

        void Start();
        void Update(States newState, uint8_t heartRate);

        States State() const { return state; }
        uint8_t HeartRate() const { return heartRate; }

      private:
        States state = States::NotEnoughData;
        uint8_t heartRate = 0;
    };
  }
}