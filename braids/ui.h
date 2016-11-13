// Copyright 2012 Olivier Gillet, 2015 Tim Churches
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
// Modifications: Tim Churches (tim.churches@gmail.com)
// Modifications may be determined by examining the differences between the last commit 
// by Olivier Gillet (pichenettes) and the HEAD commit at 
// https://github.com/timchurches/Mutated-Mutables/tree/master/braids 
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// User interface.

#ifndef BRAIDS_UI_H_
#define BRAIDS_UI_H_

#include "stmlib/stmlib.h"

#include "stmlib/ui/event_queue.h"

#include "braids/drivers/display.h"
#include "braids/drivers/encoder.h"
#include "braids/settings.h"

namespace braids {

enum UiMode {
  MODE_SPLASH,
  MODE_EDIT,
  MODE_MENU,
  MODE_CALIBRATION_STEP_1,
  MODE_CALIBRATION_STEP_2,
  MODE_SELECT_PRESET,
};

class Ui {
 public:
  Ui() { }
  ~Ui() { }
  
  void Init();
  void Poll();
  void DoEvents();
  void FlushEvents();
  void Print(const char* text) {
    display_.Print(text);
  }
/*
//   void PrintDebugInteger(uint16_t x) {
//     char buffer[5];
//     buffer[4] = '\0';
//     for (uint16_t i = 0; i < 4; ++i) {
//       buffer[3 - i] = '0' + (x % 10);
//       x /= 10;
//     }
//     Print(buffer);
//   }
*/  
  inline void UpdateCv(
      int16_t cv_param,
      int16_t cv_color,
      int16_t cv_pitch,
      int16_t cv_fm) {
    cv_[0] = cv_param;
    cv_[1] = cv_color;
    cv_[2] = cv_pitch;
    cv_[3] = cv_fm;
  }
  
  // Following method is retained because it is responsible for causing the CV tester
  // to blink on each trigger received. But we don't need to increment marquee_step 
  // it no longer exists.
  inline void StepMarquee() {
    // marquee_step_++;
    blink_ = true;
  }

  // Overrides oscillator shape display when in meta mode.
  inline void set_meta_shape(MacroOscillatorShape shape) {
    meta_shape_ = shape;
  }
  
 private:
  void OnIncrement(const stmlib::Event& event);
  void OnClick();
  void OnLongClick();
  void RefreshDisplay();
  void OnClickPreset(bool long_click);
  void DisplayPreset(char prefix);

  stmlib::EventQueue<16> queue_;
  
  uint32_t encoder_press_time_;
  bool inhibit_further_switch_events_;
  
  int16_t value_;
  uint8_t sub_clock_;
  
  UiMode mode_;
  int16_t setting_index_;
  int16_t last_setting_index_;
  Setting setting_;
  Setting last_setting_;
  
  Display display_;
  Encoder encoder_;
  
  int16_t dac_code_c2_;
  int16_t cv_[4];

  uint8_t splash_frame_;
  bool blink_;
  
  MacroOscillatorShape meta_shape_;

  int16_t preset_slot_, last_preset_slot_;

  DISALLOW_COPY_AND_ASSIGN(Ui);
};

}  // namespace braids

#endif // BRAIDS_UI_H_
