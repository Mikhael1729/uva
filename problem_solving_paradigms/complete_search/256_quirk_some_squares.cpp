#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

int computeLimit(int digits)
{
  string max = "";
  for(int i = 0; i < digits; i++)
    max += '9';

  return stoi(max);
}

string toString(int number, int digits)
{
  string converted = to_string(number);
  while(converted.length() < digits)
    converted = '0' + converted;

  return converted;
}
  
int main() {
  // Request numbers
  int n;
  while(scanf("%d", &n))
  {
    for(int i = 0; i < computeLimit(n); i++)
    {
      string digits = toString(i, n);
      int middle = digits.length() / 2;

      string digit1 = digits.substr(0, middle);
      string digit2 = digits.substr(middle, middle + middle);
      int power = pow(stoi(digit1) + stoi(digit2), 2);
      
      if(i == power)
        cout << digits << endl;
    }
  }

  return 0;
}
