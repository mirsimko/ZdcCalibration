#include <limits>
#include <iostream>
#include <TROOT.h>
#include "zdcTree.h"
using namespace std;


int run(int tofMultCut = std::numeric_limits<int>::max(), int runNumber = 0)
{
  if (runNumber < 1e7 || runNumber >= 1e8)
  {
    cout << "invalid run number ... has to have 8 digits" << endl;
    return 1;
  }

  zdcTree t(runNumber, 0,tofMultCut);
  t.Loop();

  return 0;
}
