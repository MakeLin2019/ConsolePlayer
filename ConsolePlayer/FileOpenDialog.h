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
#include <windows.h>
#include "common.h"
#include <shobjidl.h>
/*!
 * \class CFileOpenDialog
 *
 * \brief ���ļ��Ի���
 *
 * \author Mewiteor
 * \date ���� 2015
 */
class CFileOpenDialog
{
public:

	//************************************
	// Method:      CFileOpenDialog
	// FullName:    CFileOpenDialog::CFileOpenDialog
	// Access:      public 
	// Returns:     
	// Qualifier:  
	// Description: 
	//************************************
	CFileOpenDialog();

	//************************************
	// Method:      ~CFileOpenDialog
	// FullName:    CFileOpenDialog::~CFileOpenDialog
	// Access:      public 
	// Returns:     
	// Qualifier:  
	// Description: 
	//************************************
	~CFileOpenDialog();

	//************************************
	// Method:      Show
	// FullName:    CFileOpenDialog::Show
	// Access:      public 
	// Returns:     bool
	// Qualifier:  
	// Description: ��ʾ�ļ��򿪶Ի���
	//************************************
	bool Show();

	//************************************
	// Method:      GetResult
	// FullName:    CFileOpenDialog::GetResult
	// Access:      public 
	// Returns:     void
	// Qualifier:  
	// Parameter:   char fileName[MAX_PATH]
	// Parameter:   ColorType & colorType
	// Description: ��ȡ�û�ѡ����ļ�����ɫģʽ
	//************************************
	void GetResult(char fileName[MAX_PATH], ColorType& colorType);
private:
	IFileOpenDialog *m_pFileOpenDialog;
	IFileDialogCustomize *m_pFileDialogCustomize;
	IShellItem* m_pShellItem;
	LPWSTR m_lpFileName;
	static const DWORD ID_GROUP, ID_RADIOBUTTIONLIST;
};

