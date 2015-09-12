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
#include <wtypes.h>
#include<cstdint>
#include "common.h"
#include "Console.h"

class CColorQuantization;
class CErrorDiffusion;
class CBayer;

 /*!
  * \class CVideo
  *
  * \brief ��Ƶ������
  *
  * \author Mewiteor
  * \date ���� 2015
  */
class CVideo
{
	enum { MAX_VIDEO_DATA_COUNT = 64 };
	struct ATTR
	{
		WORD* attr;					// ����̨����
		COLORREF colorTable[16];	// ����̨��ɫ��
		int64_t timestamp;			// ʱ���
	};
	struct DATA
	{
		uint8_t * data;				// ��Ƶ����,RGB����,����Ϊ����̨��Ļ���ܳ��ȵ�3��
		int64_t timestamp;			// ʱ���
	};
public:

	//************************************
	// Method:      CVideo
	// FullName:    CVideo::CVideo
	// Access:      public 
	// Returns:     
	// Qualifier:  
	// Parameter:   const CConsole & console
	// Parameter:   DWORD duration
	// Parameter:   ColorType colorType
	// Parameter:   bool & audioStart
	// Parameter:   bool & videoStart
	// Parameter:   HANDLE hStartEvent
	// Parameter:   const char * filePath
	// Parameter:   COLORREF defaultColorTable[16]
	// Description: 
	//************************************
	CVideo(const CConsole &console, DWORD duration, ColorType colorType,
		bool &audioStart, bool &videoStart, HANDLE hStartEvent,
		const char* filePath, COLORREF defaultColorTable[16] = nullptr);

	//************************************
	// Method:      ~CVideo
	// FullName:    CVideo::~CVideo
	// Access:      public 
	// Returns:     
	// Qualifier:  
	// Description: 
	//************************************
	~CVideo();

	//************************************
	// Method:      Push
	// FullName:    CVideo::Push
	// Access:      public 
	// Returns:     void
	// Qualifier:  
	// Parameter:   unsigned char * buf
	// Parameter:   size_t len
	// Parameter:   int64_t timestamp
	// Description: ѹ����Ƶ���ݵ�dataѭ������
	//************************************
	void Push(unsigned char *buf, size_t len, int64_t timestamp);

	//************************************
	// Method:      Stop
	// FullName:    CVideo::Stop
	// Access:      public 
	// Returns:     void
	// Qualifier:  
	// Parameter:   bool force,true:��ESC�˳�,false:�������˳�
	// Description: ���Ž���
	//************************************
	void Stop(bool force);

private:
	//************************************
	// Method:      ColorQuantizationThread
	// FullName:    CVideo::ColorQuantizationThread
	// Access:      private static 
	// Returns:     DWORD CALLBACK
	// Qualifier:  
	// Parameter:   LPVOID lp
	// Description: 
	//************************************
	static DWORD CALLBACK ColorQuantizationThread(LPVOID lp);
	
	//************************************
	// Method:      VideoColorQuantizationThread
	// FullName:    CVideo::VideoColorQuantizationThread
	// Access:      private 
	// Returns:     DWORD
	// Qualifier:  
	// Description: 
	//************************************
	DWORD VideoColorQuantizationThread();
	
	//************************************
	// Method:      WriteAttrThread
	// FullName:    CVideo::WriteAttrThread
	// Access:      private static 
	// Returns:     DWORD CALLBACK
	// Qualifier:  
	// Parameter:   LPVOID lp
	// Description: 
	//************************************
	static DWORD CALLBACK WriteAttrThread(LPVOID lp);
	
	//************************************
	// Method:      VideoWriteAttrThread
	// FullName:    CVideo::VideoWriteAttrThread
	// Access:      private 
	// Returns:     DWORD
	// Qualifier:  
	// Description: 
	//************************************
	DWORD VideoWriteAttrThread();

	//************************************
	// Method:      DataFull
	// FullName:    CVideo::DataFull
	// Access:      private 
	// Returns:     bool
	// Qualifier:   const
	// Description: 
	//************************************
	inline bool DataFull()const
	{
		return m_nDataStart < m_nDataToAttrIndex ?
			m_nDataStart + 1 == m_nDataToAttrIndex :
			!m_nDataToAttrIndex&&m_nDataStart == MAX_VIDEO_DATA_COUNT - 1;
	}
	
