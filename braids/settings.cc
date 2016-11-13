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

#include "braids/settings.h"
#include "braids/preset_storage.h"

#include <cstring>

// Replace with custom storage for version 4.1 and later
// #include "stmlib/system/storage.h"
#include "braids/page_storage.h"

namespace braids {

using namespace stmlib;

const SettingsData kInitSettings = {
  MACRO_OSC_SHAPE_CSAW, // shape
  RESOLUTION_16_BIT,    // resolution
  true,                 // rate_inversion
  false,                // auto_trig (Trig source)
  1,                    // trig_delay
  false,                // meta_modulation
  PITCH_RANGE_EXTERNAL, // pitch_range
  2,                    // pitch_octave
  PITCH_QUANTIZATION_OFF, //pitch_quantization
  0,                    // vco_drift 
  2,                    // brightness
  0,                    // mod1_attack_shape
  0,                    // mod2_attack_shape
  0,                    // mod1_decay_shape
  0,                    // mod2_decay_shape
  0,                    // mod1_timbre_depth
  0,                    // mod2_timbre_depth
  63,                   // mod1_ad_ratio
  63,                   // mod2_ad_ratio
  0,                    // mod1_mode
  0,                    // mod2_mode  
  20,                   // mod1_rate
  20,                   // mod2_rate  
  0,                    // mod1_color_depth
  0,                    // mod2_color_depth
  0,                    // mod1_level_depth
  0,                    // mod2_level_depth   
  0,                    // mod1_vibrato_depth
  0,                    // mod2_vibrato_depth
  0,                    // mod1_mod2_depth
  false,                // quantize_vibrato
  1,                    // mod1_sync
  1,                    // mod2_sync
  false,                // osc_sync
  0,                    // metaseq_parameter_dest, was mod1_mod2_timbre_depth
  31,                   // fine_tune, was mod1_mod2_color_depth
  false,                // mod1_mod2_vibrato_depth
  127,                  // initial_gain = 65535
  0,                    // metaseq
  0,                    // metaseq_shape1
  1,                    // metaseq_step_length1
  0,                    // metaseq_shape2
  1,                    // metaseq_step_length2
  0,                    // metaseq_shape3
  1,                    // metaseq_step_length3
  0,                    // metaseq_shape4
  1,                    // metaseq_step_length4
  0,                    // metaseq_shape5
  1,                    // metaseq_step_length5
  0,                    // metaseq_shape6
  1,                    // metaseq_step_length6
  0,                    // metaseq_shape7
  1,                    // metaseq_step_length7
  0,                    // metaseq_shape8
  1,                    // metaseq_step_length8
  SAMPLE_RATE_96K,      // sample_rate
  0,                    // metaseq_direction
  0,                    // reset_type
  false,                // pitch_sample_hold
  31,                   // metaseq_note1
  31,                   // metaseq_note2
  31,                   // metaseq_note3
  31,                   // metaseq_note4
  31,                   // metaseq_note5
  31,                   // metaseq_note6
  31,                   // metaseq_note7
  31,                   // metaseq_note8
  127,                  // metaseq_parameter1
  127,                  // metaseq_parameter2
  127,                  // metaseq_parameter3
  127,                  // metaseq_parameter4
  127,                  // metaseq_parameter5
  127,                  // metaseq_parameter6
  127,                  // metaseq_parameter7
  127,                  // metaseq_parameter8
  1,                    // metaseq_clock_div
  1,                    // turing_clock_div
  0,                    // turing_length
  12,                   // turing_window
  0,                    // turing_prob
  0,                    // turing_init
  0,                    // musical_scale
  false,                // edit wrap
  0,                    // padding
  50,                   // pitch_cv_offset
  15401,                // pitch_cv_scale
  2048,                 // fm_cv_offset
  'B'
};

Storage<0x8020000, 3> storage;

void Settings::Init() {
  if (!storage.ParsimoniousLoad(&data_, &version_token_) ||
      !ValidateSettings()) {
    Reset(false);
  }
}

bool Settings::ValidateSettings() const {
  bool settings_within_range = true;
  for (int32_t i = 0; i <= SETTING_LAST_EDITABLE_SETTING; ++i) {
    const Setting setting = static_cast<Setting>(i);
    const SettingMetadata& setting_metadata = metadata(setting);
    uint8_t value = GetValue(setting);
    settings_within_range = settings_within_range && \
        value >= setting_metadata.min_value && \
        value <= setting_metadata.max_value;
  }

  settings_within_range = settings_within_range && data_.magic_byte == 'B';
  return settings_within_range;
}

void Settings::Reset(bool except_cal_data) {
  if (except_cal_data) {
     int32_t saved_pitch_cv_offset = data_.pitch_cv_offset; 
     int32_t saved_pitch_cv_scale = data_.pitch_cv_scale; 
     int32_t saved_fm_cv_offset = data_.fm_cv_offset; 
     memcpy(&data_, &kInitSettings, sizeof(SettingsData));
     data_.pitch_cv_offset = saved_pitch_cv_offset; 
     data_.pitch_cv_scale = saved_pitch_cv_scale; 
     data_.fm_cv_offset = saved_fm_cv_offset; 
  } else {
     memcpy(&data_, &kInitSettings, sizeof(SettingsData));
  }
  data_.magic_byte = 'B';
}

void Settings::Save() {
  data_.magic_byte = 'B';
  storage.ParsimoniousSave(data_, &version_token_);
}

void Settings::SavePreset(uint16_t preset_slot) {
  preset_storage.Save(preset_slot, &data_, "\0\0\0\0");
}

void Settings::LoadPreset(uint16_t preset_slot, bool load_calibration) {
  preset_storage.Load(preset_slot, &data_, load_calibration);
    
  if (!ValidateSettings()) {
    Reset(!load_calibration);
  }
}

void Settings::LoadSaved(bool load_calibration) {
  const int32_t pitch_cv_offset = data_.pitch_cv_offset;
  const int32_t pitch_cv_scale = data_.pitch_cv_scale;
  const int32_t fm_cv_offset = data_.fm_cv_offset;

  Init();
  if (!load_calibration) {
    data_.pitch_cv_offset = pitch_cv_offset;
    data_.pitch_cv_scale = pitch_cv_scale;
    data_.fm_cv_offset = fm_cv_offset;
  }
}

const char* const boolean_values[] = { "OFF ", "ON  " };

const char* const algo_values[] = {
    "CSAW",
    "^\x88\x8D_",
    "\x88\x8A\x8C\x8D",
    "SYNC",
    "FOLD",
    "\x8E\x8E\x8E\x8E",
    "\x88\x88x3",
    "\x8C_x3",
    "/\\x3",
    "SIx3",
    "RING",
    "\x88\x89\x88\x89",
    "\x88\x88\x8E\x8E",
    "TOY*",
    "ZLPF",
    "ZPKF",
    "ZBPF",
    "ZHPF",
    "VOSM",
    "VOWL",
    "VFOF",
    "FM  ",
    "FBFM",
    "WTFM",
    "PLUK",
    "BOWD",
    "BLOW",
    "FLUT",
    "BELL",
    "DRUM",
    "KICK",
    "CYMB",
    "SNAR",
    "WTBL",
    "WMAP",
    "WLIN",
    "WTx4",
    // "NOIS",
    // "TWNQ",
    "CLKN",
    "CLOU",
    // "PRTC",
    "BYT0",
    "BYT1",
    "BYT2",
    "BYT3",
    "ZERO", // this is the RenderSilence digital model 
};

const char* const bits_values[] = {
    "2BIT", // 0
    "3BIT", // 1
    "4BIT", // 2
    "6BIT", // 3
    "8BIT", // 4
    "12B", // 5
    "16B", // 6
};

const char* const sample_rate_values[] = {
    "4K", // 0
    "8K", // 1
    "16K",  // 2
    "24K",  // 3
    "32K",  // 4
    "48K",  // 5
    "96K" }; // 6

  
const char* const mod_rate_values[] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "17",
    "18",
    "19",
    "20",
    "21",
    "22",
    "23",
    "24",
    "25",
    "26",
    "27",
    "28",
    "29",
    "30",
    "31",
    "32",
    "33",
    "34",
    "35",
    "36",
    "37",
    "38",
    "39",
    "40",
    "41",
    "42",
    "43",
    "44",
    "45",
    "46",
    "47",
    "48",
    "49",
    "50",
    "51",
    "52",
    "53",
    "54",
    "55",
    "56",
    "57",
    "58",
    "59",
    "60",
    "61",
    "62",
    "63",
    "64",
    "65",
    "66",
    "67",
    "68",
    "69",
    "70",
    "71",
    "72",
    "73",
    "74",
    "75",
    "76",
    "77",
    "78",
    "79",
    "80",
    "81",
    "82",
    "83",
    "84",
    "85",
    "86",
    "87",
    "88",
    "89",
    "90",
    "91",
    "92",
    "93",
    "94",
    "95",
    "96",
    "97",
    "98",
    "99",
    "100",
    "101",
    "102",
    "103",
    "104",
    "105",
    "106",
    "107",
    "108",
    "109",
    "110",
    "111",
    "112",
    "113",
    "114",
    "115",
    "116",
    "117",
    "118",
    "119",
    "120",
    "121",
    "122",
    "123",
    "124",
    "125",
    "126",
    "127",
};

