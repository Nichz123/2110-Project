#include <iostream>
#include "polution.h"
using namespace std;

//adds the amount of polution each industrial zone will create
void addPolution(City* myCity)
{
	CellBlock temp;
	char curBlock = ' ';
	
	for(int i = 0; i < myCity->getRegionY(); ++i) 
	{
		for (int j = 0; j < myCity->getRegionX(); ++j)
		{
			temp = *myCity->getRegion(i,j);
			curBlock = temp.GetLetterRep();
			switch (curBlock)
			{
				case 'I':
				{
					myCity->getRegion(i,j)->setPolSpread();
				}
				default:
				{
				break;
				}
			}
		}
	}
	//the following code was written out before error testing. 
	//When error testing the code did not seem to do anything but could not figure out why it was written so it is commented out in case its needed
	//wll be removed or implemented when testing the fucntionality
	/*
	for(loop to look through the city)
	{
		switch case
		{	
			case industrial
			{
				toBeAdded = getPolSpread();
				spreadPolution();
			}

			defalt
			{
			break;
			}
		}
	}*/
}

//fucntion that creates a vector of all nodes that need to spread and then passes each node into the function that actually spreads the polution
void startSpread(City* myCity)
{
	CellBlock temp;
	vector<CellBlock*> polAdd;
	char selector = '0';
	CellBlock* itHolder;	//for some reason I got a wierd compiler error when trying to call a function from the iterorator.
							//Was unable to find any solutions online or when speaking to groupmates
							//a new pointer was created and set equal to the itterator to get around this issue
	for(int i = 0; i < myCity->getRegionY(); ++i) 
	{
		for (int j = 0; j < myCity->GetRegionSize_x(); ++j)
		{
			temp = *myCity->getRegion(i,j);
			selector = temp.getLetterRep();
			switch (selector)
			{
				case 'I':
				{
					myCity->getRegion(i,j)->setPolution();
					polAdd.push_back(myCity->getRegion(i,j));
				}
				default:
				break;
			}
		}
	}
	for (auto it = polAdd.begin(); it != polAdd.end(); ++it)
	{
		itHolder = *it;
		itHolder->setHigh(itHolder->getPolSpread());
		spreadPolution(polAdd, *itHolder);
		itHolder->setZero(itHolder);
	}
}


//recursive function that spreads polution to nearby cells

void spreadPolution(vector<CellBlock*> polAdd, CellBlock spreader)
{
	for(auto it = polAdd.begin(); it != polAdd.end(); ++it)
	{
		CellBlock* itHolder = *it;
		if (spreader.getPolSpread() > 1)
		{
			spreader.decreaseSpread();
			spreadPolution(polAdd,spreader);
			spreader.increaseSpread();
			if(spreader.getPolSpread() > itHolder->getHighestVisited())
			{
				itHolder->addPolution(spreader.getPolSpread() - itHolder->getHighestVisited());
				itHolder->setHigh(spreader.getPolSpread());
				itHolder->setHigh(1);
			}
		}
		else if (spreader.getPolSpread() == 1)
		{
			if(spreader.getPolSpread() > itHolder->getHighestVisited())  //since nodes will be visited multiple times each time a node is spreading this checks that only the higest value of spread that applies to the node is added
			{
				itHolder->addPolution(spreader.getPolSpread() - itHolder->getHighestVisited());
				itHolder->setHigh(spreader.getPolSpread());
				itHolder->setHigh(1);
			}
			
		}
	}
	return;
}

//funciton that actually adds the polution value to cellblocks
void growPolution(vector<CellBlock*> polAdd)
{
	for(auto it = polAdd.begin(); it != polAdd.end(); ++it)
	{
		polAdd.front()->addPolution(polAdd.front()->getPolutionToAdd());
	}
}

//displays the polution values.
//population numbers from cellblocks are no longer displayed since they are already known and this way all numbers shown will be the polution values
//function not written yet, will be in next commit
void display()
{
	//display the polution map
}