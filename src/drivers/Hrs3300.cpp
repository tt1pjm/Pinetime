#include <sdk/components/libraries/util/nrf_assert.h>
#include <drivers/TwiMaster.h>
#include <sdk/integration/nrfx/nrfx_log.h>
#include <drivers/Hrs3300/hrs3300.h>
#include <cmath>
#include <sdk/modules/nrfx/hal/nrf_gpio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "Hrs3300.h"
using namespace Pinetime::Drivers;

Hrs3300* hrs3300Instance = nullptr;

extern "C" {
void Hrs3300_write_reg(uint8_t addr, uint8_t data) {
  ASSERT(hrs3300Instance != nullptr);
  hrs3300Instance->WriteRegister(addr, data);
}

uint8_t Hrs3300_read_reg(uint8_t addr) {
  ASSERT(hrs3300Instance != nullptr);
  return hrs3300Instance->ReadRegister(addr);
}
int __hardfp_sqrt(int f){
  return std::sqrt(f); }
}

Hrs3300::Hrs3300(TwiMaster &twiMaster, uint8_t twiAddress) : twiMaster{twiMaster}, twiAddress{twiAddress} {
  ASSERT(hrs3300Instance == nullptr);
  hrs3300Instance = this;
}

void Hrs3300::Init() {
  nrf_gpio_cfg_input(30, NRF_GPIO_PIN_NOPULL) ;

  Disable();

  vTaskDelay(100);
  auto id = ReadRegister(0x00);
  NRF_LOG_INFO("HRS3300 chip ID : %d", id);

  Hrs3300_chip_init();
  Hrs3300_chip_enable();
  Hrs3300_set_exinf(0, 0, 0, 0, 0, 0);
  Hrs3300_alg_open();

}

uint8_t Hrs3300::ReadRegister(uint8_t registerAddress) {
  uint8_t data;
  twiMaster.Read(twiAddress, registerAddress, &data, 1);
  return data;
}

void Hrs3300::WriteRegister(uint8_t registerAddress, uint8_t buffer) {
  twiMaster.Write(twiAddress, registerAddress, &buffer, 1);
}

void Hrs3300::Disable() {
  Hrs3300_chip_disable();
}

uint8_t Hrs3300::Process() {

  auto heartRate = get_heart_rate();
  /*
   * 253 = not enough measurement, please wait
   * 254 = no touch
   * 255 = no value (a value comes out every 25 calls)
   */
  if(heartRate != 255)
    NRF_LOG_INFO("Heart rate : %d", heartRate);

  return heartRate;
}
