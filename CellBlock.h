#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

#ifndef CELLBLOCK_H
#define CELLBLOCK_H

class CellBlock
{
    public:
        void SetLetterRep(char inputChar);
        char GetLetterRep();
        void SetPopulationNum(int inputPopNum);
        int GetPopulationNum();
        void push_back(CellBlock *inputCellBlock);
        void outputAdjList();
        void promptChange();
        void SetGrow(bool input);
        bool GetGrow();
        void SetMaxPopulation(int input);
        void setPolSpread();
		int getPolution();
		void startSpread();
		void spreadPolution();
		void addPolution();
		void addPolution(int toBeAdded);
		void setHigh(int highNum);
		void increaseSpread();
		void decreaseSpread();
		void setZero(CellBlock* startPoint);
		char getLetterRep();
		int getPolSpread();
		void setPolutionToAdd();
		int getPolutionToAdd();
		int getHighestVisited();
		void setPolution();
		CellBlock* getStart();
		CellBlock* getEnd();
		
		list<CellBlock*> adjList;

    protected:
        
        char letterRep = ' ';
        int populationNum = -1; //-1 for powerlines and roads (not supposed to grow at all)
        bool grow = false;
        int maxPopulation = 0;
		int polution = 0;
		int polSpread = 0;
		int polutionToAdd = 0;
		int highestVisited = 0;
};

#endif
