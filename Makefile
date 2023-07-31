.PHONY: build

build:
	rm -rf build/
	mkdir build/
	cd build/ && cmake .. && make