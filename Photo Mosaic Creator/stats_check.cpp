#include "stats.h"


#include "stats.h"

stats::stats(PNG & im){

/* Your code here!! */
    vector<long> blank;
    
    for (unsigned int y = 0; y < im.height(); y++) {
        blank.push_back(0);
    }
    
    for (unsigned int x = 0; x < im.width(); x++) {
        sumRed.push_back(blank);
        sumGreen.push_back(blank);
        sumBlue.push_back(blank);
        sumsqRed.push_back(blank);
        sumsqGreen.push_back(blank);
        sumsqBlue.push_back(blank);
        red.push_back(blank);
        green.push_back(blank);
        blue.push_back(blank);
    }
    
//    vector< vector< long >> red(im.width(), vector<long> (im.height(), 0));
//    vector< vector< long >> blue(im.width(), vector<long> (im.height(), 0));
//    vector< vector< long >> green(im.width(), vector<long> (im.height(), 0));
    
    
//    RGBAPixel *pix_zero = im.getPixel(0,0);
//    sumRed[0][0] = pix_zero->r;
//    sumGreen[0][0] = pix_zero->g;
//    sumBlue[0][0] = pix_zero->b;
//    sumsqRed[0][0] = (sumRed[0][0])^2;
//    sumsqGreen[0][0] = (sumGreen[0][0])^2;
//    sumsqBlue[0][0] = (sumBlue[0][0])^2;
    
    
    for(int i=0; i<(int)im.width(); i++) {
        for (int j=0; j<(int)im.height(); j++) {
            RGBAPixel *pix = im.getPixel(i,j);
            red[i][j] = pix->r;
            green[i][j] = pix->g;
            blue[i][j] = pix->b;
            cout<<"r at ("<<i<<","<<j<<") is "<<red[i][j]<<endl;
            cout<<"g at ("<<i<<","<<j<<") is "<<green[i][j]<<endl;
        }
    }
    
    for(int i=0; i<(int)im.width(); i++) {
        for (int j=0; j<(int)im.height(); j++) {
            sumRed[i][j] = startSum(red, i, j);
            sumBlue[i][j] = startSum(blue, i, j);
            sumGreen[i][j] = startSum(green, i, j);
            cout<<"sum g at ("<<i<<","<<j<<") is "<<sumGreen[i][j]<<endl;
        }
    }
    
    for(int i=0; i<(int)im.width(); i++) {
        for (int j=0; j<(int)im.height(); j++) {
            sumsqRed[i][j] = startSq(red, i, j);
            sumsqBlue[i][j] = startSq(blue, i, j);
            sumsqGreen[i][j] = startSq(green, i, j);
            //cout<<"sq r at ("<<i<<","<<j<<") is "<<sumsqRed[i][j]<<endl;
        }
    }
    
             
            
//            sumRed[i][j] = getSum(r, make_pair(0,0), i, j);
//            sumGreen[i][j] = getSum(g, make_pair(0,0), i, j);
//            sumBlue[i][j] = getSum(b, make_pair(0,0), i, j);
//            sumsqRed[i][j] = getSumSq(r, make_pair(0,0), i, j);
//            sumsqGreen[i][j] = getSumSq(g, make_pair(0,0), i, j);
//            sumsqBlue[i][j] = getSumSq(b, make_pair(0,0), i, j);

}

long stats::startSum(vector<vector<long>> vec, int w, int h) {
    //cout<<__LINE__<<endl;
    long sum = 0;
    for (int i=0; i<=w; i++) {
        for (int j=0; j<=h; j++) {
            sum = sum + vec[i][j];
        }
    }
//    while (i != w) {
//        while (j != h) {
//            cout<<"helper fn r at ("<<i<<","<<j<<") is "<<vec[i][j]<<endl;
//            sum = sum + vec[i][j];
//            cout<<"sum at ("<<i<<","<<j<<") is "<<sum<<endl;
//            j++;
//        }
//        i++;
//    }
    return sum;
}

