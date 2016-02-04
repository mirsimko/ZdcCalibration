#!/bin/bash

tofCut=${1:-32767}

root -l -b -q loadZDCtree.C 'run.C++('$tofCut')'
