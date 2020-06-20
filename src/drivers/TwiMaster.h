#pragma once
#include <FreeRTOS.h>
#include <semphr.h>
#include <drivers/include/nrfx_twi.h>


namespace Pinetime {
  namespace Drivers {
    class TwiMaster {
      public:
        TwiMaster(const nrfx_twi_t& twi, const nrfx_twi_config_t& config);
        TwiMaster(const TwiMaster&) = delete;
        TwiMaster& operator=(const TwiMaster&) = delete;
        TwiMaster(TwiMaster&&) = delete;
        TwiMaster& operator=(TwiMaster&&) = delete;

        void Init();
        void Probe();

        void Read(uint8_t address, uint8_t* buffer, size_t size);
      private:
        const nrfx_twi_t &twi;
        const nrfx_twi_config_t &config;
        SemaphoreHandle_t mutex;
    };
  }
}