#include <limits>
#include <iostream>
#include <TROOT.h>
#include "zdcTree.h"
using namespace std;


int run(int tofMultCut = std::numeric_limits<int>::max())
{
  zdcTree t(0,tofMultCut);
  t.Loop();

  return 0;
}
