#ifndef QUEUE_H_
#define QUEUE_H_

#include <exception>

class QueueIsFull : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Queue is full\n";
	}

};

class QueueIsEmpty : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Queue is empty\n";
	}

};

/*
Oone_Array object is array intialized in O(1) time complexity to a given "Zero Object"
object is template of class T. T should have operator=
inherits from Oone_Array
*/
template <class T>
class Queue {
private:
	T* arr;
	int first;
	int last;
	int count;
	int size;
	int indexToInsert() const;
	
	Queue(const Queue& other){}
	void operator=(const Queue& other){}
public:
	/*
	Queue intialztion requires size (k) and T object.
	*/
	Queue(unsigned k) : arr(new T[k]), first(0), last(0), count(0), size(k){}
	void enqueue(T data);
	T dequeue();

	/*
	function isFull will return if queue is full
	*/
	bool isFull() const{
		return (count == size);
	}
	/*
	function isEmpty will return if queue is empty
	*/
	bool isEmpty() const{
		return (count == 0);
	}
	~Queue(){
		delete[] arr;
	}

};


/*
function enqueue will insert an object to the queue
set the next write placeholder in the right position
increase count
*/
template <class T>
void Queue<T>::enqueue(T data){
	if (isFull()){
		throw QueueIsFull();
	}
	arr[last]=data;
	if (last + 1 < size){
		++last;
	}
	else{
		last = 0;
	}
	++count;
}

/*
function dequeue will return an object from the queue
set the next read placeholder in the right position
decrease count
*/
template <class T>
T Queue<T>::dequeue(){
	if (isEmpty()){
		throw QueueIsFull();
	}
	T data = arr[first];
	if (first + 1 < size){
		++first;
	}
	else{
		first = 0;
	}
	--count;
	return data;
}


#endif