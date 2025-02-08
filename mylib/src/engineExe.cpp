// COULD NOT DELETE THIS FILE
// AS IT GENERATE A CMAKE ERROR

#include "engineExe.h"
#include <iostream>
#include <limits>

Engine::Engine() {}
Engine::~Engine() {}

enum Mode
{
	Array = 1
    , List
    , IntrusiveList
    , Vector
    , VectorND
    , Matrix
    , Quit
};

void Engine::displayMainMenu()
{
    std::cout << "\n--- Mathematical Library Demo ---\n";
    std::cout << "1. Vector Operations\n";
	std::cout << "2. Matrix Operations\n";
	std::cout << "3. VectorND Operations\n";
	std::cout << "4. List Operations\n";
	std::cout << "5. myIntrusiveList Operations\n";
	std::cout << "6. Array Operations\n";
    std::cout << "7. Exit\n";
    std::cout << "\nChoose an option: ";
}

void Engine::vectorOperations()
{
    myVector<int, 10> vec;
    std::cout << "\n--- Vector Operations ---\n";

    vec.push_back(10);

	std::cout << "Vector size: " << vec.size() << std::endl;
    std::cout << "First element: " << vec.front() << std::endl;
    std::cout << "Last element: " << vec.back() << std::endl;
}

void Engine::matrixOperations()
{

}

void Engine::vectorNDOperations()
{

}

void Engine::listOperations()
{

}

void Engine::intrusiveListOperations()
{

}

void Engine::arrayOperations()
{

}

void Engine::run()
{
    int choice;

    do 
    {
        displayMainMenu();
        std::cin >> choice;

        switch (choice)
    	{
        case Vector: 
            vectorOperations();
        	break;
		case Matrix:
			matrixOperations();
			break;
		case VectorND:
			vectorNDOperations();
			break;
		case List:
			listOperations();
			break;
		case IntrusiveList:
			intrusiveListOperations();
			break;
		case Array:
            arrayOperations();
			break;
        case Quit: 
            std::cout << "\nExiting...\n";
        	break;
        default: 
            std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);
}
