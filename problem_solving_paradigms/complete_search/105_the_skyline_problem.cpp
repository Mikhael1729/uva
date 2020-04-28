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

  static bool isHigher(BuildingEvent &first, BuildingEvent &second)
  {
    return first.building->height > second.building->height;
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
  int maximumNumber = 0;
  map<int, BuildingEvent> inProcess; // Coordinates not yet placed in the skyline. 
  map<int, int> skyline;

  for(BuildingEvent buildingEvent : plan)
  {
    cout << buildingEvent << endl;

    if(buildingEvent.event == STARTS)
    {
      // Find the height of the higher building in process.
      int higher = 0;
      for(map<int, BuildingEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
      {
        int current = it->second.building->height;
        if(current > higher)
          higher = current;
      }

      // Register the start coordinate of a building in the skyline.
      int x = buildingEvent.coordinate;
      int y = buildingEvent.building->height;

      //cout << buildingEvent << endl;
      //cout << "higher: " << higher << endl;
      //cout << "" << endl;

      bool isNotHidden = y > higher;
      if(isNotHidden)
      {
        skyline[x] = y;
        cout << "x: " << x << "y: " << y << endl;
      }

      // Register the buildingEvent in the collection of events.
      inProcess.insert(pair<int, BuildingEvent>(buildingEvent.id, buildingEvent));
      int const size = inProcess.size();
      maximumNumber = max(maximumNumber, size);
    }
    else
    {
      BuildingEvent temp = buildingEvent;

      // Delete the process from the map of in process BuildingEvent.
      inProcess.erase(buildingEvent.id);

      // Find the higher ended process.
      pair<int, BuildingEvent>* higherEndedProcess = NULL;
      for(map<int, BuildingEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
      {
        if(higherEndedProcess != NULL)
        {
          bool isHigher = it->second.building->height > higherEndedProcess->second.building->height;
          if(isHigher)
            higherEndedProcess = new pair<int, BuildingEvent>(it->first, it->second);
        }
        else
          higherEndedProcess = new pair<int, BuildingEvent>(it->first, it->second);
      }
  
      int y1 = skyline[temp.coordinate];
      int y2 = (higherEndedProcess != NULL ? higherEndedProcess->second.building->height : 0);
      int y3 = buildingEvent.building->height;
      
      bool isNotHidden = y3 >= y1 && y3 > y2;
      if(isNotHidden)
        skyline[temp.coordinate] = temp.building->height;
    }
  }

  // Print the maximum number of buildings at the same time.
  cout << "\nmaximumNumber: " << maximumNumber << "\n" << endl;

  // Print the skyline.
  cout << "\nSkyline:" << "\n" << endl;
  for(map<int, int>::iterator it = skyline.begin(); it != skyline.end(); ++it)
    cout << it->first << ", " << it->second << " ";

  return 0;
}
