#include <iostream>

using namespace std;

bool hasRepeatedDigits(unsigned long long number)
{
  string inString = to_string(number); // Stores the number in string format.
  bool record[10] { false };

  for(int i = 0; i < inString.length(); i++)
  {
    int current = inString[i] - '0'; // Convert char value to an integer one.
    if(!record[current])
      record[current] = true;
    else
      return true;
  }

  return false;
}

// Computes the required solution for the sepecified number `n`.
void compute(unsigned long long n)
{
  unsigned long long limit = 9900000000;
  unsigned long long i;

  for(unsigned long long j = 1; j < limit; j++)
    if(!hasRepeatedDigits(j))
    {
      i = n * j;

      if(i >= limit)
        break;

      if((i / j) == n && !hasRepeatedDigits(i))
        cout << i << " / " << j << " = " << n << endl;
    }
}

int main()
{
  // Request the number of test cases.
  int testCases;
  cin >> testCases;

  cout << "" << endl;

  // Generates the output for each one of them.
  for(int i = 0; i < testCases; i++)
  {
    int n;
    cin >> n;
    compute(n);
  }
  
  return 0;
}
