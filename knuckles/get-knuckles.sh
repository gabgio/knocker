#!/bin/sh

PACKAGE=knuckles
PREFIX=../../$PACKAGE

make distclean

rm -rf src/*.c
rm -rf src/*.h

cp -r  $PREFIX/src/*.c src/
cp -r  $PREFIX/src/*.h src/

