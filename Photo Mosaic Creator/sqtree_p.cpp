/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  // Your code here.
  stats s(imIn);
  pair<int,int> ul(0,0);
  root = buildTree(s,ul,imIn.width(),imIn.height(),tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  // Your code here.
  if(w==0 || h ==0){
    return NULL;
  }
  if(w==1 && h == 1){
    SQtree :: Node * newNode1 = new Node(ul,w,h,s.getAvg(ul,w,h),0);
    return newNode1;
  }

  if(s.getVar(ul,w,h)<=tol) {
    SQtree :: Node * newNode2 = new Node(ul,w,h,s.getAvg(ul,w,h),s.getVar(ul,w,h));
    return newNode2;
  }
  
  
  
  double min = -1;
  double bestx = ul.first;
  double besty = ul.second;
  for( int x = 0; x < w;x++){
    for( int y = 0; y<h;y++){
      if( x!=0 || y!=0){
        double a = s.getVar(ul,x,y);//NW
        pair<int,int> ulb(ul.first+x,ul.second); 
        double b = s.getVar(ulb,w-x,y);//NE
        pair<int,int> ulc(ul.first,ul.second+y); 
        double c = s.getVar(ulc,x,h - y);//SW
        pair<int,int> uld(ul.first+x,ul.second+y); 
        double d = s.getVar(uld,w-x,h-y);//SE
        double max = fmax(a,b);
        max = fmax(max,c);
        max = fmax(max,d);

        if (min == -1 || max < min) {
            min = max;
            bestx = x;
            besty = y;      
      }
   }
  }
}

    SQtree :: Node* newNode = new Node(ul,w,h,s.getAvg(ul,w,h),s.getVar(ul,w,h));
    newNode->NW = buildTree(s,ul,bestx,besty,tol);
    pair<int,int>  ulbb(ul.first+bestx,ul.second);
    pair<int,int>  ulbc(ul.first,ul.second+besty);
    pair<int,int>  ulbd(ul.first+bestx,ul.second+besty);
    newNode->NE = buildTree(s,ulbb,w-bestx,besty,tol);
    newNode->SW = buildTree(s,ulbc,bestx,h - besty,tol);
    newNode->SE = buildTree(s,ulbd,w-bestx,h - besty,tol);
    return newNode;
}
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  // Your code here.
  PNG im(root->width,root->height);
  render(im,root);
  return im;
} 

void SQtree::render(PNG& im1, Node* n){
 if (n != NULL) { 
  if (n->NW == NULL && n->NE == NULL && n->SW == NULL && n->SE == NULL) {
    for( int i = n->upLeft.first; i < n->upLeft.first+n->width;i++) {
      for( int j = n->upLeft.second; j<n->upLeft.second+n->height;j++){
        RGBAPixel* pixel = im1.getPixel(i,j);
        *pixel = n -> avg;
      }
    }

  } else {
    render(im1,n->NW);
    render(im1,n->NE);
    render(im1,n->SW);
    render(im1,n->SE);
  }
  }
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  // Your code here.
  clear(root);
}
void SQtree::clear(Node* &curr){
  if(curr != NULL) {
    clear(curr->NW);
    clear(curr->NE);
    clear(curr->SW);
    clear(curr->SE);
    delete curr;
    curr = NULL;
  }  
}

void SQtree::copy(const SQtree & other) {
  // Your code here.
  root = copy(other.root);
}

SQtree::Node* SQtree::copy(const Node* curr) {
  // Your code here.
  SQtree :: Node* temp = NULL;
  if(curr != NULL) {
    SQtree :: Node* temp = new Node(curr->upLeft,curr->width,curr->height,curr->avg,curr->var);
    temp->NW = copy(curr->NW);
    temp->NE = copy(curr->NE);
    temp->SW = copy(curr->SW);
    temp->SE = copy(curr->SE);
    return temp;
  }
   return temp;
}

int SQtree::size(){
  return size(root);
}


int SQtree::size(const Node*  curr) {
  // Your code here.
  if(curr != NULL) {
    return 1 + size(curr->NW) + size(curr->NE) + size(curr->SW) + size(curr->SE);
  } else{
    return 0;
  }
}

