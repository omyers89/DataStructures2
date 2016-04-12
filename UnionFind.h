#ifndef UNIONFIND_H_
#define UNIONFIND_H_
#include <stdlib.h>
#include <exception>
using std::exception;



/********exception class****************/
//object of this class will be thrown when trying to access information of group that is not exists.

class GroupNotExists : public exception{
public:
	virtual const char* what() const throw(){
		return "Group not found\n";
	}
};

//object of this class will be thrown when trying to access an object with wrong id.
class outOfBoundaries : public exception{
public:
	virtual const char* what() const throw(){
		return "out Of Boundaries\n";
	}
};



template < class Details = int >

class UnionFind{
private:
	/******intern classes  ******/
	
	class UnionFindRecored;
	/*UnionFindNode- a node in the tree of the objects in the structur of the union-find class.*/
	class UnionFindNode{
	public:
		unsigned int  id;
		UnionFindNode* parent;
		UnionFindRecored* details;
	
		UnionFindNode(const unsigned int i) : id(i), parent(NULL),details(NULL){}
	};
	/*UnionFindRecored- a struct that holds a pointer to the head of the tree 
						and the size of the tree*/
	class UnionFindRecored{
	public:
		UnionFindNode* const head;
		//RecordDetails details;
		unsigned int size;
		UnionFindRecored(UnionFindNode* const node) : head(node), size(1){}
			
	};
	/*UnionFindGroupObject- object we keep in the array of the groups connects between the
							details and the record.*/
	class UnionFindGroupObject{
	private:
		UnionFindGroupObject(const UnionFindGroupObject& other){}
		void operator=(const UnionFindGroupObject other){}
	public:
		UnionFindRecored* record;
		Details* details;
		UnionFindGroupObject() : record(NULL), details(NULL){}

		~UnionFindGroupObject(){
			delete details;
			delete record;
		}
		
	};
	/**************************************/
	unsigned int size;
	UnionFindNode** nodesArr;
	UnionFindGroupObject* groupsArr;

	UnionFind(const UnionFind& newUniFind){}
	void operator=(const UnionFind& newUniFind){}
public:
	UnionFind(int newSize) : size(newSize),
		nodesArr(new UnionFindNode*[size]), groupsArr(new UnionFindGroupObject[size]){
		//intialization of values in  nodes array and groups array.
		for (unsigned int i = 0; i<size; ++i){
			UnionFindNode* newNode = (new UnionFindNode(i));
			nodesArr[i] = newNode;
			UnionFindRecored* record = new UnionFindRecored(newNode);
			groupsArr[i].record = record;
			newNode->details = record;
		}

	}
	// insert specific details for every group.
	void intializeDetails(Details* details){
		for (unsigned int i = 0; i < size; ++i){
			Details* d = new Details(details[i]);
			(groupsArr[i]).details = d;
		}
	}

	~UnionFind(){
		for(unsigned int i=0;i<size;++i){
			if (nodesArr){
				delete nodesArr[i];
			}
			
		}
		delete[] groupsArr;
		delete[] nodesArr;
	}


	unsigned int Union (unsigned int group1, unsigned int group2);
	
	//update the details about a specific group
	void updateRecord(const Details& newDetails, unsigned int groupId){
		if (!groupsArr[groupId].details){
			throw GroupNotExists();
		}
		delete groupsArr[groupId].details;
		Details* tmpDetails = new Details(newDetails);
		groupsArr[groupId].details = tmpDetails;
	}


	unsigned int getGroupSize(unsigned int groupId)const{
		if (!groupsArr[groupId].record){
			throw GroupNotExists();
		}
		UnionFindRecored* record = groupsArr[groupId].record;	
		return record->size;
	}

	unsigned int Find(unsigned int id)const;

	const Details& getGroupDetails(unsigned int groupId){
		
		return *(groupsArr[groupId].details);
	}

};


template < class Details >
unsigned int  UnionFind<Details>::Union (unsigned int group1, unsigned int group2){
		if (group1 == group2){
			return group1;
		}
		//check if groups are available.
		if (!groupsArr[group1].record || !groupsArr[group2].record){
			throw GroupNotExists();
		}
		UnionFindRecored* record1 = groupsArr[group1].record;
		UnionFindRecored* record2 = groupsArr[group2].record;
		UnionFindNode* head1 = record1->head;
		UnionFindNode* head2 = record2->head;
		unsigned int newSize=record2->size+record1->size;
		//add the small group to the large.
		if (record1->size<=record2->size){
			record2->size=newSize;
			head1->parent=head2;
			delete groupsArr[group1].record;
			groupsArr[group1].record = NULL;
			head1->details=NULL;
			return group2;
		}
		else {
			record1->size=newSize;
			head2->parent=head1;
			delete groupsArr[group2].record;
			groupsArr[group2].record = NULL;
			head2->details=NULL;
			return group1;
		}

	}

template < class Details >
unsigned int UnionFind<Details>::Find(unsigned int id)const{
		if (id>=size){
			throw outOfBoundaries();
		}
		UnionFindNode* tmpNode=nodesArr[id];
		while (tmpNode->parent !=NULL){
			tmpNode=tmpNode->parent;
		}
		UnionFindNode* tmpParent=tmpNode;
		tmpNode=nodesArr[id];
		//connect every node on the path to the head of the group.
		while (tmpNode->parent !=NULL){
			UnionFindNode* nextNode=tmpNode->parent;
			tmpNode->parent=tmpParent;
			tmpNode=nextNode;
		}
		return tmpNode->id;

	}

#endif