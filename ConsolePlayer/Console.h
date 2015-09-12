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

#include<Windows.h>
#include<xstring>

/*!
 * \class CConsole
 *
 * \brief ����̨��
 *
 * \author Mewiteor
 * \date ���� 2015
 */
class CConsole
{
public:
	//************************************
	// Method:      CConsole
	// FullName:    CConsole::CConsole
	// Access:      private 
	// Returns:     
	// Qualifier:  
	// Description: �������̨����
	//************************************
	CConsole();

	//************************************
	// Method:      ~CConsole
	// FullName:    CConsole::~CConsole
	// Access:      private 
	// Returns:     
	// Qualifier:  
	// Description: ��������̨����
	//************************************
	~CConsole();

	//************************************
	// Method:      WriteBg
	// FullName:    CConsole::WriteBg
	// Access:      private 
	// Returns:     DWORD
	// Qualifier:   const
	// Parameter:   const WORD * attr
	// Description: д��ȫ������
	//************************************
	DWORD WriteBg(const WORD* attr) const;

	//************************************
	// Method:      GetSize
	// FullName:    CConsole::GetSize
	// Access:      private 
	// Returns:     const COORD&
	// Qualifier:   const
	// Description: ���ؿ���̨��ǰ��С
	//************************************
	const COORD& GetSize()const { return m_crSize; }

	//************************************
	// Method:      SetSize
	// FullName:    CConsole::SetSize
	// Access:      private 
	// Returns:     void
	// Qualifier:  
	// Parameter:   COORD cr
	// Description: ���ÿ���̨��С
	//************************************
	void  SetSize(COORD cr);

	//************************************
	// Method:      SetColorTable
	// FullName:    CConsole::SetColorTable
	// Access:      private 
	// Returns:     void
	// Qualifier:   const
	// Parameter:   const COLORREF clrTb[16]
	// Description: ���ÿ���̨�ĵ�ɫ��
	//************************************
	void  SetColorTable(const COLORREF clrTb[16])  const;

	//************************************
	// Method:      SetTitle
	// FullName:    CConsole::SetTitle
	// Access:      private static 
	// Returns:     int
	// Qualifier:  
	// Parameter:   const char * format
	// Parameter:   ...
	// Description: ���ø�ʽ���Ŀ���̨����
	//************************************
	static int SetTitle(const char* format, ...);

private:

	//************************************
	// Method:      GetMaxHeight
	// FullName:    CConsole::GetMaxHeight
	// Access:      private 
	// Returns:     void
	// Qualifier:  
	// Description: ��ÿ���̨һ�ο�д������߶�
	//************************************
	void GetMaxHeight();

public:
	static const COORD m_DEFAULT_FONT_COORD; // ����̨�����С

private:
	HANDLE m_hStdIn,	// ��׼������
		m_hStdOut,		// ��׼�����
		m_hNewOut;		// �´����������
	CONSOLE_SCREEN_BUFFER_INFOEX m_oldCsbiex;	// �ɵĿ���̨��Ļ����Ϣ�ı���
	CONSOLE_FONT_INFOEX m_oldCfiex;	// �ɵĿ���̨������Ϣ�ı���
	DWORD m_dwOldShowStatus;	// �ɵĿ���̨��ʾģʽ�ı���
	bool m_bSetCfi,		// �Ƿ��������µĿ���̨������Ϣ
		m_bSetCsbi;		// �Ƿ��������µĿ���̨��Ļ����Ϣ
	COORD m_crSize;		// ����̨��ǰ��Ļ����С
	DWORD m_dwLength;	// ����̨��Ļ�����ܳ���(m_crSize.X*m_crSize.Y)
	SHORT m_nMaxHeight;	// ����̨һ�ο�д������߶�
};

