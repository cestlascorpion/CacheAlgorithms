#ifndef CACHES_CACHELRU_H
#define CACHES_CACHELRU_H

#include "CacheBase.h"
#include <list>
#include <map>

struct lru_value {
    string value;
    mutable size_t hit;

    explicit lru_value(const string &val)
        : value(val)
        , hit(0) {}
};

class CacheLRU : public CacheBase {
public:
    enum { CACHE_LRU_THRESHOLD = 1 };

public:
    explicit CacheLRU(size_t threshold = CACHE_LRU_THRESHOLD);
    ~CacheLRU() override;

public:
    RESULT Get(const string &key, string &val) override;
    RESULT Set(const string &key, const string &val) override;

private:
    inline void update_hit(const lru_value &val) const {
        ++val.hit;
    }
    inline void set_threshold(size_t threshold) {
        m_threshold = threshold;
    }
    inline size_t get_threshold() const {
        return m_threshold;
    }

private:
    size_t m_threshold;

private:
    std::list<std::pair<string, lru_value>> m_list;
    std::map<string, std::list<std::pair<string, lru_value>>::iterator> m_hash;
};

#endif // CACHES_CACHELRU_H
