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
#include <shlwapi.h>
#include "FileOpenDialog.h"
#include "Exception.h"

template <class T>
void SafeRelease(T* &ppT);

const DWORD CFileOpenDialog::ID_GROUP = 1000,
	CFileOpenDialog::ID_RADIOBUTTIONLIST = 1001;


CFileOpenDialog::CFileOpenDialog()
	: m_pFileOpenDialog(nullptr)
	, m_pShellItem(nullptr)
	, m_pFileDialogCustomize(nullptr)
	, m_lpFileName(nullptr)
{
	CoInitialize(nullptr);
	ComThrow(CoCreateInstance(CLSID_FileOpenDialog,
		nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pFileOpenDialog)));
	COMDLG_FILTERSPEC rgSpec[] =
	{
		{ L"����֧�ֵ�ý���ļ�",L"*.rm;*.rmvb;*.3gp;*.3g2;*.mpg;*.mpeg;*.mod;"
								L"*.dvr-ms;*.m2ts;*.mts;*.mov;*.qt;*.dv;*.dif;"
								L"*.wmv;*.asf;*.vfw;*.avs;*.ts;*.h264;*.264;"
								L"*.avi;*.amv;*.dat;*.flv;*.fli;*.gif;*.mkv;"
								L"*.mp4;*.m4v;*.f4v;*.ogm;*.cpk;*.bik;*.vob;"
								L"*.xv;*.yuv;" },
		{ L"Real Media�ļ�",L"*.rm;*.rmvb" },
		{ L"3GPP�ļ�",L"*.3gp;*.3g2" },
		{ L"MPEG�ļ�",L"*.mpg;*.mpeg" },
		{ L"JVC MPEG Mod�ļ�",L"*.mod" },
		{ L"DVR-MS�ļ�",L"*.dvr-ms" },
		{ L"MTS�ļ�",L"*.m2ts;*.mts" },
		{ L"Quick Time�ļ�",L"*.mov;*.qt" },
		{ L"Digital Video�ļ�",L"*.dv;*.dif" },
		{ L"Windows Media�ļ�",L"*.wmv;*.asf;*.vfw" },
		{ L"AviSynth�ļ�",L"*.avs" },
		{ L"TS�ļ�",L"*.ts" },
		{ L"Raw H264��",L"*.h264;*.264" },
		{ L"AVI�ļ�",L"*.avi" },
		{ L"AMV�ļ�",L"*.amv" },
		{ L"DAT�ļ�",L"*.dat" },
		{ L"FLV�ļ�",L"*.flv" },
		{ L"FLI�ļ�",L"*.fli" },
		{ L"GIF�ļ�",L"*.gif" },
		{ L"MKV�ļ�",L"*.mkv" },
		{ L"MP4�ļ�",L"*.mp4" },
		{ L"M4V�ļ�",L"*.m4v" },
		{ L"F4V�ļ�",L"*.f4v" },
		{ L"OGM�ļ�",L"*.ogm" },
		{ L"SEGA Film�ļ�",L"*.cpk" },
		{ L"Bink Video�ļ�",L"*.bik" },
		{ L"VOB�ļ�",L"*.vob" },
		{ L"XV�ļ�",L"*.xv" },
		{ L"YUV�ļ�",L"*.yuv" },
		{ L"�����ļ�",L"*.*" }
	};
	ComThrow(m_pFileOpenDialog->SetFileTypes(_countof(rgSpec), rgSpec));
	ComThrow(m_pFileOpenDialog->SetFileTypeIndex(0));
	ComThrow(m_pFileOpenDialog->QueryInterface(&m_pFileDialogCustomize));
	ComThrow(m_pFileDialogCustomize->StartVisualGroup(ID_GROUP, L"��ɫģʽ"));
	ComThrow(m_pFileDialogCustomize->AddRadioButtonList(ID_RADIOBUTTIONLIST));
	ComThrow(m_pFileDialogCustomize->AddControlItem(ID_RADIOBUTTIONLIST, ColorType::MONO, L"�ڰ�"));
	ComThrow(m_pFileDialogCustomize->AddControlItem(ID_RADIOBUTTIONLIST, ColorType::STANDARD, L"��׼"));
	ComThrow(m_pFileDialogCustomize->AddControlItem(ID_RADIOBUTTIONLIST, ColorType::AUTO, L"�Զ�"));
	ComThrow(m_pFileDialogCustomize->EndVisualGroup());
	ComThrow(m_pFileDialogCustomize->SetSelectedControlItem(ID_RADIOBUTTIONLIST, ColorType::AUTO));
}


CFileOpenDialog::~CFileOpenDialog()
{
	if (m_lpFileName)
	{
		CoTaskMemFree(m_lpFileName);
		m_lpFileName = nullptr;
	}
	SafeRelease(m_pShellItem);
	SafeRelease(m_pFileDialogCustomize);
	SafeRelease(m_pFileOpenDialog);
}

bool CFileOpenDialog::Show()
{
	if (!m_pFileOpenDialog)return false;
	HRESULT hr = m_pFileOpenDialog->Show(GetConsoleWindow());
	if (FAILED(hr))
	{
		if (HRESULT_FROM_WIN32(ERROR_CANCELLED) == hr)
			return false;
		else
			ThrowWin32Error(m_pFileOpenDialog->Show, hr);
	}
	return true;
}

void CFileOpenDialog::GetResult(char fileName[MAX_PATH], ColorType & colorType)
{
	if (!m_pFileOpenDialog)return;
	ComThrow(m_pFileOpenDialog->GetResult(&m_pShellItem));
	ComThrow(m_pShellItem->GetDisplayName(SIGDN::SIGDN_DESKTOPABSOLUTEPARSING, &m_lpFileName));
	DWORD dw;
	HRESULT hr = m_pFileDialogCustomize->GetSelectedControlItem(ID_RADIOBUTTIONLIST, &dw);
	if (E_FAIL == hr)throw "δѡ����ɫģʽ";
	else if (FAILED(hr)) ThrowWin32Error(m_pFileDialogCustomize->GetSelectedControlItem, hr);
	colorType = (ColorType)dw;
	ComThrow(WideCharToMultiByte(CP_ACP, 0, m_lpFileName, int(wcslen(m_lpFileName) + 1), fileName, MAX_PATH, NULL, NULL));
	if(!PathFileExistsA(fileName))
		throw "�ļ����а���Unicode�ַ�,�޷���";
}

template <class T>
void SafeRelease(T* &ppT)
{
	if (ppT)
	{
		ppT->Release();
		ppT = NULL;
	}
}