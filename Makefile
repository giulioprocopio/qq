.PHONY: submodules build test

submodules:
	git submodule update --init --recursive

build:
	cmake -B build/ -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/ --config Debug

test:
	cd build/ && ctest

all: submodules build test