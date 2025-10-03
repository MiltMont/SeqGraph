#! /bin/bash

echo "---Compiling libosw---"
cd libosw/
make

cd ../
mv libosw/lib/libosw.a lib/libosw.a
