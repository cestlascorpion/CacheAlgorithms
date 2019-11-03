#include "CacheLFU.h"

using namespace std;

CacheLFU::CacheLFU()
    : m_list()
    , m_hash() {}

CacheLFU::~CacheLFU() = default;

RESULT CacheLFU::Get(const string &key, string &val) {
    auto iter = m_hash.find(key);
    if (iter == m_hash.end()) {
        return GET_FAIL;
    }

    visit(iter, key);
    val = iter->second.value;
    return GET_SUCCESS;
}

RESULT CacheLFU::Set(const string &key, const string &val) {
    auto iter = m_hash.find(key);
    if (iter != m_hash.end()) {
        visit(iter, key);
        return SET_EXIST;
    }

    auto res = SET_NO_REC;
    if (m_hash.size() == m_capacity) {
        auto it = m_list.front().second.begin();
        m_hash.erase(*it);
        m_list.front().second.erase(it);
        if (m_list.front().second.empty()) {
            m_list.erase(m_list.begin());
        }
        res = SET_AND_REC;
    }
    if (m_list.empty() || m_list.front().first != 1) {
        m_list.push_front({1, {key}});
    } else {
        m_list.front().second.push_back(key);
    }
    m_hash[key] = {val, m_list.begin(), prev(m_list.front().second.end())};
    return res;
}

void CacheLFU::visit(map<string, lfu_info>::iterator iter, const string &key) {
    auto it_pair = iter->second.it_pair; // 外层pair链表迭代器
    auto it_key = iter->second.it_key;   // 内层sting链表迭代器
    int hit = it_pair->first + 1;        // 频次

    it_pair->second.erase(it_key);
    // it_pair成为指向下一个频次的pair链表的迭代器
    if (it_pair->second.empty()) {
        it_pair = m_list.erase(it_pair); // 当前频次为空
    } else {
        advance(it_pair, 1); // 频次加1
    }
    // 没有当前频次的链表 需要新建一个
    if (it_pair == m_list.end() || it_pair->first != hit) {
        it_pair = m_list.insert(it_pair, {hit, {key}});
    } else {
        it_pair->second.push_back(key);
    }

    iter->second.it_pair = it_pair;                    // 更新外层迭代器
    iter->second.it_key = prev(it_pair->second.end()); // 更新内层迭代器
}
