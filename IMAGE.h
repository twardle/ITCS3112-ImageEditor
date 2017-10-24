using namespace std;

class IMAGE{
private:
	int width, height;
public:
	IMAGE();

	int **imgArr;

	IMAGE(string input_file);
	IMAGE(int height_, int width_);

	~IMAGE();

	int getWidth();
	void setWidth(int w);

	int getHeight();
	void setHeight(int h);

	void getImagePixel(int col, int row, int arr[]);
	void setImagePixel(int col, int row, int* pixel);

	int read(string infile);
	void write(string outfile);
};