const char* const bipolar_values[] = {
    "-31", // 0
    "-30",
    "-29",
    "-28",
    "-27",
    "-26",
    "-25",
    "-24",
    "-23",
    "-22",
    "-21",
    "-20",
    "-19",
    "-18",
    "-17",
    "-16",
    "-15",
    "-14",
    "-13",
    "-12",
    "-11",
    "-10",
    "-9",
    "-8",
    "-7",
    "-6",
    "-5",
    "-4",
    "-3",
    "-2",
    "-1",
    "0", // 31
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "17",
    "18",
    "19",
    "20",
    "21",
    "22",
    "23",
    "24",
    "25",
    "26",
    "27",
    "28",
    "29",
    "30",
    "31",
};

    
const char* const quantization_values[] = { 
    "OFF",  // 0
    "QTR",  // 1
    "SEMI", // 2
    "ION",  // 3
    "DOR",  
    "PHR",
    "LYD",
    "MIXO",
    "AEOL",
    "LOCR",
    "BLMJ",
    "BLMN",
    "5MAJ",
    "5MIN",
    "BHAI",
    "SHRI",
    "RUPA",
    "TODI",
    "RAGE",
    "KAAF",
    "MEGH",
    "MALK",
    "DEEP",
    "FOLK",
    "JAPN",
    "GAML",
    "WHOL", // 26
};

