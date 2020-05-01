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

struct PointEvent
{
  int id;
  int x;
  int y;
  Event event;

  PointEvent(
    int id = -1,
    int x = -1,
    int y = -1,
    Event event = STARTS
  )
    : id(id), x(x), y(y), event(event)
  { }

  bool operator < (PointEvent &other) const
  {
    if(x != other.x)
      return x < other.x;

    return event < other.event;
  }

  friend ostream& operator << (ostream& stream, const PointEvent& buildingEvent)
  {
    return stream << "PointEvent("
      << buildingEvent.id
      << ", " << buildingEvent.x
      << ", " << buildingEvent.y
      << ", " << toEventToString(buildingEvent.event)
      << ")";
  }
};

int main()
{
  // Request buildings.
  vector<PointEvent> plan;

  int id = 1;

  Building b;
  while(scanf("%d %d %d" , &b.left, &b.height, &b.right) == 3)
  {
    plan.push_back(PointEvent(id, b.left, b.height, STARTS));
    plan.push_back(PointEvent(id++, b.right, b.height, ENDS));
  }

  sort(plan.begin(), plan.end());

  // Compute the skyline.
  map<int, int> skyline;
  map<int, PointEvent> inProcess; // Coordinates such that its final coordinate is not placed in the skyline yet.
  for(PointEvent current : plan)
  {
    if(current.event == STARTS)
    {
      bool isHidden = false;
      for(map<int, PointEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
      {
        isHidden = it->second.y > current.y;
        if(isHidden)
          break;
      }

      if(!isHidden)
        skyline[current.x] = current.y;

      inProcess.insert({ current.id, current });
    }
    else
    {
      // Remove the corresponding start event from inProcess collection.
      inProcess.erase(current.id);

      int y = current.y;

      // Find the height to use in a non hidden end coordinate.
      PointEvent* higher = NULL;
      bool isHidden = false;
      for(map<int, PointEvent>::iterator it = inProcess.begin(); it != inProcess.end(); ++it)
      {
        int y2 = it->second.y;

        isHidden =  y2 > y;
        if(isHidden)
          break;
        else
        {
          if(higher != NULL && y2 > higher->y)
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
          skyline[current.x] = higher->y;
        else
          skyline[current.x] = 0;
      }
    }
  }


  // Print the skyline.
  for(map<int, int>::iterator it = skyline.begin(); it != skyline.end(); ++it)
    cout << it->first << " " << it->second << " ";

  return 0;
}
