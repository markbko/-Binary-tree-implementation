binaryTree.x: binaryTree.cpp
	g++ -std=c++11 -Wall -pedantic -o binaryTree_driver.cpp bet.h 
clean:
	rm -f *.o *.x
