#pragma once

#ifndef _HEADINFO_H_
#define _HEADINFO_H_
#define __STDC_CONSTANT_MACROS
extern "C"{
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswresample/swresample.h>
	#include <libavutil/avstring.h>
	#include <libavutil/pixfmt.h>
	#include <libavutil/samplefmt.h>
	#include <libavutil/channel_layout.h>
	#include <libavutil/audio_fifo.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
	#include <windows.h>
	#include <process.h>
	#include <io.h>
	#include <direct.h>
    #include <jconfig.h>
	#include <jerror.h>
	#include <jinclude.h>
	#include <jmorecfg.h>
	#include <jpeglib.h>
}

#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 
#include <thread>
#include <sstream>
using namespace std;

#define OUTPUT_CHANNELS   2
#define OUTPUT_BIT_RATE   64000
#define NO_VALUE          -99999999   //初值



#define AV_DICT_SET_ERROR				-1				//参数设置错误
#define OPEN_INPUT_ERROER				-2				//打开流错误，网络不通
#define FIND_INFO_ERROER				-3				//查找流错误
#define NO_AUDIO_VIDEO_ERROR			-4              //找不到音视频
#define FIND_DECODER_ERROR				-5              //查找解码器错误
#define AVCODEC_OPEN_ERROR				-6              //打开解码器错误
#define SEARCH_I_FRAME_ERROR			-7              //寻找I帧错误

#define ADD_VIDEO_STREAM_ERROR			-8              //添加视频流错误
#define ADD_AUDIO_STREAM_ERROR			-9             //添加音频流错误

#define CREATE_MP4_ERROR				-10				//创建mp4头错误
#define ADD_H264_TRACK_ERROR			-11				//添加H264轨迹错误
#define ADD_AAC_TRACK_ERROR				-12             //添加aac轨迹错误
#define WRITE_AUDIO_DATA_ERROR			-13             //利用mp4v2写入音频帧错误
#define WRITE_H264DATA_ERROR			-14             //写入h264数据错误

#define DECODE_AUDIO_ERROR				-15             //音频解码错误
#define AUDIO_ENCODE_DATA_ERROR			-16             //音频编码错误
#define SWR_INIT_ERROR					-17             //swrcontex初始化失败
#define SWR_CONVERT_ERROR				-18             //重采样转换失败
#define REALLOCATE_FIFO_ERROR			-19             //重分配FIFO内存失败
#define WRITE_DATA_TO_FIFO_ERROR		-20             //写入数据到fifo失败
#define WRITE_AUDIO_PACKET_ERROR		-21             //利用ffmpeg写入音频帧错误
#define READ_DATA_FROM_FIFO_ERROR		-22             //从fifo读取数据错误
#define NO_VIDEO_ERROR					-23             //获取不到视频流


#define ALLOC_AVFORMATCONTEX_ERROR		-24             //分配avformat内存错误
#define ALLOC_AVFRAME_ERROR				-25             //分配帧内存错误
#define ALLOC_H264BUFFER_ERROR			-26             //分配h264内存错误
#define ALLOC_PACKET_DATA_ERROR			-27             //packet中数据分配内存错误
#define ALLOC_FIFO_ERROR				-28             //分配fifo内存错误
#define ALLOC_CONVERT_SAMPLES_ERROR		-29             //分配ConvertSamples内存失败
#define ALLOC_AV_SAMPLES_ERROR          -30             //分配samples失败
#define ALLOC_OUTPUT_FRAME_ERROR		-31             //分配输出samples错误

#define GET_FILE_DURATION_ERROR			-32				//获取时长错误
#define AVIO_OPEN_ERROR					-33				//打开文件错误
#define WRITE_HEAD_ERROR				-34				//写文件头错误
#define AV_INTERLEAVED_WRITE_ERROR		-35				//写入文件错误
#define AV_WRITE_TRAILER_ERROR			-36				//写文件尾错误 与流媒体服务器断开连接

#define GET_IP_ERROR					-37				//获取IP地址错误
#define OPEN_MP4_ERROR					-38				//打开mp4文件失败
#define AVPICTURE_FILL_ERROR			-39				//图片填充错误
#define DECODE_VIDEO_ERROR				-40				//视频解码错误
#define INITIALIZE_CONVERSION_ERROR		-41				//转换结构初始化错误
#define NULL_ADDRESS_ERROR				-42				//地址为空
#define COPY_STR_ERROR					-43				//复制字符串错误
#define ADD_STREAM_ERROR				-44				//添加流错误
#define AVCODEC_FIND_ENCODER_ERROR      -45             //查找编码器错误
#define AVCODEC_ENCODE_VIDEO2_ERROR     -46				//视频编码错误
#define AV_NEW_PACKET_ERROR				-47             //分配packet内存错误
#define AV_WRITE_FRAME_ERROR			-48             //写入帧数据错误
#define CAN_NOT_READ_FRAME_ERROR		-49             //mp4读取不到数据
#define MALLOC_ERROR					-50             //分配内存错误
#define AV_BITSTREAM_FILTER_ERROR		-51             //直播过滤错误
#define ALLOC_AVCODECCONTEXT_ERROR		-52             //分配avcodeccontext错误
#define COPY_CODECCONTEXT_ERROR			-53             //复制avcodeccontext错误
#define AV_AUDIO_SEND_FRAME_ERROR		-54             //音频send_frame错误
#define AV_VIDEO_SEND_PACKET_ERROR		-55             //视频send_packet错误
#define AV_AUDIO_SEND_PACKET_ERROR		-56             //音频send_packet错误
#define AV_AUDIO_RECEIRVE_FRAME_ERROR	-58             //音频receive_frame错误


//异常
#define INTERRUPT_NET_WORK_EXTREMELY -404     //中途断网


typedef struct{
	char inputURL[100];
    char name[250];
	char folder[250];
	int  flag;
    long s_time;
}RtspInfo;

typedef struct{
	char rtspURL[100];
    char rtmpURL[100];
	char folder[250];
	int  flag;
    long s_time;
}RtmpInfo;

typedef struct{
	char rtspURL[100];
	int  flag;
    long s_time;
}ConnectInfo;

typedef struct{
	char rtmpURL[100];
	int  flag;
	char name[250];
	char folder[250];
    long s_time;
}VGAInfo;

#endif