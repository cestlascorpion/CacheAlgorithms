#include "CacheQ2.h"

using namespace std;

CacheQ2::CacheQ2(size_t percent)
    : _percent(percent)
    , _list()
    , _hash() {}

CacheQ2::~CacheQ2() = default;

RESULT CacheQ2::Get(const string &key, string &val) {
    auto iter = _hash.find(key);
    if (iter == _hash.end()) {
        return GET_FAIL;
    }

    q2_value tmp = iter->second->second;
    update_hit(tmp);

    _list.erase(iter->second);
    _hash[key] = _list.insert(_list.end(), {key, tmp});

    val = tmp.value;
    return GET_SUCCESS;
}

RESULT CacheQ2::Set(const string &key, const string &val) {
    auto iter = _hash.find(key);
    if (iter != _hash.end()) {
        q2_value tmp = iter->second->second;
        update_hit(tmp);

        _list.erase(iter->second);
        _hash[key] = _list.insert(_list.end(), {key, tmp});
        return SET_EXIST;
    }

    q2_value value(val);
    if (_list.size() < _capacity) {
        long distance = (long)(_list.size() / 100 * get_percent());
        auto pos = _list.begin();
        advance(pos, distance);
        _hash[key] = _list.insert(pos, {key, value});
        // _hash[key] = _list.insert(_list.end(), {key, value});
        return SET_NO_REC;
    }

    _hash.erase(_list.front().first);
    _list.pop_front();
    long distance = (long)(_list.size() / 100 * get_percent());
    auto pos = _list.begin();
    advance(pos, distance);
    _hash[key] = _list.insert(pos, {key, value});
    // _hash[key] = _list.insert(_list.end(), {key, value});
    return SET_AND_REC;
}