const char* const trig_source_values[] = { "EXT", "AUTO" };

const char* const pitch_range_values[] = {
    "EXT",
    "FREE",
    "XTND",
    "440",
    "LFO"
};

const char* const octave_values[] = { "-2", "-1", "0", "1", "2" };

const char* const trig_delay_values[] = {
    "NONE",
    "125u",
    "250u",
    "500u",
    "1ms",
    "2ms",
    "4ms"
};

const char* const brightness_values[] = {
    "LOW",
    "MED",
    "HIGH",
};

const char* const meta_values[] = { 
    "FREQ", // 0
    "META", // 1
    "RATE", // 2
    "RAT1", // 3
    "RAT2", // 4
    "DCAY", // 5
    "DCY1", // 6
    "DCY2", // 7
    "LEVL", // 8 
    "HARM", // 9 = harmonic intervals,
    "TRNG", // 10 = Turing Machine shift register length 0 to 32
    "PROB", // 11 = Turing Machine probability 0 to 127
    "SPAN", // 12 = Turing Machine range (window) 2 to 36
    "JITR", // 13 
    "BITS", // 14 
    "SRAT", // 15 
    "SMUT", // 16 = BITS + SRAT 
    "FCKD", // 17 = BITS + SRAT + JITR 
};

const char* const mod_shape_values[] = { 
    "EXPO",  // 0 exponentially-curved triangle
    "LINR",  // 1 linear triangle
    "WIGL",  // 2 wiggly, using ws_sine_fold (a show about nothing?)
    "SINE",  // 3 sine-ish, using ws_moderate_overdrive
    "SQRE",  // 4 square-ish, using ws_violent_overdrive
    "BOWF",  // 5 bowing friction LUT
    "RNDE",  // 6 random target, exponent easing to it
    "RNDL",  // 7 random target, linear easing to it
    "RNDS",  // 8 random target, rounded square-ish easing to it 
    "RNDM",  // 9 random value, may cause clicks due to sudden jumps
};

