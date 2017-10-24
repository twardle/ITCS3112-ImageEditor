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
	data.fname = ("data/colorado1.dat");
	//IMAGE img;
	string oName;
	bool rerun = true;

	//prints the pixel values to the out file.
	cout << "filename:\t";
	cin >> oName;
	oName = "data/" + oName + ".ppm";
	IMAGE* img = new IMAGE(oName);


	while(rerun){
		//allows the user to pick the starting x value
		bool vInput = false;
		data.y = 200;
		data.x = 0;
		int pixArr[] = {255,0,0};
		img->reset();
		int temp = -1;

		vInput = false;
		while(!vInput){
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
		while(!vInput){
			cout << "press 1 to run with a new Y value: ";
			cin >> rerun;

			if(!cin){
				cout <<"ERR: INVALID INPUT" << endl;
				cin.clear();
				cin.ignore(80, '\n');
			}
			else if(rerun == true || rerun == false){
				vInput = true;
			}
			else{
				cout << "ERR: OUTSIDE RANGE" << endl;
			}
		}

	}


	img->~IMAGE();
	//end of program
	return 0;
}
