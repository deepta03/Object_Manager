main: main.o ObjectManager.o
	clang -Wall -o main main.o ObjectManager.o
main.o: main.c
	clang -Wall -c main.c
ObjectManager.o: ObjectManager.c
	clang -Wall -c ObjectManager.c
