#include <iostream>
#include <vector>
#include <array>

using namespace std;

struct Building
{
  int left; // Left or starting point of current in horizontal axis.
  int height; // Height of the current (vertical axis).
  int right; // Right or ending point of current in horizontal axis.
};

int main()
{
  // Request buildings.
  int n, i = 1;
  vector<Building> buildings;
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
  Building current, next;
  for(int i = 0, j = i + 1; i < buildings.length(); i++)
  {
    // Current building.
    current = buildings[i];

    // Draw the skyline.
    skyline.push_back(buildings[i].left);
    skyline.push_back(buildings[i].height);

    // Select buildings to pass above (discarding the hidden buildings).
    vector<Building> insideRange;
    for(; next.left < current.r; j++)
    {
      next = buildings[j]
      bool visibleWithCurrentBuilding =
        next.right > current.right || next.height > current.height;

      if(insideRange.length() == 0)
      {
        if(visibleWithCurrentBuilding)
          insideRange.push_back(next);
      }
      else
      {
        bool visibleWithPreviousBuilding =
        (
          next.right > insideRange[j - 1].right &&
          next.height > insideRange[j - 1].height
        );

        if(visibleWithCurrentBuilding || visibleWithPreviousBuilding)
          insideRange.push_back(next);
        else
          insideRange.erase(insideRange.begin() + j - 1);
      }
    }

    // Avoid the processed buildings.
    i = j;
  }

  return 0;
}
