#include <iostream>
using namespace std;

int main () {
  int surveydata[10] = { 3, 2, 3, 4, 4, 4, 3, 3, 9, 10 };
  int histogram[10];
  int mode = 0;
  for(int i = 0; i < 10; i++) { histogram[i] = 0; }
  for(int i = 0; i < 10; i++) { histogram[surveydata[i] - 1]++; }
  for(int i = 0; i < 10; i++) {
    if(histogram[i] > histogram[mode]) mode = i;
  }
  cout << "The mode is " << ++mode << endl;
}
