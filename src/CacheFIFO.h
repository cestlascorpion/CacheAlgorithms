#ifndef CACHES_CACHEFIFO_H
#define CACHES_CACHEFIFO_H

#include "CacheBase.h"
#include <list>
#include <map>

class CacheFIFO : public CacheBase {
public:
    CacheFIFO();
    ~CacheFIFO() override;

public:
    RESULT Get(const string &key, string &val) override;
    RESULT Set(const string &key, const string &val) override;

private:
    std::list<std::pair<string, string>> _list;
    std::map<string, std::list<std::pair<string, string>>::iterator> _hash;
};

#endif // CACHES_CACHEFIFO_H
