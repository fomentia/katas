#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class IWString {
  struct charNode {
    char currentChar;
    int currentIndex;
    charNode * nextChar;
  };
  typedef charNode * stringArray;

  stringArray self;

  static stringArray stringLinker(string str) {
    vector<char> v(str.begin(), str.end());
    stringArray sa;
    sa = NULL;
    for(int ch = 0; ch < str.size(); ch++) {
      charNode * node = new charNode;
      node->currentChar = v[ch];
      node->currentIndex = ch;
      node->nextChar = sa;
      sa = node;
    }
    return sa;
  }

  string toString(stringArray sa) {
    string str;
    charNode * loop = self;
    while(loop != NULL) {
      str += loop->currentChar;
      loop = loop->nextChar;
    }
    reverse(str.begin(), str.end());
    return str;
  }

public:
  IWString() { self = NULL; }
  IWString(string initialString) {
    self = stringLinker(initialString);
  }

  string replace(string target, string replaceText) {
    string source = toString(self);
    stringArray targetArray = stringLinker(target);

    charNode * loop = self;
    charNode * targetloop = targetArray;
    vector<vector<int> > result;
    vector<int> cache;
    while(loop != NULL) {
      if(targetloop != NULL) {
        if(loop->currentChar == targetloop->currentChar) {
          cache.push_back(loop->currentIndex);
          targetloop = targetloop->nextChar;
        } else {
          targetloop = targetArray; cache.clear();
        }
      }
      if(targetloop == NULL) {
        result.push_back(cache);
        targetloop = targetArray; cache.clear();
      }
      loop = loop->nextChar;
    }

    for(int i = 0; i < result.size(); ++i) {
      source.replace(result[i].back(), result[i].size(), replaceText);
    }

    return source;
  }

  string remove(const int& start, const int& count) {
    // Manual implementation of std::string::erase
    string wholestr = toString(self);
    string alteredstr;
    vector<int> toRemove;
    for(int i = start; i < start + count; ++i) { toRemove.push_back(i); }
    for(int i = 0; i < wholestr.length(); ++i) {
      if(std::find(toRemove.begin(), toRemove.end(), i) == toRemove.end()) {
        alteredstr += wholestr[i];
      }
    }
    return alteredstr;
  }
};
