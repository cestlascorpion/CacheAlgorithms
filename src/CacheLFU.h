#pragma once

#include "CacheBase.h"

#include <list>
#include <map>

namespace scorpion {

struct lfu_info {
    std::string value;
    // 同频次构成链表，外层是{频次-链表}的链表，外层链表迭代器
    std::list<std::pair<int, std::list<std::string>>>::iterator it_pair;
    std::list<std::string>::iterator it_key; // 内层链表迭代器
};

class CacheLFU : public CacheBase {
public:
    CacheLFU();
    ~CacheLFU() override;

public:
    RESULT Get(const std::string &key, std::string &val) override;
    RESULT Set(const std::string &key, const std::string &val) override;

private:
    void visit(std::map<std::string, lfu_info>::iterator, const std::string &key);

private:
    std::list<std::pair<int, std::list<std::string>>> _list;
    std::map<std::string, lfu_info> _hash;
};

} // namespace scorpion
