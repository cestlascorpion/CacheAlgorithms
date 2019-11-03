#include "../src/CacheMD5.h"
#include <fstream>
#include <iostream>

using namespace std;

void generate_data(const string &in_file);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage: ./generator in_file" << endl;
        return 0;
    }
    string in_file = argv[1];
    generate_data(in_file);
    return 0;
}

void generate_data(const string &in_file) {
    fstream in;
    in.open(in_file, ios::in);
    fstream out;
    out.open("../conf/data.txt", ios::app | ios::out);
    string line;
    while (getline(in, line)) {
        string md5 = MD5(line).to_str();
        int random = rand() % 10;
        if (random < 3) {
            out << "Set " << md5 << endl;
        } else {
            out << "Get " << md5 << endl;
        }
    }
    in.close();
    out.close();
}