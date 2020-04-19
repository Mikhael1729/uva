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
  int size = buildings.length();
  for(int i = 0, j = 1; i < size; i++)
  {
    // Current building.
    Building current = buildings[i];

    // Draw the first coordinates in the skyline.
    skyline.push_back(current.left);
    skyline.push_back(current.height);

    // Do the following until reach a separated building or an overlaping one.
    Building previous, next;
    Building xBuilding = Building(), yBuilding = Building(),overlapingBuilding = Building(); // It's the higher building with the greater range. // It's the building a step before in range and heigth of the closeleBuilding.
    for(j = i + 1; j < size; j++)
    {
      previous = buildings[j-1];
      next = buildings[j];

      // TODO: make the adjustement for possible yBuilding incorrect analisis.
      bool buildingsAreSeparated = next.left > xBuilding.right;
      if(buildingsAreSeparated)
        break;

      // Delete hidden elements from the skyline.
      //bool overlapsPreviousBuilding = (
        //next.right > xBuilding.right &&
        //next.height > yBuilding.height &&
        //next.height > current.height &&
        //next.right > current.right);

      // TODO: Review the following analisis.
      // Know when the following building hides the previous ones.
      bool overlapsPreviousBuildings = (
        next.left <= current.right &&
        next.height >= yBuilding.height &&
        next.right >= xBuilding.right);

      if (overlapsPreviousBuildings)
        skyline.erase(skyline.begin() + (i), skyline.end());

      // Register in the skyline vector the corresponding coordinates.
      bool exceedsPreviousRange = next.right > previous.right;
      bool exceedsPreviousHeight = next.height > previous.height;

      if(exceedsPreviousRange && exceedsPreviousHeight)
      {
        skyline.push_back(next.left);
        stkyline.push_back(next.height);

        // TODO: it's probably necessary to do something here.
      }
      else if(exceedsPreviousRange && !exceedsPreviousHeight)
      {
        // Indicates x Coordinate
        skyline.push_back(previous.right);

        // Indicates y coordinate.
        bool existsTraversalBuilding = xBuilding.right > previous.right;
        if(!existsTraversalBuilding)
          skyline.push_back(next.height); // TODO: analize the previous line.
        else
          skyline.push_back(xBuilding.height);
      }
      else if(!exceedsPreviousRange && exceedsPreviousHeight)
      {
        skyline.push_back(next.left);
        skyline.push_back(next.height);

        // TODO: it's probably necessary to do something here.
      }

      // TODO: There is a thing that it's necessary to be analized. :3
      bool isHigherThanYBuilding = yBuilding.height < next.height;
      bool exceedsXBuildingRange = xBuilding.right < next.right;

      if(isHigherThanYBuilding)
        yBuilding = next;
      if(exceedsXBuildingRange)
        xBuilding = next;
    }

    // Draw end building coordinates of the last one before an empty space.
    skyline.push_back(previous.right);
    skyline.push_back(0);

    i = j;
  }

  return 0;
}
