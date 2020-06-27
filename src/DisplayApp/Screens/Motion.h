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
#include <Components/Motion/MotionController.h>
#include "../Fonts/lcdfont14.h"
#include "../Fonts/lcdfont70.h"
#include "../../Version.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {

      class Motion : public Screen{
        public:
          Motion(DisplayApp* app, Controllers::MotionController& motionController);
          ~Motion() override;

          bool Refresh() override;
          bool OnButtonPushed() override;

        private:
          Controllers::MotionController& motionController;
          lv_obj_t * chart;
          lv_chart_series_t * ser1;
          lv_chart_series_t * ser2;
          lv_chart_series_t * ser3;

          lv_obj_t* labelStep;
          lv_obj_t* labelStepValue;
          static constexpr uint8_t nbStepsBufferSize = 9;
          char nbStepsBuffer[nbStepsBufferSize+1];
          bool running = true;

      };
    }
  }
}
