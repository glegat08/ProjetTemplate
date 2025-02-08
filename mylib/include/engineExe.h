// COULD NOT DELETE THIS FILE
// AS IT GENERATE A CMAKE ERROR

#pragma once
#include "mathLib.h"
#include "myVector.h"
#include "myMatrix.h"
#include "myVectorND.h"
#include "myList.h"
#include "myIntrusiveList.h"
#include "myArray.h"

class Engine
{
public:
    Engine();
    ~Engine();
    void run();

private:
    void displayMainMenu();
    void vectorOperations();
	void matrixOperations();
	void vectorNDOperations();
	void listOperations();
	void intrusiveListOperations();
	void arrayOperations();
};