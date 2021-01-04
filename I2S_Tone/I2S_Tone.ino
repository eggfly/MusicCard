
#include "my_i2s.h"



/*
  const uint16_t i2s_sine_wave_800hz[SINE_800HZ_SAMPLES_NUM] = {
    32768, 53830, 65038, 61145, 43975,
    21561,  4391,   498, 11706, 32768
  };*/


const int16_t i2s_sine_wave_800hz[SINE_800HZ_SAMPLES_NUM] = {
  0,       21062 >> 1,  32269 >> 1,  28377 >> 1,     11206 >> 1,
  -11206 >> 1, -28377 >> 1, -32269 >> 1, -21062 >> 1,     0
};

static bool prepare_i2s();
static bool play_sound();

static bool init_all_tones();

void setup() {
  Serial.begin(115200);
  Serial.println("Hello!");

  init_all_tones();
  if (!prepare_i2s()) {
    Serial.println("Failed to initialize i2s");
    while (true);
  }

  SetGain(0.02);
}

void loop() {
  play_sound();
  //delay(10);
}

uint8_t gainF2P6; // Fixed point 2.6

bool SetGain(float f) {
  if (f > 4.0) f = 4.0;
  if (f < 0.0) f = 0.0;
  gainF2P6 = (uint8_t)(f * (1 << 6));
  return true;
}

inline int16_t Amplify(int16_t s) {
  int32_t v = (s * gainF2P6) >> 6;
  if (v < -32767) return -32767;
  else if (v > 32767) return 32767;
  else return (int16_t)(v & 0xffff);
}

static bool init_all_tones() {
  auto freq = C5;
  for (int i = 0; i < 100; i++) {
    auto v = sin(PI);
    Serial.printf("\n");
  }
}

static bool play_sound() {
  static uint8_t sin_samples[SINE_800HZ_SAMPLES_NUM * 2];
  for (uint32_t i = 0; i < SINE_800HZ_SAMPLES_NUM; i++) {
    int16_t * p_sample16 = (int16_t*)&sin_samples[i * 2];
    *p_sample16 = Amplify(i2s_sine_wave_800hz[i]);
    // sin_samples[i * 2] = ((i2s_sine_wave_800hz[i]) >> 3) & 0xFF;
    // sin_samples[i * 2 + 1] = (i2s_sine_wave_800hz[i] >> 11) & 0xFF;
  }

  if (i2s_write_bytes(I2S_PORT_NO, (const char*)sin_samples, SINE_800HZ_SAMPLES_NUM * 2, portMAX_DELAY)
      != SINE_800HZ_SAMPLES_NUM * 2) {
    return false;
  }

  return true;
}


static bool prepare_i2s() {
  if (i2s_driver_install(I2S_PORT_NO, &i2s_config, 0, NULL) != ESP_OK) {
    Serial.println("Failed to initialize i2s driver");
    return false;
  }

  i2s_pin_config_t pins = {
    .bck_io_num = 26,
    .ws_io_num = 25,
    .data_out_num = 27,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  i2s_set_pin((i2s_port_t)I2S_PORT_NO, &pins);

  // i2s_set_sample_rates(I2S_PORT_NO, I2S_SAMPLE_RATE);

  return true;
}
