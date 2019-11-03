#include "CacheFIFO.h"

using namespace std;

CacheFIFO::CacheFIFO()
    : m_list()
    , m_hash() {}

CacheFIFO::~CacheFIFO() = default;

RESULT CacheFIFO::Get(const string &key, string &val) {
    auto iter = m_hash.find(key);
    if (iter == m_hash.end()) {
        return GET_FAIL;
    }
    val = iter->second->second;
    return GET_SUCCESS;
}

RESULT CacheFIFO::Set(const string &key, const string &val) {
    auto iter = m_hash.find(key);
    if (iter != m_hash.end()) {
        return SET_EXIST;
    }
    if (m_list.size() < m_capacity) {
        m_hash[key] = m_list.insert(m_list.end(), {key, val});
        return SET_NO_REC;
    }
    m_hash.erase(m_list.front().first);
    m_list.pop_front();
    m_hash[key] = m_list.insert(m_list.end(), {key, val});
    return SET_AND_REC;
}
