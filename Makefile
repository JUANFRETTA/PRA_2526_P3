bin/testTableEntry:  testTableEntry.cpp TableEntry1.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp


bin/testHashTable: testHashTable.cpp HashTable.h TableEntry1.h Dict.h
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp

bin/testBSTree: testBSTree.cpp BSTree.h BSNode.h
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp

clean:
	rm -rf *.o *.gch bin



