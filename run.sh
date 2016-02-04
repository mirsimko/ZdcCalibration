#!/bin/bash

tofCut=${1:-32767}

root -l -b -q loadZDCtree.C 'run.cxx++('$tofCut')'

echo Creating .htm file

root -l -b -q html_maker.cpp
