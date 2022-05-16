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
	stats s(imIn);
  pair<int, int> ul (0, 0);
	root = buildTree(s, ul, imIn.width(), imIn.height(), tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  Node* newNode;
  double var = s.getVar(ul, w, h);
	if (w==0 || h==0){
    return NULL;
  } else if((w==1 && h==1)){
		newNode = new Node(ul, w, h, s.getAvg(ul, w, h), 0);
		return newNode;
	} else if(var <= tol) {
    newNode = new Node(ul, w, h, s.getAvg(ul, w, h), var);
		return newNode;
  }
  double minVar = -1;
  int horizontal = ul.first;
  int vertical = ul.second;
  for(int i = 0; i < w; i++) {
    for(int j = 0; j < h; j++) {
      if(i != 0 || j != 0) {
        double nwVar = s.getVar(ul, i, j);
        double swVar = s.getVar(pair<int,int>(ul.first, ul.second+j), i, h-j);
        double neVar = s.getVar(pair<int,int>(ul.first+i, ul.second), w-i, j);
        double seVar = s.getVar(pair<int,int>(ul.first+i, ul.second+j), w-i, h-j);
        double maxVar = findMax(nwVar, swVar, neVar, seVar);
        if(maxVar < minVar || minVar == -1){
          minVar = maxVar;
          horizontal = i;
          vertical = j;
        }
      }
    }
  }
  pair<int, int> swul (ul.first, ul.second+vertical);
  pair<int, int> neul (ul.first+horizontal, ul.second);
  pair<int, int> seul (ul.first+horizontal, ul.second+vertical);

  newNode = new Node(ul, w, h, s.getAvg(ul, w, h), var);
  newNode->NW = buildTree(s, ul, horizontal, vertical, tol);
	newNode->SW = buildTree(s, swul, horizontal, h-vertical, tol);
  newNode->NE = buildTree(s, neul, w-horizontal, vertical, tol);
	newNode->SE = buildTree(s, seul, w-horizontal, h-vertical, tol);
	return newNode;
}
double SQtree::findMax(double a, double b, double c, double d) {
  if(a>b){
    //a>b
    if(a>c){
      //a>bc
      if(a>d) return a;
      else return d;
    } else {
      //c>ab
      if(c>d) return c;
      else return d;
    }
  } else {
    //b>a
    if(b>c){
      //b>ac
      if(b>d) return b;
      else return d;
    } else {
      //c>ab
      if(c>d) return c;
      else return d;
    }
  }
}
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  PNG im(root->width, root->height);
	render(im, root);
	return im;
}
void SQtree::render(PNG& im, Node* root){
	if(root != NULL){
      if(root->NW == NULL && root->NE == NULL && root->SW == NULL && root->SE == NULL){
      for(int i = root->upLeft.first; i < root->upLeft.first+root->width; i++){
        for(int j = root->upLeft.second; j < root->upLeft.second+root->height; j++){
          RGBAPixel *pix = im.getPixel(i, j);
          *pix = root->avg;
        }
      }
    } else {
      render(im, root->NW);
      render(im, root->NE);
      render(im, root->SW);
      render(im, root->SE);
    }
  }
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  clear(root);
}
void SQtree::clear(Node * & curr) {
	if(curr != NULL){
    clear(curr->NW);
    clear(curr->NE);
    clear(curr->SW);
    clear(curr->SE);
	  delete curr;
	}
}

void SQtree::copy(const SQtree & other) {
  copy(root);
}
SQtree::Node* SQtree::copy(const Node * curr){
	Node* temp = NULL;
  if(curr != NULL){
    temp = new Node(curr->upLeft, curr->width, curr->height, curr->avg, curr->var);
		temp->NW = copy(curr->NW);
		temp->NE = copy(curr->NE);
    temp->SW = copy(curr->SW);
		temp->SE = copy(curr->SE);
	}
	return temp;
}

int SQtree::size() {
  return size(root);
}
int SQtree::size(const Node * curr) {
  if(curr != NULL) 
    return 1+size(curr->NW)+size(curr->NE)+size(curr->SW)+size(curr->SE);
  else
    return 0;
}
