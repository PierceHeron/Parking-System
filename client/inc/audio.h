/*************************************************************************
 * @Filename              :  audio.h
 * @Author                :  haidee
 * @Email                 :  1003261954@qq.com
 * @Date                  :  2018-08-15 Wed
 * @Last modified by      :  haidee
 * @Last modified time    :  2018-08-20 Mon
 ************************************************************************/


#ifndef __AUDIO_H
#define __AUDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <malloc.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <locale.h>

#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <alsa/asoundlib.h>

#define 	WAV_FMT_PCM 	0x0001

#define 	MIN(a,b)	\
		({		\
			typeof(a) _a = a;	\
			typeof(b) _b = b;	\
			(void)(_a == _b);	\
			_a < _b ? _a : _b;	\
		})

typedef		long long	off64_t;

//==================================================//

//RIFF块
struct wav_header
{
	uint32_t id;		//固定为RIFF
	uint32_t size;		//除了ID与size之外，整个wav文件的大小
	uint32_t format;	//fmt chunk的格式，此处为WAVE
};

//fmt块
struct wav_fmt
{
	uint32_t fmt_id;		//固定为fmt
	uint32_t fmt_size;		//在fmt块的大小，固定为16个字节
	uint16_t fmt;			//data块中数据的格式代码
	uint16_t channels;		//音轨数目：1为单音轨， 2为立体声
	uint32_t sample_rate;		//采样频率
	uint32_t byte_rate;		//码率 = 采样鹿X帧大小
	uint16_t block_align;		//帧大小 = 音轨数X量化级/8
	uint16_t bits_per_sample;	//量化位数： 典型值是8、16、32
};

//data块
struct wav_data
{
	uint32_t data_id;		//固定为data
	uint32_t data_size;		//除了wav格式头之外的音频数据大小
};

typedef struct
{
	struct wav_header head;
	struct wav_fmt format;
	struct wav_data data;
}wav_format;

//===================================================//

typedef struct
{
	snd_pcm_t *handle;			//PCM设备操作句柄
	snd_pcm_format_t format;		//数据格式

	uint16_t channels;
	size_t bits_per_sample;			//一个采样点内的位数（8位、16位）
	size_t bytes_per_frame;			//一个帧内的字节数

	snd_pcm_uframes_t frames_per_period;	//一个周期内的帧个数
	snd_pcm_uframes_t frames_per_buffer;	//系统buffer的帧个数

	uint8_t *period_buf;			//存放从wav文件中读取的一个周期的数据

}pcm_container;

//===================================================//

// 根据本系统的具体字节序处理的存放格式
#if __BYTE_ORDER == __LITTLE_ENDIAN

#define 	RIFF 	('F'<<24 | 'F'<<16 | 'I'<<8 | 'R'<<0)
#define 	WAVE 	('E'<<24 | 'V'<<16 | 'A'<<8 | 'W'<<0)
#define 	FMT 	(' '<<24 | 't'<<16 | 'm'<<8 | 'f'<<0)
#define 	DATA 	('a'<<24 | 't'<<16 | 'a'<<8 | 'd'<<0)

#define 	LE_SHORT(val)  	(val)
#define 	LE_INT(val)	(val)

#elif __BYTE_ORDER == __BIG_ENDIAN

#define 	RIFF 	('R'<<24 | 'I'<<16 | 'F'<<8 | 'F'<<0)
#define 	WAVE 	('W'<<24 | 'A'<<16 | 'V'<<8 | 'E'<<0)
#define 	FMT 	('f'<<24 | 'm'<<16 | 't'<<8 | ' '<<0)
#define 	DATA 	('d'<<24 | 'a'<<16 | 't'<<8 | 'a'<<0)

#define 	LE_SHORT(val) 	bswap_16(val)
#define 	LE_INT(val)	bswap_32(val)

#endif

#define DURATION_TIME 3

void prepare_wav_params(wav_format *wav);
void set_wav_params(pcm_container *sound, wav_format *wav);

snd_pcm_uframes_t read_pcm_data(pcm_container *sound,snd_pcm_uframes_t frames);
void recorder(int fd, pcm_container *sound, wav_format *wav);

int check_wav_format(wav_format *wav);
int get_wav_header_info(int fd, wav_format *wav);

int set_params(pcm_container *pcm, wav_format *wav);

ssize_t read_pcm_from_wav(int fd, void *buf, size_t count);
void play_wav(pcm_container *pcm, wav_format *wav, int fd);

void User_Recorder(char * filename);
void User_Player(char * filename);

#endif
