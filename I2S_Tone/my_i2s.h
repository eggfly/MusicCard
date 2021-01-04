#ifndef MY_I2S_H
#define MY_I2S_H


#include <driver/i2s.h>
#include <driver/dac.h>

/* I2S DAC */
#define  DAC_CHANNEL            DAC_CHANNEL_1                   // GPIO25 channel

#define I2S_PORT_NO                I2S_NUM_0
#define I2S_SAMPLE_RATE         8000
#define I2S_BITS_PER_SAMPLE     I2S_BITS_PER_SAMPLE_16BIT
#define I2S_CHANNELS_NUM        I2S_CHANNEL_MONO
#define I2S_CHANNEL_FORMAT      I2S_CHANNEL_FMT_ONLY_RIGHT
#define I2S_DAC_CHANNEL         I2S_DAC_CHANNEL_RIGHT_EN        // corresponds to DAC 1 channel

#define SINE_SAMPLES_NUM            256
#define SINE_800HZ_SAMPLES_NUM      10


#define NOTE_B4 493.88
#define NOTE_C5 523.25
#define NOTE_CS5 554.37
#define NOTE_D5 587.33
#define NOTE_DS5 622.25
#define NOTE_E5 659.26
#define NOTE_F5 698.46
#define NOTE_FS5 739.99
#define NOTE_G5 783.99
#define NOTE_GS5 830.61
#define NOTE_A5 880
#define NOTE_AS5 932.33
#define NOTE_B5 987.77

const i2s_config_t i2s_config = {
  .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
  .sample_rate =  I2S_SAMPLE_RATE,
  .bits_per_sample = I2S_BITS_PER_SAMPLE,
  .channel_format = I2S_CHANNEL_FORMAT,
  .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
  .intr_alloc_flags = 0,
  .dma_buf_count = 2,
  .dma_buf_len = 128,
  .use_apll = false,
  // .fixed_mclk = 0,
};

#endif
