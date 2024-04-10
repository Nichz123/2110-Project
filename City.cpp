#include "City.h"


City::City()
{  

}

void City::OutputCity()
{
    cout << endl;

    for (int i = 0; i < region.size(); i++)
    {
        for (int j = 0; j < regionSize_x; j++)
        {
            if (region[i][j]->GetPopulationNum() > 0)
            {
                cout << " " << region[i][j]->GetPopulationNum() << " ";
            }
            else
            {
                cout << " " << region[i][j]->GetLetterRep() << " ";
            }
        }
        cout << endl;
    }
}

void City::OutputDesc()
{

    cout << endl;
    cout << "Available Workers: " << totalPopulation << endl;
    cout << "Available Goods: " << totalGoods << endl;
    cout << endl;
}

void City::SetRegionSize_x(int inputSize_x)
{
    this->regionSize_x = inputSize_x;
}

void City::SetTimeLimit(int inputTime)
{
    timeLimit = inputTime;
}
void City::SetRefreshRate(int inputRefreshRate)
{
    refreshRate = inputRefreshRate;
}

int City::GetRegionSize_x()
{
    return this->regionSize_x;
}

void City::appendRow(vector<CellBlock*> inputRow)
{
    region.push_back(inputRow);
}

void City::CreateAdjList()
{
    for (int i = 0; i < region.size(); i++)
    {
        for (int j = 0; j < GetRegionSize_x(); j++)
        {
            //Bellow cell
            if (i + 1 < region.size())
            {
                region[i][j]->push_back(region[i+1][j]);
            }

            //Above Cell
            if (i - 1 >= 0)
            {
                region[i][j]->push_back(region[i-1][j]);
            }

            //Right of cell
            if (j + 1 < regionSize_x)
            {
                region[i][j]->push_back(region[i][j+1]);
            }

            //Left of cell
            if (j - 1 >= 0)
            {
                region[i][j]->push_back(region[i][j-1]);
            }

            //Top right of cell
            if (i + 1 < region.size() && j + 1 < regionSize_x)
            {
                region[i][j]->push_back(region[i+1][j+1]);
            }

            //Top left of cell
            if (i + 1 < region.size() && j - 1 >= 0)
            {
                region[i][j]->push_back(region[i+1][j-1]);
            }

            //Bottom right of cell
            if (i - 1 >= 0 && j + 1 < regionSize_x)
            {
                region[i][j]->push_back(region[i-1][j+1]);
            }
            
            //Bottom left of cell
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                region[i][j]->push_back(region[i-1][j-1]);
            }
        }
    }
}

void City::scopeRegion()
{
    int areaPopulation = 0;
    int areaPollution = 0;
    bool doAnalysis;
    int xCoordTopLeftCorner;
    int yCoordTopLeftCorner;
    int xCoordBottomRightCorner;
    int yCoordBottomRightCorner;

    cout << "Would you like to do regional analysis for population? (1 for yes, 0 for no)" << endl;
    cin >> doAnalysis;

    if (!doAnalysis)
    {
        return;
    }

    while(true)
    {
        cout << "Input x coordinate of top left corner" << endl;
        cin >> xCoordTopLeftCorner;

        cout << "Input y coordinate of top left corner" << endl;
        cin >> yCoordTopLeftCorner;

        cout << "Input x coordinate of bottom right corner" << endl;
        cin >> xCoordBottomRightCorner;

        cout << "Input y coordinate of bottom right corner" << endl;
        cin >> yCoordBottomRightCorner;

        for (int i = yCoordTopLeftCorner; i <= yCoordBottomRightCorner; i++)
        {
            for (int j = xCoordTopLeftCorner; j <= xCoordBottomRightCorner; j++)
            {
                if (region[i][j]->GetPopulationNum() == -1)
                {
                    continue;
                }

                areaPopulation += region[i][j]->GetPopulationNum();
            }

        }

        cout << "Area Population: " << areaPopulation << endl;

        cout << "Do you wish to continue? (1 for yes, 0 for no)" << endl;
        cin >> doAnalysis;

        if (!doAnalysis)
        {
            return;
        }
    }

}

void City::BeginSimulation()
{
    char inputChar;

    while (toupper(inputChar) != 'Y' && inputChar != 'N')
    {
        cout << "Begin Simulation (Y or N)" << endl;
        cin >> inputChar;

        if (toupper(inputChar) == 'Y')
        {
            SimulationLoop();
	        scopeRegion();
        }
        else if (toupper(inputChar) == 'N')
        {
            return;
        }
        else
        {
            cout << "Incorrect input, please try again." << endl;
        }
    }
}

