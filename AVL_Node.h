/*
Written by Myers, Omri & Dukhan, Dvir
Some algorithms implemntaions are taken from, or inspired by
1 .Technion's CS faculty's "Data Structurs 234218" course lecture notes made by Prof. Dan Guyger
2. "Introduction to Algorithms" by Cormen, Leiserson, Rivest & Stein
*/


#ifndef AVL_NODE_H_
#define AVL_NODE_H_
#include <stdlib.h>
#include<iostream>
#include <exception>
#include <stdio.h>


using std::cout;
using std::endl;



class Null_Argument : public std::exception{
public:
	virtual const char* what() const throw(){
		return "A Null Argument was sent\n";
	}

};

class keyAlreadyIn : public std::exception{
public:
	virtual const char* what() const throw(){
		return "A Node with that key already exists\n";
	}
};

class KeyNotFound : public std::exception{
public:
	virtual const char* what() const throw(){
		return "A Node with that key was not found\n";
	}
};

class KeyOutOfBundries : public std::exception{
public:
	virtual const char* what() const throw(){
		return "The given search value is out of boundries\n";
	}
};


/*
AVL_Node object will hold key of class K and value from class T
K &  T must have operator =
each node has pointer to its parent, left son and right son
*/
template <class K, class T>

class AVL_Node {
private:
	AVL_Node* parent;
	AVL_Node* left;
	AVL_Node* right;
	int hight;
	K key;
	T data;

	AVL_Node(const AVL_Node<K,T>& other){}
	void operator=(const AVL_Node<K, T> other){}
public:
	/*
	AVL_Node intialization by sending key object(k) and data object(d)
	*/
	AVL_Node(K k,T d) : parent(NULL), left(NULL), right(NULL), hight(0),
				 key(k), data(d){}

	/*
	set AVL_Node (p) as this object's parent
	*/
	inline void setParent(AVL_Node* p){
		parent = p;
	}

	/*
	return this object's parent
	*/
	inline AVL_Node* getParent() const{
		return parent;
	}

	/*
	set AVL_Node (l) as this object's left son
	*/
	inline void setLeft(AVL_Node* l){
		left = l;
	}

	/*
	return this object's left son
	*/
	inline AVL_Node* getLeft() const{
		return left;
	}

	/*
	set AVL_Node (r) as this object's righ son
	*/
	inline void setRight(AVL_Node* r){
		right = r;
	}

	/*
	return this object's right son
	*/
	inline AVL_Node* getRight() const{
		return right;
	}

	/*
	getBF returns this node balance factor according to the left and right sons hight
	if the is no son then its hight equels -1
	*/
	inline int getBF(){
		int lHight = (left==NULL) ? -1: left->hight;
		int rHight = (right==NULL) ? -1: right->hight;
		return  lHight- rHight;
	}

	/*
	getData return the data in the node
	*/
	inline T& getData(){
		return data;
	}

	/*
	setData sets/changes the data in the node
	*/
	inline void setData(const T& d){
		data=d;
	}

	/*
	getKey return the key of the node
	*/
	inline const K& getKey() const{
		return key;
	}

	/*
	setKey sets/changes the key in the node
	*/
	inline void setKey(const K& k){
		key=k;
	}

	/*
	getHight return the hight of the node
	*/
	inline int getHight() const{
		return hight;
	}
	/*
	setHight sets/changes the hight of the node
	*/
	inline void setHight(int h){
		hight = h;
	}
		
	void updateHight();
};

/*
updateHight will change the hight of this node to be the maximum hight of its sons +1

*/
template <class K, class T>
void AVL_Node<K, T>::updateHight(){
	if (left == NULL && right == NULL){
		hight = 0;
		return;
	}
	if (left == NULL){
		hight = right->getHight() + 1;
		return;
	}
	if (right == NULL){
		hight = left->getHight() + 1;
		return;
	}
	hight = left->getHight() > right->getHight() ? left->getHight() + 1 : right->getHight() + 1;
}

/*
a "function objcet" which prints node data
T & K must support operator<<
*/
template <class K, class T>
class printNode{
	public:
		printNode(){}
		void operator()(AVL_Node<K, T>* node){
			cout<<"Key = "<<node->getKey()<<" value = "<<node->getData()<<" hight = "<<node->getHight()<<" BF= "<<node->getBF() <<endl;
		}
};

/*
a "function objcet" which deletes node
*/
template <class K, class T>
class removeNode{
	public:
		removeNode(){}
		void operator()(AVL_Node<K, T>* node){
			delete node;
		}
};

template <class K, class T>
class getNodeValue{
public:
	getNodeValue(){}
	T operator()(AVL_Node<K, T>* node){
		return node->getData();
	}
};

#endif /* AVL_NODE_H_ */
