#include "CellBlock.h"

void CellBlock::SetLetterRep(char inputChar)
{
    this->letterRep = inputChar;
}

char CellBlock::GetLetterRep()
{
    return this->letterRep;
}

void CellBlock::SetPopulationNum(int inputPopNum)
{
    this->populationNum = inputPopNum;
}

int CellBlock::GetPopulationNum()
{
    return this->populationNum;
}

void CellBlock::push_back(CellBlock *inputCellBlock)
{
    adjList.push_back(inputCellBlock);
}

void CellBlock::outputAdjList()
{
    for (auto cellBlock : adjList)
    {
        cout << cellBlock->GetLetterRep() << endl;
    }
}

void CellBlock::SetGrow(bool input)
{
    this->grow = input;
}

bool CellBlock::GetGrow()
{
    return this->grow;
}

void CellBlock::SetMaxPopulation(int input)
{
    this->maxPopulation = input;
}

void CellBlock::addPolution()
{
	polution = this->populationNum;
}

void CellBlock::addPolution(int toBeAdded)
{
	polution += toBeAdded;
}

void CellBlock::setPolSpread()
{
	if (populationNum > 0)
	{
		polSpread = this->populationNum - 1;
	}
}
int CellBlock::getPolSpread()
{
	return polSpread;
}
int CellBlock::getPolution()
{
	return polution;
}
void CellBlock::setHigh(int highNum)
{
	highestVisited = highNum;
}
void CellBlock::decreaseSpread()
{
polSpread -= 1;
}
	void CellBlock::increaseSpread()
{
polSpread += 1;
}

//function that clears the values used to protect from double spreading polution when running the function so that the next spread is unimpeaded
void CellBlock::setZero(CellBlock* startPoint)
{
	if (this->getPolSpread() > 1)
	{
		for (auto it = startPoint->adjList.begin(); it != startPoint->adjList.end(); ++it)
		{
			this->decreaseSpread();
			setZero(*it);
			this->increaseSpread();
			//it->setHigh(0);
		}
	}
	else if (this->getPolSpread() == 1)
	{
		this->setHigh(0);
	}
}
char CellBlock::getLetterRep()
{
return letterRep;
}

void CellBlock::setPolutionToAdd()
{
	this->polutionToAdd += 1;
}
int CellBlock::getPolutionToAdd()
{
	return polutionToAdd;
}
int CellBlock::getHighestVisited()
{
	return highestVisited;
}

void CellBlock::promptChange() {
    if(populationNum == 0) {
        //Adjacent to a powerline OR Adjacent to a cell with a population > 0
        for (auto cellBlock : adjList) {
            if((cellBlock->GetPopulationNum() > 0) || cellBlock->GetLetterRep() == '#' || cellBlock->GetLetterRep() == 'T') {
                grow = true;
                break;
            }
        }
    } else if(populationNum > 0 && populationNum < maxPopulation){
        int counter = 0; // num of ajecent cells that meet criteria

        //Adjacent to [population*2]+ cells with population of [population]+
        for (auto cellBlock : adjList) {
            if((cellBlock->GetPopulationNum() >= populationNum)) {
                counter++;
            }
        }
        if(counter >= populationNum*2) {
            grow = true;
        }
    }
}
void CellBlock::setPolution()
{
	polution = populationNum;
}

CellBlock* CellBlock::getStart()
{
	return adjList.front();
}
CellBlock* CellBlock::getEnd()
{
	return adjList.back();
}