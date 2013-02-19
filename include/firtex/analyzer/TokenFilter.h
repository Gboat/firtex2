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
// Created	: 2005/11/24
//
// �ĵ�ע���޸�
// �޸���	: �ط�(GuanFeng)
// Email	: guanfeng@software.ict.ac.cn
// �޸�����	: 2009/2/26
//

#ifndef __TOKENFILTER_H
#define __TOKENFILTER_H

#include "firtex/analyzer/TokenSource.h"
#include "firtex/utility/Singleton.h"

FX_NS_DEF(analyzer)

#define DECLARE_FILTER_CREATOR(FilterClass, FilterName)                 \
    class Creator : public TokenFilter::Creator                         \
                  , public FX_NS(utility)::Singleton<FilterClass::Creator> \
    {                                                                   \
    public:                                                             \
        Creator()                                                       \
        {                                                               \
            m_identifier += FilterName;                                 \
        }                                                               \
        virtual ~Creator(){}                                            \
    public:                                                             \
        virtual TokenFilter* create() const                             \
        {return new FilterClass;}                                       \
    public:                                                             \
    };                                                                  

class TokenFilter
{
public:
    class Creator
    {
    protected:
        Creator()
            : m_identifier(_T("filter"))
        {}

    public:
        virtual ~Creator(){}
    public:
        /**
         * create a collection object
         * @param[in] param parameter for filter
         * @return create a analyzer
         */
        virtual TokenFilter* create() const = 0; 

        /** 
         * get the identifier of collection
         */
        virtual const tstring& getIdentifier() const {return m_identifier;}

    protected:
        tstring m_identifier;
    };

public:
    static std::string PARAM_SEPERATOR;
    static std::string EQUAL_MARK;

public:
    TokenFilter(void);
    TokenFilter(const TokenFilter& src);
    TokenFilter(TokenFilter* pPreFilter);
    virtual ~TokenFilter(void);

public:
    /**
     * \if EN
     * attach a filter which would be called before this filter
     * @param[in] pPreFilter ante-filter
     * \endif
     *
     * \if CN
     * ����������.
     * ����ǰ�������������ʱ���ȵ��øù�����.
     * @param[in] pPreFilter ǰ��
     * \endif
     */
    void attachFilter(TokenFilter* pPreFilter);

    /**
     * \if EN
     * detach a filter
     * @return detached filter
     * \endif
     *
     * \if CN
     * ��ǰ��������������.
     * @return ���������ǰ�������
     * \endif
     */
    TokenFilter* detachFilter(TokenFilter* pPreFilter);

    /**
     * \if EN
     * detach a filter by identifier
     * @return detached filter
     * \endif
     *
     * \if CN
     * ��ǰ��������������.
     * @return ���������ǰ�������
     * \endif
     */
    TokenFilter* detachFilter(const tstring& szIdentifier);

public:
    /**
     * Clone a new object
     */
    virtual TokenFilter* clone() const = 0;

    /**
     * set parameter for token filter
     */
    virtual void setParam(const tstring& sParam) { }

    /**
     * \if EN
     * Filter tokens from token source
     * @param tokenSource token source for filter
     * \endif
     */
    void filter(TokenSourcePtr& tokenSource) const;

public:
    /**
     * \if EN
     * get identifier of Filter
     * \endif
     *
     * \if CN
     * ��ȡ�������ı�ʶ��
     * \endif
     */
    virtual const tstring& getIdentifier() const = 0;

protected:
    /**
     * \if EN
     * Filter interface, must implement by sub class
     * @param tokenSource token source for filter
     * \endif
     */
    virtual void filterInternal(TokenSourcePtr& tokenSource) const = 0;

protected:
    TokenFilter* m_pPreFilter;
};

FX_NS_END

#endif
