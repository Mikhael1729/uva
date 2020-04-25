#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <map>

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

  // Compute the skyline of the buildings.
  map<int, int> preskyline;

  // Code the first building into preskyline.
  Building first = buildings[0];
  for(int i = first.left; i <= first.right; i++)
    preskyline.insert(pair<int, int>(i, first.height));

  // Code the rest of the buildings in the preskyline.
  int desviation = 0;
  for(int i = 1; i < buildings.size(); i++)
  {
    Building current = buildings[i];
    Building previous = buildings[i - 1];
    map<int, int>::const_reverse_iterator last = preskyline.crbegin(); // Last encoded building.

    int x = current.left + desviation;
    int y = current.height;

    // Encode separation between previous building and the current one.
    bool areSeparated = current.left > previous.right;
    if(areSeparated)
    {
      // Update values.
      preskyline[x] *= -1; // Encode the separation of buildings (if exists a traversal buildings recognize it as an space with a negative value).
      desviation++;
      x++;
    }

    // Encode the new building (a building will be hidden depending on its parameters).
    for(; x <= current.right + desviation; x++)
    {
      bool isNotHidden = (x >= last->first || y >= last->second);
      if(isNotHidden)
        preskyline[x] = y;
    }
  }

  // Print skyline
  int previousHeight = -1;
  desviation = 0;
  for(map<int, int>::iterator it = preskyline.begin(); it != preskyline.end(); ++it)
  {
    // Get coordinates.
    int x = it->first - desviation, y = it->second;

    bool isNextRepresentation = y != previousHeight;
    if(isNextRepresentation)
    {
      previousHeight = y;

      // Print buildings separation (separation with a traversal building or blank space between).
      bool areSeparated= y <= 0; 
      if(areSeparated)
      {
        // Get previous coordinates.
        map<int, int>::iterator previous = it;
        advance(previous, -1);

        // Adjust the current coordinates and print them (repressents the separation).
        x = previous->first - desviation;
        y *= -1;

        cout << x << " " << y << " ";

        // Because of the new separation, increase the x coordinate desviation.
        desviation++;
      }

      // Print current coordinate.
      else
        cout << x << " " << y << " ";
    }
  }

  map<int, int>::const_reverse_iterator last = preskyline.crbegin(); // Last encoded building.
  cout << last->first - desviation << " " << 0;

  return 0;
}
