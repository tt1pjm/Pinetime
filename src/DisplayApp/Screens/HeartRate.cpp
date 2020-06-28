#include <libs/lvgl/lvgl.h>
#include "HeartRate.h"
#include "../DisplayApp.h"

using namespace Pinetime::Applications::Screens;
extern lv_font_t jetbrains_mono_extrabold_compressed;
extern lv_font_t jetbrains_mono_bold_20;


HeartRate::HeartRate(Pinetime::Applications::DisplayApp *app, Controllers::HeartRateController& heartRateController) : Screen(app), heartRateController{heartRateController} {
  label_dummy = lv_label_create(lv_scr_act(), NULL);

  labelBigStyle = const_cast<lv_style_t *>(lv_label_get_style(label_dummy, LV_LABEL_STYLE_MAIN));
  labelBigStyle->text.font = &jetbrains_mono_extrabold_compressed;

  label_hr = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(label_hr, LV_LABEL_STYLE_MAIN, labelBigStyle);
  lv_obj_align(label_hr, lv_scr_act(), LV_ALIGN_CENTER, -70, 0);

  lv_label_set_text(label_hr, "000");

}

HeartRate::~HeartRate() {
  lv_obj_clean(lv_scr_act());
}

bool HeartRate::Refresh() {
  char hr[4];

  switch(heartRateController.State()) {
    case Controllers::HeartRateController::States::NoTouch:
    case Controllers::HeartRateController::States::NotEnoughData:
      lv_label_set_text(label_hr, "000");
      break;
    default:
      sprintf(hr, "%03d", heartRateController.HeartRate());
      lv_label_set_text(label_hr, hr);
  }


  return running;
}

bool HeartRate::OnButtonPushed() {
  running = false;
  return true;
}
