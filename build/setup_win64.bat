@echo off


mkdir ga-win64

cd ga-win64

cmake -G "Visual Studio 15 2017 Win64" ../../src/engine

cd ..
