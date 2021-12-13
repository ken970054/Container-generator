#ifndef _STLDESIGN_CLASS_H
#define _STLDESIGN_CLASS_H

#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
const int max_range = 2000000000;
const int max_range_per_rect = 10;
//const int Rect_num = 10000;
const int Rect_num = 100;

///////////////////////////
// Container with vector //
///////////////////////////
class PolyContainer_vector {
    vector<struct Rectangle> polygons;
public:
    vector<struct Rectangle>::iterator begin() { return polygons.begin(); }
    vector<struct Rectangle>::iterator end() { return polygons.end(); }

    int get_polygons_size() { return polygons.size(); }

    void Gen_Rect_vector (int,int);
};

/////////////////////////
// Container with list //
/////////////////////////
class PolyContainer_list {
    list<struct Rectangle> polygons;
public:
    list<struct Rectangle>::iterator begin() { return polygons.begin(); }
    list<struct Rectangle>::iterator end() { return polygons.end(); }

    int get_polygons_size() { return polygons.size(); }

    void Gen_Rect_list(int,int);
};

#endif
