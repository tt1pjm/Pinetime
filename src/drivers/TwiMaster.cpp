#include <sdk/integration/nrfx/nrfx_log.h>
#include "TwiMaster.h"

using namespace Pinetime::Drivers;


TwiMaster::TwiMaster(const nrfx_twi_t &twi, const nrfx_twi_config_t &config) : twi{twi}, config{config} {
  mutex = xSemaphoreCreateBinary();
  ASSERT(mutex != NULL);
}

void TwiMaster::Init() {
  auto ret = nrfx_twi_init(&twi, &config, nullptr, this);
  ASSERT(ret == NRFX_SUCCESS);
  nrfx_twi_enable(&twi);
  xSemaphoreGive(mutex);
}

void TwiMaster::Probe() {
  nrfx_err_t ret;
  for(int i = 0; i < 127; i++) {
    uint8_t data;
    ret = nrfx_twi_rx(&twi, i, &data, 1);
    if(ret == NRFX_SUCCESS) {
      NRF_LOG_INFO("I2C device detected at address %d", i);
    }
  }
}

void TwiMaster::Read(uint8_t address, uint8_t *buffer, size_t size) {
  xSemaphoreTake(mutex, portMAX_DELAY);
  nrfx_twi_rx(&twi, address, buffer, size);
  xSemaphoreGive(mutex);
}