const char* const mod_mode_values[] = { 
    "OFF",  // 0 
    "LFO",  // 1 
    "ENV-",  // 2 
    "ENV+",  // 3 
};

const char* const metaseq_values[] = {
    "OFF",  // 0
    "2",    // 1
    "3",    // 2
    "4",    // 3
    "5",    // 4
    "6",    // 5
    "7",    // 6
    "8",    // 7
};

const char* const metaseq_dir_values[] = {
    "LOOP", // 0
    "SWNG", // 1
    "RNDM", // 2
};

const char* const reset_type_values[] = {
    "NO", // 0
    "DFLT", // 1
    "NO", // 2
    "FULL", // 3
};

const char* const metaseq_parameter_dest_values[] = {
    "NONE", // 0
    "TIMB", // 1
    "COLR", // 2
    "T+C",  // 3
    "LEVL", // 4
    "T+L",  // 5
    "C+L",  // 6
    "TLC",  // 7
};

const char* const musical_scale_values[] = {
    "CHRM", // 0=chromatic
    "ION",  // 1
    "DOR",  
    "PHR",
    "LYD",
    "MIXO",
    "AEOL",
    "LOCR",
    "BLMJ",
    "BLMN",
    "5MAJ",
    "5MIN",
    "BHAI",
    "SHRI",
    "RUPA",
    "TODI",
    "RAGE",
    "KAAF",
    "MEGH",
    "MALK",
    "DEEP",
    "FOLK",
    "JAPN",
    "GAML",
    "WHOL", // 24
    "HARM", // 25=Harmonic 
};

