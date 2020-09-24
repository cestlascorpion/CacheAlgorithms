#ifndef CACHES_CACHELFU_H
#define CACHES_CACHELFU_H

#include "CacheBase.h"
#include <list>
#include <map>

struct lfu_info {
    string value;
    // 同频次构成链表，外层是{频次-链表}的链表，外层链表迭代器
    std::list<std::pair<int, std::list<string>>>::iterator it_pair;
    std::list<string>::iterator it_key; // 内层链表迭代器
};

class CacheLFU : public CacheBase {
public:
    CacheLFU();
    ~CacheLFU() override;

public:
    RESULT Get(const string &key, string &val) override;
    RESULT Set(const string &key, const string &val) override;

private:
    void visit(std::map<string, lfu_info>::iterator, const string &key);

private:
    std::list<std::pair<int, std::list<string>>> _list;
    std::map<string, lfu_info> _hash;
};

#endif // CACHES_CACHELFU_H
