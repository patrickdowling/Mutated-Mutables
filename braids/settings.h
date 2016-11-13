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
// Settings

#ifndef BRAIDS_SETTINGS_H_
#define BRAIDS_SETTINGS_H_

#include "stmlib/stmlib.h"

namespace braids {

enum MacroOscillatorShape {
  MACRO_OSC_SHAPE_CSAW,
  MACRO_OSC_SHAPE_MORPH,
  MACRO_OSC_SHAPE_SAW_SQUARE,
  MACRO_OSC_SHAPE_SQUARE_SYNC,
  MACRO_OSC_SHAPE_SINE_TRIANGLE,
  MACRO_OSC_SHAPE_BUZZ,
  
  MACRO_OSC_SHAPE_TRIPLE_SAW,
  MACRO_OSC_SHAPE_TRIPLE_SQUARE,
  MACRO_OSC_SHAPE_TRIPLE_TRIANGLE,
  MACRO_OSC_SHAPE_TRIPLE_SINE,
  MACRO_OSC_SHAPE_TRIPLE_RING_MOD,
  MACRO_OSC_SHAPE_SAW_SWARM,
  MACRO_OSC_SHAPE_SAW_COMB,
  MACRO_OSC_SHAPE_TOY,

  MACRO_OSC_SHAPE_DIGITAL_FILTER_LP,
  MACRO_OSC_SHAPE_DIGITAL_FILTER_PK,
  MACRO_OSC_SHAPE_DIGITAL_FILTER_BP,
  MACRO_OSC_SHAPE_DIGITAL_FILTER_HP,
  MACRO_OSC_SHAPE_VOSIM,
  MACRO_OSC_SHAPE_VOWEL,
  MACRO_OSC_SHAPE_VOWEL_FOF,

  MACRO_OSC_SHAPE_FM,
  MACRO_OSC_SHAPE_FEEDBACK_FM,
  MACRO_OSC_SHAPE_CHAOTIC_FEEDBACK_FM,

  MACRO_OSC_SHAPE_PLUCKED,
  MACRO_OSC_SHAPE_BOWED,
  MACRO_OSC_SHAPE_BLOWN,
  MACRO_OSC_SHAPE_FLUTED,
  MACRO_OSC_SHAPE_STRUCK_BELL,
  MACRO_OSC_SHAPE_STRUCK_DRUM,
  MACRO_OSC_SHAPE_KICK,
  MACRO_OSC_SHAPE_CYMBAL,
  MACRO_OSC_SHAPE_SNARE,

  MACRO_OSC_SHAPE_WAVETABLES,
  MACRO_OSC_SHAPE_WAVE_MAP,
  MACRO_OSC_SHAPE_WAVE_LINE,
  MACRO_OSC_SHAPE_WAVE_PARAPHONIC,

  // MACRO_OSC_SHAPE_FILTERED_NOISE,
  // MACRO_OSC_SHAPE_TWIN_PEAKS_NOISE,
  MACRO_OSC_SHAPE_CLOCKED_NOISE,
  MACRO_OSC_SHAPE_GRANULAR_CLOUD,
  // MACRO_OSC_SHAPE_PARTICLE_NOISE,

  MACRO_OSC_SHAPE_BYTEBEAT0,  
  MACRO_OSC_SHAPE_BYTEBEAT1,  
  MACRO_OSC_SHAPE_BYTEBEAT2,  
  MACRO_OSC_SHAPE_BYTEBEAT3,  
  MACRO_OSC_SHAPE_SILENCE,