/* static */
const SettingMetadata Settings::metadata_[] = {
  { 0, MACRO_OSC_SHAPE_LAST - 1, "SAVE", algo_values },
  { 0, RESOLUTION_LAST - 1, "BITS", bits_values },
  { 0, 1, "RINV", boolean_values },
  { 0, 1, "TSRC", trig_source_values },
  { 0, 6, "TDLY", trig_delay_values },
  { 0, 17, "FMCV", meta_values },
  { 0, 4, "RANG", pitch_range_values }, // enable LFO pitch range
  { 0, 4, "OCTV", octave_values },
  { 0, PITCH_QUANTIZATION_LAST - 1, "QNTZ", quantization_values },
  { 0, 127, "JITR", mod_rate_values },
  { 0, 2, "BRIG", brightness_values },
  { 0, 9, "\x83" "SH1", mod_shape_values },
  { 0, 9, "\x83" "SH2", mod_shape_values },
  { 0, 9, "\x82" "SH1", mod_shape_values },
  { 0, 9, "\x82" "SH2", mod_shape_values },
  { 0, 127, "M1" "\x85" "T", mod_rate_values },
  { 0, 127, "M2" "\x85" "T", mod_rate_values },
  { 0, 127, "\x83" "\x82" "1", mod_rate_values },
  { 0, 127, "\x83" "\x82" "2", mod_rate_values },
  { 0, 3, "MOD1", mod_mode_values },
  { 0, 3, "MOD2", mod_mode_values },
  { 0, 127, "RAT1", mod_rate_values },
  { 0, 127, "RAT2", mod_rate_values },
  { 0, 127, "M1" "\x85" "C", mod_rate_values },
  { 0, 127, "M2" "\x85" "C", mod_rate_values },
  { 0, 127, "M1" "\x85" "L", mod_rate_values },
  { 0, 127, "M2" "\x85" "L", mod_rate_values },
  { 0, 127, "M1" "\x85" "F", mod_rate_values },
  { 0, 127, "M2" "\x85" "F", mod_rate_values },
  { 0, 127, "M1" "\x85" "2", mod_rate_values },
  { 0, 1, "QVIB", boolean_values },
  { 0, 127, "M1SY", mod_rate_values },
  { 0, 127, "M2SY", mod_rate_values },
  { 0, 1, "OSYN", boolean_values },
  { 0, 7, "MSPD", metaseq_parameter_dest_values }, 
  { 0, 62, "FTUN", bipolar_values }, // was M1C2
  { 0, 1, "M1F2", boolean_values },
  { 0, 127, "LEVL", mod_rate_values },
  { 0, 7, "MSEQ", metaseq_values },
  { 0, MACRO_OSC_SHAPE_LAST - 1, "WAV1", algo_values },
  { 1, 127, "RPT1", mod_rate_values },
  { 0, MACRO_OSC_SHAPE_LAST - 1, "WAV2", algo_values },
  { 1, 127, "RPT2", mod_rate_values },
  { 0, MACRO_OSC_SHAPE_LAST - 1, "WAV3", algo_values },
  { 1, 127, "RPT3", mod_rate_values },
  { 0, MACRO_OSC_SHAPE_LAST - 1, "WAV4", algo_values },
  { 1, 127, "RPT4", mod_rate_values },
  { 0, MACRO_OSC_SHAPE_LAST - 1, "WAV5", algo_values },
  { 1, 127, "RPT5", mod_rate_values },
  { 0, MACRO_OSC_SHAPE_LAST - 1, "WAV6", algo_values },
  { 1, 127, "RPT6", mod_rate_values },
  { 0, MACRO_OSC_SHAPE_LAST - 1, "WAV7", algo_values },
  { 1, 127, "RPT7", mod_rate_values },
  { 0, MACRO_OSC_SHAPE_LAST - 1, "WAV8", algo_values },
  { 1, 127, "RPT8", mod_rate_values },
  { 0, SAMPLE_RATE_LAST - 1, "SRAT", sample_rate_values },  
  { 0, 2, "MDIR", metaseq_dir_values },
  { 0, 3, "RST ", reset_type_values },
  { 0, 1, "FS+H", boolean_values },
  { 0, 62, "NOT1", bipolar_values },
  { 0, 62, "NOT2", bipolar_values },
  { 0, 62, "NOT3", bipolar_values },
  { 0, 62, "NOT4", bipolar_values },
  { 0, 62, "NOT5", bipolar_values },
  { 0, 62, "NOT6", bipolar_values },
  { 0, 62, "NOT7", bipolar_values },
  { 0, 62, "NOT8", bipolar_values },
  { 0, 127, "PAR1", mod_rate_values },
  { 0, 127, "PAR2", mod_rate_values },
  { 0, 127, "PAR3", mod_rate_values },
  { 0, 127, "PAR4", mod_rate_values },
  { 0, 127, "PAR5", mod_rate_values },
  { 0, 127, "PAR6", mod_rate_values },
  { 0, 127, "PAR7", mod_rate_values },
  { 0, 127, "PAR8", mod_rate_values },
  { 1, 127, "MDIV", mod_rate_values },
  { 1, 127, "TDIV", mod_rate_values },
  { 0, 32, "TRNG", mod_rate_values },
  { 2, 36, "SPAN", mod_rate_values }, // was WIND, turing_window
  { 0, 127, "PROB", mod_rate_values },
  { 0, 127, "SEED", mod_rate_values },
  { 0, 25, "SCAL", musical_scale_values },
  { 0, 1, "WRAP", boolean_values },
  { 0, 0, "CAL.", NULL },
  { 0, 0, "    ", NULL },  // Placeholder for CV tester
  { 0, 0, "v4.1", NULL },  // Placeholder for version string
  { 0, 0, "LOAD", NULL },  // Placeholder for preset loading
};

