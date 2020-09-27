#include "CacheFIFO.h"

using namespace std;

namespace scorpion {

CacheFIFO::CacheFIFO()
    : _list()
    , _hash() {}

CacheFIFO::~CacheFIFO() = default;

RESULT CacheFIFO::Get(const string &key, string &val) {
    auto iter = _hash.find(key);
    if (iter == _hash.end()) {
        return GET_FAIL;
    }
    val = iter->second->second;
    return GET_SUCCESS;
}

RESULT CacheFIFO::Set(const string &key, const string &val) {
    auto iter = _hash.find(key);
    if (iter != _hash.end()) {
        return SET_EXIST;
    }
    if (_list.size() < _capacity) {
        _hash[key] = _list.insert(_list.end(), {key, val});
        return SET_NO_REC;
    }
    _hash.erase(_list.front().first);
    _list.pop_front();
    _hash[key] = _list.insert(_list.end(), {key, val});
    return SET_AND_REC;
}

} // namespace scorpion
