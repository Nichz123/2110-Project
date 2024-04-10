#include "CellBlock.h"
#include "Industrial.h"
#include "Residential.h"
#include "Commercial.h"
using namespace std;

#ifndef CITY_H
#define CITY_H

class City
{
    public:
        City();
        void OutputCity();
        void OutputDesc();
        void SetRegionSize_x(int inputSize_x);
        void SetTimeLimit(int inputTime);
        void SetRefreshRate(int inputRefreshRate);
        int GetRegionSize_x();
        void appendRow(vector<CellBlock*> inputRow);
        void CreateAdjList();
        void scopeRegion();
        void BeginSimulation();
        void SimulationLoop();
		int getRegionX();
		int getRegionY();
		CellBlock* getRegion(int x, int y);
	void OutputPolution();
	void displayPolutionInArea();	
    private:
        vector<vector<CellBlock*>> region;
        list<CellBlock*> readyToGrow;

        int timeLimit;
        int refreshRate;


        int regionSize_x = 0;
        int totalPolution = 0;
        int availibleWorkers = 0;
        int availibleGoods = 0;
        int totalPopulation = 0;
        int totalGoods = 0;
};

#endif
