/*
Written by Myers, Omri & Dukhan, Dvir
Some algorithms implemntaions are taken from, or inspired by
1 .Technion's CS faculty's "Data Structurs 230402" course lecture notes made by Prof. Dan Guyger
2. "Introduction to Algorithms" by Cormen, Leiserson, Rivest & Stein
*/

#ifndef AVL_TREE_H_
#define AVL_TREE_H_
#include "AVL_Node.h"
#include "Oone_array.h"
#include "Queue.h"
#include <iostream>

/*
AVL_Tree is a data structurs which allow insert, find, remove actions in O(log(n)) time complexity
*/
template <class K, class T>
class AVL_Tree {
	private:
		AVL_Node<K, T>* root;
		int treeSize;
		void removeUpdateTree(AVL_Node<K, T>* currNode);
		void updateTree(AVL_Node<K, T>* currNode);
		void rotateRight(AVL_Node<K, T>* node);
		void rotateLeft(AVL_Node<K, T>* node);
		AVL_Node<K, T>* find(const K& key);
		AVL_Node<K, T>* findGE(const K& key);
		AVL_Node<K, T>* findSE(const K& key);
		AVL_Node<K, T>* successor(const K& key);
		AVL_Node<K, T>* treeMinimum(const K& key);
		AVL_Node<K, T>* treeMaximum(const K& key);
		template <class functionObject>
		void inorderTreeWalk(AVL_Node<K, T>* node, functionObject& doSomthing);
		template <class functionObject>
		void preorderTreeWalk(AVL_Node<K, T>* node, functionObject& doSomthing);
		template <class functionObject>
		void postorderTreeWalk(AVL_Node<K, T>* node, functionObject& doSomthing);
		template <class functionObject>
		void reverseOrderTreeWalk(AVL_Node<K, T>* node, functionObject& doSomthing);
		
		void operator=(const AVL_Tree<K, T>& other){}
		AVL_Tree(const AVL_Tree<K, T>& other): root(NULL), treeSize(0){}
	public:
		/*
		AVL_Tree intialization
		*/
		AVL_Tree() : root(NULL), treeSize(0){}


		/*
		function isEmpty will return if the tree is empty
		*/
		inline bool isEmpty() const{
				if (root == NULL){
					return true;
				}
				return false;
		
		
		}


		/*
		function getSize will return the tree size
		*/
		inline int getSize() const{
			return treeSize;
		}
	

		void insert(K key, T data);
		void remove(const K& key);

		/*
		function isIn will return if a key is already in the tree
		*/
		bool isIn(const K& key){
			if (find(key) != NULL){
				return true;
			}
			return false;
		}

		/*
		function getValue will return data for given key
		if key is not found an exception will be throw
		*/
		inline T getValue(const K& key){
			if (!isIn(key)){
				throw KeyNotFound();
			}
			return find(key)->getData();
		}

		/*
		function getGEValue will return data for given key which its key is the smallest greatest or equel to the given key
		if key is not found an exception will be throw
		*/
		inline T getGEValue(const K& key){
			AVL_Node<K, T>* node = findGE(key);
			if (!node){
				throw KeyOutOfBundries();
			}
			return node->getData();
		}
		/*
		function getSEValue will return data for given key which its key is the biggest smallest or equel to the given key
		if key is not found an exception will be throw
		*/
		inline T getSEValue(const K& key){
			AVL_Node<K, T>* node = findSE(key);
			if (!node){
				throw KeyOutOfBundries();
			}
			return node->getData();
		}

		

		
		/*
		function treeMinValue will return data for the smallet key in the given key sub-tree
		if key is not found an exception will be throw
		*/
		inline T treeMinValue(const K&key){
			if (!isIn(key)){
				throw KeyNotFound();
			}
			return treeMinimum(key)->getData();
		}
		/*
		function treeMinValue will return data for the smallet key in the tree
		if the tree is empty an exception will be throw
		*/
		inline T treeMinValue(){
			if (!root){
				throw Null_Argument();
			}
			return treeMinimum(root->getKey())->getData();
		}

