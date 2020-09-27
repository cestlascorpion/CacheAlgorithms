#include "CacheLRU.h"

using namespace std;

namespace scorpion {

CacheLRU::CacheLRU(size_t threshold)
    : _threshold(threshold)
    , _list()
    , _hash() {}

CacheLRU::~CacheLRU() = default;

RESULT CacheLRU::Get(const string &key, string &val) {
    auto iter = _hash.find(key);
    if (iter == _hash.end()) {
        return GET_FAIL;
    }

    lru_value tmp = iter->second->second;
    update_hit(tmp);

    if (tmp.hit >= _threshold) {
        _list.erase(iter->second);
        _hash[key] = _list.insert(_list.end(), {key, tmp});
    }

    val = tmp.value;
    return GET_SUCCESS;
}

RESULT CacheLRU::Set(const string &key, const string &val) {
    auto iter = _hash.find(key);
    if (iter != _hash.end()) {
        lru_value tmp = iter->second->second;
        update_hit(tmp);

        if (tmp.hit >= _threshold) {
            _list.erase(iter->second);
            _hash[key] = _list.insert(_list.end(), {key, tmp});
        }
        return SET_EXIST;
    }

    lru_value value(val);
    if (_list.size() < _capacity) {
        _hash[key] = _list.insert(_list.end(), {key, value});
        return SET_NO_REC;
    }

    _hash.erase(_list.front().first);
    _list.pop_front();

    _hash[key] = _list.insert(_list.end(), {key, value});
    return SET_AND_REC;
}

} // namespace scorpion
