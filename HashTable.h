#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include "AVL_Tree.h"



template <class T,class HashFunction>
class HashTable{
private:
	//the current size of the table
	unsigned int size;
	//hash function spread the keys in a uniform distribution.
	HashFunction hashFunction;
	//the table of the hashTable (this array is dynamic and will be multiplied and divided accordi to the load factor.
	AVL_Tree<T, T>* treeArr;
	//current nuber of keys in the table
	unsigned int numberOfKeys;
	//helper function to allocates new array and copy all elements from the original one.
	void changeSize(unsigned int newSize);
	HashTable(const HashTable& other){}
	void operator=(const HashTable& other){}

public:
	//n is the basic size of the table, h is a class function to convert any key to the borders of the table.
	HashTable(unsigned int n, HashFunction h) :size(n), hashFunction(h), treeArr(new AVL_Tree<T, T>[n]), numberOfKeys(0){}
	
	/*allocate and insert a copy of the key to the table. using the insertion function of the tree
		in case that the key already exist exception will be thrown-keyAlreadyIn();*/
	void insert(const T& key);
	
	/*removes the object with the key using the remove function of the tree 
	if the key was not found the exception- KeyNotFound()*/
	void remove(const T& key);

/*return true if the is in the table and false otherwise - no throw.*/
	bool member(const T& key);
	unsigned int getSize() const{
		return size;
	}

	//returns the current number of keys in the table
	unsigned int getNumberOfKey() const{
		return numberOfKeys;
	}
	~HashTable(){
		delete[] treeArr;
	}

};

template <class T, class HashFunction>
void HashTable <T, HashFunction>::insert(const T& key){
	unsigned int i = hashFunction(key, size) % size;
	treeArr[i].insert(key, key);
	++numberOfKeys;
	if (numberOfKeys == size){
		changeSize(size*2 + 1);

	}
}

template <class T, class HashFunction>
void HashTable <T, HashFunction>::remove(const T& key){
	unsigned int i = hashFunction(key,size) % size;
	treeArr[i].remove(key);
	--numberOfKeys;
	if (numberOfKeys <= size / 4){
		changeSize(size/2);
	}
}



template <class T, class HashFunction>
bool HashTable <T, HashFunction>::member(const T& key){
	unsigned int i = hashFunction(key, size) % size;
	if (treeArr[i].isIn(key) == true){
		return true;
	}
	return false;
}

template <class T, class HashFunction>
void HashTable <T, HashFunction>::changeSize(unsigned int newSize){
	unsigned int tmpSize = size;
	size = newSize;
	AVL_Tree<T,T> *newarr = new AVL_Tree<T,T>[newSize];
	AVL_Tree<T, T> *tmparr = treeArr;
	treeArr = newarr;
	numberOfKeys = 0;
	for (unsigned int i = 0; i < tmpSize; ++i){
		unsigned int treeSize = tmparr[i].getSize();
		if (treeSize == 0){
			continue;
		}
		treeToArray<T,T> TTA(treeSize);
		tmparr[i].inorderTreeWalk(tmparr[i].getRootKey(),TTA);
		T* arr = TTA.getMaxArray();
		for (unsigned int j = 0; j < treeSize; ++j){
			insert(arr[j]);
		}
		delete[] arr;
	}

	delete [] tmparr;
}
#endif