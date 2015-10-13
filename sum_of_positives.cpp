#include <iostream>
using namespace std;

int iterative_sum_of_positives(int vector_of_numbers[], int size) {
  int result = 0;
  for(int i = 0; i < size; ++i) {
    if(vector_of_numbers[i] > 0) {
      result += vector_of_numbers[i];
    }
  }
  return result;
}

int recursive_sum_of_positives(int vector_of_numbers[], int size) {
  if(size == 0) return 0;
  int decrementer = 1;
  while(true) {
    if(vector_of_numbers[size - decrementer] < 0) {
      ++decrementer;
    } else {
      break;
    }
  }
  int lastPositive = vector_of_numbers[size - decrementer];
  int allButLastPositive = recursive_sum_of_positives(vector_of_numbers, size - decrementer);

  return lastPositive + allButLastPositive;
}

int main() {
  int a[9] = {5, 4, 33, -9, -9, -1, 0, -444, 15};
  cout << iterative_sum_of_positives(a, 9) << endl;
  cout << recursive_sum_of_positives(a, 9) << endl;
}
