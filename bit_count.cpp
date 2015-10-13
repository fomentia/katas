#include <iostream>
using namespace std;

bool iterative_bits_odd(int bits[], int size) {
  int count_of_ones = 0;
  for(int i = 0; i < size; ++i) {
    if(bits[i] == 1)
      ++count_of_ones;
  }

  if(count_of_ones % 2 == 0) return false;
  return true;
}

bool recursive_bits_odd(int bits[], int size) {
  if(size == 0) return false;
  int decrementer = 1;
  while(true) {
    if(bits[size - decrementer] == 0) {
      ++decrementer;
    } else {
      break;
    }
  }
  int lastOne = bits[size - decrementer];
  int allButLastOne = recursive_bits_odd(bits, size - decrementer);

  if((lastOne + allButLastOne) % 2 == 0) return false;
  return true;
}

int main() {
  int a[10] = {1, 0, 0, 0, 0, 1, 0, 1, 1, 1};
  cout << iterative_bits_odd(a, 10) << endl;
  cout << recursive_bits_odd(a, 10) << endl;
}