	//************************************
	// Method:      DataEmpty
	// FullName:    CVideo::DataEmpty
	// Access:      private 
	// Returns:     bool
	// Qualifier:   const
	// Description: 
	//************************************
	inline bool DataEmpty()const { return m_nDataStart == m_nDataToAttrIndex; }
	
	//************************************
	// Method:      AttrFull
	// FullName:    CVideo::AttrFull
	// Access:      private 
	// Returns:     bool
	// Qualifier:   const
	// Description: 
	//************************************
	inline bool AttrFull()const
	{
		return m_nDataToAttrIndex < m_nAttrEnd ?
			m_nDataToAttrIndex + 1 == m_nAttrEnd :
			!m_nAttrEnd&&m_nDataToAttrIndex == MAX_VIDEO_DATA_COUNT - 1;
	}
	
	//************************************
	// Method:      AttrEmpty
	// FullName:    CVideo::AttrEmpty
	// Access:      private 
	// Returns:     bool
	// Qualifier:   const
	// Description: 
	//************************************
	inline bool AttrEmpty()const { return m_nDataToAttrIndex == m_nAttrEnd; }
	
	//************************************
	// Method:      Convert24bppTo4bpp
	// FullName:    CVideo::Convert24bppTo4bpp
	// Access:      private static 
	// Returns:     WORD
	// Qualifier:  
	// Parameter:   short red
	// Parameter:   short green
	// Parameter:   short blue
	// Description: ��24λ��ɫת��Ϊ��ӽ��Ŀ���̨Ĭ�ϵ�ɫ���ϵ�4λ��ɫ
	//************************************
	static WORD Convert24bppTo4bpp(short red, short green, short blue);

private:
	const CConsole &m_cConsole;
	ColorType m_cColorType;
	ATTR m_cAttributes[MAX_VIDEO_DATA_COUNT];		// ����̨����ѭ������
	DWORD m_dwStartTime,		// ��ʼ���ŵ�ʱ��,��λms
		m_dwLastTime,			// ��һ֡��ʱ��,��λms
		m_dwLastTimeSeconds;	// ��һ֡��ʱ��,��λs
	DWORD m_dwDuration;			// ��Ƶ��ʱ��,��λs
	unsigned int m_nFrames;	// ��¼֡��,���ڼ���fps
	float m_fLastFps;			// ��һ�μ������fps
	CColorQuantization* m_pColorQuantization;
	CErrorDiffusion* m_pErrorDiffusion;
	CBayer* m_pBayer;
	size_t m_nLength;			// ����̨��Ļ�����ܳ���(console.GetSize().X*console.GetSize().Y)
	bool m_bContinue,			// �����߳��Ƿ����
		m_bForce;				// TRUE:��ESC�˳�,FALSE:�������˳�
	HANDLE m_hColorQuantizationThread, m_hWriteAttrThread;
	DATA m_cData[MAX_VIDEO_DATA_COUNT];	// ֡RGB����ѭ������
	size_t m_nDataStart,		// ֡RGB����ѭ�����еĶ���
		m_nDataToAttrIndex,	// ֡RGB����ѭ�����еĶ�β,����̨����ѭ�����еĶ���,����������һֱ����ȵ�
		m_nAttrEnd;			// ����̨����ѭ�����еĶ�β
	HANDLE m_hDataNotEmptyEvent,
		m_hAttrNotFullEvent,
		m_hConvertDataToAttrEvent;
	bool &m_bAudioStart, &m_bVideoStart;
	HANDLE m_hStartEvent;		// ��ʼ�����¼�
	const char* m_strPlayFilePath;
	const COLORREF* m_pDefaultColorTable;	// Ĭ�ϵ�ɫ��,����ColorType::MONO(�ڰ�)��ColorType::STANDARD(��׼)������ɫģʽ
	DWORD m_dwPeriodMin;	// ��ʱ���ȵ���Сֵ
};

