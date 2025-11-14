
#Autoria de Augusto Antonio Kolb Schiavini (GRR 20232337) e João Eduardo Zangari Ambrosio(GRR 20232344)|
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
