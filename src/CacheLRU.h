#pragma once

#include "CacheBase.h"

#include <list>
#include <map>

namespace scorpion {

struct lru_value {
    std::string value;
    mutable size_t hit;

    explicit lru_value(const std::string &val)
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
    RESULT Get(const std::string &key, std::string &val) override;
    RESULT Set(const std::string &key, const std::string &val) override;

private:
    inline void update_hit(const lru_value &val) const {
        ++val.hit;
    }
    inline void set_threshold(size_t threshold) {
        _threshold = threshold;
    }
    inline size_t get_threshold() const {
        return _threshold;
    }

private:
    size_t _threshold;

private:
    std::list<std::pair<std::string, lru_value>> _list;
    std::map<std::string, std::list<std::pair<std::string, lru_value>>::iterator> _hash;
};

} // namespace scorpion
