#include <hal/nrf_gpio.h>
#include "BrightnessController.h"

using namespace Pinetime::Controllers;


void BrightnessController::Init() {
  nrf_gpio_cfg_output(pinLcdBacklight1);
  nrf_gpio_cfg_output(pinLcdBacklight2);
  nrf_gpio_cfg_output(pinLcdBacklight3);
  Set(level);
}

void BrightnessController::Set(BrightnessController::Levels level) {
  this->level = level;
  switch(level) {
    default:
    case Levels::High:
      nrf_gpio_pin_clear(pinLcdBacklight1);
      nrf_gpio_pin_clear(pinLcdBacklight2);
      nrf_gpio_pin_clear(pinLcdBacklight3);
      break;
    case Levels::Medium:
      nrf_gpio_pin_clear(pinLcdBacklight1);
      nrf_gpio_pin_clear(pinLcdBacklight2);
      nrf_gpio_pin_set(pinLcdBacklight3);
      break;
    case Levels::Low:
      nrf_gpio_pin_clear(pinLcdBacklight1);
      nrf_gpio_pin_set(pinLcdBacklight2);
      nrf_gpio_pin_set(pinLcdBacklight3);
      break;
    case Levels::Off:
      nrf_gpio_pin_set(pinLcdBacklight1);
      nrf_gpio_pin_set(pinLcdBacklight2);
      nrf_gpio_pin_set(pinLcdBacklight3);
      break;
  //   case Levels::High:
  //     nrf_gpio_pin_clear(pinLcdBacklight1);
  //     nrf_gpio_pin_clear(pinLcdBacklight2);
  //     nrf_gpio_pin_clear(pinLcdBacklight3);
  //     break;
  //   case Levels::HighMedium:
  //     nrf_gpio_pin_set(pinLcdBacklight1);
  //     nrf_gpio_pin_clear(pinLcdBacklight2);
  //     nrf_gpio_pin_clear(pinLcdBacklight3);
  //     break;
  //   case Levels::MediumHigh:
  //     nrf_gpio_pin_clear(pinLcdBacklight1);
  //     nrf_gpio_pin_set(pinLcdBacklight2);
  //     nrf_gpio_pin_clear(pinLcdBacklight3);
  //     break;
  //   case Levels::Medium:
  //     nrf_gpio_pin_clear(pinLcdBacklight1);
  //     nrf_gpio_pin_clear(pinLcdBacklight2);
  //     nrf_gpio_pin_set(pinLcdBacklight3);
  //     break;
  //  case Levels::MediumLow:
  //     nrf_gpio_pin_set(pinLcdBacklight1);
  //     nrf_gpio_pin_clear(pinLcdBacklight2);
  //     nrf_gpio_pin_set(pinLcdBacklight3);
  //     break;
  //   case Levels::LowMedium:
  //     nrf_gpio_pin_clear(pinLcdBacklight1);
  //     nrf_gpio_pin_set(pinLcdBacklight2);
  //     nrf_gpio_pin_set(pinLcdBacklight3);
  //     break;
  //   case Levels::Low:
  //     nrf_gpio_pin_set(pinLcdBacklight1);
  //     nrf_gpio_pin_set(pinLcdBacklight2);
  //     nrf_gpio_pin_set(pinLcdBacklight3);
  //     break;
  }
}

void BrightnessController::Lower() {
  switch(level) {
    case Levels::High: Set(Levels::Medium); break;
    case Levels::Medium: Set(Levels::Low); break;
    case Levels::Low: Set(Levels::Off); break;
    // case Levels::High: Set(Levels::HighMedium); break;
    // case Levels::HighMedium: Set(Levels::MediumHigh); break;
    // case Levels::MediumHigh: Set(Levels::Medium); break;
    // case Levels::Medium: Set(Levels::MediumLow); break;
    // case Levels::MediumLow: Set(Levels::LowMedium); break;
    // case Levels::LowMedium: Set(Levels::Low); break;
    default: break;
  }
}

void BrightnessController::Higher() {
  switch(level) {
    case Levels::Off: Set(Levels::Low); break;
    case Levels::Low: Set(Levels::Medium); break;
    case Levels::Medium: Set(Levels::High); break;
    // case Levels::Low: Set(Levels::LowMedium); break;
    // case Levels::LowMedium: Set(Levels::MediumLow); break;
    // case Levels::MediumLow: Set(Levels::Medium); break;
    // case Levels::Medium: Set(Levels::MediumHigh); break;
    // case Levels::MediumHigh: Set(Levels::HighMedium); break;
    // case Levels::HighMedium: Set(Levels::High); break;
    default: break;
  }
}

BrightnessController::Levels BrightnessController::Level() const {
  return level;
}

void BrightnessController::Backup() {
  backupLevel = level;
}

void BrightnessController::Restore() {
  Set(backupLevel);
}

