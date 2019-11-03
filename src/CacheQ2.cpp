#include "CacheQ2.h"

using namespace std;

CacheQ2::CacheQ2(size_t percent)
    : m_percent(percent)
    , m_list()
    , m_hash() {}

CacheQ2::~CacheQ2() = default;

RESULT CacheQ2::Get(const string &key, string &val) {
    auto iter = m_hash.find(key);
    if (iter == m_hash.end()) {
        return GET_FAIL;
    }

    q2_value tmp = iter->second->second;
    update_hit(tmp);

    m_list.erase(iter->second);
    m_hash[key] = m_list.insert(m_list.end(), {key, tmp});

    val = tmp.value;
    return GET_SUCCESS;
}

RESULT CacheQ2::Set(const string &key, const string &val) {
    auto iter = m_hash.find(key);
    if (iter != m_hash.end()) {
        q2_value tmp = iter->second->second;
        update_hit(tmp);

        m_list.erase(iter->second);
        m_hash[key] = m_list.insert(m_list.end(), {key, tmp});
        return SET_EXIST;
    }

    q2_value value(val);
    if (m_list.size() < m_capacity) {
        long distance = (long)(m_list.size() / 100 * get_percent());
        auto pos = m_list.begin();
        advance(pos, distance);
        m_hash[key] = m_list.insert(pos, {key, value});
        // m_hash[key] = m_list.insert(m_list.end(), {key, value});
        return SET_NO_REC;
    }

    m_hash.erase(m_list.front().first);
    m_list.pop_front();
    long distance = (long)(m_list.size() / 100 * get_percent());
    auto pos = m_list.begin();
    advance(pos, distance);
    m_hash[key] = m_list.insert(pos, {key, value});
    // m_hash[key] = m_list.insert(m_list.end(), {key, value});
    return SET_AND_REC;
}
