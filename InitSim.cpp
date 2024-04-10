#include "InitSim.h"

int InitSim::InputConfig(City &theCity)
{
    //variable declarations
    ifstream fin;
    string fileName;
    string line;
    int colonPos;
    
    
    cout << "Please enter the configuration file name" << endl;
    cin >> fileName;

    //open config file
    fin.open("./" + fileName);

    //file error
    if (fin.fail())
    {
        cout << "Error in opening file, aborting program" << endl;
        return 1;
    }

    //read config file information into correct variables
    getline(fin, line);
    colonPos = line.find(":");
    this->regionLayout = line.substr(colonPos + 1);
    getline(fin, line);
    colonPos = line.find(":");
    theCity.SetTimeLimit(stoi(line.substr(colonPos + 1)));
    getline(fin, line);
    colonPos = line.find(":");
    theCity.SetRefreshRate(stoi(line.substr(colonPos + 1)));
    
    //close config file
    fin.close();

    //file is closed successfully
    return 0;
}

int InitSim::InputRegionData(City& theCity)
{
    ifstream fin;
    string line;
    string cellStrInput;
    char cellCharInput;

    int xcoordinate = 0;


    //open region layout file
    fin.open("./" + this->regionLayout);

    //file error
    if (fin.fail())
    {
        cout << "Error in opening file, aborting program" << endl;
        return 1;
    }

    //outer loop reads the entire line, inputs every x coordinate value on that y index
    //then, once the entire line is read, it moves onto the next y coordinate value and
    //repeats
	//was commented out during polution writing since the classes were not complete yet so this section would prevent compiling will be added when classes are complete
    while (getline(fin, line))
    {
        //allows for string to be read as a stream
        stringstream tempStr(line);
        vector<CellBlock*> tempRow;
        xcoordinate = 0;

        //inner loop reads each single character and applys the correct character representation 
        //to the correct spot in the array
        while (getline(tempStr, cellStrInput, ','))
        {
            CellBlock* tempCellBlockPtr;
            //Instead of CelBlock, we want the indivisual class thingies
            //CellBlock* tempCellBlockPtr = new CellBlock;

            //converts string to character
            cellCharInput = cellStrInput[0];
            
            switch(cellCharInput) {
                case 'R': {
                    tempCellBlockPtr = new Residential;
                    tempCellBlockPtr->SetLetterRep('R');
                    tempCellBlockPtr->SetPopulationNum(0);
                    tempCellBlockPtr->SetMaxPopulation(5);
                    break;
                }
                case 'I': {
                    tempCellBlockPtr = new Industrial;
                    tempCellBlockPtr->SetLetterRep('I');
                    tempCellBlockPtr->SetPopulationNum(0);
                    tempCellBlockPtr->SetMaxPopulation(3);
                    break;
                }
                case 'C': {
                    tempCellBlockPtr = new Commercial;
                    tempCellBlockPtr->SetLetterRep('C');
                    tempCellBlockPtr->SetPopulationNum(0);
                    tempCellBlockPtr->SetMaxPopulation(2);
                    break;
                }
                default: {
                    tempCellBlockPtr = new CellBlock;
                    break;
                }
            }

            tempCellBlockPtr->SetLetterRep(cellCharInput);

            tempRow.push_back(tempCellBlockPtr);
            xcoordinate++;

            if (theCity.GetRegionSize_x() < xcoordinate)
            {
                theCity.SetRegionSize_x(xcoordinate);
            }
        }
        
        theCity.appendRow(tempRow);
    }
    
    //close config file
    fin.close();

    return 0;

}
