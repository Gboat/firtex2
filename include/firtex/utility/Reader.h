//
// Copyright(C) 2005--2011 FirteX Development Team. 
// All rights reserved.
// This file is part of FirteX (www.firtex.org)
//
// Use of the FirteX is subject to the terms of the software license set forth in 
// the LICENSE file included with this software, and also available at
// http://www.firtex.org/license.html
//
// Author	: �����(GuoRuijie)
// Email	: ruijieguo@software.ict.ac.cn,ruijieguo@gmail.com
// Created	: 2006/5/20
//
#ifndef __READER_H
#define __READER_H

#include "firtex/common/StdHeader.h"
#include "Charset.h"
#include <string>
using namespace std;


FX_NS_DEF(utility)

class Reader
{	
public:
	Reader(char* buffer,size_t buffsize);
	Reader(size_t buffsize = 0);			
	virtual ~Reader(void);
public:
	/**
	 * \if EN
	 * read data
	 * @param data address to store data
	 * @param length length to read
 	 * \endif
	 *
	 * \if CN
	 * ��ȡ���ݿ�
	 * @param data Ŀ�����ݿ��׵�ַ
	 * @param length Ŀ�����ݿ��С
	 * \endif
	 */
	void		read(char* data, size_t length);

	/**
	 * \if EN
	 * read data without copy operation
	 * @param length data size
	 * @return data pointer
	 * \endif
	 *
	 * \if CN
	 * ֱ�Ӷ�ȡ���ݿ�,û�����ݿ���			 
	 * @param length ���ݿ��С
	 * @return ���ݿ��׵�ַ
	 * \endif
	 */
	char*		readWithoutCopy(size_t& length);		

	/**
	 * \if EN
	 * get current position
	 * \endif
	 *
	 * \if CN
	 * �������ļ��еĵ�ǰλ�ã���һ�ζ������λ�ÿ�ʼ
	 * \endif
	 */			
	int64_t		getFilePointer(){return m_bufferStart + m_bufferPosition;}

	/**
	 * \if EN
	 * seek to position
	 * @param pos seek to specific position
	 * \endif
	 *
	 * \if CN
	 * �����ļ��ĵ�ǰ��λ�ã���һ�ζ������λ�ÿ�ʼ
	 * @param pos ��λ��λ��
	 * \endif
	 */	
	void		seek(int64_t pos);	

	/**
	 * \if EN
	 * get file size
	 * \endif
	 *
	 * \if CN
	 * �����ļ�����			 
	 * \endif
	 */	
	int64_t		length(){return m_length;}

	/**
	 * set encoding of the reader
	 * @param _charset Charset of the content 
	 */
	void		setEncoding(charset_t _charset){m_encoding = _charset;}

	/**
	 * get encoding of the reader 
	 * @return encoding 
	 */
	charset_t	getEncoding(){return m_encoding;}

	/**
	 * \if EN
	 * end or not
	 * \endif
	 *
	 * \if CN
	 * �ж��ļ������Ƿ�����
	 * \endif
	 */
	virtual bool	isEof(){return ( (m_bufferStart + (int64_t )m_bufferPosition) >= m_length);}

	/**
	 * \if EN
	 * close file
	 * \endif
	 *
	 * \if CN
	 * �ر��ļ���������ʵ��
	 * \endif
	 */
	virtual void  close();
public:
	/**
	 * \if EN
	 * clone an object 
	 * \endif
	 *
	 * \if CN
	 * ��¡һ��Reader����,��¡����ʹ��buffer��Ϊ����	 
	 * \endif
	 */			
	virtual Reader*	clone(char* buffer,size_t buffsize) = 0;

	/**
	* \if EN
	 * clone an object
	 *
	 * \endif
	 *
	 * \if CN
	 * ��¡һ��Reader����,��¡����ʹ���Լ�˽�е��ڴ���Ϊ����	 
	 * \endif
 	 */		
	virtual Reader*	clone() = 0;
protected:
	/**
	 * \if EN
	 * seek to position, sub-class MUST implement it
	 * @param pos seek position
	 * \endif
	 *
	 * \if CN
	 * ʵ���ļ���λ������readInternal�Ķ����������λ�ÿ�ʼ��������ʵ��
	 * @param pos ��λλ��
	 * \endif
	 */				
	virtual void  seekInternal(int64_t position) = 0;

	/**
	 * \if EN
	 * read data from data source, sub-class MUST implement it 
	 * @param b target address
	 * @param offset read offset 
	 * @length length of data
	 * \endif
	 *
	 * \if CN
	 * ���ļ��е�ǰλ�ö����ݣ�������ʵ�ִ˺���
	 * @param b Ŀ���ַ
	 * @param offset ƫ����
	 * @length ����
	 \endif
	 */
	virtual void  readInternal(char* b, size_t offset, size_t length) = 0;	

protected:
	/**
	 * \if EN
	 * fill data to buffer
	 * \endif
	 *
	 * \if CN
	 * ���ļ����ж�������䵽��������
	 * \endif
	 */
	void	refill();	
public:
	const static int READER_BUFFSIZE = 32768*10;
protected:
	char*		m_buffer;
	size_t		m_bufferSize;			

	int64_t		m_bufferStart;		/// position in file of m_buffer
	size_t		m_bufferLength;		/// end of valid bytes
	size_t		m_bufferPosition;	/// next byte to read

	int64_t		m_length;			/// set by subclasses
	bool		m_bOwnBuff;

	charset_t	m_encoding;			///encoding name
};

//////////////////////////////////////////////////////////////////////////
//
inline void  Reader::refill()
{
	int64_t start = m_bufferStart + (int64_t)m_bufferPosition;
	int64_t end = start + (int64_t)m_bufferSize;
	if (end > m_length)	//�����˽�β					
		end = m_length;
	m_bufferLength = (size_t) (end - start);
	if (m_bufferLength == 0)
		return;

	if (m_buffer == NULL)
		m_buffer = new char[m_bufferSize]; // allocate m_buffer lazily
	readInternal(m_buffer, 0, m_bufferLength);

	m_bufferStart = start;
	m_bufferPosition = 0;
}

FX_NS_END

#endif