		/*
		function treeMaxValuewill return data for the biggest key in the given key sub-tree
		if key is not found an exception will be throw
		*/
		inline T treeMaxValue(const K&key){
			if (!isIn(key)){
				throw KeyNotFound();
			}
			return treeMaximum(key)->getData();
		}

		/*
		function treeMaxValue will return data for the biggest key in the tree
		if the tree is empty an exception will be throw
		*/
		inline T treeMaxValue(){
			if (!root){
				throw Null_Argument();
			}
			return treeMaximum(root->getKey())->getData();
		}
		
		/*
		function treeMaxValue will return data for the root
		if the tree is empty an exception will be throw
		*/
		inline K getRootKey() const{
			if (root == NULL){
				throw KeyNotFound();
			}
			return root->getKey();
		}

		template <class functionObject>
		void inorderTreeWalk(K key, functionObject& doSomthing);
		template <class functionObject>
		void preorderTreeWalk(K key, functionObject& doSomthing);
		template <class functionObject>
		void postorderTreeWalk(K key, functionObject& doSomthing);

		template <class functionObject>
		void reverseOrderTreeWalk(K key, functionObject& doSomthing);

		/*
		function printAVL print the key and data for each node in assecinding order
		K and T objects should support operatr  <<
		*/
		void printAVL(){
			printNode<K,T> printer;
			inorderTreeWalk (root, printer);
		}
		/*
		functino treeClear will delete every node in the tree and the tree pointer will point to null
		*/
		void treeClear(){
			removeNode<K,T> remover;
			postorderTreeWalk(root, remover);
			root = NULL;
		}

		/*
		functino treeGetHight will return the hight of the tree
		*/
		inline int treeGetHight(){
			return root->getHight();
		}
		~AVL_Tree(){
			treeClear();
		}

};

/*
function find will return a node with the given key. a null wil return if the key is not found
*/
template <class K, class T>
AVL_Node<K, T>* AVL_Tree<K,T>::find(const K& key) {

	AVL_Node<K, T>* node = root;
	while (node != NULL){
		if (node->getKey() == key){
			return node;
		}

		if (node->getKey() < key){
			node = node->getRight();
		}
		else{
			node = node->getLeft();
		}
	}
	return node;
}


/*
function findGE will return a node with key which is equel or the smallest greatest from the given key. a null wil return if the key is not found
*/
template <class K, class T>
AVL_Node<K, T>* AVL_Tree<K, T>::findGE(const K& key) {

	AVL_Node<K, T>* node = root;
	AVL_Node<K, T>* tmpGE = NULL;
	while (node != NULL){
		if (node->getKey() >= key){
			tmpGE = node;
			node = node->getLeft();
		}
		else{
			node = node->getRight();
		}
	}
	return tmpGE;
}

/*
function findSE will return a node with key which is equel or the greatest smallest from the given key. a null wil return if the key is not found
*/
template <class K, class T>
AVL_Node<K, T>* AVL_Tree<K, T>::findSE(const K& key) {

	AVL_Node<K, T>* node = root;
	AVL_Node<K, T>* tmpSE = NULL;
	while (node != NULL){
		if (node->getKey() <= key){
			tmpSE = node;
			node = node->getRight();
		}
		else{
			node = node->getLeft();
		}
	}
	return tmpSE;
}







/*
function insert will insert key and data values to the tree
if key already in the tree, an exception will be thrown
*/
template <class K, class T>
void AVL_Tree<K,T>::insert(K key, T data){
	AVL_Node<K,T>* parent=NULL;
	AVL_Node<K,T>* currNode = root;
	while (currNode){
		parent=currNode;
		if (key == currNode->getKey()){
			throw keyAlreadyIn();
		}
		if (key > currNode->getKey()){
			currNode=currNode->getRight();
		}
		else{
			currNode=currNode->getLeft();
		}
	}
	AVL_Node<K,T>* newNode = new AVL_Node<K,T>(key, data);
	newNode->setParent(parent);
	if (parent == NULL){
		root=newNode;
	}
	else if(key > parent->getKey()){
		parent->setRight(newNode);
		}
	else{
		parent->setLeft(newNode);
	}

	updateTree(newNode);
	++treeSize;
}

