#! /bin/bash

echo "---Initializing submodules---"
git submodule init
git submodule update

echo "---Compiling libosw---"
cd libosw/
make

echo "---Cloning include folder---"
cd ../
cp -r libosw/include/libosw include/libosw
mv libosw/lib/libosw.a lib/libosw.a
