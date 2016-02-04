#include <iostream>
#include <TROOT.h>
using namespace std;

int run()
{
	gROOT->ProcessLine(".L zdcTree.C");
	gROOT->ProcessLine("zdcTree t");
	gROOT->ProcessLine("t.Loop\(\)");
	gROOT->ProcessLine(".q");

	return 0;
}
