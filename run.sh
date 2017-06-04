#!/bin/bash

runNumber=${1:-0}
tofCut=${2:-32767}

root -l -b -q loadZDCtree.C 'run.cxx++g('$tofCut','$runNumber')'
root -l -q 'html_maker.cpp('$runNumber')'
