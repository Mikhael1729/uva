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

  int id = 1;
  for(int i = 0 ; i < buildings.size(); i++)
  {
    Building* b = &buildings[i];
    plan.push_back(BuildingEvent(id, b->left, STARTS, b));
    plan.push_back(BuildingEvent(id++, b->right, ENDS, b));
  }

  // Sort them.
  sort(plan.begin(), plan.end());

  cout << "\nPlan:\n" << endl;

  // Compute the skyline.
  const int LAST_ID = id;
  map<int, BuildingEvent> inProcess; // Coordinates not yet placed in the skyline. 
  map<int, int> preskyline;
  map<int, int> skyline;
  bool unusable[LAST_ID] {  };

  for(BuildingEvent current : plan)
  {
    cout << current << endl;

    if(current.event == STARTS)
    {
      // Draw the coordinate.
      bool thereAreEventsProcessing = inProcess.size() > 0;
      skyline[current.coordinate] = current.building->height;

      // Register the current building event as an event in process.
      inProcess.insert({ current.id, current });
    }
    else
    {
      // Remove the corresponding start event from in process list.
      BuildingEvent startsEvent = inProcess[current.id];
      inProcess.erase(current.id);

      // Travel acroos the processing events to find new coordinates.
      for(map<int, BuildingEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
      {
        int height = it->second.building->height;

        bool isHigher = current.building->height > height;

        if(isHigher)
          skyline[current.coordinate] = height;
        else
          skyline[inProcess[it->second.id].coordinate] = height;
      }

      // In the case there are no in process elements
      bool thereAreEventsProcessing = inProcess.size() == 0;
      if(thereAreEventsProcessing)
        skyline[current.coordinate] = 0;
    
      // Manage overlaping.
      cout << "[startsEvent: " << startsEvent << "]" << endl;
      map<int, int>::iterator startIt = skyline.find(startsEvent.coordinate);
      map<int, int>::iterator endIt = skyline.find(current.coordinate);
      cout << "[startIt->first: " << startIt->first << "]" << endl;
      cout << "[startIt->second: " << startIt->second << "]" << endl;
      cout << "[endIt->first: " << endIt->first << "]" << endl;
      cout << "[endIt->second: " << endIt->second << "]" << endl;

      for(map<int, int>::iterator it = startIt; it != endIt; ++it)
      {
        cout << "[current: " << current << "]" << endl;
        cout << "[it->first: " << it->first << "]" << endl;
        cout << "[it->second: " << it->second << "]" << endl;
        cout << "" << endl;
        bool isHidden = current.building->height > it->second;
        if(isHidden)
          skyline.erase(it->first);
      }
    }
  }

  // Print the preskyline.
  cout << "\nPreskyline:" << "\n" << endl;
  for(map<int, int>::iterator it = preskyline.begin(); it != preskyline.end(); ++it)
    cout << it->first << ", " << it->second << " " << endl;
  

  // Print the skyline.
  cout << "\nSkyline:" << "\n" << endl;
  for(map<int, int>::iterator it = skyline.begin(); it != skyline.end(); ++it)
    cout << it->first << ", " << it->second << ", ";

  return 0;
}