void City::SimulationLoop()
{
    bool noChange = false;
    int refreshRateAdder = 0;
    vector<CellBlock*> RVector;
    vector<CellBlock*> CVector;
    vector<CellBlock*> IVector;
    
    for(int i = 0; i < timeLimit; i++)
    {
        //Increment refreshRate
        refreshRateAdder++;

        //Only outputs at given refreshRate
        if (refreshRateAdder == refreshRate)
        {
            OutputCity();
            OutputDesc();
            refreshRateAdder = 0;
        }

        //**In a nested for loop** region[i][j].PromptChange()
        for (size_t i = 0; i < region.size(); ++i) {
            for (size_t j = 0; j < region[i].size(); ++j) {
                CellBlock* cell = region[i][j];

                //Function call to check for population growth
                cell->promptChange();
                //Go through each bool grow == true and put them in a vector
                if (cell->GetGrow()) {
                    if(cell->GetLetterRep() == 'R') {
                        RVector.push_back(cell);
                    } else if(cell->GetLetterRep() == 'C') {
                        CVector.push_back(cell);
                    } else if(cell->GetLetterRep() == 'I') {
                        IVector.push_back(cell);
                    }
                }
            }
        }
        //Then iterate to check tie breakers
        for(size_t i = 0; i < RVector.size(); i++){
            CellBlock* cell = RVector[i];
            cell->SetPopulationNum(cell->GetPopulationNum() + 1);
            totalPopulation++;
            availibleWorkers++;

            RVector.erase(RVector.begin() + i);
            i--;
            cell->SetGrow(false);
        }
        //Defined in City.h
        //        int availibleWorkers
        //        int availibleGoods
        for(size_t i = 0; i < CVector.size(); i++){
            CellBlock* cell = CVector[i];
            //Commercials conditions
             if (availibleWorkers > 0 && availibleGoods > 0)
            {
                cell->SetPopulationNum(cell->GetPopulationNum() + 1);
                totalPopulation++;
                availibleWorkers--;
                availibleGoods--;
            }

            CVector.erase(CVector.begin() + i);
            i--;
            cell->SetGrow(false);
        }
        for(size_t i = 0; i < IVector.size(); i++){
            CellBlock* cell = IVector[i];
            //Industrials conditions
       	if (availibleWorkers >= 2) {
		cell->SetPopulationNum(cell->GetPopulationNum() + 1);
		totalPopulation++;
		availibleWorkers -= 2;
		availibleGoods++;
		totalGoods++;
		}
            IVector.erase(IVector.begin() + i);
            i--;
            cell->SetGrow(false);
        }
    }
}

int City::getRegionX()
{
	return regionSize_x;
}
int City::getRegionY()
{
	return region.size();
}

CellBlock* City::getRegion(int x, int y)
{
	return region[x][y];
}
//function to output the polution numbers
//function was intentnionally writen to never show population numbers to ensure all number valuses shown are Polution numbers
void City::OutputPolution()
{
	int polTracker = 0;
    for (int i = 0; i < region.size(); i++)
    {
        for (int j = 0; j < regionSize_x; j++)
        {
            if (region[i][j]->getPolution() > 0)
            {
                cout << " " << region[i][j]->getPolution() << " ";
				polTracker += region[i][j]->getPolution();
            }
            else
            {
                cout << " " << region[i][j]->GetLetterRep() << " ";
            }
        }
		cout << endl;
    }
	 cout << endl << endl << "total polution = " << polTracker << endl;
}

void City::displayPolutionInArea()
{
	bool selection;
	do
	{
		cout << "Would you like to display the polution analysis in a specific area? (1 for yes or 0 for no)" << endl;
		cin >> selection;
		if (selection)
		{
	
			int xCoordTopLeftCorner;
			int yCoordTopLeftCorner;
			int xCoordBottomRightCorner;
			int yCoordBottomRightCorner;
			int polutionCounter = 0;
			cout << "Input x coordinate of top left corner" << endl;
			cin >> xCoordTopLeftCorner;

			cout << "Input y coordinate of top left corner" << endl;
			cin >> yCoordTopLeftCorner;

			cout << "Input x coordinate of bottom right corner" << endl;
			cin >> xCoordBottomRightCorner;

			cout << "Input y coordinate of bottom right corner" << endl;
			cin >> yCoordBottomRightCorner;

			for (int i = yCoordTopLeftCorner; i <= yCoordBottomRightCorner; i++)
			{
				for (int j = xCoordTopLeftCorner; j <= xCoordBottomRightCorner; j++)
				{
					polutionCounter += region[i][j]->getPolution();
				}
			}

			cout << "Total polution: " << polutionCounter << endl;
		}
		else
			return;
	}while(true);
}
