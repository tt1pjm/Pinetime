#include <libs/lvgl/lvgl.h>
#include "Brightness.h"

using namespace Pinetime::Applications::Screens;

void slider_event_cb(lv_obj_t * slider, lv_event_t event) {
  if(event == LV_EVENT_VALUE_CHANGED) {
    auto* brightnessSlider = static_cast<Brightness*>(slider->user_data);
    brightnessSlider->OnValueChanged();
  }
}

Brightness::Brightness(Pinetime::Applications::DisplayApp *app, Controllers::BrightnessController& brightness) : Screen(app), brightness{brightness} {
  slider = lv_slider_create(lv_scr_act(), NULL);
  lv_obj_set_user_data(slider, this);
  lv_obj_set_width(slider, LV_DPI * 2);
  lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_event_cb(slider, slider_event_cb);
  lv_slider_set_range(slider, 0, 2);
  // lv_slider_set_range(slider, 0, 6);
  lv_slider_set_value(slider, LevelToInt(brightness.Level()), LV_ANIM_OFF);

  slider_label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(slider_label, LevelToString(brightness.Level()));
  lv_obj_set_auto_realign(slider_label, true);
  lv_obj_align(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

Brightness::~Brightness() {
  lv_obj_clean(lv_scr_act());
}

bool Brightness::Refresh() {
  return running;
}

bool Brightness::OnButtonPushed() {
  running = false;
  return true;
}

const char *Brightness::LevelToString(Pinetime::Controllers::BrightnessController::Levels level) {
  switch(level) {
    case Pinetime::Controllers::BrightnessController::Levels::Off: return "Off";
    case Pinetime::Controllers::BrightnessController::Levels::Low: return "Low";
    case Pinetime::Controllers::BrightnessController::Levels::Medium: return "Medium";
    case Pinetime::Controllers::BrightnessController::Levels::High: return "High";
    // case Pinetime::Controllers::BrightnessController::Levels::Low: return "Low";
    // case Pinetime::Controllers::BrightnessController::Levels::LowMedium: return "Low-Medium";
    // case Pinetime::Controllers::BrightnessController::Levels::MediumLow: return "Medium-Low";
    // case Pinetime::Controllers::BrightnessController::Levels::Medium: return "Medium";
    // case Pinetime::Controllers::BrightnessController::Levels::MediumHigh: return "Medium-High";
    // case Pinetime::Controllers::BrightnessController::Levels::HighMedium: return "High-Medium";
    // case Pinetime::Controllers::BrightnessController::Levels::High: return "High";
    default : return "???";
  }
}

void Brightness::OnValueChanged() {
  SetValue(lv_slider_get_value(slider));
}

void Brightness::SetValue(uint8_t value) {
  switch(value) {
    case 0: brightness.Set(Controllers::BrightnessController::Levels::Low); break;
    case 1: brightness.Set(Controllers::BrightnessController::Levels::Medium); break;
    case 2: brightness.Set(Controllers::BrightnessController::Levels::High); break;
    // case 1: brightness.Set(Controllers::BrightnessController::Levels::LowMedium); break;
    // case 2: brightness.Set(Controllers::BrightnessController::Levels::MediumLow); break;
    // case 3: brightness.Set(Controllers::BrightnessController::Levels::Medium); break;
    // case 4: brightness.Set(Controllers::BrightnessController::Levels::MediumHigh); break;
    // case 5: brightness.Set(Controllers::BrightnessController::Levels::HighMedium); break;
    // case 6: brightness.Set(Controllers::BrightnessController::Levels::High); break;
  }
  lv_label_set_text(slider_label, LevelToString(brightness.Level()));
}

uint8_t Brightness::LevelToInt(Pinetime::Controllers::BrightnessController::Levels level) {
  switch(level) {
    case Pinetime::Controllers::BrightnessController::Levels::Off: return 0;
    case Pinetime::Controllers::BrightnessController::Levels::Low: return 0;
    case Pinetime::Controllers::BrightnessController::Levels::Medium: return 1;
    case Pinetime::Controllers::BrightnessController::Levels::High: return 2;
    // case Pinetime::Controllers::BrightnessController::Levels::Off: return 0;
    // case Pinetime::Controllers::BrightnessController::Levels::Low: return 0;
    // case Pinetime::Controllers::BrightnessController::Levels::LowMedium: return 1;
    // case Pinetime::Controllers::BrightnessController::Levels::MediumLow: return 2;
    // case Pinetime::Controllers::BrightnessController::Levels::Medium: return 3;
    // case Pinetime::Controllers::BrightnessController::Levels::MediumHigh: return 4;
    // case Pinetime::Controllers::BrightnessController::Levels::HighMedium: return 5;
    // case Pinetime::Controllers::BrightnessController::Levels::High: return 6;
    default : return 0;
  }
}

bool Brightness::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  switch(event) {
    case TouchEvents::SwipeLeft:
      brightness.Lower();
      SetValue();
      return true;
    case TouchEvents::SwipeRight:
      brightness.Higher();
      SetValue();
      return true;
    default:
      return false;
  }
}

void Brightness::SetValue() {
  lv_slider_set_value(slider, LevelToInt(brightness.Level()), LV_ANIM_OFF);
  lv_label_set_text(slider_label, LevelToString(brightness.Level()));
}
