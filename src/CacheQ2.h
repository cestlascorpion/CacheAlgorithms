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
        m_percent = percent;
    }
    inline size_t get_percent() const {
        return m_percent;
    }

private:
    inline void update_hit(const q2_value &val) const {
        ++val.hit;
    }

private:
    size_t m_percent;

private:
    std::list<std::pair<string, q2_value>> m_list;
    std::map<string, std::list<std::pair<string, q2_value>>::iterator> m_hash;
};

#endif // CACHES_CACHEQ2_H
