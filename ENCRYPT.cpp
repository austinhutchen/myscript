#pragma once
#include <__config>
#include <bitset>
#include <climits>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <stack>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

class Secure {
public:
  void reverseString(string &s) {
    // ptr swap at beginning and end;
    char *beg = &s[0];
    char *last = &s[s.size() - 1];
    for (; beg < last && last != &s[0]; beg++ && last--) {
      swap(beg, last);
    }
  }

  vector<bitset<8> > strbit(string &myString, uint &max) {
    max = myString.size();
    vector<bitset<8> > ret;
    for (std::size_t i = 0; i < myString.size(); ++i) {
      ret.push_back(bitset<8>(myString[i]));
    }
    return ret;
  }

  uint b2hx(vector<bitset<8> > input, uint &size) {
    long int binaryval, hexadecimalval = 0, i = 1, remainder;
    int k = 0;
    while (k < size) {
      remainder = binaryval % 10;
      hexadecimalval = hexadecimalval + remainder * i;
      i = i << 1;
      binaryval = binaryval / 10;
      k++;
    }
    return hexadecimalval;
  }

  vector<bitset<8> > encrypt(string &input, unsigned int &hx) {
    // cypher algorithm
    reverseString(input);
    char c;
    std::bitset<8> mask(INT_MAX);
    unsigned long i;
    uint max;
    vector<bitset<8> > vect = strbit(input, max);
    for (int i = 0; i < vect.size(); i++) {
      // take one's complement
      // XOR is bijective mapping, allowing reverse-engineer of decryption
      // string
      vect[i] = ~vect[i] ^ mask;
      vect[i] = vect[i] << 2 | vect[i] >> (6);
    }
    hx = b2hx(vect, max);
    return vect;
  }

  vector<bitset<8> > load() {
    ifstream in;
    in.open("./txt/in.txt");
    string line;
    string file;
    uint hx;
    while (getline(in, line)) {
      file += line + ' ';
    }
    return encrypt(file, hx);
  }

  void print(vector<bitset<8> > vect) {
    ofstream fout;
    fout.open("./txt/out.txt");
    for (int i = 0; i < vect.size(); i++) {
      fout << vect[i] << endl;
    }
    fout.close();
  }

  string decrypt(vector<bitset<8> > vect) {
    char c;
    string output;
    int x;
    std::bitset<8> mask(INT_MAX);
#pragma omp parallel for
    for (int i = 0; i < vect.size(); i++) {
      vect[i] = ~vect[i] ^ mask;
      vect[i] = vect[i] >> 2 | vect[i] << (6);
      x = vect[i].to_ulong();
      if (x <= CHAR_MAX) {
        c = static_cast<char>(x);
        output += c;
      } else {
        output += ' ';
      }
    }
    reverseString(output);
    return output;
  }
};