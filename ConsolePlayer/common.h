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

/*!
 * \enum ColorType
 *
 * \brief ��ɫģʽö��
 *
 * \author Mewiteor
 * \date ���� 2015
 */
enum ColorType
{
	MONO=1002,	// �ڰף�16���Ҷ�
	STANDARD,	// ��׼��ʹ�ÿ���̨Ĭ�ϵ�ɫ��
	AUTO		// �Զ���ʵʱ����֡�����ŵ�ɫ��
};

#define MAX_AUDIO_FRAME_SIZE 192000

// ��ʽ�����������Ϣ���������
#ifdef _DEBUG
#define DebugPrint(fmt,...) _DebugPrint(fmt,__VA_ARGS__)
#else
#define DebugPrint(fmt,...)
#endif

//************************************
// Method:      _DebugPrint
// FullName:    _DebugPrint
// Access:      public 
// Returns:     void
// Qualifier:  
// Parameter:   const char * format
// Parameter:   ...
// Description: ��ʽ�����������Ϣ���������
//************************************
void _DebugPrint(const char* format, ...);
