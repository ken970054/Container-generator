#ifndef _OODESIGN_H
#define _OODESIGN_H

#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;

typedef long long int lli;
const int max_range = 2000000000;
const int max_range_per_rect = 10;
//const int Rect_num = 10000;
const int Rect_num = 100;

/////////////////////
// Rectangle class //
/////////////////////
struct Rectangle {
    int x1, y1, x2, y2;
};

//bool operator<(const Rectangle &r1, const Rectangle &r2) {
//    return r1.y1 < r2.y1;
//}

//std:ostream &operator<<(std::ostream &str, const Rectange &r) {
//    return str << '(' << r.x1 << ", " << r.x2 ')';
//}

//////////////////////////////////
// Area calculation(base class) //
//////////////////////////////////

// base class needs to declare before derived class
class Area_Calculation {

    int total_area = 0;

    int overlapping_area = 0;
    map<int, int> overlapping_area_map;

    int total_covered_area = 0;
public:
    virtual size_t get_num_rects(void) = 0;
    virtual const Rectangle& get_rect(size_t n) = 0;

    int total_rect_area();

    //// overlapping area function ////
    void calculate_overlapping_area(struct Rectangle, vector<struct Rectangle>, int);
    // for sort vector use(need to define to static, why??)
    static bool compareRectY1(struct Rectangle R1, struct Rectangle R2) { return R1.y1 < R2.y1; }
    // main overlapping rect area function which use calculate_overlapping_area() to implement recursion to calculate different level of overlapping area
    int overlapping_rect_area();

    int total_rect_covered_area();
};

///////////////////////////
// Container with vector //
///////////////////////////
class PolyContainer_vector: public Area_Calculation {
    vector<struct Rectangle> polygons;
public:
    void Gen_Rect_vector (int,int);

    // define get_num_rects from base class virtual function
    size_t get_num_rects(void) {
        size_t num = polygons.size();
        return num;
    }

    // define get_rect from base class virtual function
    const Rectangle& get_rect(size_t n) {
        return polygons[n];
    }

};

/////////////////////////
// Container with list //
/////////////////////////
class PolyContainer_list : public Area_Calculation {
    list<struct Rectangle> polygons;
    list<struct Rectangle>::iterator polygons_itr;

public:
    void Gen_Rect_list (int,int);

    // define get_num_rects from base class virtual function
    size_t get_num_rects(void) {
        size_t num = polygons.size();
        return num;
    }

    // define get_rect from base class virtual function
    const Rectangle& get_rect(size_t n) {
        polygons_itr = polygons.begin();
        auto current_item = next(polygons_itr, n);
        return *current_item;
    }
};

#endif
