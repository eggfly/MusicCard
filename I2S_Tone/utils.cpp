#include "utils.h"
#include "my_i2s.h"

uint8_t gainF2P6; // Fixed point 2.6

int16_t Amplify(int16_t s) {
  int32_t v = (s * gainF2P6) >> 6;
  if (v < -32767) return -32767;
  else if (v > 32767) return 32767;
  else return (int16_t)(v & 0xffff);
}

static uint16_t cache;

bool SetGain(float f) {
  if (f > 4.0) f = 4.0;
  if (f < 0.0) f = 0.0;
  gainF2P6 = (uint8_t)(f * (1 << 6));
  return true;
}

static bool init_all_tones() {
  auto freq = NOTE_A5; // 523.25
  auto sample_rate = 22050.0;

  auto count = (int)(sample_rate / freq);
  auto start = micros();
  auto delta_x = 2 * PI / count;
  for (long i = 0; i < count; i++) {
    int16_t value = (int16_t)(sin(delta_x * i) * 32767);
    int16_t v = Amplify(value);
    cache = v;
    // Serial.printf("%d\n", value);
  }
  auto cost = micros() - start;
  Serial.printf("count: %d, cost: %d micros, cost@%fHz=%f s\n", count, cost, sample_rate, cost * sample_rate / count / 1000000.0);
  if (cache == 0) {
    Serial.println();
  }
}
