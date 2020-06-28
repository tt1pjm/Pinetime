#pragma once

#include <cstdint>
#include <chrono>
#include <Components/Gfx/Gfx.h>
#include "Screen.h"
#include <bits/unique_ptr.h>
#include <libs/lvgl/src/lv_core/lv_style.h>
#include <libs/lvgl/src/lv_core/lv_obj.h>
#include <Components/Battery/BatteryController.h>
#include <Components/Ble/BleController.h>
#include <Components/HeartRate/HeartRateController.h>
#include "../Fonts/lcdfont14.h"
#include "../Fonts/lcdfont70.h"
#include "../../Version.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {

      class HeartRate : public Screen{
        public:
          HeartRate(DisplayApp* app, Controllers::HeartRateController& HeartRateController);
          ~HeartRate() override;

          bool Refresh() override;
          bool OnButtonPushed() override;

        private:
          Controllers::HeartRateController& heartRateController;
          lv_obj_t* label_hr;
          lv_obj_t* label_dummy;
          lv_style_t* labelBigStyle;

          bool running = true;

      };
    }
  }
}