  MACRO_OSC_SHAPE_LAST,
  MACRO_OSC_SHAPE_LAST_ACCESSIBLE_FROM_META = MACRO_OSC_SHAPE_BYTEBEAT3
};

enum Resolution {
  RESOLUTION_2_BIT,
  RESOLUTION_3_BIT,
  RESOLUTION_4_BIT,
  RESOLUTION_6_BIT,
  RESOLUTION_8_BIT,
  RESOLUTION_12_BIT,
  RESOLUTION_16_BIT,
  RESOLUTION_LAST
};

enum SampleRate {
  SAMPLE_RATE_4K,
  SAMPLE_RATE_8K,
  SAMPLE_RATE_16K,
  SAMPLE_RATE_24k,
  SAMPLE_RATE_32k,
  SAMPLE_RATE_48K,
  SAMPLE_RATE_96K,
  SAMPLE_RATE_LAST
};


enum PitchQuantization {
  PITCH_QUANTIZATION_OFF,
  PITCH_QUANTIZATION_QUARTER_TONE,
  PITCH_QUANTIZATION_SEMITONE,
  PITCH_QUANTIZATION_IONIAN,
  PITCH_QUANTIZATION_DORIAN,
  PITCH_QUANTIZATION_PHRYGIAN,
  PITCH_QUANTIZATION_LYDIAN,
  PITCH_QUANTIZATION_MIXOLYDIAN,
  PITCH_QUANTIZATION_AEOLIAN,
  PITCH_QUANTIZATION_LOCRIAN,
  PITCH_QUANTIZATION_BLUES_MAJOR,
  PITCH_QUANTIZATION_BLUES_MINOR,
  PITCH_QUANTIZATION_PENTATONIC_MAJOR,
  PITCH_QUANTIZATION_PENTATONIC_MINOR,
  PITCH_QUANTIZATION_BHAIRAV,
  PITCH_QUANTIZATION_SHRI,
  PITCH_QUANTIZATION_RUPAVATI,
  PITCH_QUANTIZATION_TODI,
  PITCH_QUANTIZATION_RAGESHRI,
  PITCH_QUANTIZATION_KAAFI,
  PITCH_QUANTIZATION_MEGH,
  PITCH_QUANTIZATION_MALKAUNS,
  PITCH_QUANTIZATION_DEEPAK,
  PITCH_QUANTIZATION_FOLK,
  PITCH_QUANTIZATION_JAPANESE,
  PITCH_QUANTIZATION_GAMELAN,
  PITCH_QUANTIZATION_WHOLE_TONE,
  PITCH_QUANTIZATION_LAST
};

enum PitchRange {
  PITCH_RANGE_EXTERNAL,
  PITCH_RANGE_FREE,
  PITCH_RANGE_EXTENDED,
  PITCH_RANGE_440,
  PITCH_RANGE_LFO  // This setting is hidden by default! But now unhidden!!
};

enum Setting {
  SETTING_OSCILLATOR_SHAPE,
  SETTING_RESOLUTION,
  SETTING_RATE_INVERSION,
  SETTING_TRIG_SOURCE,
  SETTING_TRIG_DELAY,
  SETTING_META_MODULATION,
  SETTING_PITCH_RANGE,
  SETTING_PITCH_OCTAVE,
  SETTING_PITCH_QUANTIZER,
  SETTING_VCO_DRIFT,
  SETTING_BRIGHTNESS,
  SETTING_MOD1_ATTACK_SHAPE,
  SETTING_MOD2_ATTACK_SHAPE,
  SETTING_MOD1_DECAY_SHAPE,
  SETTING_MOD2_DECAY_SHAPE,
  SETTING_MOD1_TIMBRE_DEPTH, 
  SETTING_MOD2_TIMBRE_DEPTH, 
  SETTING_MOD1_AD_RATIO,
  SETTING_MOD2_AD_RATIO,
  SETTING_MOD1_MODE,
  SETTING_MOD2_MODE,
  SETTING_MOD1_RATE,
  SETTING_MOD2_RATE,
  SETTING_MOD1_COLOR_DEPTH, 
  SETTING_MOD2_COLOR_DEPTH, 
  SETTING_MOD1_LEVEL_DEPTH, 
  SETTING_MOD2_LEVEL_DEPTH, 
  SETTING_MOD1_VIBRATO_DEPTH,
  SETTING_MOD2_VIBRATO_DEPTH,
  SETTING_MOD1_MOD2_DEPTH, 
  SETTING_QUANT_BEFORE_VIBRATO,
  SETTING_MOD1_SYNC,
  SETTING_MOD2_SYNC,
  SETTING_OSC_SYNC,
  SETTING_METASEQ_PARAMETER_DEST, 
  SETTING_FINE_TUNE,
  SETTING_MOD1_MOD2_VIBRATO_DEPTH,
  SETTING_INITIAL_GAIN,
  SETTING_METASEQ,
  SETTING_METASEQ_SHAPE1, 
  SETTING_METASEQ_STEP_LENGTH1, 
  SETTING_METASEQ_SHAPE2, 
  SETTING_METASEQ_STEP_LENGTH2, 
  SETTING_METASEQ_SHAPE3, 
  SETTING_METASEQ_STEP_LENGTH3, 
  SETTING_METASEQ_SHAPE4, 
  SETTING_METASEQ_STEP_LENGTH4, 
  SETTING_METASEQ_SHAPE5, 
  SETTING_METASEQ_STEP_LENGTH5, 
  SETTING_METASEQ_SHAPE6, 
  SETTING_METASEQ_STEP_LENGTH6, 
  SETTING_METASEQ_SHAPE7, 
  SETTING_METASEQ_STEP_LENGTH7, 
  SETTING_METASEQ_SHAPE8, 
  SETTING_METASEQ_STEP_LENGTH8, 
  SETTING_SAMPLE_RATE,
  SETTING_METASEQ_DIRECTION,
  SETTING_PITCH_SAMPLE_HOLD,
  SETTING_METASEQ_NOTE1, 
  SETTING_METASEQ_NOTE2, 
  SETTING_METASEQ_NOTE3, 
  SETTING_METASEQ_NOTE4, 
  SETTING_METASEQ_NOTE5, 
  SETTING_METASEQ_NOTE6, 
  SETTING_METASEQ_NOTE7, 
  SETTING_METASEQ_NOTE8, 
  SETTING_METASEQ_PARAMETER1, 
  SETTING_METASEQ_PARAMETER2, 
  SETTING_METASEQ_PARAMETER3, 
  SETTING_METASEQ_PARAMETER4, 
  SETTING_METASEQ_PARAMETER5, 
  SETTING_METASEQ_PARAMETER6, 
  SETTING_METASEQ_PARAMETER7, 
  SETTING_METASEQ_PARAMETER8, 
  SETTING_METASEQ_CLOCK_DIV, 
  SETTING_TURING_CLOCK_DIV, 
  SETTING_TURING_LENGTH,
  SETTING_TURING_WINDOW,
  SETTING_TURING_PROB,
  SETTING_TURING_INIT,
  SETTING_MUSICAL_SCALE,
  SETTING_EDIT_WRAP,
  SETTING_LAST_EDITABLE_SETTING = SETTING_EDIT_WRAP,
  