/*
function removeUpdateTree will get node and will update its hight, check its BF and rotate tree according to BF
the function will run all over the tree's hight
*/
template <class K, class T>
void AVL_Tree<K,T>::removeUpdateTree(AVL_Node<K,T>* currNode){
	while (currNode != NULL){
		currNode-> updateHight();
		int BF = currNode->getBF();
		if (BF == 2){
		AVL_Node<K,T>* tmpLchild= currNode->getLeft();
			if (tmpLchild->getBF() == -1){ //case LR
				rotateLeft(tmpLchild);
				tmpLchild->updateHight();
				AVL_Node<K,T>* tmpNode=tmpLchild->getParent();
				tmpNode->updateHight();
			}
				rotateRight(currNode); // case only LL
				currNode->updateHight();
			}

			if (BF == -2){
				AVL_Node<K,T>* tmpRchild= currNode->getRight();
				if (tmpRchild->getBF() == 1){
					rotateRight(tmpRchild);
					tmpRchild->updateHight();
					AVL_Node<K,T>* tmpNode=tmpRchild->getParent();
					tmpNode->updateHight();
				}
				rotateLeft(currNode);//case only RR
				currNode->updateHight();
			}
			currNode = currNode->getParent();
	}
}

/*
function updateTree will get a node, check if its parent hight is >= to the node's hight+1
if the hight is not ok the it'll change to be the node's hight+1 and then removeTreeUpdate will be called
*/
template <class K, class T>
void AVL_Tree<K,T>::updateTree(AVL_Node<K,T>* currNode){
			currNode->updateHight();
			AVL_Node<K,T>* tmpParent = NULL;
			if (currNode != root){
				tmpParent = currNode->getParent();
				if (tmpParent->getHight() >= currNode->getHight()+1 ){
					return;
				}
				tmpParent->setHight(currNode->getHight()+1);
			}
			else{
				tmpParent = root;
			}
			removeUpdateTree(tmpParent);
			
}

/*
function rotateRight will change the given node to be it's left sons' right son
*/
template <class K, class T>
void  AVL_Tree<K,T>::rotateRight(AVL_Node<K, T>* rootToRotate){
		AVL_Node<K, T>*A = rootToRotate;
		AVL_Node<K, T>*B = rootToRotate->getLeft();
		AVL_Node<K, T>*parent = rootToRotate->getParent();
			if (parent != NULL){
				if(parent->getRight() == A){
					parent->setRight(B);
				}
				else{
					parent->setLeft(B);
				}
			}
			else{
				root=B;
			}
			B->setParent(parent);
			AVL_Node<K, T>* tmpNode=B->getRight();
			B->setRight(A);
			A->setParent(B);
			A->setLeft(tmpNode);
			if (tmpNode != NULL){
				tmpNode->setParent(A);
			}
}

/*
function rotateLet will change the given node to be it's right sons' left son
*/
template <class K, class T>
void  AVL_Tree<K,T>::rotateLeft(AVL_Node<K, T>* rootToRotate){
		AVL_Node<K, T>*A = rootToRotate;
		AVL_Node<K, T>*B = rootToRotate->getRight();
		AVL_Node<K, T>*parent = rootToRotate->getParent();
			if (parent != NULL){
				if(parent->getRight() == A){
					parent->setRight(B);
				}
				else{
					parent->setLeft(B);
				}
			}
			else{
					root=B;
				}
				B->setParent(parent);
				AVL_Node<K, T>* tmpNode=B->getLeft();
				B->setLeft(A);
				A->setParent(B);
				A->setRight(tmpNode);
				if (tmpNode != NULL){
						tmpNode->setParent(A);
					}
				
}

/*
functinon treeMinimum will return the node with the smallet key
*/
template <class K, class T>
 AVL_Node<K, T>* AVL_Tree<K, T>::treeMinimum(const K& key) {
	AVL_Node<K, T>* node = find(key);
	if (node!=NULL){
		while (node->getLeft() != NULL){
			node = node->getLeft();
		}
	}
	return node;
}

 /*
function treeMaximum will return the node with the biggest key
 */
