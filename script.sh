#!/bin/bash

FILES=/home/ahrytsevich/Work/Test_projects/TestTasl4Karamba/*
for f in $FILES
do
  echo "Processing $f file..."
  HASH="$(./TestTasl4Karamba $f)"
  echo $HASH
done