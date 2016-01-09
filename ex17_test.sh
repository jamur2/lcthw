#!/bin/bash

set -e

echo "Creating database..."
./ex17 db.dat c
echo "Adding Zed..."
./ex17 db.dat s 1 zed zed@zedshaw.com
echo "Adding Frank..."
./ex17 db.dat s 2 frank frank@zedshaw.com
echo "Adding Joe..."
./ex17 db.dat s 3 joe joe@zedshaw.com

echo "Listing addresses..."
./ex17 db.dat l
echo "Deleting Joe"
./ex17 db.dat d 3
echo "Listing addresses..."
./ex17 db.dat l
echo "Retrieving Frank..."
./ex17 db.dat g 2
echo "Done"
