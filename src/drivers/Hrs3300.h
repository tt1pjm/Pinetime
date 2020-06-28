#pragma once

#include <cstdint>

namespace Pinetime {
  namespace Drivers {
    class TwiMaster;

    class Hrs3300 {
      public:
        Hrs3300(TwiMaster& twiMaster, uint8_t twiAddress);
        Hrs3300(const Hrs3300&) = delete;
        Hrs3300& operator=(const Hrs3300&) = delete;
        Hrs3300(Hrs3300&&) = delete;
        Hrs3300& operator=(Hrs3300&&) = delete;

        void Init();


        void Disable();

        uint8_t Process();

        uint8_t ReadRegister(uint8_t registerAddress);
        void WriteRegister(uint8_t registerAddress, uint8_t buffer);

      private:
        TwiMaster& twiMaster;
        uint8_t twiAddress;
    };
  }
}

