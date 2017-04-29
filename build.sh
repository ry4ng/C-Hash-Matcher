#!/bin/sh

echo ""
cd src
echo "Building now..."
gcc main.c sha256.c -w
echo "Complete."
echo ""
