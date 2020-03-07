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

int combinations[18] = {
  1, 2, 3,
  1, 3, 2,
  3, 1, 2,
  3, 2, 1,
  2, 3, 1,
  2, 1, 3
};

void compute(vector<int> bins)
{
  // j: indicates the current color position in a bin (1: brown, 2: green, 3: clear)
  // k: indicates the bin where will the box that contains bottles of an specific color be put.
  // l: current bin in the series of 3 bins.
  string best = "ZZZ", worst = "";
  int smallest = numeric_limits<int>::max(), current = 0, c = 0;
  int box, bin, index, value;
  for(int i = 0, j = combinations[0], k = 1, l = 0, o = 0; i < bins.size() * 6; i++)
  {
    box = (c > i ? c - i : i - c); // Current box in the combinations.
    bin = l - o; // Current bin in the real serie of boxes
    index = ((3 * k - 3) + (j - 1));  // Index where is the box of bottles in process: bin index (in a linear position) + box color index.
    value = bins[index]; // The quantity of bottles in the box of bottles of the current color in proceess.,

    // Sum the quantity of movments that are needed to be done in the current combination of 3 bins.
    if(!isInCurrentBin(index, bin))
      current += value;

    if(k < 3)
      k++;
    else
    {
      worst += computeLetter(j);
      k = 1, j = combinations[++l];
    }

    // If is ended the process of a serie of 3 bins, 
    if(box == 8)
    {
      // Update the value of the best disposition.
      if(best > worst || current < smallest)
        best = worst;

      // Update the value of the smallest quantity with the new one.
      if(current < smallest)
        smallest = current;

      // Restart current quantity of movements value. Also, sum 9 to adjust the `i` value.
      current = 0, c += 9, o += 3, worst = "";
    }
  }

  cout << best << " " << smallest << endl;
}

int main() {

  // Request bins.
  vector<int> bins;
  int n, i = 0;
  while(scanf("%d", &n) == 1)
    bins.push_back(n);

  // Compute oputput.
  vector<int> current;
  for(int i = 0; i < bins.size(); i++)
  {
    current.push_back(bins[i]);
    if(current.size() == 9)
    {
      compute(current);
      current.clear();
    }
  }

  return 0;
}
