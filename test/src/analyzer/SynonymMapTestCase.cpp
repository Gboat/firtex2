//
// Copyright(C) 2005--2009 FirteX Develop Team. 
// All rights reserved.
// This file is part of FirteX (www.firtex.org)
//
// Use of the FirteX is subject to the terms of the software license set forth in 
// the LICENSE file included with this software, and also available at
// http://www.firtex.org/license.html
//
// Author	: �����(GuoRuijie)
// Email	: ruijieguo@gmail.com
// Created	: 2009/3/17
//
#include "SynonymMapTestCase.h"
#include "firtex/analyzer/SynonymMap.h"
#include "firtex/utility/File.h"
#include "TestHelper.h"
#include <memory>

using namespace std;
FX_NS_USE(utility);


FX_NS_DEF(analyzer);

CPPUNIT_TEST_SUITE_REGISTRATION(SynonymMapTestCase);

SynonymMapTestCase::SynonymMapTestCase(void)
{
}

SynonymMapTestCase::~SynonymMapTestCase(void)
{
}

void SynonymMapTestCase::testGetSynonyms()
{
	SynonymMap sm;
	bool bRet = sm.addSynonyms("ϲ��", _T("����"));
    CPPUNIT_ASSERT(bRet);
    bRet = sm.addSynonyms("һƳ","CAST,CATCH SIGHT OF,COLOR,COMPANY,DEKKO, \
		   FLING,FORM,GLANCE,GLAUM,GLIMPSE,KIND,LOOK,MOLD,\
		   NOTICE,PITCH,SEE,SHADE,SHAPE,SKIM,SORT,THROW,\
		   TINT,TOSS,TROUPE,TYPE,VARIETY,һ��,Ͷ��,��Ա��,�۹�,������,����");
    CPPUNIT_ASSERT(bRet);
	SynonymMap::Group* pGroup = sm.getSynonyms(_T("ϲ��"));
	CPPUNIT_ASSERT(pGroup != NULL);
	CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
	pGroup = sm.getSynonyms(_T("����"));
	CPPUNIT_ASSERT(pGroup != NULL);
	CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
	pGroup = sm.getSynonyms(_T("һƳ"));
	CPPUNIT_ASSERT(pGroup != NULL);
	CPPUNIT_ASSERT_EQUAL((size_t)32, pGroup->size());

    bRet = sm.addSynonyms(_T("aa"), _T(""));
    CPPUNIT_ASSERT(!bRet);

    bRet = sm.addSynonyms(_T(""), _T("aa"));
    CPPUNIT_ASSERT(!bRet);
}

void SynonymMapTestCase::testLoad()
{
    tstring strSynFile = TestHelper::getTestDataPath();
    strSynFile += _T("/testload.sym");
    SynonymMap sm;
    try
    {
        sm.load(strSynFile.c_str());
    }
    catch(...)
    {
        CPPUNIT_ASSERT(false);
    }

    CPPUNIT_ASSERT_EQUAL((size_t)6, sm.getNumSynonyms());
    SynonymMap::Group* pGroup = sm.getSynonyms("�����");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("computer"), (*pGroup)[0]);

    pGroup = sm.getSynonyms("COMPUTER");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("�����"), (*pGroup)[0]);

    pGroup = sm.getSynonyms("����");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)2, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("see"), (*pGroup)[0]);
    CPPUNIT_ASSERT_EQUAL(string("watch"), (*pGroup)[1]);

    pGroup = sm.getSynonyms("see");
    CPPUNIT_ASSERT(pGroup == NULL);
    pGroup = sm.getSynonyms("watch");
    CPPUNIT_ASSERT(pGroup == NULL);

    pGroup = sm.getSynonyms("����");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("blind date"), (*pGroup)[0]);

    pGroup = sm.getSynonyms("һ������");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)2, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("һĿ��Ȼ"), (*pGroup)[0]);
    CPPUNIT_ASSERT_EQUAL(string("����ָ��"), (*pGroup)[1]);

    pGroup = sm.getSynonyms("һĿ��Ȼ");
    CPPUNIT_ASSERT(pGroup == NULL);

    pGroup = sm.getSynonyms("����ָ��");
    CPPUNIT_ASSERT(pGroup == NULL);
}

void SynonymMapTestCase::testSave()
{
    tstring str = TestHelper::getTestDataPath();
    tstring strSynFile = str + _T("/testload.sym");
    tstring strSynSave = str + _T("/testsave.sym");
    try
    {
        SynonymMap sm1;
        sm1.load(strSynFile.c_str());
        sm1.save(strSynSave.c_str());
    }
    catch(...)
    {
        CPPUNIT_ASSERT(false);
    }
    SynonymMap sm2;
    sm2.load(strSynSave.c_str());
    CPPUNIT_ASSERT_EQUAL((size_t)6, sm2.getNumSynonyms());
    SynonymMap::Group* pGroup = sm2.getSynonyms("�����");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("computer"), (*pGroup)[0]);

    pGroup = sm2.getSynonyms("COMPUTER");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("�����"), (*pGroup)[0]);

    pGroup = sm2.getSynonyms("����");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)2, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("see"), (*pGroup)[0]);
    CPPUNIT_ASSERT_EQUAL(string("watch"), (*pGroup)[1]);

    pGroup = sm2.getSynonyms("see");
    CPPUNIT_ASSERT(pGroup == NULL);
    pGroup = sm2.getSynonyms("watch");
    CPPUNIT_ASSERT(pGroup == NULL);

    pGroup = sm2.getSynonyms("����");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("blind date"), (*pGroup)[0]);

    pGroup = sm2.getSynonyms("һ������");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)2, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(string("һĿ��Ȼ"), (*pGroup)[0]);
    CPPUNIT_ASSERT_EQUAL(string("����ָ��"), (*pGroup)[1]);

    pGroup = sm2.getSynonyms("һĿ��Ȼ");
    CPPUNIT_ASSERT(pGroup == NULL);

    pGroup = sm2.getSynonyms("����ָ��");
    CPPUNIT_ASSERT(pGroup == NULL);
}

void SynonymMapTestCase::testAddSynonym()
{
	SynonymMap sm;
	bool bRet = sm.addSynonym(_T("aa"), _T("bb"));
    CPPUNIT_ASSERT(bRet);
    SynonymMap::Group* pGroup = sm.getSynonyms("aa");
    CPPUNIT_ASSERT(pGroup != NULL);
    CPPUNIT_ASSERT_EQUAL((size_t)1, pGroup->size());
    CPPUNIT_ASSERT_EQUAL(std::string("bb"), (*pGroup)[0]);
}

FX_NS_END
