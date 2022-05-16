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
  pair<int,int> ul (0,0);
  root = buildTree(s,ul,imIn.width(),imIn.height(),tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  // Your code here.
  if (w==0 || h==0) {
    return NULL;
  }

  if (w==1 && h==1) {
    Node* one_pixel = new Node(ul,1,1,s.getAvg(ul,1,1),0);
    return one_pixel;
  }

  if (s.getVar(ul,w,h) < tol) {
    Node* accepted = new Node(ul,w,h,s.getAvg(ul,w,h),s.getVar(ul,w,h));
    return accepted;
  }

  double  min_var = -1;
  double best_hori = ul.first;
  double best_ver = ul.second;

  for (int horizontal = 0; horizontal<w; horizontal++){
    for (int vertical = 0; vertical<h; vertical++) {
      if (horizontal !=0 || vertical != 0) {
        double NW_var = s.getVar(ul,horizontal,vertical);
        
        double NE_var = s.getVar(pair<int,int>(ul.first+horizontal, ul.second), w-horizontal, vertical);
        
        double SW_var = s.getVar(pair<int,int>(ul.first, ul.second+vertical), horizontal, h-vertical);
        
        double SE_var = s.getVar(pair<int,int>(ul.first+horizontal, ul.second+vertical), w-horizontal, h-vertical);

        double max;
        max= fmax(NW_var,NE_var);
        max= fmax(max,SW_var);
        max= fmax(max,SE_var);

        if(max<min_var || min_var == -1) {
          min_var = max;
          best_hori = horizontal;
          best_ver = vertical;
        }
      }
    }
  }

  Node* newNode = new Node(ul,w,h,s.getAvg(ul,w,h),s.getVar(ul,w,h));

  newNode -> NW = buildTree (s, ul, best_hori, best_ver, tol);

  pair<int, int> NE_ul (ul.first+best_hori, ul.second);
  newNode -> NE = buildTree (s, NE_ul, (w-best_hori),best_ver, tol);

  pair<int, int> SW_ul (ul.first, ul.second+best_ver);
  newNode -> SW = buildTree (s, SW_ul, best_hori, (h-best_ver), tol);

  pair<int, int> SE_ul (ul.first+best_hori, ul.second+best_ver);
  newNode -> SE = buildTree (s, SE_ul, (w-best_hori), (h-best_ver), tol);

  return newNode;
}
  
// /**
//  * Render SQtree and return the resulting image.
//  */
// PNG SQtree::render() {
//   // Your code here.
//   int w = root->width;
//   int h = root->height;
//   PNG image (w,h);
//   render(image,root);
//   return image;
// }


// void SQtree::render(PNG& im, Node* root) {
//   if (root -> NW == NULL && root->NE == NULL && root->SW==NULL && root->SE == NULL) {
//     for (int i = root->upLeft.first; i < root->upLeft.first+(root->width); i++) {
//       for (int j = root->upLeft.second; j < root->upLeft.second+(root->height); j++) {
//       RGBAPixel* pixel = im.getPixel(i,j);
//         *pixel = root -> avg;
//       }
//     }
//   } else {
//     if(root -> NW != NULL) {
//       render(im, root -> NW);
//     }

//     if (root -> NE != NULL) {
//       render(im, root -> NE);
//     }

//     if (root -> SW != NULL) {
//       render(im, root -> SW);
//     }

//     if (root -> SE != NULL) {
//       render(im, root -> SE);
//     } 
//   } 
// }

// /**
//  * Delete allocated memory.
//  */
// void SQtree::clear() {
//   // Your code here.
//   clear(root);
// }

// void SQtree::clear(Node*& curr) {
//   if (curr != NULL) {
//     clear(curr-> NW);
//     clear(curr-> NE);
//     clear(curr-> SE);
//     clear(curr-> SW);
//     delete curr;
//     curr = NULL;
//   } 
// }

// void SQtree::copy(const SQtree & other) {
//   // Your code here.
//   copy(other.root);
// }

// SQtree::Node* SQtree::copy(const Node* curr) {
//   if (curr != NULL) {
//     Node* temp = new Node(curr->upLeft, curr->width, curr->height, curr->avg, curr->var);
//     temp -> NW = copy(temp -> NW);
//     temp -> NE = copy(temp -> NE);
//     temp -> SE = copy(temp -> SE);
//     temp -> SW = copy(temp -> SW);
//     return temp;
//   } else {return NULL;}
// }

// int SQtree::size() {
//   // Your code here.
//   return size(root);
// }

// int SQtree::size(const Node* curr) {
//   if (curr != NULL) {
//     return 1 + size(curr->NW)+ size(curr->SE) + size(curr->NE) + size(curr->SW);
//   } else {
//     return 0;
//   }
// }

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

