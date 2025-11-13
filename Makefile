MAKEFLAGS += --silent

default: 
	mkdir -p build/
	cd build
	cmake -S . -B build
	make -C build -s
	echo "Build completa! Executável em build/"
c:
	./build/clientCoin
s:
	./build/miniCoin
purge:
	rm -rf build/
