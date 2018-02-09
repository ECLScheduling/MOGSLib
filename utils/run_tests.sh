#!/bin/bash

declare BINDIR=$(dirname "$0")/../bin
cd $BINDIR

for dirname in $(ls */ -d); do
  cd $dirname
  echo "Begining tests on ${dirname} directory..."
  for filename in $(ls); do
    echo "Test: ${filename}"
    ./$filename
  done
  echo "Exiting ${dirname} directory"
  cd ..
done