  // Not settings per se, but used for menu display!
  SETTING_CALIBRATION,
  SETTING_CV_TESTER,
  SETTING_VERSION,
  SETTING_LOAD_PRESET,
  SETTING_LAST
};

struct SettingsData {
  uint8_t shape;
  uint8_t resolution;
  uint8_t rate_inversion ; 
  uint8_t auto_trig;
  uint8_t trig_delay;
  uint8_t meta_modulation;
  uint8_t pitch_range;
  uint8_t pitch_octave;
  uint8_t pitch_quantization;
  uint8_t vco_drift;
  uint8_t brightness;
  uint8_t mod1_attack_shape;
  uint8_t mod2_attack_shape;
  uint8_t mod1_decay_shape;
  uint8_t mod2_decay_shape;
  uint8_t mod1_timbre_depth; 
  uint8_t mod2_timbre_depth;  
  uint8_t mod1_ad_ratio;
  uint8_t mod2_ad_ratio;
  uint8_t mod1_mode;
  uint8_t mod2_mode;
  uint8_t mod1_rate;
  uint8_t mod2_rate;  
  uint8_t mod1_color_depth; 
  uint8_t mod2_color_depth; 
  uint8_t mod1_level_depth; 
  uint8_t mod2_level_depth; 
  uint8_t mod1_vibrato_depth;   
  uint8_t mod2_vibrato_depth; 
  uint8_t mod1_mod2_depth;   
  uint8_t quantize_vibrato;  
  uint8_t mod1_sync; 
  uint8_t mod2_sync; 
  uint8_t osc_sync; 
  uint8_t metaseq_parameter_dest; // was mod1_mod2_timbre_depth 
  uint8_t fine_tune; // was mod1_mod2_color_depth 
  uint8_t mod1_mod2_vibrato_depth; 
  uint8_t initial_gain; 
  uint8_t metaseq;
  uint8_t metaseq_shape1;
  uint8_t metaseq_step_length1;
  uint8_t metaseq_shape2;
  uint8_t metaseq_step_length2;
  uint8_t metaseq_shape3;
  uint8_t metaseq_step_length3;
  uint8_t metaseq_shape4;
  uint8_t metaseq_step_length4;
  uint8_t metaseq_shape5;
  uint8_t metaseq_step_length5;
  uint8_t metaseq_shape6;
  uint8_t metaseq_step_length6;
  uint8_t metaseq_shape7;
  uint8_t metaseq_step_length7;
  uint8_t metaseq_shape8;
  uint8_t metaseq_step_length8;
  uint8_t sample_rate;  
  uint8_t metaseq_direction;
  uint8_t pitch_sample_hold;
  uint8_t metaseq_note1;
  uint8_t metaseq_note2;
  uint8_t metaseq_note3;
  uint8_t metaseq_note4;
  uint8_t metaseq_note5;
  uint8_t metaseq_note6;
  uint8_t metaseq_note7;
  uint8_t metaseq_note8;
  uint8_t metaseq_parameter1;
  uint8_t metaseq_parameter2;
  uint8_t metaseq_parameter3;
  uint8_t metaseq_parameter4;
  uint8_t metaseq_parameter5;
  uint8_t metaseq_parameter6;
  uint8_t metaseq_parameter7;
  uint8_t metaseq_parameter8;
  uint8_t metaseq_clock_div;
  uint8_t turing_clock_div;
  uint8_t turing_length;
  uint8_t turing_window;
  uint8_t turing_prob;
  uint8_t turing_init;
  uint8_t musical_scale;
  uint8_t edit_wrap;
  uint8_t extra_padding[2];
  int32_t pitch_cv_offset; 
  int32_t pitch_cv_scale; 
  int32_t fm_cv_offset; 
  char magic_byte;
};

struct SettingMetadata {
  uint8_t min_value;
  uint8_t max_value;
  const char name[5];
  const char* const* strings;
  
