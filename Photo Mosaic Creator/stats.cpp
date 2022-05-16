#include "stats.h"


#include "stats.h"

stats::stats(PNG & im){

/* Your code here!! */
// sumRed

sumRed.resize(im.width());
for (unsigned int i = 0;i < im.width(); i++) {
    sumRed[i].resize(im.height());
}

for (unsigned int x = 0; x < im.width(); x++) {
    long sum = 0;
    long v_sum = 0;
    for (unsigned int y = 0; y< im.height(); y++) {
        sum = sum + im.getPixel(x,y)->r;
        if (x != 0) {
            v_sum = sum + sumRed[x-1][y];
            sumRed[x][y] = v_sum;
        } else {
            sumRed[x][y] = sum;
        }
    }
}

// sumGreen
sumGreen.resize(im.width());
for (unsigned int i = 0;i < im.width(); i++) {
    sumGreen[i].resize(im.height());
}

for (unsigned int x = 0; x < im.width(); x++) {
    long sum = 0;
    long v_sum = 0;
    for (unsigned int y = 0; y< im.height(); y++) {
        sum = sum + im.getPixel(x,y)->g;
        if (x != 0) {
            v_sum = sum + sumGreen[x-1][y];
            sumGreen[x][y] = v_sum;
        } else {
            sumGreen[x][y] = sum;
        }
    }
}

// sumBlue
sumBlue.resize(im.width());
for (unsigned int i = 0;i < im.width(); i++) {
    sumBlue[i].resize(im.height());
}

for (unsigned int x = 0; x < im.width(); x++) {
    long sum = 0;
    long v_sum = 0;
    for (unsigned int y = 0; y< im.height(); y++) {
        sum = sum + im.getPixel(x,y)->b;
        if (x != 0) {
            v_sum = sum + sumBlue[x-1][y];
            sumBlue[x][y] = v_sum;
        } else {
            sumBlue[x][y] = sum;
        }
    }
}

// sumsqRed
sumsqRed.resize(im.width());
for (unsigned int i = 0;i < im.width(); i++) {
    sumsqRed[i].resize(im.height());
}

for (unsigned int x = 0; x < im.width(); x++) {
    long sum = 0;
    long v_sum = 0;
    for (unsigned int y = 0; y< im.height(); y++) {
        sum = sum + (im.getPixel(x,y)->r * im.getPixel(x,y)->r);
        if (x != 0) {
            v_sum = sum + sumsqRed[x-1][y];
            sumsqRed[x][y] = v_sum;
        } else {
            sumsqRed[x][y] = sum;
        }
    }
}

// sumsqGreen
sumsqGreen.resize(im.width());
for (unsigned int i = 0;i < im.width(); i++) {
    sumsqGreen[i].resize(im.height());
}

for (unsigned int x = 0; x < im.width(); x++) {
    long sum = 0;
    long v_sum = 0;
    for (unsigned int y = 0; y< im.height(); y++) {
        sum = sum + (im.getPixel(x,y)->g * im.getPixel(x,y)->g);
        if (x != 0) {
            v_sum = sum + sumsqGreen[x-1][y];
            sumsqGreen[x][y] = v_sum;
        } else {
            sumsqGreen[x][y] = sum;
        }
    }
}

// sumsqBlue
sumsqBlue.resize(im.width());
for (unsigned int i = 0;i < im.width(); i++) {
    sumsqBlue[i].resize(im.height());
}

for (unsigned int x = 0; x < im.width(); x++) {
    long sum = 0;
    long v_sum = 0;
    for (unsigned int y = 0; y< im.height(); y++) {
        sum = sum + (im.getPixel(x,y)->b * im.getPixel(x,y)->b);
        if (x != 0) {
            v_sum = sum + sumsqBlue[x-1][y];
            sumsqBlue[x][y] = v_sum;
        } else {
            sumsqBlue[x][y] = sum;
        }
    }
}
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
int br_first = ul.first + w;
int br_second = ul.second + h;
pair<int,int> bottom_right (br_first,br_second);
long sum = NULL;

if (channel == 'r') {
    long br = sumRed[bottom_right.first-1][bottom_right.second-1];
    if (ul.first == 0 && ul.second == 0) {
        sum = br;
    } else if (ul.first == 0) {
        long above = sumRed[ul.first+w-1][ul.second-1];
        sum = (br - above);
    } else if (ul.second == 0) {
        long left = sumRed[ul.first-1][ul.second+h-1];
        sum = (br-left);
    } else {
        long above = sumRed[ul.first+w-1][ul.second-1];
        long left = sumRed[ul.first-1][ul.second+h-1];
        long up_left = sumRed[ul.first-1][ul.second-1];
        sum = (br - above - left + up_left);
    }
} else if (channel == 'g') {
    long br = sumGreen[bottom_right.first-1][bottom_right.second-1];
    if (ul.first == 0 && ul.second == 0) {
        sum = br;
    } else if (ul.first ==0) {
        long above = sumGreen[ul.first+w-1][ul.second-1];
        sum = (br - above);
    } else if (ul.second == 0) {
        long left = sumGreen[ul.first-1][ul.second+h-1];
        sum = (br-left);
    } else {
        long above = sumGreen[ul.first+w-1][ul.second-1];
        long left = sumGreen[ul.first-1][ul.second+h-1];
        long up_left = sumGreen[ul.first-1][ul.second-1];
        sum = (br - above - left + up_left);
    }
} else if (channel == 'b') {
    long br = sumBlue[bottom_right.first-1][bottom_right.second-1];
    if (ul.first == 0 && ul.second == 0) {
        sum = br;
    } else if (ul.first ==0) {
        long above = sumBlue[ul.first+w-1][ul.second-1];
        sum = (br - above);
    } else if (ul.second ==0) {
        long left = sumBlue[ul.first-1][ul.second+h-1];
        sum = (br-left);
    } else {
        long above = sumBlue[ul.first+w-1][ul.second-1];
        long left = sumBlue[ul.first-1][ul.second+h-1];
        long up_left = sumBlue[ul.first-1][ul.second-1];
        sum = (br - above - left + up_left);
    }
}

return sum;
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
int br_first = ul.first + w;
int br_second = ul.second + h;
pair<int,int> bottom_right (br_first,br_second);
long sum = NULL;

if (channel == 'r') {
    long br = sumsqRed[bottom_right.first-1][bottom_right.second-1];
    if (ul.first == 0 && ul.second == 0) {
        sum = br;
    } else if (ul.first ==0) {
        long above = sumsqRed[ul.first+w-1][ul.second-1];
        sum = (br - above);
    } else if (ul.second == 0) {
        long left = sumsqRed[ul.first-1][ul.second+h-1];
        sum = (br-left);
    } else {
        long above = sumsqRed[ul.first+w-1][ul.second-1];
        long left = sumsqRed[ul.first-1][ul.second+h-1];
        long up_left = sumsqRed[ul.first-1][ul.second-1];
        sum = (br - above - left + up_left);
    }
} else if (channel == 'g') {
    long br = sumsqGreen[bottom_right.first-1][bottom_right.second-1];
    if (ul.first == 0 && ul.second == 0) {
        sum = br;
    } else if (ul.first ==0) {
        long above = sumsqGreen[ul.first+w-1][ul.second-1];
        sum = (br - above);
    } else if (ul.second==0) {
        long left = sumsqGreen[ul.first-1][ul.second+h-1];
        sum = (br-left);
    } else {
        long above = sumsqGreen[ul.first+w-1][ul.second-1];
        long left = sumsqGreen[ul.first-1][ul.second+h-1];
        long up_left = sumsqGreen[ul.first-1][ul.second-1];
        sum = (br - above - left + up_left);
    }
} else if (channel == 'b') {
    long br = sumsqBlue[bottom_right.first-1][bottom_right.second-1];
    if (ul.first == 0 && ul.second == 0) {
        sum = br;
    } else if (ul.first ==0) {
        long above = sumsqBlue[ul.first+w-1][ul.second-1];
        sum = (br - above);
    } else if (ul.second ==0) {
        long left = sumsqBlue[ul.first-1][ul.second+h-1];
        sum = (br-left);
    } else {
        long above = sumsqBlue[ul.first+w-1][ul.second-1];
        long left = sumsqBlue[ul.first-1][ul.second+h-1];
        long up_left = sumsqBlue[ul.first-1][ul.second-1];
        sum = (br - above - left + up_left);
    }
}

return sum;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
/* Your code here!! */
if (w==0 || h==0) {
    return 0;
}

double size = w*h;
double red_part = getSumSq('r', ul, w, h) - (getSum('r', ul, w, h)*getSum('r', ul, w, h)/size);
double green_part = getSumSq('g', ul, w, h) - (getSum('g', ul, w, h)*getSum('g', ul, w, h)/size);
double blue_part = getSumSq('b', ul, w, h) - (getSum('b', ul, w, h)*getSum('b', ul, w, h)/size);

return (red_part + green_part + blue_part);
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
/* Your code here!! */
if (w==0 || h==0) {
    return RGBAPixel(0,0,0); 
}

double size = w*h;
long red = getSum ('r', ul, w, h)/size;
long green = getSum ('g', ul, w, h)/size;
long blue = getSum ('b', ul, w, h)/size;

return RGBAPixel(red,green,blue);
}
