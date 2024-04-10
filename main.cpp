#include <iostream>
#include "InitSim.h"
#include "polution.h"
using namespace std;

int main()
{
    InitSim BeginSim;
    City myCity;
    int fileReadFail;

    //reads in configuration information
    fileReadFail = BeginSim.InputConfig(myCity);

    if (fileReadFail == 1)
    {
        return 1;
    }

    //reads in region information and initializes the region
    fileReadFail = BeginSim.InputRegionData(myCity);

    if (fileReadFail == 1)
    {
        return 1;
    }

    //ALL CHANGES AND INPUTS INTO ARRAY MUST BE DONE BEFORE HERE (besides the simulation)
    myCity.CreateAdjList();
    
    //Output Initial Region State
    cout << endl << "Initial Region State:";
    myCity.OutputCity();
    myCity.OutputDesc();

    //Prompt to begin simulation
    myCity.BeginSimulation();

    //Pollution prompts
    addPolution(&myCity);
	startSpread(&myCity);
	cout << endl;
	cout << "POLLUTION STATE:" << endl;
	myCity.OutputPolution();
	myCity.displayPolutionInArea();
}
