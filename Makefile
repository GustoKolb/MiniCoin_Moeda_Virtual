CC = g++
CFLAGS = -Wall -Wextra -g --pedantic

EXECS = teste
MAIN = main.cpp
OBJECTS = Currency.o BlockChain.o

# regra principal
all: $(MAIN) $(OBJECTS)
	@echo "👷⚒️  Construindo Main:" $(EXECS)
	@$(CC) $(CFLAGS) -o $(EXECS) $(MAIN) $(OBJECTS)

# regra de compilação dos objetos
%.o: %.cpp
	@echo "👷⚒️  Construindo Objeto:" $*
	@$(CC) $(CFLAGS) -c $<

debug: CFLAGS += -DDEBUG
debug: all

clean:
	@echo "Limpando... 🧹🗑️ ✨"
	@rm -f $(OBJECTS)

purge: clean
	@rm -f $(EXECS)