template <class K, class T>
AVL_Node<K, T>* AVL_Tree<K, T>::treeMaximum(const K& key) {
	AVL_Node<K,T>* node = find(key);
	if (node != NULL){
		while (node->getRight() != NULL){
			node = node->getRight();
		}
	}

	return node;
}

/*
successor will return the node with the next bigger  key
implementaion of the course book's algorithm
*/
template <class K, class T>
AVL_Node<K,T>* AVL_Tree<K,T>::successor(const K& key){
	AVL_Node<K,T>* tmpNode = find(key);
	if (tmpNode == NULL){
		throw KeyNotFound(); 
	}
	if (tmpNode->getRight() != NULL){
		return treeMinimum(tmpNode->getRight()->getKey());
	}
	AVL_Node<K,T>* tmpParent = tmpNode->getParent();
	while (tmpParent != NULL && tmpNode==tmpParent->getRight()){
		tmpNode=tmpParent;
		tmpParent=tmpParent->getParent();
	}
	return tmpParent;
}

/*
remove will remove a node with a given key
implementaion of the course book's algorithm
in the end removeTreeUpdate will be called on the removed node son ot parent if a son does not exists,and treeSize will be decreased
*/
template <class K, class T>
void AVL_Tree<K,T>::remove(const K& key){
	if (!isIn(key)){
		throw KeyNotFound();
	}
	AVL_Node<K,T>* zNode = find(key);
	AVL_Node<K,T>* yNode = NULL;
	if (zNode->getRight() == NULL || (zNode->getLeft() == NULL)){
		yNode = zNode;
	}
	else{
		yNode = successor(key);		
	}
	AVL_Node<K,T>* xNode = NULL;
	if (yNode->getLeft() != NULL){
		xNode = yNode->getLeft();
	}
	else{
		xNode= yNode->getRight();
	}
	if (xNode != NULL) {
		xNode->setParent(yNode->getParent());
	}
	if (yNode->getParent() == NULL){
		root = xNode;
	}
	else{
		if (yNode== yNode->getParent()->getLeft()){
			yNode->getParent()->setLeft(xNode);
		}
		else{
			yNode->getParent()->setRight(xNode);
		}
	}
	if (zNode != yNode){
		zNode->setKey(yNode->getKey());
		zNode->setData(yNode->getData());
	}
	if (xNode){
	removeUpdateTree(xNode);
	}
	else{
		if (root != NULL){
			removeUpdateTree(yNode->getParent());
		}
	}
	removeNode<K,T> remover;
	remover(yNode);
	--treeSize;
}



template <class K ,class T>
template <class functionObject>
void AVL_Tree<K, T>::inorderTreeWalk(AVL_Node<K, T>* node, functionObject& doSomthing){
	if (node != NULL){
		inorderTreeWalk(node->getLeft(), doSomthing);
		doSomthing(node);
		inorderTreeWalk(node->getRight(), doSomthing);
	}
}


template <class K ,class T>
template <class functionObject>
void AVL_Tree<K, T>::reverseOrderTreeWalk(AVL_Node<K, T>* node, functionObject& doSomthing){
	if (node != NULL){
		reverseOrderTreeWalk(node->getRight(), doSomthing);
		doSomthing(node);
		reverseOrderTreeWalk(node->getLeft(), doSomthing);	
	}
}



template <class K ,class T>
template <class functionObject>
void AVL_Tree<K, T>::preorderTreeWalk(AVL_Node<K, T>* node, functionObject& doSomthing){
	if (node != NULL){
		doSomthing(node);
		preorderTreeWalk(node->getLeft(), doSomthing);
		preorderTreeWalk(node->getRight(), doSomthing);
	}
}



template <class K ,class T>
template <class functionObject>
void AVL_Tree<K, T>::postorderTreeWalk(AVL_Node<K, T>* node, functionObject& doSomthing){
	if (node != NULL){
		postorderTreeWalk(node->getLeft(), doSomthing);
		postorderTreeWalk(node->getRight(), doSomthing);
		doSomthing(node);
	}
}


