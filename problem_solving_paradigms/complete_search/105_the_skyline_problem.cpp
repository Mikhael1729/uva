#include <iostream>
#include <vector>
#include <array>

using namespace std;

struct Building
{
  int left; // Left or starting point of current in horizontal axis.
  int height; // Height of the current (vertical axis).
  int right; // Right or ending point of current in horizontal axis.

  Building(int left = -1, int height = -1, int right = -1) : left(left), height(height), right(right)
  { }
};

void drawInSkyline(Building next, Building previous, vector<int> skyline, vector<int> previousBuildings = vector<int>())
{
  bool areAdjacents = next.left <= previous.right;
  if(!areAdjacents)
  {
    skyline.push_back(previous.right);
    skyline.push_back(0);

    skyline.push_back(next.left);
    skyline.push_back(next.height);
  }
  else
  {
    // Register in the skyline vector the corresponding coordinates.
    bool endsAfterPrevious = next.right > previous.right;
    bool exceedsPreviousHeight = next.height > previous.height;

    if(endsAfterPrevious && exceedsPreviousHeight)
    {
      skyline.push_back(next.left);
      stkyline.push_back(next.height);
    }
    else if(endsAfterPrevious && !exceedsPreviousHeight)
    {
      skyline.push_back(previous.right);
      skyline.push_back(next.height);
    }
    else if(!endsAfterPrevious && exceedsPreviousHeight)
    {
      skyline.push_back(next.left);
      skyline.push_back(next.height);
    }
  }
}

int main()
{
  // Request buildings.
  int n, i = 1;
  vector<Building> buildings; // TODO: Make it a vector of pointers: vector<Building*> buildings { new Building() };
  Building current;
  while(scanf("%d", &n))
  {
    if(i == 1) current.l = n;
    if(i == 2) current.h = n;
    if(i == 3)
    {
      current.r = n;
      buildings.push_back(current);
      i = 1;
    }

    i++;
  }

  // Compute the skyline of the buildings.
  vector<int> skyline;
  int size = buildings.length();

  // Add initial coordinates.
  skyline.push_back(buildings[0].left);
  skyline.push_back(buildings[0].height);

  Building previous, next;
  for(int i = 1; i < size; i++)
  {
    previous = buildings[i - 1];
    next = buildings[i];

    vector<int> subSkyline;

    // Search for buildings that hides others.
    for(int j = 1; j < skyline.size(); j += 2)
    {
      int x = j - 1; // 5
      int y = j; // 6

      // Know if the next building starts before another one in the skyline.
      bool startsBefore = next.left < skyline[x];
      if(startsBefore)
      {
        subSkyline = vector<int>(skyline.begin() + x, skyline.end());
        skyline.erase(skyline.begin() + x, skyline.end())
        break;
      }
    }

    // Draw in the skyline.
    bool hideOtherBuildings = subSkyline.size() > 0;
    if(!hideOtherBuildings)
    {
      drawInSkyline(previous, next, skyline);
    }
    else
    {
      for(int j = 1; j < subSkyline.size(); j += 2)
      {
        int x = j - 1; 
        int y = j;

        bool coordinateIsInRange = next.right > subSkyline[x];
        if(coordinateIsInRange)
        {
          bool isHigherThanCurrent = next.height > subSkyline[y];
          if(isHigherThanCurrent)
          {
            subSkyline.erase(subSkyline.begin() + x, subSkyline.begin() + x + 1);
            drawInSkyline(previous, next, skyline);
          }
          else
          {
            drawInSkyline(previous, next, subSkyline);
          }
        }
      }

      // Merge the sub skyline with the original one.
      // TODO: If the sub skyline is without element there is no problem?
      skyline.insert(skyline.end(), subSkyline.begin(), subSkyline.end());
    }
  }

  // Last building coordinate.
  skyline.push_back(next.right);
  skyline.push_back(0);

  return 0;
}
