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
  Building* building;

  BuildingEvent(
    int id = 0,
    int coordinate = -1,
    Event event = STARTS,
    Building* building = new Building()
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
      << ", " << *(buildingEvent.building)
      << ")";
  }
};

pair<int, BuildingEvent>* findHigher(map<int, BuildingEvent> inProcess)
{
  pair<int, BuildingEvent>* higher = NULL;

  for(map<int, BuildingEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
  {
    if(higher != NULL)
    {
      bool isHigher = it->second.building->height > higher->second.building->height;
      if(isHigher)
        higher = new pair<int, BuildingEvent>(it->first, it->second);
    }
    else
      higher = new pair<int, BuildingEvent>(it->first, it->second);
  }

  return higher;
}

int main()
{
  // Request buildings.
  vector<Building> buildings;
  vector<BuildingEvent> plan;

  {
    int n, i = 1;
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
        buildings.push_back(building);
        i = 0;
      }

      i++;
    }
  }

  int id = 1, last = 0;
  for(int i = 0 ; i < buildings.size(); i++)
  {
    Building* b = &buildings[i];
    plan.push_back(BuildingEvent(id, b->left, STARTS, b));
    plan.push_back(BuildingEvent(id++, b->right, ENDS, b));

    if(b->right > last)
      last = b->right;
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
        isHidden = it->second.building->height > current.building->height;
        if(isHidden)
          break;
      }

      if(!isHidden)
        skyline[current.coordinate] = current.building->height;

      inProcess.insert({ current.id, current });
    }
    else
    {
      // Remove the corresponding start event from in process list.
      inProcess.erase(current.id);

      int y = current.building->height;

      // Find the height to use in a non hidden end coordinate.
      BuildingEvent* higher = NULL;

      bool isHidden = false;
      for(map<int, BuildingEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
      {
        int y2 = it->second.building->height;

        isHidden =  y2 > y;
        if(isHidden)
          break;
        else
        {
          if(higher != NULL && y2 > higher->building->height)
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
          skyline[current.coordinate] = higher->building->height;
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
