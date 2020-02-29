#pragma once

#ifndef _MP4ENCODER_H_
#define _MP4ENCODER_H_
#include "mp4v2/mp4v2.h"

class MP4Encoder
{
public:
	MP4Encoder(void);
	~MP4Encoder(void);

	int MP4CreateFile(const char *sFileName,int Movie_Time_Scale=90000);
	int MP4AddH264Track(const uint8_t *sData, int nSize,int nWidth, int nHeight, int nFrameRate = 25,int Video_Time_Scale=90000);
	int MP4AddAACTrack(const uint8_t *sData, int nSize,int Audio_Time_Scale=44100);
	int MP4WriteH264Data(uint8_t *sData, int nSize,uint64_t video_cur_pts);
	int MP4WriteAACData(const uint8_t *sData, int nSize,uint64_t audio_cur_pts);
	void MP4ReleaseFile();
private:

	MP4FileHandle m_hFile;
	MP4TrackId m_videoTrack, m_audioTrack;
};
#endif