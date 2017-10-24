using namespace std;

class IMAGE{
private:
	int width, height;
	int ***imgArr;
	int ***orgArr;
public:
	IMAGE();

	IMAGE(string input_file);
	IMAGE(int height_, int width_);

	~IMAGE();

	int getWidth();
	void setWidth(int w);

	int getHeight();
	void setHeight(int h);

	void getImagePixel(int col, int row, int arr[]);
	void setImagePixel(int col, int row, int* pixel);

	void toGrayscale();
	void flipHorizontal();
	void negateBlue();
	void flattenRed();

	void reset();

	int read(string infile);
	void write(string outfile);
};
