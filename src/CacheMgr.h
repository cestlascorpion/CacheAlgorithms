#ifndef CACHES_CACHEMGR_H
#define CACHES_CACHEMGR_H

#include "CacheFIFO.h"
#include "CacheLFU.h"
#include "CacheLRU.h"
#include "CacheMD5.h"
#include "CacheQ2.h"
#include <vector>

class CacheMgr {
public:
    enum TYPE { FIFO = 0, LRU = 1, LFU = 2, TWOQ = 3 };
    enum { EACH_MEMORY_MB = 1024, EACH_CONTROL_MB = 128, EACH_VAL_MB = 4 };

public:
    CacheMgr();
    ~CacheMgr();

public:
    void Init(size_t me_MB, size_t slice_num, size_t val_MB, TYPE type, size_t extra);
    double Calculate(const string &file);
    void Release();

private:
    TYPE _type;
    size_t _size;
    size_t _value;
    size_t _length;

    std::vector<CacheBase *> _cache;
};

#endif // CACHES_CACHEMGR_H
