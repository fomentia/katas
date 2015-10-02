#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct charNode {
  char currentChar;
  int currentIndex;
  charNode * nextChar;
};
typedef charNode * stringArray;

stringArray stringArrayInitializer(string str) {
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

void replace(string source, string target, string replaceText) {
  reverse(source.begin(), source.end());
  reverse(target.begin(), target.end());
  reverse(replaceText.begin(), replaceText.end());
  stringArray sourceArray = stringArrayInitializer(source);
  stringArray targetArray = stringArrayInitializer(target);

  charNode * loop = sourceArray;
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

  reverse(source.begin(), source.end());
  cout << source << endl;
}

int main () {
  string source; string target; string replacement;
  cout << "Please enter your string: ";
  getline(cin, source);
  cout << "Please enter your target: ";
  getline(cin, target);
  cout << "Please enter your replacement text: ";
  getline(cin, replacement);

  replace(source, target, replacement);
}
