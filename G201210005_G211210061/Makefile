all:derle bagla calistir
derle:
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I "./include" ./src/BST.cpp -o ./lib/BST.o
	g++ -c -I "./include" ./src/BSTlinkedlist.cpp -o ./lib/BSTlinkedlist.o	
	g++ -c -I "./include" ./src/linkedlist.cpp -o ./lib/linkedlist.o
	g++ -c -I "./include" ./src/stacklinkedlist.cpp -o ./lib/stacklinkedlist.o
bagla:
	g++ ./lib/BST.o ./lib/BSTlinkedlist.o ./lib/linkedlist.o ./lib/stacklinkedlist.o ./lib/main.o -o ./bin/program
calistir:
	./bin/program