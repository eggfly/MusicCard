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


#define NOTE_C6 1047

#define NOTE_DS8 4978

/*

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
*/
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