  int16_t Clip(int16_t value) const {
    if (value > max_value) {
      value = max_value;
    } else if (value < min_value) {
      value = min_value;
    }
    return value;
  }

  int16_t Wrap(int16_t value) const {
    if (value > max_value) {
      value = min_value;
    } else if (value < min_value) {
      value = max_value;
    }
    return value;
  }

};

class Settings {
 public:
  Settings() { }
  ~Settings() { }
  
  void Init();
  void Save();

  void Reset(bool except_cal_data);
  void SavePreset(uint16_t preset_slot);
  void LoadPreset(uint16_t preset_slot, bool load_calibration);
  void LoadSaved(bool load_calibration);

  void SetValue(Setting setting, uint8_t value) {
    uint8_t* data = static_cast<uint8_t*>(static_cast<void*>(&data_));
    data[setting] = value;
  }
  
  uint8_t GetValue(Setting setting) const {
    const uint8_t* data = static_cast<const uint8_t*>(
        static_cast<const void*>(&data_));
    return data[setting];
  }
  
  inline MacroOscillatorShape shape() const {
    return static_cast<MacroOscillatorShape>(data_.shape);
  }
  
  inline Resolution resolution() const {
    return static_cast<Resolution>(data_.resolution);
  }

  inline SampleRate sample_rate() const {
    return static_cast<SampleRate>(data_.sample_rate);
  }
  
  inline bool rate_inversion() const {
    return data_.rate_inversion;
  }
  
  inline PitchQuantization pitch_quantization() const {
    return static_cast<PitchQuantization>(data_.pitch_quantization);
  }

  inline uint16_t vco_drift() const {
    return data_.vco_drift;
  }

  inline uint8_t trig_delay() const {
    return data_.trig_delay;
  }

  inline uint8_t mod1_timbre_depth() const {
    return data_.mod1_timbre_depth * 2;
  }

  inline uint8_t mod2_timbre_depth() const {
    return data_.mod2_timbre_depth * 2;
  }

  inline uint8_t mod1_color_depth() const {
    return data_.mod1_color_depth * 2;
  }

  inline uint8_t mod2_color_depth() const {
    return data_.mod2_color_depth * 2;
  }

  inline uint8_t mod1_level_depth() const {
    return data_.mod1_level_depth * 2;
  }

  inline uint8_t mod2_level_depth() const {
    return data_.mod2_level_depth * 2;
  }

