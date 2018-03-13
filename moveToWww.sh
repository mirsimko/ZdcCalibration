#!/bin/bash

wwwDir=~/WWW/run18.ZdcCalibration

mkdir -p "$wwwDir"
cp *.html "$wwwDir"
cp *.htm "$wwwDir"
cp -r analysis "$wwwDir"
cp -r asym "$wwwDir"
cp -r pdf "$wwwDir"
