#ifndef CACHES_CACHEQ2_H
#define CACHES_CACHEQ2_H

#include "CacheBase.h"
#include <list>
#include <map>

struct q2_value {
    string value;
    mutable size_t hit;

    explicit q2_value(const string &val)
        : value(val)
        , hit(0) {}
};

class CacheQ2 : public CacheBase {
public:
    enum { PERCENTAGE = 80 };

public:
    explicit CacheQ2(size_t percent = PERCENTAGE);
    ~CacheQ2() override;

public:
    RESULT Get(const string &key, string &val) override;
    RESULT Set(const string &key, const string &val) override;

public:
    inline void set_percent(size_t percent) {
        _percent = percent;
    }
    inline size_t get_percent() const {
        return _percent;
    }

private:
    inline void update_hit(const q2_value &val) const {
        ++val.hit;
    }

private:
    size_t _percent;

private:
    std::list<std::pair<string, q2_value>> _list;
    std::map<string, std::list<std::pair<string, q2_value>>::iterator> _hash;
};

#endif // CACHES_CACHEQ2_H
