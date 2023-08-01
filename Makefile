.PHONY: build test

build:
	cmake -B build/ -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/ --config Debug

test:
	cd build/ && ctest

all: build test