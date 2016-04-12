#ifndef _ELECTIONSYSTEM_H_
#define _ELECTIONSYSTEM_H_
#include "AVL_Tree.h"
#include "HashTable.h"
#include "UnionFind.h"
#include <math.h>
//#include "ProjectUtilities.h"



	class illegalCandidate : public exception{
public:
	virtual const char* what() const throw(){
		return " illegal Candidate id\n";
	}
};

class voterAlreadyVoted : public exception{
public:
	virtual const char* what() const throw(){
		return "voter Already Voted\n";
	}
};

class FromSameCamp : public exception{
public:
	virtual const char* what() const throw(){
		return "Both candidates are from the same camp\n";
	}
};

class notTheStrongestInCamp : public exception{
public:
	virtual const char* what() const throw(){
		return "One of the candidates is not the strongest\n";
	}
};

/*******************************candidate class ****************************************/

// class that keeps all the information we have on the candidate
class Candidate{
private:
	int id;
	int numOfVotes;
public:	
	//initialize a candidate with a given id
	Candidate(int i=-1) :id(i), numOfVotes(0){}
	Candidate(const Candidate& c):id(c.id), numOfVotes(c.numOfVotes){}
	void changeVotes(int newVotes){
		numOfVotes = newVotes;
	}
	void increasVotes(){
		++numOfVotes;
	}
	int getVotes(){
		return numOfVotes;
	}
	bool operator<(const Candidate& other) const;
		
	
	int getID(){
		return id;
	}
	bool operator>(const Candidate& other) const;
	bool operator==(const Candidate& other) const{
		return (id == other.id && numOfVotes == other.numOfVotes);
	}
	bool operator!=(const Candidate& other) const{
		return (id != other.id || numOfVotes != other.numOfVotes);
	}
	bool operator<=(const Candidate& other) const{
		return (operator<(other) || operator==(other));
	}
	bool operator>=(const Candidate& other) const{
		return (operator>(other) || operator==(other));
	}
};

//a class of the key to hold in the tree of the candidates. allow us to comparison by id and num of votes
class CandidateKey{
private:
	int id;
	int numOfVotes;
public:
	CandidateKey(Candidate c) : id(c.getID()), numOfVotes(c.getVotes()) {}
	bool operator < (const CandidateKey& other) const;
	bool operator >(const CandidateKey& other) const;
	bool operator==(const CandidateKey& other) const{
		return (id == other.id && numOfVotes == other.numOfVotes);
	}
	bool operator!=(const CandidateKey& other) const{
		return (id != other.id || numOfVotes != other.numOfVotes);
	}
	bool operator<=(const CandidateKey& other) const{
		return (operator<(other) || operator==(other));
	}
	bool operator>=(const CandidateKey& other) const{
		return (operator>(other) || operator==(other));
	}
	friend std::ostream& operator<<(std::ostream& out, const CandidateKey& cand);
};

/*************************************************************************************/
class PhiHashFunction{
public:
	PhiHashFunction(){}
	unsigned int operator()(unsigned int key, unsigned int size){
		double phi = (sqrt(5) - 1) / 2;
		return (unsigned int)floor(size*fmod(phi*key, 1));
	}
};

class ElectionSystem{
private:

	//array that holds the ditails of the candidates
	Candidate* candidatesArray;

	//generated hash function for the hash table
	PhiHashFunction h;
	
	//AVL tree to hold the candidates sorted by otes and id.
	AVL_Tree <CandidateKey,Candidate> votesTree;
	
	//hash table to hold the voters id.
	HashTable<int, PhiHashFunction> hTable;
	
	//unionFind structur to hold the candidates ids and details about the camps
	UnionFind<int> UF;
	
	//current number of camps in the system
	int numberOfGroups;
	
	//the number of candidates we initialized the system with
	int numberOfCandidates;
	
	//support updates the number of votes to a specific candidate, and update the array and the tree
	void support(int cadidate);
	
	//returns the maximium number of votes for a candidate in the group.
	int getMaxVotes(unsigned int groupId);
	
	//compare 2 groups and returns the id of the candidate that will be the leader of the group
	int getNewLeader(unsigned int group1,unsigned int group2);
	
	void operator=(const ElectionSystem& other){}

public:
	//Construcor- initialize the arrays of the additional information we keep on the candidates in the system.
	ElectionSystem(int n) :candidatesArray(new Candidate[n]), hTable(n, h), UF(n), numberOfGroups(n), numberOfCandidates(n){
		int* arr = new int[n];
		for (int i = 0; i < n; ++i){
			{
				arr[i] = i;
				Candidate c(i);
				candidatesArray[i] = c;
			}
		}
		UF.intializeDetails(arr);
		delete [] arr;
	}

	/*add a ote to the candidate and update all the sources.
	**throw illegalCandidate();
	**throw voterAlreadyVoted();
	*/
	void Vote(int voterId, int candidate);
	
	/*union 2 camps in the system after checking validity
	**throw outOfBoundaries(); if the candidate is illegal
	**throw FromSameCamp();
	**throw notTheStrongestInCamp();
	*/
	void signAgreement(int candidate1, int candidate2);
	
	/*returns the Leader of the camp the candidate is found in using the find function of UnionFind
	**throw outOfBoundaries(); if the candidate is illegal
	*/
	int campLeader(int candidate);
	
	//prints the ranking of all candidates
	void CurrentRanking(int results [][2]);
	
	//returns the number of candidates in the system.
	inline int getNumOfCandidates() const{
		return numberOfCandidates;
	}
	~ElectionSystem(){
		delete[] candidatesArray;
	}
	
};



#endif