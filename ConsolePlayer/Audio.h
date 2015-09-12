/*
 * copyright (c) 2015 Mewiteor
 *
 * This file is part of ConsolePlayer.
 *
 * ConsolePlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ConsolePlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ConsolePlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#pragma once
#include "common.h"
#include <wtypes.h>
/*!
 * \class CAudio
 *
 * \brief ��Ƶ������
 *
 * \author Mewiteor
 * \date ���� 2015
 */
class CAudio
{
	enum
	{
		MAX_WAVE_COUNT=8,
		MAX_WAVE_DATA_COUNT=64
	};
	struct DATA { char data[MAX_AUDIO_FRAME_SIZE]; size_t len; };
public:

	//************************************
	// Method:      CAudio
	// FullName:    CAudio::CAudio
	// Access:      public 
	// Returns:     
	// Qualifier:  
	// Parameter:   WORD channels
	// Parameter:   DWORD sample_rate
	// Parameter:   WORD bits_per_sample
	// Parameter:   bool & _audioStart
	// Parameter:   bool & _videoStart
	// Parameter:   HANDLE & _hStartEvent
	// Description: 
	//************************************
	CAudio(WORD channels, DWORD sample_rate, WORD bits_per_sample,
		bool &_audioStart, bool &_videoStart,HANDLE &_hStartEvent);

	//************************************
	// Method:      ~CAudio
	// FullName:    CAudio::~CAudio
	// Access:      public 
	// Returns:     
	// Qualifier:  
	// Description: 
	//************************************
	~CAudio();

	//************************************
	// Method:      Push
	// FullName:    CAudio::Push
	// Access:      public 
	// Returns:     void
	// Qualifier:  
	// Parameter:   unsigned char * buf
	// Parameter:   size_t len
	// Description: ѹ����Ƶ���ݵ�dataѭ������
	//************************************
	void Push(unsigned char *buf, size_t len);
	
	//************************************
	// Method:      Stop
	// FullName:    CAudio::Stop
	// Access:      public 
	// Returns:     void
	// Qualifier:  
	// Parameter:   bool force,true:��ESC�˳�,false:�������˳�
	// Description: ���Ž���
	//************************************
	void Stop(bool force);
private:
	
	//************************************
	// Method:      ThreadProc
	// FullName:    CAudio::ThreadProc
	// Access:      private static 
	// Returns:     DWORD CALLBACK
	// Qualifier:  
	// Parameter:   LPVOID lp
	// Description: 
	//************************************
	static DWORD CALLBACK ThreadProc(LPVOID lp);

	//************************************
	// Method:      AudioThreadProc
	// FullName:    CAudio::AudioThreadProc
	// Access:      private 
	// Returns:     DWORD
	// Qualifier:  
	// Description: 
	//************************************
	DWORD AudioThreadProc();
	
	//************************************
	// Method:      waveOutProc
	// FullName:    CAudio::waveOutProc
	// Access:      private static 
	// Returns:     void CALLBACK
	// Qualifier:  
	// Parameter:   HWAVEOUT hWaveOut
	// Parameter:   UINT uMsg
	// Parameter:   DWORD_PTR dwInstance,hDataEvent
	// Parameter:   DWORD_PTR dwParam1,waveHdr
	// Parameter:   DWORD_PTR dwParam2
	// Description: 
	//************************************
	static void CALLBACK waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD_PTR dwInstance,
		DWORD_PTR dwParam1, DWORD_PTR dwParam2);

	//************************************
	// Method:      DataFull
	// FullName:    CAudio::DataFull
	// Access:      private 
	// Returns:     bool
	// Qualifier:   const
	// Description: 
	//************************************
	inline bool DataFull() const { return m_dwStart < m_dwEnd ? m_dwStart + 1 == m_dwEnd : 0 == m_dwEnd&&MAX_WAVE_DATA_COUNT - 1 == m_dwStart; }
	
	//************************************
	// Method:      DataEmpty
	// FullName:    CAudio::DataEmpty
	// Access:      private 
	// Returns:     bool
	// Qualifier:   const
	// Description: 
	//************************************
	inline bool DataEmpty() const { return m_dwStart == m_dwCur; }
private:
	HWAVEOUT m_hWaveOut;
	static DATA m_cData[MAX_WAVE_DATA_COUNT];	// ѭ�����У����ڻ�����Ƶ����
	DWORD m_dwStart;		// dataѭ�����еĶ���
	DWORD m_dwCur;			// ��ʼ����dataѭ�����������ݵ�����
	DWORD m_dwEnd;			// dataѭ�����еĶ�β
	DWORD m_dwWaveHdrIndex;	// ��ǰʹ�õ�waveHdr������
	WAVEHDR m_cWaveHdr[MAX_WAVE_COUNT];	// ����waveOutWrite�Ļ�����,ʵ�ֶ໺�岥��
	DWORD m_dwCount;		// ��ǰ���ڲ��ŵ�wave������
	HANDLE m_hDataEvent,	// һ��wave�������¼�
		m_hNotFullEvent, m_hNotEmptyEvent;	// dataѭ����������¼�
	HANDLE m_hThread;		// ��dataѭ�����в�����Ƶ���߳�
	BOOL m_bContinue,		// �����߳��Ƿ����
		m_bForce;			// TRUE:��ESC�˳�,FALSE:�������˳�
	bool &m_bAudioStart, &m_bVideoStart;	// ��/��Ƶ�Ƿ��ѿ�ʼ����
	HANDLE m_hStartEvent;	// ��ʼ�����¼�
};

