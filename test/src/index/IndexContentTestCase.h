// Firtex����
// tester : �ط�
// E-mail : guanfeng@software.ict.ac.cn
// ��  �� : 2009/3/26
//

/**
 * \if CN
 * ������������Ƿ���ȷ�������.dfp�Լ�.pop�������Ƿ���ȷ
 * \endif
 */

#ifndef _INDEXCONTENTTESTCASE_H
#define _INDEXCONTENTTESTCASE_H


#include "cppunit/extensions/HelperMacros.h"
#include "firtex/utility/Path.h"

FX_NS_DEF(index);

class IndexContentTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( IndexContentTestCase );
	CPPUNIT_TEST( testIndexContent_WL );
	//CPPUNIT_TEST( testIndexContent_DL );//TODO:
	//CPPUNIT_TEST( testIndexContent_DL0 );//TODO:
	CPPUNIT_TEST_SUITE_END();

public:
	IndexContentTestCase(void);
	~IndexContentTestCase(void);

public:
    void setUp();
	void tearDown();
protected:
	/**
	 * \if CN
	 * ���Դʼ�����������ݡ�
	 * ���ÿ���ʵĵ������е�λ����Ϣ�Ƿ���ȷ���Լ��ܴ����Ƿ���ȷ
	 * �����õ��ĵ������Լ������ļ�Ĭ��λ��Ϊ��
	 * bin/testDocs/WL, bin/testIndex/WL
	 * \endif
	 */
	void testIndexContent_WL();

	/**
	 * \if CN
	 * �����ĵ�������������ݡ�
	 * ���ÿ���ʵĵ������е��ĵ�id�ʹ�Ƶ�Ƿ���ȷ
	 * �����õ��ĵ������Լ������ļ�Ĭ��λ��Ϊ��
	 * bin/testDocs/DL, bin/testIndex/DL
	 * \endif
	 */
	void testIndexContent_DL();

	/**
	 * \if CN
	 * �����ĵ�����0���������ݡ�
	 * ���ÿ���ʵĵ������е��ĵ�id�Ƿ���ȷ
	 * �����õ��ĵ������Լ������ļ�Ĭ��λ��Ϊ��
	 * bin/testDocs/DL0, bin/testIndex/DL0
	 * \endif
	 */
	void testIndexContent_DL0();

private:
	DocumentScanner		*m_pDocScanner;
    FX_NS(utility)::Path m_testFilePath;    
};

FX_NS_END

#endif
