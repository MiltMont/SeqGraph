#! /bin/bash

echo "---Initializing submodules---"
git submodule init
git submodule update

echo "---Compiling libosw---"
cd libosw/
make

cd ../
mv libosw/lib/libosw.a lib/libosw.a