/* static */
const Setting Settings::settings_order_[] = {
  SETTING_OSCILLATOR_SHAPE,
  SETTING_LOAD_PRESET,
  SETTING_INITIAL_GAIN,
  SETTING_META_MODULATION,
  SETTING_MOD1_MODE,
  SETTING_MOD1_RATE,
  SETTING_MOD1_AD_RATIO,
  SETTING_MOD1_ATTACK_SHAPE,
  SETTING_MOD1_DECAY_SHAPE,
  SETTING_MOD1_SYNC,
  SETTING_MOD1_TIMBRE_DEPTH,
  SETTING_MOD1_COLOR_DEPTH,
  SETTING_MOD1_LEVEL_DEPTH,
  SETTING_MOD1_VIBRATO_DEPTH,
  SETTING_MOD1_MOD2_DEPTH,
  SETTING_MOD2_MODE,
  SETTING_MOD2_RATE,
  SETTING_MOD2_AD_RATIO,
  SETTING_MOD2_ATTACK_SHAPE,
  SETTING_MOD2_DECAY_SHAPE,
  SETTING_MOD2_SYNC,
  SETTING_MOD2_TIMBRE_DEPTH,
  SETTING_MOD2_COLOR_DEPTH,
  SETTING_MOD2_LEVEL_DEPTH,
  SETTING_MOD2_VIBRATO_DEPTH,
  SETTING_MOD1_MOD2_VIBRATO_DEPTH,
  SETTING_OSC_SYNC,
  SETTING_RATE_INVERSION, 
  SETTING_BRIGHTNESS, 
  SETTING_EDIT_WRAP,
  SETTING_CALIBRATION,
  SETTING_CV_TESTER,
  SETTING_VERSION,
  SETTING_PITCH_RANGE,
  SETTING_PITCH_SAMPLE_HOLD,
  SETTING_PITCH_QUANTIZER,
  SETTING_QUANT_BEFORE_VIBRATO,
  SETTING_TRIG_DELAY,
  SETTING_TRIG_SOURCE,
  SETTING_RESOLUTION,
  SETTING_SAMPLE_RATE,
  SETTING_VCO_DRIFT,
  SETTING_METASEQ,
  SETTING_METASEQ_CLOCK_DIV,
  SETTING_METASEQ_DIRECTION, 
  SETTING_METASEQ_SHAPE1, 
  SETTING_METASEQ_SHAPE2, 
  SETTING_METASEQ_SHAPE3, 
  SETTING_METASEQ_SHAPE4, 
  SETTING_METASEQ_SHAPE5, 
  SETTING_METASEQ_SHAPE6, 
  SETTING_METASEQ_SHAPE7, 
  SETTING_METASEQ_SHAPE8, 
  SETTING_METASEQ_NOTE1,
  SETTING_METASEQ_NOTE2,
  SETTING_METASEQ_NOTE3,
  SETTING_METASEQ_NOTE4,
  SETTING_METASEQ_NOTE5,
  SETTING_METASEQ_NOTE6,
  SETTING_METASEQ_NOTE7,
  SETTING_METASEQ_NOTE8,
  SETTING_METASEQ_STEP_LENGTH1, 
  SETTING_METASEQ_STEP_LENGTH2, 
  SETTING_METASEQ_STEP_LENGTH3, 
  SETTING_METASEQ_STEP_LENGTH4, 
  SETTING_METASEQ_STEP_LENGTH5, 
  SETTING_METASEQ_STEP_LENGTH6, 
  SETTING_METASEQ_STEP_LENGTH7, 
  SETTING_METASEQ_STEP_LENGTH8, 
  SETTING_METASEQ_PARAMETER_DEST,
  SETTING_METASEQ_PARAMETER1,
  SETTING_METASEQ_PARAMETER2,
  SETTING_METASEQ_PARAMETER3,
  SETTING_METASEQ_PARAMETER4,
  SETTING_METASEQ_PARAMETER5,
  SETTING_METASEQ_PARAMETER6,
  SETTING_METASEQ_PARAMETER7,
  SETTING_METASEQ_PARAMETER8,
  SETTING_TURING_LENGTH,
  SETTING_TURING_WINDOW,
  SETTING_MUSICAL_SCALE,
  SETTING_TURING_PROB,
  SETTING_TURING_INIT,
  SETTING_TURING_CLOCK_DIV,
  SETTING_RESET_TYPE,
  SETTING_FINE_TUNE,
  SETTING_PITCH_OCTAVE,
};

/* extern */
Settings settings;

}  // namespace braids
