/*
 * Main.cpp
 *
 *  Created on: Sep 11, 2017
 *      Author: Tyler Wardle
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <array>
#include <cmath>
#include "IMAGE.h"

using namespace std;

/**
 *    structure defining the DATA type, used to hold variables related to the file
 */

struct DATA {
	string fname;	//filename
	int maxVal;		//maximum height value in the .dat
	int x;			//current x value
	int y;			//current y value
};


/**
 *    Program takes an image file, iterates across the pixels drawing a red band then outputs the array to a new .ppm file and converts it into a .png
 */
int main(){
	DATA data;
	bool vInput = false;
	data.fname = "";
	//IMAGE img;
	string oName;
	bool rerun = true;

	//prints the pixel values to the out file.
	ifstream infile;
	//checks for invalid input
	while(!vInput){
		cout << "filename:\t";
		cin >> oName;
		oName = "data/" + oName + ".ppm";
		infile.open(oName);

		//tests file to make sure it exists
		if(!cin){
			cout <<"ERR: INVALID INPUT" << endl;
			cin.clear();
			cin.ignore(80, '\n');
		}
		else if(infile.good()){
			vInput = true;
		}
		else{
			cout << "ERR: FILE DOES NOT EXIST" << endl;
		}

	}
	//creates the IMAGE object
	IMAGE* img = new IMAGE(oName);

	//allows the user to rerun the image manipulation
	while(rerun){
		//sets up the initial values
		vInput = false;
		data.y = 200;
		data.x = 0;
		int temp = -1;

		vInput = false;
		while(!vInput){
			//prints a menu and allows the user to pick an option, error checks their input
			cout << "***MENU***\n1)\tTo Grayscale\n2)\tFlip Horizontally\n3)\tNegate Blue\n4)\tFlatten Red\n";
			cin >> temp;

			if(!cin){
				cout <<"ERR: INVALID INPUT" << endl;
				cin.clear();
				cin.ignore(80, '\n');
			}
			else if(temp < 5 && temp > -1){
				vInput = true;
			}
			else{
				cout << "ERR: OUTSIDE RANGE" << endl;
			}
		}
		//switch based on user input, runs the appropriate image manipulation
		switch(temp){
		case 1:
			img->toGrayscale();
			break;
		case 2:
			img->flipHorizontal();
			break;
		case 3:
			img->negateBlue();
			break;
		case 4:
			img->flattenRed();
			break;
		default:
			cout << "ERR: INVALID INPUT";
		}

		//opens a new out file for the new path
		cout << "Name the file:\t";
		cin >> oName;
		oName = "data/" + oName;

		//prints the path.ppm
		img->write(oName);

		//validation of rerun input
		vInput = false;
		bool vInput2 = false;
		bool reset = false;
		while(!vInput){
			//asks the user if they would like to rerun the program
			cout << "press 1 to rerun the program: ";
			cin >> rerun;

			if(!cin){
				cout <<"ERR: INVALID INPUT" << endl;
				cin.clear();
				cin.ignore(80, '\n');
			}
			else if(rerun == true || rerun == false){
				vInput = true;
				if(rerun){
					while(!vInput2){
						//allows the user to reset any changes they've made to the image
						cout << "press 1 to reset the modifications: ";
						cin >> reset;

						if(!cin){
							cout <<"ERR: INVALID INPUT" << endl;
							cin.clear();
							cin.ignore(80, '\n');
						}
						else if(reset == true || reset == false){
							vInput2 = true;

							if(reset) img->reset();
						}
						else{
							cout << "ERR: OUTSIDE RANGE" << endl;
						}
					}
				}
			}
			else{
				cout << "ERR: OUTSIDE RANGE" << endl;
			}
		}
	}
	//deconstructs the image object
	img->~IMAGE();
	//end of program
	return 0;
}
