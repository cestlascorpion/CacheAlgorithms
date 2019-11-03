#include "CacheMgr.h"
#include "CacheMD5.h"
#include <fstream>
#include <regex>

using namespace std;

static vector<string> regex_split(const string &str, const string &ch) {
    regex re{ch};
    return vector<string>{sregex_token_iterator(str.begin(), str.end(), re, -1), sregex_token_iterator()};
}

static uint32_t to_u32(const string &str) {
    auto *digest = MD5(str).get_digest();
    uint32_t integer = 0;
    for (uint32_t i = 0; i < 4; ++i) {
        integer += ((uint32_t)(digest[i * 4u + 3u] & 0xFFu) << 24u) | ((uint32_t)(digest[i * 4u + 2u] & 0xFFu) << 16u) |
                   ((uint32_t)(digest[i * 4u + 1u] & 0xFFu) << 8u) | ((uint32_t)(digest[i * 4u + 0u] & 0xFFu));
    }
    return integer;
}
CacheMgr::CacheMgr()
    : m_type(FIFO)
    , m_size(EACH_MEMORY_MB - EACH_CONTROL_MB)
    , m_value(EACH_VAL_MB)
    , m_length(m_size / m_value) {}

CacheMgr::~CacheMgr() {
    for (auto *cache : m_cache) {
        if (cache != nullptr) {
            delete cache;
            cache = nullptr;
        }
    }
}

void CacheMgr::Init(size_t mem_MB, size_t slice_num, size_t val_MB, TYPE type, size_t extra) {
    m_size = (mem_MB / slice_num) - EACH_CONTROL_MB;
    m_length = m_size / val_MB;
    m_type = type;

    m_cache.resize(slice_num);
    for (auto &cache : m_cache) {
        switch (m_type) {
        case FIFO:
            cache = new CacheFIFO;
            cache->SetCapacity(m_length);
            break;
        case LRU:
            cache = new CacheLRU;
            cache->SetCapacity(m_length);
            break;
        case LFU:
            cache = new CacheLFU;
            cache->SetCapacity(m_length);
            break;
        case TWOQ:
            cache = new CacheQ2(extra);
            cache->SetCapacity(m_length);
            break;
        }
    }
}

double CacheMgr::Calculate(const string &file) {
    double ratio = 0.0;
    fstream urls;
    urls.open(file);
    if (!urls.is_open()) {
        return -1.0;
    }

    string line;
    uint32_t total = 0;
    uint32_t hit = 0;
    while (getline(urls, line)) {
        if (line.empty()) {
            continue;
        }
        auto txt = regex_split(line, " ");
        string key = txt[1];
        string val = "val";
        size_t idx = to_u32(key) % m_cache.size();

        ++total;
        if (txt[0] == "Get") {
            if (m_cache[idx]->Get(key, val) == GET_SUCCESS) {
                ++hit;
            }
        } else {
            if (m_cache[idx]->Set(key, val) == SET_EXIST) {
                ++hit;
            }
        }
    }
    ratio = (double)hit / (double)total;
    return ratio;
}

void CacheMgr::Release() {
    for (auto *cache : m_cache) {
        if (cache != nullptr) {
            delete cache;
            cache = nullptr;
        }
    }
    m_cache.clear();
}
