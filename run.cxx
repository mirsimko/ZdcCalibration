#include <climits>
#include <iostream>
#include <TROOT.h>
#include "zdcTree.h"
using namespace std;


int run(int tofMultCut = INT_MAX)
{
  zdcTree t(0,tofMultCut);
  t.Loop();

  return 0;
}
