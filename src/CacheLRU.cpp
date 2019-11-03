#include "CacheLRU.h"

using namespace std;

CacheLRU::CacheLRU(size_t threshold)
    : m_threshold(threshold)
    , m_list()
    , m_hash() {}

CacheLRU::~CacheLRU() = default;

RESULT CacheLRU::Get(const string &key, string &val) {
    auto iter = m_hash.find(key);
    if (iter == m_hash.end()) {
        return GET_FAIL;
    }

    lru_value tmp = iter->second->second;
    update_hit(tmp);

    if (tmp.hit >= m_threshold) {
        m_list.erase(iter->second);
        m_hash[key] = m_list.insert(m_list.end(), {key, tmp});
    }

    val = tmp.value;
    return GET_SUCCESS;
}

RESULT CacheLRU::Set(const string &key, const string &val) {
    auto iter = m_hash.find(key);
    if (iter != m_hash.end()) {
        lru_value tmp = iter->second->second;
        update_hit(tmp);

        if (tmp.hit >= m_threshold) {
            m_list.erase(iter->second);
            m_hash[key] = m_list.insert(m_list.end(), {key, tmp});
        }
        return SET_EXIST;
    }

    lru_value value(val);
    if (m_list.size() < m_capacity) {
        m_hash[key] = m_list.insert(m_list.end(), {key, value});
        return SET_NO_REC;
    }

    m_hash.erase(m_list.front().first);
    m_list.pop_front();

    m_hash[key] = m_list.insert(m_list.end(), {key, value});
    return SET_AND_REC;
}
