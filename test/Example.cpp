#include "CacheMgr.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace scorpion;

int main() {
    auto *manager = new CacheMgr;
    string file = "../conf/data.txt";

    size_t mem_MB = 5 * 1024;
    size_t sli_num = 5;
    size_t val_MB = 3;

    const vector<pair<CacheMgr::TYPE, size_t>> paras = {
        {CacheMgr::FIFO, 0},  {CacheMgr::LRU, 0},   {CacheMgr::LFU, 0},   {CacheMgr::TWOQ, 10},
        {CacheMgr::TWOQ, 20}, {CacheMgr::TWOQ, 30}, {CacheMgr::TWOQ, 40}, {CacheMgr::TWOQ, 50},
        {CacheMgr::TWOQ, 60}, {CacheMgr::TWOQ, 70}, {CacheMgr::TWOQ, 80}, {CacheMgr::TWOQ, 90}};

    for (const auto &p : paras) {
        manager->Init(mem_MB, sli_num, val_MB, p.first, p.second);
        auto ratio = manager->Calculate(file);
        manager->Release();
        cout << fixed << setprecision(4) << ratio * 100 << endl;
    }

    delete manager;
    return 0;
}