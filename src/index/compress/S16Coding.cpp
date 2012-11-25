#include "firtex/index/compress/S16Coding.h"

FX_NS_DEF(index);

uint32_t S16Coding::MASK[16][28] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                     {2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
                                     {1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
                                     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,0,0,0,0,0,0,0},
                                     {2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {4,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {3,4,4,4,4,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {5,5,5,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {4,4,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {6,6,6,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {5,5,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {10,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {14,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                     {28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

S16Coding::S16Coding() 
{
    PACK_COUNT[0] = 28;
    PACK_COUNT[1] = 21;
    PACK_COUNT[2] = 21;
    PACK_COUNT[3] = 21;
    PACK_COUNT[4] = 14;
    PACK_COUNT[5] = 9;
    PACK_COUNT[6] = 8;
    PACK_COUNT[7] = 7;
    PACK_COUNT[8] = 6;
    PACK_COUNT[9] = 6;
    PACK_COUNT[10] = 5;
    PACK_COUNT[11] = 5;
    PACK_COUNT[12] = 4;
    PACK_COUNT[13] = 3;
    PACK_COUNT[14] = 2;
    PACK_COUNT[15] = 1;
}

S16Coding::~S16Coding() 
{
}

size_t S16Coding::encode(uint32_t* dest, size_t nDestLen,
                         const uint32_t* src, size_t nSrcLen,
                         bool /** bSeal */) const
{
    return doEncode(dest, nDestLen, src, nSrcLen);
}

size_t S16Coding::decode(uint32_t* dest, size_t nDestLen,
                         const uint32_t* src, size_t nSrcLen,
                         bool& /** bExhausted */) const
{
    return doDecode(dest, nDestLen, src, nSrcLen);
}

FX_NS_END
