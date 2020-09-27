#pragma once

#include "CacheBase.h"
#include <list>
#include <map>

namespace scorpion {

struct q2_value {
    std::string value;
    mutable size_t hit;

    explicit q2_value(const std::string &val)
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
    RESULT Get(const std::string &key, std::string &val) override;
    RESULT Set(const std::string &key, const std::string &val) override;

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
    std::list<std::pair<std::string, q2_value>> _list;
    std::map<std::string, std::list<std::pair<std::string, q2_value>>::iterator> _hash;
};

} // namespace scorpion
