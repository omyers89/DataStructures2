/*
Written by Mayers, Omri & Dukhan, Dvir
Some algorithms implemntaions are taken from, or inspired by
1 .Technion's CS faculty's "Data Structurs 230402" course lecture notes made by Prof. Dan Guyger
2. "Introduction to Algorithms" by Cormen, Leiserson, Rivest & Stein
*/


#ifndef _OONE_ARRAY_H_
#define _OONE_ARRAY_H_
#include <exception>
#include <stdio.h>
#include<iostream>

class outOfBoundries : public std::exception{
public:
	virtual const char* what() const throw(){
		return "ilegal index \n";
	}
};

/*
Oone_Array object is array intialized in O(1) time complexity to a given "Zero Object"
object is template of class T. T should have operator=

*/
template <class T=int>
class Oone_Array{
private:
	int top;
	T* A;
	int* B;
	int* C;
	T returnVal;
	unsigned maxSize;


	/*
	function isGarbage will get index (i) and checks if a T object was inserted to Oone_Array object.
	*/
	int isGarbage(int i){
		return !((B[i] < top && B[i] >= 0) && C[B[i]] == i);
	}

public:
	/*
	Oone_Array intialztion requires size (k) and T object (r) which act as the "Zero Object"
	*/
	Oone_Array(unsigned k, const T& r =0 ) : top(0), A(new T[k]), B(new int[k]), C(new int[k]), returnVal(r), maxSize(k){}
	

	/*
	get fucntion will get index(i) and will check if an item was insertd before in that index
	if yes it will return the value
	if not it will return the "Zero Object"
	*/
	T get(int i){
		if (isGarbage(i)){
			return returnVal;
		}
		return A[i];
	}

	/*
	store function will get index(i) and T object (element) and will insert the element to the array
	if i is bigger than array size an exception will be thrown
	*/
	void store(unsigned i,const T& element){
		if (i>=maxSize){
			throw outOfBoundries();
		}
		if (isGarbage(i)){ 
			C[top] = i;
			B[i] = top;
			++top;
		}
		A[i] = element; 
	}


	~Oone_Array(){
		delete[] C;
		delete[] B;
		delete[] A;
	}
	
	/*
	function getTop will return the first index of the array which is not intialized
	*/
	int getTop() const{
		return top;
	}

	/*
	fuction whatReturnVal will return the "Zero Object"
	*/
	T whatReturnVal() const{
		return returnVal;
	}
	static Oone_Array<T>* merge(Oone_Array<T>& A, Oone_Array<T>& B);
};



/*
simple merge algorithm for 2 Oone_Array objects
*/
template <class T>
Oone_Array<T>* Oone_Array<T>::merge(Oone_Array& A, Oone_Array& B){
	int size = A.getTop() + B.getTop();
	Oone_Array<T>* C = new Oone_Array<T>(size, A.whatReturnVal());
	int i = 0, j = 0, k = 0;
	T Aret = A.whatReturnVal(), Bret = B.whatReturnVal();
	while (A.get(i)!=Aret && B.get(j)!=Bret){
		if (A.get(i) <= B.get(j)){
			C->store(k, A.get(i));
			++k;
			++i;
		}
		else{
			C->store(k, B.get(j));
			++k;
			++j;
		}
	}
	if (i != A.getTop()){
		while (i < A.getTop()){
			C->store(k, A.get(i));
			++k;
			++i;
		}
	}
	else{
		while (j < B.getTop()){
			C->store(k, B.get(j));
			++k;
			++j;
		}
	}
	return C;
}

#endif