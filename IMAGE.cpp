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
#include <cmath>
#include "IMAGE.h"

using namespace std;
	/**
	 *    constructor function for object
	 */
	IMAGE::IMAGE(){
		width = 0;
		height = 0;
		imgArr = {};
		orgArr = imgArr;
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
		imgArr = new int **[height];
		for(int i = 0; i < height; i++){
			imgArr[i] = new int*[width];
			for(int j = 0; j < width; j++){
				imgArr[i][j] = (int*) new int[3];
			}
		}
		orgArr = imgArr;
	}
	/**
	 *    function that de-constructs the object
	 */
	IMAGE::~IMAGE(){
		for(int i = (height - 1); i >= 0; i--) {
			for(int j = width; j >= 0; j--) delete [] imgArr[i][j];
			delete [] imgArr[i];
		}
		delete [] imgArr;

		for(int i = (height - 1); i >= 0; i--) {
					for(int j = width; j >= 0; j--) delete [] orgArr[i][j];
					delete [] orgArr[i];
				}
				delete [] orgArr;
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
		arr[0] = imgArr[col][row][0];
		arr[1] = imgArr[col][row][1];
		arr[2] = imgArr[col][row][2];
	}
	/**
	 *    function sets a pixel to the values in a pixel array passed to the function
	 *
	 *    @param int row Row Number
	 *    @param int col Column Number
	 *    @param int* pixel array with pixel RGB values
	 */
	void IMAGE::setImagePixel(int col, int row, int* pixel){
		for(int rgb = 0; rgb < 3; rgb++)
			imgArr[row][col][rgb] = pixel[rgb];

	}

	void IMAGE::toGrayscale(){
		int temp[3];
		for(int row = 0; row < height; row++){
			for(int col = 0; col < width; col++){
				for(int rgb = 0; rgb < 3; rgb++)
					temp[rgb] = imgArr[row][col][0] * 0.299 + imgArr[row][col][1] * 0.587 + imgArr[row][col][2] * 0.144;
				setImagePixel(col, row, temp);
			}
		}
		for(int row = 0; row < height; row++){
					for(int col = 0; col < width; col++){
						for(int rgb = 0; rgb < 3; rgb++){
							//cout << imgArr[row][col][rgb] << ",";
						}
					}
					//cout << endl;
				}
	}
	//may need work
	void IMAGE::flipHorizontal(){
		int temp[3];
		for(int row; row < height; row++)
			for(int col = 0; col < floor(width/2); col++){
				for(int k=0; k < 3; k++){
					temp[k] = imgArr[row][col][k];
					setImagePixel(col,row,imgArr[row][width-col-1]);
					setImagePixel(width-col-1,row,temp);
				}
			}
	}

	void IMAGE::negateBlue(){
		int temp[3];
		for(int row; row < height; row++)
			for(int col = 0; col < width; col++){
				temp[0] = imgArr[row][col][0];
				temp[1] = 255 - imgArr[row][col][2];
				temp[2] = imgArr[row][col][2];
				for(int rgb=0; rgb < 3; rgb++)
					setImagePixel(col,row,temp);
			}

	}

	void IMAGE::flattenRed(){
		int temp[3];
		for(int row; row < height; row++)
			for(int col = 0; col < width; col++){
				temp[0] = 0;
				temp[1] = imgArr[row][col][1];
				temp[2] = imgArr[row][col][2];
				for(int rgb=0; rgb < 3; rgb++)
					setImagePixel(col,row,temp);
			}
	}

	void IMAGE::reset(){
		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				for(int k = 0; k < 3; k++)
					imgArr[i][j][k] = orgArr[i][j][k];
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

		//opens the .dat file
		file.open(infile);
		//reads each line, for the first three values (length, width and maxVal)
		file >> line;
		file >> line;
		setWidth(atoi(line.c_str()));
		file >> line;
		setHeight(atoi(line.c_str()));
		file >> line;
		maxVal = atoi(line.c_str());

		imgArr = new int **[height];
				for(int i = 0; i < height; i++){
					imgArr[i] = new int*[width];
					for(int j = 0; j < width; j++) imgArr[i][j] = (int*) new int[3];
				}
		orgArr = new int **[height];
						for(int i = 0; i < height; i++){
							orgArr[i] = new int*[width];
							for(int j = 0; j < width; j++) orgArr[i][j] = (int*) new int[3];
						}


		//until the end of the file, read the values into the new image array.
			for(int col = 0; col < getHeight(); col++)
					for(int row = 0; row < width; row++)
						for(int rgb = 0; rgb < 3; rgb++){
							file >> line;
							imgArr[col][row][rgb] = atoi(line.c_str());
						}

		for(int i = 0; i < height; i++)
					for(int j = 0; j < width; j++)
						for(int k = 0; k < 3; k++)
							orgArr[i][j][k] = imgArr[i][j][k];
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
			for(int j = 0; j < getWidth(); j++)
				for(int k = 0; k < 3; k++){
					//cout << imgArr[i][j][k] << ",";
					ofile << imgArr[i][j][k] << " ";
				}
			//cout << endl;
			ofile << endl;
		}
		ofile.close();


		system(("convert " + outfile + ".ppm " + outfile + ".png").c_str());
		return;
	}