long stats::startSq(vector<vector<long>> vec, int w, int h) {
    
    long sum = 0;
    for (int i=0; i<=w; i++) {
        for (int j=0; j<=h; j++) {
            sum = sum + pow(vec[i][j], 2);
        }
    }
    return sum;
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    
    int x = ul.first;
    int y = ul.second;
    cout<<x<<endl;
    cout<<y<<endl;
    cout<<w<<endl;
    cout<<h<<endl;
    if (channel == 'r') {
        if (x==0 && y==0) {
            return sumRed[x+w-1][y+h-1];
        } else if (x == 0) {
            return sumRed[x+w-1][y+h-1] - sumRed[x+w-1][y-1];
        } else if (y == 0) {
            return sumRed[x+w-1][y+h-1] - sumRed[x-1][y+h-1];
        } else {
            return sumRed[x+w-1][y+h-1]-sumRed[x-1][y+h-1]-sumRed[x+w-1][y-1]+sumRed[x-1][y-1];
        }
        
    } else if (channel == 'g') {
          if (x==0 && y==0) {
            return sumGreen[x+w-1][y+h-1];
        } else if (x == 0) {
            return sumGreen[x+w-1][y+h-1] - sumGreen[x+w-1][y-1];
        } else if (y == 0) {
            return sumGreen[x+w-1][y+h-1] - sumGreen[x-1][y+h-1];
        } else {
            return sumGreen[x+w-1][y+h-1]-sumGreen[x-1][y+h-1]-sumGreen[x+w-1][y-1]+sumGreen[x-1][y-1];
        }
    } else {
         if (x==0 && y==0) {
            return sumBlue[x+w-1][y+h-1];
        } else if (x == 0) {
            return sumBlue[x+w-1][y+h-1] - sumBlue[x+w-1][y-1];
        } else if (y == 0) {
            return sumBlue[x+w-1][y+h-1] - sumBlue[x-1][y+h-1];
        } else {
            return sumBlue[x+w-1][y+h-1]-sumBlue[x-1][y+h-1]-sumBlue[x+w-1][y-1]+sumBlue[x-1][y-1];
        }
    }
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    int x = ul.first;
    int y = ul.second;
    
    if (channel == 'r') {
        if (x==0 && y==0) {
            return sumsqRed[x+w-1][y+h-1];
        } else if (x == 0) {
            return sumsqRed[x+w-1][y+h-1] - sumsqRed[x+w-1][y-1];
        } else if (y == 0) {
            return sumsqRed[x+w-1][y+h-1] - sumsqRed[x-1][y+h-1];
        } else {
            return sumsqRed[x+w-1][y+h-1]-sumsqRed[x-1][y+h-1]-sumsqRed[x+w-1][y-1]+sumsqRed[x-1][y-1];
        }
    } else if (channel == 'g') {
        if (x==0 && y==0) {
            return sumsqGreen[x+w-1][y+h-1];
        } else if (x == 0) {
            return sumsqGreen[x+w-1][y+h-1] - sumsqGreen[x+w-1][y-1];
        } else if (y == 0) {
            return sumsqGreen[x+w-1][y+h-1] - sumsqGreen[x-1][y+h-1];
        } else {
            return sumsqGreen[x+w-1][y+h-1]-sumsqGreen[x-1][y+h-1]-sumsqGreen[x+w-1][y-1]+sumsqGreen[x-1][y-1];
        }
    } else {
        if (x==0 && y==0) {
            return sumsqBlue[x+w-1][y+h-1];
        } else if (x == 0) {
            return sumsqBlue[x+w-1][y+h-1] - sumsqBlue[x+w-1][y-1];
        } else if (y == 0) {
            return sumsqBlue[x+w-1][y+h-1] - sumsqBlue[x-1][y+h-1];
        } else {
            return sumsqBlue[x+w-1][y+h-1]-sumsqBlue[x-1][y+h-1]-sumsqBlue[x+w-1][y-1]+sumsqBlue[x-1][y-1];
        }
    } 
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
/* Your code here!! */
    
    double size = ((double)w)*((double)h);
    double sumSqR = (double) getSumSq('r', ul, w, h);
    double sumSqG = (double) getSumSq('g', ul, w, h);
    double sumSqB = (double) getSumSq('b', ul, w, h);
    cout<<"sum of r^2 is "<<sumSqR<<endl;
    cout<<"sum of g^2 is "<<sumSqG<<endl;
    cout<<"sum of b^2 is "<<sumSqB<<endl;
    double sumR = (double) getSum('r', ul, w, h);
    double sumG = (double) getSum('g', ul, w, h);
    double sumB = (double) getSum('b', ul, w, h);
    cout<<"sum r is "<<sumR<<endl;
    cout<<"sum g is "<<sumG<<endl;
    cout<<"sum b is "<<sumB<<endl;
    double sqSumR = pow(sumR, 2);
    double sqSumG = pow(sumG, 2);
    double sqSumB = pow(sumB, 2);
    cout<<"sqr of sum r is "<<sumR<<endl;
    cout<<"sqr of sum g is "<<sumG<<endl;
    cout<<"sqr of sum b is "<<sumB<<endl;
    if (size != 0) {
        double varR = sumSqR - sqSumR/size;
        double varG = sumSqG - sqSumG/size;
        double varB = sumSqB - sqSumB/size;
        cout<<"var of sum r is "<<varR<<endl;
        cout<<"var of sum g is "<<varG<<endl;
        cout<<"var of sum b is "<<varB<<endl;
        return varR+varG+varB;
    } else {
        return 0;
    }
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
/* Your code here!! */
    long r = getSum('r', ul, w, h);
    long g = getSum('g', ul, w, h);
    long b = getSum('b', ul, w, h);
    cout<<"sum r is "<<r<<endl;
    cout<<"sum g is "<<g<<endl;
    cout<<"sum b is "<<b<<endl;
    long size = ((long)w)*((long)h);
    if (size != 0) {
        long avgR = r/size;
        long avgG = g/size;
        long avgB = b/size;
        cout<<"avg r is "<<avgR<<endl;
        cout<<"avg g is "<<avgG<<endl;
        cout<<"avg b is "<<avgB<<endl;
        return RGBAPixel(avgR, avgG, avgB); 
    } else {
        return RGBAPixel(0, 0, 0);
    }
}
