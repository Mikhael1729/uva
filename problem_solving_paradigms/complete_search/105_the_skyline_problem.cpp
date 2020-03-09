#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void compute(int building[])
{
  cout << "Hello: " << building[2] << endl;
}

int main()
{
  int n;
  vector<int> buildings;
  while(scanf("%d", &n))
    buildings.push_back(n);

  int building[3];
  for(int i = 0, j = 0; i < buildings.size(); i++)
  {
    building[j++] = buildings[i];
    
    // Reset the array to the next building secuence.
    if((i + 1) % 3 == 0)
    {
      compute(building);
      j = 0;
    }
  }

  return 0;
}
