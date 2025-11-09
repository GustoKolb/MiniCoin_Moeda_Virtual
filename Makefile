MAKEFLAGS += --silent

default: 
	rm -rf build/
	mkdir build/
	cd build
	cmake -S . -B build
	make -C build -s
	echo "Build completa! Executável em build/"