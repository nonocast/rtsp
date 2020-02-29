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
#define NO_VALUE          -99999999   //��ֵ



#define AV_DICT_SET_ERROR				-1				//�������ô���
#define OPEN_INPUT_ERROER				-2				//�����������粻ͨ
#define FIND_INFO_ERROER				-3				//����������
#define NO_AUDIO_VIDEO_ERROR			-4              //�Ҳ�������Ƶ
#define FIND_DECODER_ERROR				-5              //���ҽ���������
#define AVCODEC_OPEN_ERROR				-6              //�򿪽���������
#define SEARCH_I_FRAME_ERROR			-7              //Ѱ��I֡����

#define ADD_VIDEO_STREAM_ERROR			-8              //�����Ƶ������
#define ADD_AUDIO_STREAM_ERROR			-9             //�����Ƶ������

#define CREATE_MP4_ERROR				-10				//����mp4ͷ����
#define ADD_H264_TRACK_ERROR			-11				//���H264�켣����
#define ADD_AAC_TRACK_ERROR				-12             //���aac�켣����
#define WRITE_AUDIO_DATA_ERROR			-13             //����mp4v2д����Ƶ֡����
#define WRITE_H264DATA_ERROR			-14             //д��h264���ݴ���

#define DECODE_AUDIO_ERROR				-15             //��Ƶ�������
#define AUDIO_ENCODE_DATA_ERROR			-16             //��Ƶ�������
#define SWR_INIT_ERROR					-17             //swrcontex��ʼ��ʧ��
#define SWR_CONVERT_ERROR				-18             //�ز���ת��ʧ��
#define REALLOCATE_FIFO_ERROR			-19             //�ط���FIFO�ڴ�ʧ��
#define WRITE_DATA_TO_FIFO_ERROR		-20             //д�����ݵ�fifoʧ��
#define WRITE_AUDIO_PACKET_ERROR		-21             //����ffmpegд����Ƶ֡����
#define READ_DATA_FROM_FIFO_ERROR		-22             //��fifo��ȡ���ݴ���
#define NO_VIDEO_ERROR					-23             //��ȡ������Ƶ��


#define ALLOC_AVFORMATCONTEX_ERROR		-24             //����avformat�ڴ����
#define ALLOC_AVFRAME_ERROR				-25             //����֡�ڴ����
#define ALLOC_H264BUFFER_ERROR			-26             //����h264�ڴ����
#define ALLOC_PACKET_DATA_ERROR			-27             //packet�����ݷ����ڴ����
#define ALLOC_FIFO_ERROR				-28             //����fifo�ڴ����
#define ALLOC_CONVERT_SAMPLES_ERROR		-29             //����ConvertSamples�ڴ�ʧ��
#define ALLOC_AV_SAMPLES_ERROR          -30             //����samplesʧ��
#define ALLOC_OUTPUT_FRAME_ERROR		-31             //�������samples����

#define GET_FILE_DURATION_ERROR			-32				//��ȡʱ������
#define AVIO_OPEN_ERROR					-33				//���ļ�����
#define WRITE_HEAD_ERROR				-34				//д�ļ�ͷ����
#define AV_INTERLEAVED_WRITE_ERROR		-35				//д���ļ�����
#define AV_WRITE_TRAILER_ERROR			-36				//д�ļ�β���� ����ý��������Ͽ�����

#define GET_IP_ERROR					-37				//��ȡIP��ַ����
#define OPEN_MP4_ERROR					-38				//��mp4�ļ�ʧ��
#define AVPICTURE_FILL_ERROR			-39				//ͼƬ������
#define DECODE_VIDEO_ERROR				-40				//��Ƶ�������
#define INITIALIZE_CONVERSION_ERROR		-41				//ת���ṹ��ʼ������
#define NULL_ADDRESS_ERROR				-42				//��ַΪ��
#define COPY_STR_ERROR					-43				//�����ַ�������
#define ADD_STREAM_ERROR				-44				//���������
#define AVCODEC_FIND_ENCODER_ERROR      -45             //���ұ���������
#define AVCODEC_ENCODE_VIDEO2_ERROR     -46				//��Ƶ�������
#define AV_NEW_PACKET_ERROR				-47             //����packet�ڴ����
#define AV_WRITE_FRAME_ERROR			-48             //д��֡���ݴ���
#define CAN_NOT_READ_FRAME_ERROR		-49             //mp4��ȡ��������
#define MALLOC_ERROR					-50             //�����ڴ����
#define AV_BITSTREAM_FILTER_ERROR		-51             //ֱ�����˴���
#define ALLOC_AVCODECCONTEXT_ERROR		-52             //����avcodeccontext����
#define COPY_CODECCONTEXT_ERROR			-53             //����avcodeccontext����
#define AV_AUDIO_SEND_FRAME_ERROR		-54             //��Ƶsend_frame����
#define AV_VIDEO_SEND_PACKET_ERROR		-55             //��Ƶsend_packet����
#define AV_AUDIO_SEND_PACKET_ERROR		-56             //��Ƶsend_packet����
#define AV_AUDIO_RECEIRVE_FRAME_ERROR	-58             //��Ƶreceive_frame����


//�쳣
#define INTERRUPT_NET_WORK_EXTREMELY -404     //��;����


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