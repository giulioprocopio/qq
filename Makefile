.PHONY: build test

build:
	rm -rf build/
	mkdir build/
	cd build/ && cmake .. && make

test:
	cd build/ && ./test/test_main