template <class K, class T>
template <class functionObject>
void AVL_Tree<K, T>::inorderTreeWalk(K key, functionObject& doSomthing){
	if (!isIn(key)){
		throw KeyNotFound();
	}
	inorderTreeWalk(find(key), doSomthing);
}


template <class K, class T>
template <class functionObject>
void AVL_Tree<K, T>::preorderTreeWalk(K key, functionObject& doSomthing){
	if (!isIn(key)){
		throw KeyNotFound();
	}
	preorderTreeWalk(find(key), doSomthing);
}

template <class K, class T>
template <class functionObject>
void AVL_Tree<K, T>::postorderTreeWalk(K key, functionObject& doSomthing){
	if (!isIn(key)){
	throw KeyNotFound();
	}
	postorderTreeWalk(find(key), doSomthing);
}

		

template <class K, class T>
template <class functionObject>
void AVL_Tree<K, T>::reverseOrderTreeWalk(K key, functionObject& doSomthing){
	if (!isIn(key)){
	throw KeyNotFound();
	}
	reverseOrderTreeWalk(find(key), doSomthing);
}
/*
class treeChanger will allow change tree in linear time
use of this class should be in inorder tree walk

1. call inorder tree walk with treeChagner object
2. call treeChanger object's "treeChangerSort"
3. call inorder tree walk again with the same treeChanger object

T object should support operator <
functionObject object should support operator() with boolean return value
keyMaker object sould support operator() on T object which return K object


*/
template <class K, class T, class functionObject,class keyMaker>
class treeChanger{
private:
	Oone_Array<T> toChange;
	Oone_Array<T> notToChange;
	Queue<T>* Q;
	functionObject funcObj;
	keyMaker keyMake;
	void operator=(const treeChanger& other){}
	treeChanger(const treeChanger& other): Q(NULL){}
public:
	treeChanger(int size, T returnValue, functionObject& fo, keyMaker& km) :toChange(size, returnValue), notToChange(size, returnValue),Q(NULL), funcObj(fo), keyMake(km){}

	/*
	operatr() will get AVL_Node and if there isn't a queue intilized then the functionObject object will be activated on the node's data
	if a true return value will return the the data will be inserted to the toChnage array else to notToChange array
	if a queue is intilized then the data in the node will be changed to the first item in th queue,  keyMaker object will be activated on the node's data and the node's key will be changed
	*/
	void operator()(AVL_Node<K, T>* node){
		if (!Q){
			if (funcObj(node)){
				toChange.store(toChange.getTop(), node->getData());
			}
			else{
				notToChange.store(notToChange.getTop(), node->getData());
			}
		}
		else{
			node->setData(Q->dequeue());
			K key = keyMake(node->getData());
			node->setKey(key);
		}

	}

	/*
	Oone_Array's merge will be called on both arrays. then the returnd array will be inserted into queue and then be deleted
	*/
	 void treeChangerSort(){
		 Oone_Array<T>* C = Oone_Array<T>::merge(toChange, notToChange);
		  Q = new Queue<T>(C->getTop());
		  for (int i = 0; i < C->getTop(); ++i){
			 Q->enqueue(C->get(i));
		 }
		 delete C;
	}
	 ~treeChanger(){
		 delete Q;
	 }
};
template <class K, class T>
class treeToArray{
private:
	Queue<T> queue;
	unsigned int size;
public:
	treeToArray(unsigned int newSize) : queue(newSize), size(newSize){}
	T* getMinArray();
	T* getMaxArray();
	void operator()(AVL_Node<K, T>* node){
		queue.enqueue(node->getData());
	}
};

template <class K, class T>
T* treeToArray<K,T>::getMinArray() {
	T* arr = new T[size];
	for (int i = 0; i < size; ++i){
		arr[i] = queue.dequeue();
	}
	return arr;
}

template <class K, class T>
T* treeToArray<K, T>::getMaxArray() {
	T* arr = new T[size];
	for (int i = size-1; i >= 0; --i){
		arr[i] = queue.dequeue();
	}
	return arr;
}

#endif /* AVL_TREE_H_ */
