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
	//img->read(oName);


	while(rerun){
		//allows the user to pick the starting x value
		bool vInput = false;
		data.y = -1;
		data.x = 0;
		int pixArr[] = {200,0,0};

		//checks for a valid input, otherwise takes in another input
		while (!vInput){
			cout << "Pick StartY (0-" << (img->getHeight() - 3) <<"):\t";
			cin >> data.y;
			//if cin fails
			if(!cin){
				//output invalid input and clear the current cin
				cout <<"ERR: INVALID INPUT" << endl;
				cin.clear();
				cin.ignore(80, '\n');
			}
			else if(!(data.y > (img->getHeight() - 4) || data.y < 0)){
				vInput = true;		//if cin doesn't have an error and the input is within the parameters, it is a valid input
			}
			else{
				cout << "ERR: OUTSIDE RANGE" << endl;		//the input is outside of the range specified.
			}
		}

		//runs the pathing algorithm until it reaches the end of the horizontal
		while((data.x) < (img->getWidth())) {
			img->setImagePixel(data.x, data.y, pixArr);
			data.x += 3;
		}

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

	//opens a new out file for the new path
	cout << "Name the file:\t";
	cin >> oName;
	oName = "data/" + oName;

	//prints the path.ppm
	img->write(oName);
	img->~IMAGE();
	//end of program
	return 0;
}
