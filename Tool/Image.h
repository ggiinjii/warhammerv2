#pragma once
#include <string>
using namespace std;
class Image
{
private:
    string _fileName;
    int _resHeight;
    int _resWidth;

public :
    Image();
    Image(string filename, int height, int width);
    ~Image();

    string getFileName() { return _fileName; };
    int getHeight() { return _resHeight; };
    int getWidth() { return _resWidth; };

};

