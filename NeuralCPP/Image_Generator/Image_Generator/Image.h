#include <vector>
#include <ctime>
#include <sstream>
#include "BMP.h"

using namespace std;

void delay(int seconds) {//added due to random number for color being tied to time
    time_t start, current;

    time(&start);

    do{
        time(&current);
    } while ((current - start) < seconds);
}

struct RGB {//generates color in the given space
public:
    RGB(int px, int py, int s, int d);//s is seed
    int rgb[4];//red, green, blue, alpha
    int pos[2];//position x, position y
private:
};

RGB::RGB(int px, int py, int s, int d) {
    //srand(time(NULL) /*+ (s * d)*/);
    for (int i = 0; i < 4; i++) {//3 times for R, G, B
        rgb[i] = rand() % 255;
    }
    rgb[3] = 255;//default alpha
    pos[0] = px;
    pos[1] = py;
}

RGB generate(int xy[2], int i, int s) {//after delay, generate colored square in region
    delay(1);//due to c++ random number generation
    return RGB(xy[0], xy[1], i, s);
}

typedef vector<RGB> img;//stores 4 rgb squares in an image

struct Image {
public:
    vector<img> i_img;//for creating multiple images
    Image(const int g);
    void MakeImage(int im, const char* name);
    void ReadImage();
};

Image::Image(const int gen) {

    for (int g = 0; g < gen; g++) {
        i_img.push_back(img());//add image to images array
        for (int c = 0; c < 4; c++) {//add 4 colors to image
            int xy[2] = { 0, 0 };

            if (c == 0) { xy[0] = 0; xy[1] = 50; }
            else if (c == 1) { xy[0] = 50; xy[1] = 50; }
            else if (c == 2) { xy[0] = 50; xy[1] = 0; }
            else if (c == 3) { xy[0] = 0; xy[1] = 0; }

            i_img.back().push_back(generate(xy, gen * g, c));
        }
        cout << "Image: " << g << " | part's made: " << i_img[g].size() << endl;

        for (int c = 0; c < 4; c++) {//display what colors are being made
            cout << "red: " << i_img[g][c].rgb[0] << " | ";
            cout << "green: " << i_img[g][c].rgb[1] << " | ";
            cout << "blue: " << i_img[g][c].rgb[2] << " | ";
            cout << "position: x " << i_img[g][c].pos[0] << " y " << i_img[g][c].pos[1] << " | ";
            cout << endl;
        }

        //create file name
        std::string s = "image";
        s.append(std::to_string(g));
        s.append(".bmp");
        char const* name = s.c_str();
        //const char * name = ch + "img_test.jpg";
        cout << name << endl;

        //make file
        MakeImage(g, name);
    }

    cout << "# of images: " << i_img.size() << endl;
}

void Image::MakeImage(int im, const char* name) {
    //create BMP in memory
    BMP bmp2(100, 100, false);//width, height alpha(boolean)

    //modify bmp
    //bmp.fill_region(0, 0, 50, 50, 51, 102, 255, 255);//padding left, padding bottom, width, height, Red, Green, Blue, alpha 
    for (int rgb = 0; rgb < 4; rgb++) {

        bmp2.fill_region(i_img[im][rgb].pos[0], i_img[im][rgb].pos[1], 50, 50, i_img[im][rgb].rgb[0], i_img[im][rgb].rgb[1], i_img[im][rgb].rgb[2], 0);//padding left, padding bottom, width, height, Red, Green, Blue, alpha
    }

    //write bmp
    bmp2.write(name);

    /*
    
    
    */
}

void Image::ReadImage() {
    //read bmp
    BMP bmp("image8.bmp");
    //cout << bmp.data.size;
    bmp.write("image9");
}