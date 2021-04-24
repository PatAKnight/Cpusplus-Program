#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream> //Used to open and close the file for the histogram
#include <vector> //Used to store the histogram data from the file

#undef max //Used to undefine the max in Windows.h to be used in the cin.ignore
using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
* Function that sets the text color of a string.
* Parameters are a int that represents the color and the String statement
* Parameters are set to the default colors in case the function is called without parameters
* Returns the string updated in the color
*/
string SetColor(int color = 7, string statement = "") {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return statement;
}

/*
* Function that calls the calIntFunc that runs the Python Function WriteFile
* After calling the Python Function this function reads a specified file and prints a histogram from the data of the file
*/
void ReadHistogram() {
	int length = callIntFunc("WriteFile", "frequency.dat"); //Calls the file and sets the length to the length of the groceryItem list
	ifstream histogramFile; //The variable that will handle the file
	string itemName; //Variable to temporarily store the item names
	int quantity; //Variable to temporarily store the item quantities
	vector<string> groceryItems(length); //Vector that will store all the items
	vector<int> groceryQuantities(length); //Vector that will store all the item quantities
	int count = 0; //Index to track the locations of the vectors when storing information

	//Opens the file
	cout << "Opening file frequency.dat" << endl;
	histogramFile.open("frequency.dat");

	//Error checking to ensure file opens
	if (!histogramFile.is_open()) {
		cout << "Could not open file frequency.dat." << endl;
	}

	//While loop that will handle storing the data to the appropriate vectors
	//If there is lines to read the while loop will evaluate to true
	histogramFile >> itemName; //Initial storage of the first itemName
	while (!histogramFile.fail()) {
		groceryItems.at(count) = itemName; //Set the item name to the vector
		histogramFile >> quantity; //Get the quantity for the item
		groceryQuantities.at(count) = quantity; //Set the quantity to the vector
		histogramFile >> itemName; //Get the next item name
		++count; //Update index
	}

	//Error handling in case the file is forced to close before reaching the end
	if (!histogramFile.eof()) {
		cout << "Input failure before reaching end of file." << endl;
	}

	//Closing the file
	cout << "Closing file frequency.dat" << endl;
	histogramFile.close();

	//For loop that itterates through the two vectors printing the histogram
	for (int i = 0; i < groceryItems.size(); i++) {
		cout << SetColor(7, groceryItems.at(i)) << " "; //Default color for the item name
		cout << SetColor(2, string(groceryQuantities.at(i), '*')) << endl; //Green color for the quantity
	}

	SetColor(); //Sets the color back to the default
}

void main()
{
	char userInput; //Character that will handle which function to be called in the menu
	string userItem; //Input to find the item the user is looking for 
	bool go = true; //Boolean to handle the while loop

	cout << "Welcome to the Corner Grocery sales menu. Please Enter 1, 2, 3, or 4" << endl;

	//While this is true the loop will continue to itterate through the menu
	while (go) {
		cout << "1 to print the number of times each item was sold" << endl;
		cout << "2 to search a specific item to see how many times it was sold" << endl;
		cout << "3 to view the Histogram for the day" << endl;
		cout << "4 to end the program" << endl;
		cin >> userInput; //Gets the user input to call appropriate Function

		//Switch that will determine which function to call
		switch (userInput) {
		//If the user selects 1 then the PrintList function in Python will be called
		case '1':
			CallProcedure("PrintList");
			cout << endl;
			break;

		//If the user selects 2 then they will be prompted for the item they wish to search for
		//Then the SpecificItem function in Python will be called and the item will be passed to the function
		case '2':
			cout << "Enter the item you wish to search for." << endl;
			cin >> userItem;
			cout << callIntFunc("SpecificItem", userItem) << endl;
			cout << endl;
			break;

		//If the user selects 3 then the ReadHistogram function will be called in C++
		case '3':
			ReadHistogram();
			cout << endl;
			break;

		//If the user selects 4 then go will be set to false ending the while loop
		case '4':
			go = false;
			break;

		//If the user enters anything other then 1, 2, 3, or 4 then the default will be called in the switch
		//Notifies the user that the input was Invalid
		default:
			cout << "Invalid input" << endl;
			

			cin.clear(); //Used to clear the input stream
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //If the user enters a string the input will be ignored up to the new line
			break;
		}
		
		//Determines if the user has not attempted to close the menu
		//Then asks if the user would like to close the menu or to continue
		if (go) {
			cout << "Would you like to check another menu option?" << endl;
			cout << "Enter y or Y for yes otherwise press any key to close" << endl;
			cin >> userInput;
			//Checks to see if the user entered anything other than y or Y and if so sets go to false to close the program
			if (userInput != 'y' && userInput != 'Y') {
				go = false;
				cout << "Closing program" << endl;
			}
		}
		//If the user selected 4 then go will be false and a closing message will be printed
		else
			cout << "Closing program" << endl;
	}

}