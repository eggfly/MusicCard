
#include "my_i2s.h"
#include "utils.h"

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


void setup() {
  Serial.begin(115200);
  Serial.println("Hello!");

  SetGain(0.05);

  if (!prepare_i2s()) {
    Serial.println("Failed to initialize i2s");
    while (true);
  }
}

void loop() {
  // init_all_tones();
  play_samples_forever();
  // play_sound();
  //delay(10);
}

static long sample_time = 0;

#define sine_wave(count, i) \
  ((int16_t)(sin(2 * PI / count * i) * 8191));

#define square_wave(count, i) \
  ((int16_t) (i % count > count / 2 ? 4095 : 0));

static bool play_samples_forever() {
  auto start = millis();
  uint32_t i = 0;

  auto sample_rate = (double)I2S_SAMPLE_RATE;

  auto freq1 = NOTE_C5;
  auto freq2 = NOTE_E5;
  auto freq3 = NOTE_G5;
  auto freq4 = NOTE_C6;
  auto count1 = (int)(sample_rate / freq1);
  auto count2 = (int)(sample_rate / freq2);
  auto count3 = (int)(sample_rate / freq3);
  auto count4 = (int)(sample_rate / freq4);
  int mode = 0;
  while (1) {
    auto now = millis();
    if (now - start >= 1000) {
      start = now;
      Serial.printf("1 second! %d\n", i);
      mode++;
      mode %= 4;
      if (mode == 0) {
        Serial.printf("哆\n");
      } else if (mode == 1) {
        Serial.printf("哆+咪(和声)\n");
      } else if (mode == 2) {
        Serial.printf("哆+咪+搜(和声)\n");
      } else if (mode == 3) {
        Serial.printf("哆+咪+搜+高音哆(和声)\n");
      }
    }
    int16_t sample = 0;
    int16_t value1 = square_wave(count1, i);
    int16_t value2 = square_wave(count2, i);
    int16_t value3 = square_wave(count3, i);
    int16_t value4 = square_wave(count4, i);
    if (mode == 0) {
      sample += value1;
    } else if (mode == 1) {
      sample += value1;
      sample += value2;
    } else if (mode == 2) {
      sample += value1;
      sample += value2;
      sample += value3;
    } else if (mode == 3) {
      sample += value1;
      sample += value2;
      sample += value3;
      sample += value4;
    }
    // sample += value4;
    sample = Amplify(sample);
    // Serial.printf("%d\n", sample);
    size_t bytes_written;
    if (i2s_write(I2S_PORT_NO, (const char*)&sample, sizeof(sample) , &bytes_written, portMAX_DELAY) != ESP_OK) {
      Serial.printf("!=%d, return.\n", sizeof(sample));
      return false;
    }

    //    if (i2s_write_bytes(I2S_PORT_NO, (const char*)&sample, sizeof(sample) , portMAX_DELAY)
    //        != sizeof(sample)) {
    //      Serial.printf("!=%d, return.\n", sizeof(sample));
    //      return false;
    //    }
    i++;
  }
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
