#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

void compute(vector<int> numbers, int d, int k)
{
  int end = 0;
  for(int i = 0; i < numbers.size(); i++)
  {
    int position = i + 1; // Position of the n element of array `a`.
    int start = end + 1; // Start position of a virtual `b_m` range.
    end += position * d; // End position of a virtual `b_m` range.
    
    if(k >= start && k <= end)
    {
      cout << position << endl;
      break;
    }
  }
}

int main() {
  // Request the number of test cases.
  vector<int> numbers;
  numbers.push_back(4);
  numbers.push_back(3);
  numbers.push_back(0);
  numbers.push_back(0);
  numbers.push_back(0);
  numbers.push_back(23);
  compute(numbers, 24, 100);

  //int cases;
  //cin >> cases;

  //for(int i = 0; i < cases; i++)
  //{
    //// Request a_n numbers.
    //int n;
    //vector<int> numbers;
    //while(scanf("%d", &n) && cin.get() != '\n')
      //numbers.push_back(n);

    //// Request d.
    //int d;
    //cin >> d;

    //// Request k.
    //int k;
    //cin >> k;

    //compute(numbers, d, k);
  //}

  return 0;
}
