#include "library2.h"
#include "ElectionSystem.h"

void* Init(int n){
	ElectionSystem* newElectionSystem = new ElectionSystem(n);
	return newElectionSystem;
}

StatusType  Vote(void* DS, int voterID, int candidate){
	if (DS == NULL || voterID < 0 || candidate < 0){
		return INVALID_INPUT;
	}
	ElectionSystem* ES = (ElectionSystem*)DS;
	if (ES->getNumOfCandidates() <= candidate){
		return INVALID_INPUT;
	}
	try{
		ES->Vote(voterID, candidate);
	}
	catch (const std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
	catch (const std::exception& e){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType  SignAgreement(void* DS, int candidate1, int candidate2){
	if (DS == NULL || candidate1 < 0 || candidate2 < 0){
		return INVALID_INPUT;
	}
	ElectionSystem* ES = (ElectionSystem*)DS;
	if (ES->getNumOfCandidates() <= candidate1 || ES->getNumOfCandidates() <= candidate2){
		return INVALID_INPUT;
	}
	try{
		ES->signAgreement(candidate1, candidate2);
	}
	catch (const std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
	catch (const std::exception& e){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType  CampLeader(void* DS, int candidate, int* leader){
	if (DS == NULL || candidate < 0 || leader == NULL){
		return INVALID_INPUT;
	}
	ElectionSystem* ES = (ElectionSystem*)DS;
	if (ES->getNumOfCandidates() <= candidate){
		return INVALID_INPUT;
	}
	try{
		*leader = ES->campLeader(candidate);
	}
	catch (const std::exception& e){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType  CurrentRanking(void* DS, int results[][2]){
	if (DS == NULL || results == NULL){
		return INVALID_INPUT;
	}
	ElectionSystem* ES = (ElectionSystem*)DS;
	try{
		ES->CurrentRanking(results);
	}
	catch (const std::bad_alloc& e){
		return ALLOCATION_ERROR;
	}
	catch (const std::exception& e){
		return FAILURE;
	}
	return SUCCESS;

}

void Quit(void** DS){
	ElectionSystem* ES = (ElectionSystem*)*DS;
	delete ES;
	*DS = NULL;
}