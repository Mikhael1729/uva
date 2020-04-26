#include <iostream>
#include <map>
#include <vector>
#include <limits>

using namespace std;

struct Building
{
  int left;
  int height;
  int right;

  Building(int left = -1, int height = -1, int right = -1) : left(left), height(height), right(right)
  { }
};

int main()
{
  // Request buildings.
  int n, i = 1;
  vector<Building> buildings; // TODO: Make it a vector of pointers: vector<Building*> buildings { new Building() };
  Building current;
  while(scanf("%d", &n))
  {
    if(i == 1) current.left = n;
    if(i == 2) current.height = n;
    if(i == 3)
    {
      current.right = n;
      buildings.push_back(current);
      i = 0;
    }

    i++;
  }

  map<int, int> preskyline; // Holds a representation of the buildings that helps to generate the skyline

  // Code the first building into preskyline.
  {
    Building first = buildings[0];
    for(int i = first.left; i <= first.right; i++)
      preskyline.insert(pair<int, int>(i, first.height));
  }

  // Code the rest of the buildings in the preskyline.
  int desviation = 0;
  for(int i = 1; i < buildings.size(); i++)
  {
    Building current = buildings[i];
    int y = current.height;
    int x = current.left + desviation;

    // TODO: Probably in the following lines there is the gap.
    bool thereIsCrossBuilding = preskyline[x] > 0 && y > preskyline[x];  
    if(thereIsCrossBuilding)
    {
      preskyline[x] *= -1;
      desviation++;
      x++;
    }

    int prevY = preskyline[x];
    for(; x <= current.right; x++)
    {
      bool isHidden = y < preskyline[x];
      bool endOfPreviuosBuilding = prevY != preskyline[x + 1];
      bool endOfCurrentBuilding = x + 1 > current.right;

      if(!isHidden || (endOfPreviuosBuilding && !endOfCurrentBuilding))
        preskyline[x] = y;
    }
  }

  cout << "\ndesviation: " << desviation << endl;

  // Print preskyline.
  cout << "\nPreskyline:\n" << endl;
  for(map<int, int>::iterator it = preskyline.begin(); it != preskyline.end(); ++it)
    cout << it->first << " " << it->second << " " << endl;

  cout << "\nSkyline:\n" << endl;

  // Print skyline.
  int previousHeight = -1;
  desviation = 0;
  for(map<int, int>::iterator it = preskyline.begin(); it != preskyline.end(); ++it)
  {
    // Get coordinates.
    int x = it->first - desviation;
    int y = it->second;

    if(y <= 0)
    {
      y *= -1;
      desviation++;
    }

    bool isNextRepresentation = y != previousHeight;
    if(isNextRepresentation)
    {
      previousHeight = y;
      cout << x << " " << y << " ";
    }
  }

  // Print last coordinates for the skyline.
  map<int, int>::const_reverse_iterator last = preskyline.crbegin();
  cout << last->first << " " << 0;

  return 0;
}
