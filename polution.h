#ifndef POLUTION_H
#define POLUTION_H
#include<iostream>
#include<vector>
#include "City.h"
#include "CellBlock.h"
#include "InitSim.h"
using namespace std;

void startSpread(City* myCity);
void spreadPolution(vector<CellBlock*> polAdd, CellBlock spreader);
void growPolution(vector<CellBlock*> polAdd);
void addPolution(City* myCity);
void setPolution();

#endif