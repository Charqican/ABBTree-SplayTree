CC = g++
CFLAGS = -Wall
OBJFLAGS = -c
TEST_DIR = ./test
ARGS =

main.o: main.cpp NodeABB.o SplayTree.o
	@echo "Building main.o"
	$(CC) $(OBJFLAGS) main.cpp -o main.o


NodeABB.o: NodeABB.cpp
	@echo "Building NodeABB.o..."
	$(CC) $(OBJFLAGS) NodeABB.cpp -o NodeABB.o


SplayTree.o: SplayTree.cpp
	@echo "Building SplayTree.o..."
	$(CC) $(OBJFLAGS) SplayTree.cpp -o SplayTree.o


main: main.o NodeABB.o SplayTree.o
	@echo "Running Main..."
	$(CC) main.o NodeABB.o SplayTree.o -o main
	./main $(ARGS)


testSplay: test.o NodeABB.o SplayTree.o
	@echo "Running test..."
	$(CC) test.o NodeABB.o SplayTree.o -o test
	./test $(ARGS)

clean:
	del *.o main.exe