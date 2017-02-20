#!/bin/bash

tofCut=${1:-32767}

root -l -b -q loadZDCtree.C 'run.cxx++g('$tofCut')'
