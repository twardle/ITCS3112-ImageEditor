/*
 * IMAGE.cpp
 *
 *  Created on: Oct 4, 2017
 *      Author: itcs3112-oos
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "IMAGE.h"

using namespace std;
	/**
	 *    constructor function for object
	 */
	IMAGE::IMAGE(){
		width = 0;
		height = 0;
		imgArr = {};
	};
	/**
	 *    constructor function for object
	 *
	 *    @param String input_file file to be read from
	 */
	IMAGE::IMAGE(string input_file){
		width = 0;
		height = 0;

		read(input_file);
	};
	/**
	 *    constructor function for object
	 *
	 *    @param int height_ height value
	 *    @param int width_ width value
	 */
	IMAGE::IMAGE(int height_, int width_){
		width = width_;
		height = height_;
		imgArr = new int *[height];
		for(int i = 0; i < height; i++)
			imgArr[i] = (int*) new int[width];
	}
	/**
	 *    function that de-constructs the object
	 */
	IMAGE::~IMAGE(){
		for(int i = (width - 1); i > -1; i--)		delete [] imgArr[i];
		delete [] imgArr;
	}
	/**
	 *    function gets the value of the width
	 *    @return returns the width value
	 */
	int IMAGE::getWidth(){
		return width;
	}
	/**
	 *    function sets the value of the width
	 *
	 *    @param int w new width value
	 */
	void IMAGE::setWidth(int w){
		width = w;
	}
	/**
	 *    function gets the value of the height
	 *    @return returns the height value
	 */
	int IMAGE::getHeight(){
		return height;
	}
	/**
	 *    function sets the value of the height
	 *
	 *    @param int h new height value
	 */
	void IMAGE::setHeight(int h){
		height = h;
	}
	/**
	 *    function sets the values of an empty array passed to it to values in the row and column passed
	 *
	 *    @param int row Row Number
	 *    @param int col Column Number
	 *    @param int* arr array to be set with the pixel's RGB values
	 */
	void IMAGE::getImagePixel(int col, int row, int arr[]){
		arr[0] = imgArr[col][row];
		arr[1] = imgArr[col][row+1];
		arr[2] = imgArr[col][row+2];
	}
	/**
	 *    function sets a pixel to the values in a pixel array passed to the function
	 *
	 *    @param int row Row Number
	 *    @param int col Column Number
	 *    @param int* pixel array with pixel RGB values
	 */
	void IMAGE::setImagePixel(int row, int col, int* pixel){
		for(int i = -10; i < 10; i++){
			for(int j = 0; j < 3; j++){
				if((col + i) > 0 && ((col + i) < getHeight()) && (row + j) > 0 && (row + j) < getWidth()){
					imgArr[col+j][row+i] = pixel[j];
				}
			}
		}
	}

	/**
	 *    function for reading from the file, sets the maxVal, height and width as it pulls them from the file.
	 *
	 *    @param String infile file to be read from
	 *    @return returns the maximum value in the file
	 */
	int IMAGE::read(string infile){
		int maxVal = 0;
		ifstream file;
		string line;
		int col,row;

		//opens the .dat file
		file.open(infile);
		//reads each line, for the first three values (length, width and maxVal)
		file >> line;
		cout << line << endl;
		file >> line;
		setWidth(atoi(line.c_str()));
		cout << width << endl;
		file >> line;
		setHeight(atoi(line.c_str()));
		cout << height << endl;
		file >> line;
		maxVal = atoi(line.c_str());
		cout << maxVal << endl;

		imgArr = new int *[height];
				for(int i = 0; i < height; i++)
					imgArr[i] = (int*) new int[width * 3];

		//until the end of the file, read the values into the new image array.
			for(int i = 0; i < getHeight(); i++){
				col = i;
					for(int j = 0; j < (getWidth() * 3); j++){
						row = j / 3;
						file >> line;
						imgArr[col][row] = atoi(line.c_str());
					}
				}
		file.close();
		return maxVal;
	}
	/**
	 *    function for writing to a file, writes the entire array and then converts it to a .png
	 *
	 *    @param String outfile file to be written to
	 */
	void IMAGE::write(string outfile){
		ofstream ofile;
		ofile.open(outfile + ".ppm");

		ofile << "P3" << endl << getWidth() << " " << getHeight() << endl << "255 ";

		for(int i = 0; i < (getHeight()); i++){
			for(int j = 0; j < getWidth(); j++){
				//cout << imgArr[i][j] << " " << imgArr[i][j+1] << " " << imgArr[i][j+2] <<  endl;
				ofile << imgArr[i][j] << " " << imgArr[i][j+1] << " " << imgArr[i][j+2] <<  " ";
			}
		}
		ofile.close();


		system(("convert " + outfile + ".ppm " + outfile + ".png").c_str());
		return;
	}

