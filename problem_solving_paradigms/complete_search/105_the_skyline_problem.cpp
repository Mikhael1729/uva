#include<algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <limits>

using namespace std;

enum Event
{
  STARTS = 1,
  ENDS = 2
};

struct Building
{
  int left;
  int height;
  int right;

  Building(int left = -1, int height = -1, int right = -1) : left(left), height(height), right(right)
  { }

  friend ostream& operator << (ostream& stream, const Building& building)
  {
     return stream << "Building(" << building.left << ", " << building.height << ", " << building.right << ")";
  }
};

string toEventToString(Event event)
{
  switch(event)
  {
    case STARTS:
      return "STARTS";
    default:
      return "ENDS";
  }
}

struct BuildingEvent
{
  int coordinate;
  Event event;
  int id;
  Building building;

  BuildingEvent(
    int id = 0,
    int coordinate = -1,
    Event event = STARTS,
    Building building = Building()
  )
    : id(id), coordinate(coordinate), event(event), building(building)
  { }

  bool operator < (BuildingEvent &other) const
  {
    if(coordinate != other.coordinate)
      return coordinate < other.coordinate;

    return event < other.event;
  }

  friend ostream& operator << (ostream& stream, const BuildingEvent& buildingEvent)
  {
    return stream << "BuildingEvent("
      << buildingEvent.id
      << ", " << buildingEvent.coordinate
      << ", " << toEventToString(buildingEvent.event)
      << ", " << buildingEvent.building
      << ")";
  }
};

int main()
{
  // Request buildings.
  vector<BuildingEvent> plan;

  int last = 0;
  {
    int n, i = 1, id = 1;
    Building building;
    while(scanf("%d", &n))
    {
      if(i == 1)
        building.left = n;
      else if(i == 2)
        building.height = n;
      else
      {
        building.right = n;

        // Register the coordinates as events.
        plan.push_back(BuildingEvent(id, building.left, STARTS, building));
        plan.push_back(BuildingEvent(id++, building.right, ENDS, building));

        // Update the last right element.
        if(building.right > last)
          last = building.right;

        i = 0;
      }

      i++;
    }
  }

  sort(plan.begin(), plan.end());

  const int LAST_COORDINATE = last + 1;

  int skyline[LAST_COORDINATE] {};
  for(int i = 0; i <= LAST_COORDINATE; i++)
    skyline[i] = -1;

  // Compute the skyline.
  map<int, BuildingEvent> inProcess; // Coordinates such that its final coordinate is not placed in the skyline yet.
  for(BuildingEvent current : plan)
  {
    if(current.event == STARTS)
    {
      bool isHidden = false;
      for(map<int, BuildingEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
      {
        isHidden = it->second.building.height > current.building.height;
        if(isHidden)
          break;
      }

      if(!isHidden)
        skyline[current.coordinate] = current.building.height;

      inProcess.insert({ current.id, current });
    }
    else
    {
      // Remove the corresponding start event from in process list.
      inProcess.erase(current.id);

      int y = current.building.height;

      // Find the height to use in a non hidden end coordinate.
      BuildingEvent* higher = NULL;

      bool isHidden = false;
      for(map<int, BuildingEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
      {
        int y2 = it->second.building.height;

        isHidden =  y2 > y;
        if(isHidden)
          break;
        else
        {
          if(higher != NULL && y2 > higher->building.height)
            higher = &(it->second);
          else
            higher = &(it->second);
        }
      }

      // Register the coordinate in the skyline.
      if(!isHidden)
      {
        bool thereAreEventsProcessing = higher != NULL;
        if(thereAreEventsProcessing)
          skyline[current.coordinate] = higher->building.height;
        else
          skyline[current.coordinate] = 0;
      }
    }
  }


  // Print the skyline.
  for(int i = 0; i < LAST_COORDINATE; i++)
  {
    int height = skyline[i];
    if(height > -1)
      cout << i << " " << height << (i == LAST_COORDINATE -1 ? "" : " ");
  }

  return 0;
}
