#pragma once

#include "CacheBase.h"

#include <list>
#include <map>

namespace scorpion {

class CacheFIFO : public CacheBase {
public:
    CacheFIFO();
    ~CacheFIFO() override;

public:
    RESULT Get(const std::string &key, std::string &val) override;
    RESULT Set(const std::string &key, const std::string &val) override;

private:
    std::list<std::pair<std::string, std::string>> _list;
    std::map<std::string, std::list<std::pair<std::string, std::string>>::iterator> _hash;
};

} // namespace scorpion
