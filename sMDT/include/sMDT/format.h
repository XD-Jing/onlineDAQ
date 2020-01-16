#ifndef FORMAT_h
#define FORMAT_h

#include <bitset>

namespace PACKET{
    enum{
        GROUP_HEAD = 0,
        GROUP_TRAIL = 1,
        TDC_HEAD = 2,
        TDC_TRAIL = 3,
        MEASURE_HEAD = 4,
        MEASURE_TRAIL = 5,
        ERROR = 6,
        DEUBG = 7
    };
}

struct WORD{
    int w;

    unsigned int packet (){return static_cast<unsigned int>(((std::bitset< 4>) (w>>28)).to_ulong());}
    unsigned int tdc    (){return static_cast<unsigned int>(((std::bitset< 4>) (w>>24)).to_ulong());}
    unsigned int event  (){return static_cast<unsigned int>(((std::bitset<12>) (w>>12)).to_ulong());}
    unsigned int bunch  (){return static_cast<unsigned int>(((std::bitset<12>) (w>> 0)).to_ulong());}
    unsigned int channel(){return static_cast<unsigned int>(((std::bitset< 5>) (w>>19)).to_ulong());}
    unsigned int coarse (){return static_cast<unsigned int>(((std::bitset<12>) (w>> 7)).to_ulong());}
    unsigned int fine   (){return static_cast<unsigned int>(((std::bitset< 7>) (w>> 0)).to_ulong());}
    double time(){ return (coarse() + fine()/128.0) * 25;}
};


struct buffXDC{
    bool isTDC;
    int indexXDC;
    int channel;
    int binContents[1024];
};

#endif
