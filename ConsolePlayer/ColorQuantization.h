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
#include<set>

/*!
 * \class CColorQuantization
 *
 * \brief �ð˲����㷨����ɫ������(24bpp->4bpp)
 *
 * \author Mewiteor
 * \date ���� 2015
 */
class CColorQuantization
{
	typedef std::set<unsigned int> set_type;	// set����
	struct Node	// ���ṹ
	{
		unsigned long long red;		// ��ɫ����
		unsigned long long green;	// ��ɫ����
		unsigned long long blue;	// ��ɫ����
		unsigned long long count;	// ����������
		unsigned int index;			// ��ɫ������
		bool leaf;					// �Ƿ�ΪҶ�ӽ��
	};
public:

	//************************************
	// Method:      CColorQuantization
	// FullName:    CColorQuantization::CColorQuantization
	// Access:      public 
	// Returns:     
	// Qualifier:  
	// Parameter:   unsigned int max�������ɫ��
	// Description: ����ɫ����������
	//************************************
	CColorQuantization(unsigned int max);

	//************************************
	// Method:      ~CColorQuantization
	// FullName:    CColorQuantization::~CColorQuantization
	// Access:      public 
	// Returns:     
	// Qualifier:  
	// Description: ����ɫ����������
	//************************************
	~CColorQuantization() {}

	//************************************
	// Method:      Insert
	// FullName:    CColorQuantization::Insert
	// Access:      public 
	// Returns:     void
	// Qualifier:  
	// Parameter:   unsigned char red
	// Parameter:   unsigned char green
	// Parameter:   unsigned char blue
	// Description: ������ɫ���˲���У����Ż���
	//************************************
	void Insert(unsigned char red, unsigned char green, unsigned char blue);

	//************************************
	// Method:      Done
	// FullName:    CColorQuantization::Done
	// Access:      public 
	// Returns:     unsigned int
	// Qualifier:  
	// Parameter:   COLORREF colorTable[16]
	// Description: ���ɵ�ɫ��
	//************************************
	unsigned int Done(COLORREF colorTable[16]);

	//************************************
	// Method:      Get
	// FullName:    CColorQuantization::Get
	// Access:      public 
	// Returns:     unsigned int
	// Qualifier:  
	// Parameter:   unsigned char red
	// Parameter:   unsigned char green
	// Parameter:   unsigned char blue
	// Description: ��ȡ��ɫ�ڵ�ɫ���е���������
	//************************************
	unsigned int Get(unsigned char red, unsigned char green, unsigned char blue);

private:

	//************************************
	// Method:      InsertRGB
	// FullName:    CColorQuantization::InsertRGB
	// Access:      private 
	// Returns:     void
	// Qualifier:  
	// Parameter:   unsigned char red
	// Parameter:   unsigned char green
	// Parameter:   unsigned char blue
	// Description: ������ɫ���˲����
	//************************************
	void InsertRGB(unsigned char red, unsigned char green, unsigned char blue);
	
	//************************************
	// Method:      Reduce
	// FullName:    CColorQuantization::Reduce
	// Access:      private 
	// Returns:     void
	// Qualifier:  
	// Description: ������ɫ
	//************************************
	void Reduce();
	
	//************************************
	// Method:      fast_log2
	// FullName:    CColorQuantization::fast_log2
	// Access:      private 
	// Returns:     unsigned short
	// Qualifier:  
	// Parameter:   double d
	// Description: ���ټ�����2Ϊ�׵Ķ���
	//************************************
	inline unsigned short fast_log2(double d)
	{
		return (*(unsigned long long*)&d >> 52 & 0x7ff) - 1023;
	}

private:
	static Node m_cNodes[0111111111];	// �Ų�˲��
	unsigned int m_nColorCount;		// ��ɫ����
	const unsigned int m_nMaxCount;	// �����ɫ��
	set_type m_setLeafParent;			// Ҷ�ӽ��ĸ����ļ���
	unsigned int m_nDepth;				// �ѵĵ�ǰ���
};