  inline bool quantize_vibrato() const {
    return data_.quantize_vibrato;
  }

  inline bool osc_sync() const {
    return data_.osc_sync;
  }

  inline int32_t fine_tune() const {
    return data_.fine_tune - 64;
  }

  inline bool mod1_mod2_vibrato_depth() const {
    return data_.mod1_mod2_vibrato_depth;
  }
  
  inline int32_t initial_gain() const {
    return (data_.initial_gain * 516);
  }

  inline uint8_t metaseq_step_length(uint8_t i) const {
    return GetValue(Setting(SETTING_METASEQ_STEP_LENGTH1 + i * 2));
  }

  inline int32_t metaseq_note(uint8_t i) const {
    return int32_t(GetValue(Setting(SETTING_METASEQ_NOTE1 + i)) - 31) ;
  }

  inline MacroOscillatorShape metaseq_shape(uint8_t i) const {
    return static_cast<MacroOscillatorShape>(GetValue(Setting(SETTING_METASEQ_SHAPE1 + i * 2)));
  }

  inline uint8_t metaseq_parameter(uint8_t i) const {
    return GetValue(Setting(SETTING_METASEQ_PARAMETER1 + i)) * 5;
  }

  inline bool pitch_sample_hold() const {
    return data_.pitch_sample_hold;
  }

  inline bool edit_wrap() const {
    return data_.edit_wrap;
  }
  
  inline const SettingsData& data() const { return data_; }
  inline SettingsData* mutable_data() { return &data_; }
  
  void Calibrate(
      int32_t adc_code_c2,
      int32_t adc_code_c4,
      int32_t adc_code_fm) {
    if (adc_code_c4 != adc_code_c2) {
      int32_t scale = (24 * 128 * 4096L) / (adc_code_c4 - adc_code_c2);
      data_.pitch_cv_scale = scale;
      data_.pitch_cv_offset = (60 << 7) - 
          (scale * ((adc_code_c2 + adc_code_c4) >> 1) >> 12);
      data_.fm_cv_offset = adc_code_fm;
    }
    Save();
  }
  
  inline int32_t adc_to_pitch(int32_t pitch_adc_code) const {
    if (data_.pitch_range == PITCH_RANGE_EXTERNAL ||
        data_.pitch_range == PITCH_RANGE_LFO) {
      pitch_adc_code = pitch_adc_code * data_.pitch_cv_scale >> 12;
      pitch_adc_code += data_.pitch_cv_offset;
    } else if (data_.pitch_range == PITCH_RANGE_FREE) {
      pitch_adc_code = (pitch_adc_code - 1638);
      pitch_adc_code = pitch_adc_code * data_.pitch_cv_scale >> 12;
      pitch_adc_code += 60 << 7;
    } else if (data_.pitch_range == PITCH_RANGE_440) {
      pitch_adc_code = 69 << 7;
    } else {
      pitch_adc_code = (pitch_adc_code - 1638) * 9 >> 1;
      pitch_adc_code += 60 << 7;
    }
    return pitch_adc_code;
  }
  
  inline int32_t pitch_transposition() const {
    int32_t t = data_.pitch_range == PITCH_RANGE_LFO ? -36 << 7 : 0;
    t += (static_cast<int32_t>(data_.pitch_octave) - 2) * 12 * 128;
    return t;
  }
  
  inline int32_t adc_to_fm(int32_t fm_adc_code) const {
    fm_adc_code -= data_.fm_cv_offset;
    fm_adc_code = fm_adc_code * 7680 >> 12;
    if (data_.pitch_range == PITCH_RANGE_440) {
      fm_adc_code = 0;
    }
    return fm_adc_code;
  }

  static const SettingMetadata& metadata(Setting setting) {
    return metadata_[setting];
  }

  static const Setting setting_at_index(int16_t index) {
    return settings_order_[index];
  }
  
 private:
  bool ValidateSettings() const;

  SettingsData data_;
  
  uint16_t version_token_;
  
  static const SettingMetadata metadata_[SETTING_LAST];
  static const Setting settings_order_[SETTING_LAST];

  DISALLOW_COPY_AND_ASSIGN(Settings);
};

extern Settings settings;
extern const SettingsData kInitSettings;
}  // namespace braids

#endif  // BRAIDS_SETTINGS_H_
