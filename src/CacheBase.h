#pragma once

#include <cstdint>
#include <string>

namespace scorpion {

enum RESULT {
    GET_SUCCESS = 0,
    GET_FAIL = 1,
    SET_NO_REC = 3,
    SET_EXIST = 4,
    SET_AND_REC = 5,
};

class CacheBase {
public:
    enum { CACHE_MAX_K_NUM = 10000 };

public:
    CacheBase()
        : _capacity(CACHE_MAX_K_NUM) {}

    virtual ~CacheBase() = default;

public:
    virtual RESULT Get(const std::string &key, std::string &val) = 0;

    virtual RESULT Set(const std::string &key, const std::string &val) = 0;

public:
    virtual void SetCapacity(size_t capacity) final {
        _capacity = capacity;
    }

    virtual size_t GetCapacity() const final {
        return _capacity;
    }

protected:
    size_t _capacity;
};

} // namespace scorpion
