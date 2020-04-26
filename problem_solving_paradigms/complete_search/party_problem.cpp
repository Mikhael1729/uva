#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum Event { 
  ENTRY = 1,
  DEPARTURE = 2
};

typedef struct Guest {
  int hour;
  Event event;

  Guest(int hour, Event event) : hour(hour), event(event)
  {  }

  bool operator < (struct Guest& other)
  {
    if(hour != other.hour)
      return hour < other.hour;

    return event > other.event;
  }
} Guest;


int n;

int main() {
  // Request the data.
  cin >> n;

  vector<Guest> guests;
  int entryHour, departureTime;

  for(int i = 0; i < n; ++i)
  {
    cin >> entryHour >> departureTime;
    guests.push_back(Guest(entryHour, ENTRY));
    guests.push_back(Guest(departureTime, DEPARTURE));
  }

  // Sort it.
  sort(guests.begin(), guests.end());

  // Compute the maximum of guests in any hour in the party. :D
  int count = 0;
  int maximumNumber = 0;
  for(int i = 0; i < n; i++)
  {
    Guest current = guests[i];
    if(current.event == ENTRY)
    {
      count++;
      maximumNumber = max(maximumNumber, count);
    }
    else
      count--;
  }

  // Show the result.
  cout << maximumNumber << endl;
}



