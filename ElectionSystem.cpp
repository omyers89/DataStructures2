#include "ElectionSystem.h"

bool Candidate::operator < (const Candidate& other) const{
	if (numOfVotes<other.numOfVotes){
		return true;
	}
	if (numOfVotes == other.numOfVotes){
		return (id < other.id);
	}
	return false;
}

bool Candidate::operator >(const Candidate& other) const{
	if (numOfVotes>other.numOfVotes){
		return true;
	}
	if (numOfVotes == other.numOfVotes){
		return (id > other.id);
	}
	return false;
}


bool CandidateKey::operator < (const CandidateKey& other) const{
	if (numOfVotes<other.numOfVotes){
		return true;
	}
	if (numOfVotes == other.numOfVotes){
		return (id < other.id);
	}
	return false;
}

bool CandidateKey::operator >(const CandidateKey& other) const{
	if (numOfVotes>other.numOfVotes){
		return true;
	}
	if (numOfVotes == other.numOfVotes){
		return (id > other.id);
	}
	return false;
}
std::ostream& operator<<(std::ostream& out, const CandidateKey& candidate){
	out<< candidate.id << ","<<candidate.numOfVotes <<std::endl;
	return out;
}

void ElectionSystem::Vote(int voterId, int candidate){
	if (candidate>=numberOfCandidates || candidate<0){
		throw illegalCandidate();
	}
	if (hTable.member(voterId)){
		throw voterAlreadyVoted();
	}
	hTable.insert(voterId);
	support(candidate);
	unsigned int currCamp=UF.Find(candidate);
	int campLeader=UF.getGroupDetails(currCamp);
	Candidate tempLeader=candidatesArray[campLeader];
	Candidate votedCandidate=candidatesArray[candidate];
	if (tempLeader<votedCandidate){
		UF.updateRecord(candidate,currCamp);
		return;
	}
	
}


void ElectionSystem::support(int cadidate){
	if (candidatesArray[cadidate].getVotes()==0){
		candidatesArray[cadidate].increasVotes();
		Candidate c=candidatesArray[cadidate];
		CandidateKey newKey(c);
		votesTree.insert(newKey,c);
		return;
	}
	CandidateKey oldKey(candidatesArray[cadidate]);
	votesTree.remove(oldKey);
	candidatesArray[cadidate].increasVotes();
	CandidateKey newKey(candidatesArray[cadidate]);
	votesTree.insert(newKey,candidatesArray[cadidate]);

	
}




void ElectionSystem::signAgreement(int candidate1, int candidate2){
		unsigned int group1= UF.Find(candidate1);
		unsigned int group2= UF.Find(candidate2);
		if (group1 == group2){
			throw FromSameCamp();
		}
		
		int maxVotes1=getMaxVotes(group1);
		int maxVotes2=getMaxVotes(group2);
		int candidate1Votes= candidatesArray[candidate1].getVotes();
		int candidate2Votes= candidatesArray[candidate2].getVotes();
		if ((maxVotes1 > candidate1Votes) || (maxVotes2 > candidate2Votes)){
			throw notTheStrongestInCamp();
		}
		UF.Union(group1, group2);
		int newLeader=getNewLeader(group1,group2);
		UF.updateRecord(newLeader,UF.Find((unsigned int)newLeader));
		--numberOfGroups;
	}
int ElectionSystem::getMaxVotes(unsigned int groupId){
	int campLeader=UF.getGroupDetails(groupId);
	return  candidatesArray[campLeader].getVotes();
}
int ElectionSystem::getNewLeader(unsigned int group1,unsigned int group2){
	int campLeader1=UF.getGroupDetails(group1);
	int campLeader2=UF.getGroupDetails(group2);
	int diff=candidatesArray[campLeader1].getVotes()-candidatesArray[campLeader2].getVotes();
	if (diff==0){
		return campLeader1>campLeader2 ? campLeader1 : campLeader2;
	}
	return diff>0 ? campLeader1 : campLeader2;
}

	int ElectionSystem::campLeader(int candidate){
		unsigned int campNum =UF.Find(candidate);
		return (UF.getGroupDetails(campNum));
	}
		
	
	void ElectionSystem::CurrentRanking(int results[][2]){
		//groupIndex will hold the index of the group which the candidate belongs. the index is the rank of the group in the total results
		int *groupIndex = new int[numberOfCandidates];
		for (int i = 0; i < numberOfCandidates; ++i){
			groupIndex[i] = -1;
		}
		//resultIndex will hold the index where we should insert the next candidate from the group
		//the groups are sorted by their leaders
		int *resultIndex = new int[numberOfGroups];
		for (int i = 0; i < numberOfGroups; ++i){
			resultIndex[i] = 0;
		}
		int groupCounter = 0;
		int indexCounter = 0;
		
		//resultCandidateArray is an array which holds the candidates sorted by votes then by ID
		Candidate* resultCandidateArray = new Candidate[numberOfCandidates];
		int treeSize = votesTree.getSize();
		if (treeSize != 0){
			treeToArray<CandidateKey, Candidate> TTR(treeSize);
			votesTree.inorderTreeWalk(votesTree.getRootKey(), TTR);
			Candidate* tmpCandidateArray = TTR.getMaxArray();
			
			for (int i=0; i < treeSize; ++i){
				resultCandidateArray[i] = tmpCandidateArray[i];
			}
			delete[] tmpCandidateArray;
		}
		int i = treeSize;
		for (int j = numberOfCandidates - 1; j >= 0; --j){
			if (candidatesArray[j].getVotes() == 0){
				resultCandidateArray[i] = candidatesArray[j];
				++i;
			}
		}
		
		for (int i = 0; i < numberOfCandidates; ++i){
			Candidate c = resultCandidateArray[i];
			unsigned int id = c.getID();
			int numOfVoted = c.getVotes();
			unsigned int group = UF.Find(id);
			int tmpIndex = groupIndex[group];
			if (tmpIndex != -1){
				results[resultIndex[tmpIndex]][0] = id;
				results[resultIndex[tmpIndex]][1] = numOfVoted;
				++(resultIndex[tmpIndex]);
				
			}

			if (tmpIndex == -1){
				groupIndex[group] = groupCounter;
				tmpIndex = groupCounter;
				results[resultIndex[tmpIndex]][0] = id;
				results[resultIndex[tmpIndex]][1] = numOfVoted;
				++(resultIndex[tmpIndex]);
				
				if (groupCounter < numberOfGroups - 1){
					indexCounter += UF.getGroupSize(group);
					resultIndex[groupCounter+1] = indexCounter;
				}
				++groupCounter;
			}

		}
		delete[] resultCandidateArray;
		delete[] resultIndex;
		delete[] groupIndex;
	}


