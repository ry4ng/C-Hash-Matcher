#!/bin/sh

echo ""
# cd src
echo "Building now..."
gcc src/main.c src/sha256.c -w
echo "Complete."
echo ""
