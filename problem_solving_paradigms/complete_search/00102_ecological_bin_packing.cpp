#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int const B = 1, G = 2, C = 3;

char computeLetter(int code)
{
  switch(code)
  {
    case B:
      return 'B';
    case G:
      return 'G';
    case C:
      return 'C';
    finally:
      return '\0';
  }
}

bool isInCurrentBin(int index, int bin)
{
  int start = bin * 3;
  int end = start + 2;

  return ((index < start || index > end) ? false : true);
}

int main() {
  // INPUT:
  //   - Bin 1: Brown, Green, Clear.
  //   - Bin 2: Brown, Green, Clear.
  //   - Bin 3: Brown, Green, Clear.
  //
  // PROCESS:
  //    Compute all possible combinations of bin bottle boxes dispositions that put
  //    all box bottles of a specific color in a bin and choose the one whose movements of bottles is minimum
  //
  //  OUTPUT:
  //    - A string with letters 'B', 'G', 'C' that indidicates in which bin are
  //      placed the box bottles of an specific color.

  int combinations[18] = {
    1, 2, 3,
    1, 3, 2,
    3, 1, 2,
    3, 2, 1,
    2, 3, 1,
    2, 1, 3
  };

  // Request bins1
  int n;
  vector<int> bins1;
  while(scanf("%d", &n) == 1)
    bins1.push_back(n);

  // j: indicates the current color position in a bin (1: brown, 2: green, 3: clear)
  // k: indicates the bin where will the box that contains bottles of an specific color be put.
  // l: current bin in the series of 3 bins.
  string best = "ZZZ", worst = "";
  int smallest = numeric_limits<int>::max(), current = 0, c = 0;
  int box, bin, index, value;
  for(int i = 0, j = combinations[0], k = 1, l = 0, o = 0; i < bins1.size() * 6; i++)
  {
    box = (c > i ? c - i : i - c); // Current box in the combinations.
    bin = l - o; // Current bin in the real serie of boxes
    index = ((3 * k - 3) + (j - 1));  // Index where is the box of bottles in process: bin index (in a linear position) + box color index.
    value = bins1[index]; // The quantity of bottles in the box of bottles of the current color in proceess.,

    // Sum the quantity of movments that are needed to be done in the current combination of 3 bins.
    if(!isInCurrentBin(index, bin))
      current += value;

    cout << "j: " << j << ", k: " << k << ", i: " << i << ", c:" << c << ", box: " <<  box << ", index: " << index << ", l: " << l << ", bin: " << bin << endl;

    if(k < 3)
      k++;
    else
    {
      worst += computeLetter(j);
      k = 1;
      j = combinations[++l];
    }

    // If is ended the process of a serie of 3 bins, 
    if(box == 8)
    {
      cout << "quantity: " << current << endl;
      cout << "worst: " << worst << endl;
      // Update the value of the smallest quantity with the new one.
      if(current < smallest)
        smallest = current;

      // Update the value of the best disposition.
      if(best > worst)
        best = worst;

      // Restart current quantity of movements value. Also, sum 9 to adjust the `i` value.
      current = 0, c += 9, o += 3;
      worst = "";
    }

  }

  cout << "Selected minimum: " << smallest << endl;
  cout << "Selected disposition: " << best << endl;

  // ORIGINAL:            [1, 2, 3] , [4, 5, 6] , [7, 8, 9]
  //
  // COMBINATION 1 (BGC): [1, 4, 7] , [2, 5, 8] , [3, 6, 9]
  // COMBINATION 6 (BCG): [1, 4, 7] , [3, 6, 9] , [2, 5, 8]
  // COMBINATION 5 (CBG): [3, 6, 9] , [1, 4, 7] , [2, 5, 8]
  // COMBINATION 4 (CGB): [3, 6, 9] , [2, 5, 8] , [1, 4, 7]
  // COMBINATION 3 (GCB): [2, 5, 8] , [3, 6, 9] , [1, 4, 7]
  // COMBINATION 2 (GBC): [2, 5, 8] , [1, 4, 7] , [3, 6, 9]

  return 0;
}
