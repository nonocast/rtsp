#pragma once
#include "MP4Encoder.h"
//#pragma comment(lib, "../lib/libmp4v2.lib")


#define INVALID_PTS 0xFFFFFFFFFFFFFFFF

#define DEFAULT_VIDEO_TRACK_NUM 3
#define DEFAULT_VIDEO_PROFILE_LEVEL 1
#define DEFAULT_AUDIO_PROFILE_LEVEL 2



MP4Encoder::MP4Encoder(void)
	: m_hFile(MP4_INVALID_FILE_HANDLE)
	, m_videoTrack(MP4_INVALID_TRACK_ID)
	, m_audioTrack(MP4_INVALID_TRACK_ID)
{
}

MP4Encoder::~MP4Encoder(void)
{
}


int MP4Encoder::MP4CreateFile(const char *sFileName,int Movie_Time_Scale)
{
	m_hFile = MP4Create(sFileName);
	if (m_hFile == MP4_INVALID_FILE_HANDLE)
	{
		printf("create mp4 file error!\n");
		return -1;
	}
	if (!MP4SetTimeScale(m_hFile, Movie_Time_Scale))
	{
		printf("set time Scale error!\n");
		return -1;
	}
	return 0;
}

int  MP4Encoder::MP4AddH264Track(const uint8_t *sData, int nSize,
	int nWidth, int nHeight, int nFrameRate ,int Video_Time_Scale)
{
	int sps, pps;
	for (sps = 0; sps < nSize;)
		if (sData[sps++] == 0x00 && sData[sps++] == 0x00 && sData[sps++] == 0x00
			&& sData[sps++] == 0x01)
			break;
	for (pps = sps; pps < nSize;)
		if (sData[pps++] == 0x00 && sData[pps++] == 0x00 && sData[pps++] == 0x00
			&& sData[pps++] == 0x01)
			break;
	if (sps >= nSize || pps >= nSize)
		return -1;
	m_videoTrack = MP4AddH264VideoTrack(m_hFile, Video_Time_Scale,
		Video_Time_Scale / nFrameRate, nWidth, nHeight,
		sData[sps + 1], sData[sps + 2], sData[sps + 3], DEFAULT_VIDEO_TRACK_NUM);//sps 后面的三个字节
	if (MP4_INVALID_TRACK_ID == m_videoTrack)
	{
		printf("add video track error!\n");
		return -1;
	}
	MP4SetVideoProfileLevel(m_hFile, DEFAULT_VIDEO_PROFILE_LEVEL);
	MP4AddH264SequenceParameterSet(m_hFile, m_videoTrack, sData + sps,pps - sps - 4);//sps  内容  起始位置+长度  
	MP4AddH264PictureParameterSet(m_hFile, m_videoTrack, sData + pps,nSize - pps);// pps 内容  起始位置+长度

	return 0;
}

int   MP4Encoder::MP4AddAACTrack(const uint8_t *sData, int nSize,int Audio_Time_Scale)
{
	m_audioTrack = MP4AddAudioTrack(m_hFile, Audio_Time_Scale,
		/**
		 * In fact, this is not a magic number. A formula might be:
		 * SampleRate * ChannelNum * 2 / SampleFormat
		 * 8000 * 1 * 2 / 16 (字节对齐，这里是 AV_SAMPLE_FMT_S16)
		 */
		1024, MP4_MPEG4_AUDIO_TYPE);
	if (MP4_INVALID_TRACK_ID == m_audioTrack)
	{
		printf("add audio track error!\n");
		return -1;
	}
	MP4SetAudioProfileLevel(m_hFile, DEFAULT_AUDIO_PROFILE_LEVEL);
	if (!MP4SetTrackESConfiguration(m_hFile, m_audioTrack, sData, nSize))
	{
		printf("set track ESConfiguration error!\n");
		return -1;
	}
	return 0;
}

int MP4Encoder::MP4WriteH264Data(uint8_t *sData, int nSize,uint64_t video_cur_pts)
{

	bool result = false;
	sData[0] = (nSize - 4) >> 24;
	sData[1] = (nSize - 4) >> 16;
	sData[2] = (nSize - 4) >> 8;
	sData[3] = nSize - 4;

	if(nSize<0||sData==NULL)
		return -1;



	if ((sData[4] & 0x1F) == 5)//判断I帧
		result = MP4WriteSample(m_hFile, m_videoTrack, sData, nSize,MP4_INVALID_DURATION,0,true);
	else
		result = MP4WriteSample(m_hFile, m_videoTrack, sData, nSize,MP4_INVALID_DURATION,0,false);
	if (!result)
	{
		printf("write h264 frame error!\n");
		return -1;
	}

	return 0;
}

int  MP4Encoder::MP4WriteAACData(const uint8_t *sData, int nSize,uint64_t audio_cur_pts)
{
	bool result = false;
	if(nSize<0||sData==NULL)
		return -1;

	result = MP4WriteSample(m_hFile, m_audioTrack, sData, nSize,MP4_INVALID_DURATION,0,true);
	if (!result)
	{
		printf("write aac frame error!\n");
		return -1;
	}

	return 0;
}

void MP4Encoder::MP4ReleaseFile()
{
	if (m_hFile != MP4_INVALID_FILE_HANDLE)
	{
		//MP4Close(m_hFile,MP4_CLOSE_DO_NOT_COMPUTE_BITRATE);
		MP4Close(m_hFile);
		m_hFile = MP4_INVALID_FILE_HANDLE;
	}
}