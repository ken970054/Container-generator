#include "container_OO_design.h"

#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

/////////////////////////////////
//// Area calculation define ////
/////////////////////////////////

//// total_area implementation ////
int Area_Calculation::total_rect_area() {
    int weight{0}, height{0};
    struct Rectangle R;
    for (size_t i = 0; i < get_num_rects(); i++) {
        R = get_rect(i);
        weight = R.x2 - R.x1;
        height = R.y2 - R.y1;
        total_area = total_area + weight*height;
    }

    return total_area;
}

//// overlapping_area implementation ////
// calculating overlapping area function for recursion
void Area_Calculation::calculate_overlapping_area(struct Rectangle current_R, vector<struct Rectangle> Rects, int level) {
    //cout << "x1, y1, x2, y2 = " << current_R.x1 << ", " << current_R.y1 << ", " << current_R.x2 << ", " << current_R.y2 << endl;
    if (Rects.empty()) { return; }
    level++;

    struct Rectangle cur;
    cur = current_R;

    int area;

    // Rects has only one R left
    if (Rects.size() == 1) {
        if (cur.y2 > Rects[0].y1) {
            //cout << "level = " << level << endl;
            if (cur.y2 > Rects[0].y2) {
                area = (Rects[0].y2 - Rects[0].y1) * (cur.x2 - cur.x1);
            }
            else {
                area = (cur.y2 - Rects[0].y1) * (cur.x2 - cur.x1);
            }
            if (overlapping_area_map.count(level)) { // key level is present
                overlapping_area_map[level] = overlapping_area_map[level] + area;
            }
            else {
                overlapping_area_map[level] = area;
            }
            return;
        }
        else {
            return;
        }
		}

// Rects has more than 1 R
    vector<struct Rectangle>::iterator R_iter;

    for (R_iter = Rects.begin(); R_iter != Rects.end();) {
        if (cur.y2 > (*R_iter).y1) { // has overlapped
            //cout << "level = " << level << endl;
            struct Rectangle overlapping_rect;
            if (cur.y2 > (*R_iter).y2) { //enclosed overlap
                area = ((*R_iter).y2 - (*R_iter).y1) * (cur.x2 - cur.x1);
                overlapping_rect = {
                    cur.x1,
                    (*R_iter).y1,
                    cur.x2,
                    (*R_iter).y2
                };
            }
            else { // not enclosed overlap
                area = (cur.y2 - (*R_iter).y1) * (cur.x2 - cur.x1);
                overlapping_rect = {
                    cur.x1,
                    (*R_iter).y1,
                    cur.x2,
                    cur.y2
                };
            }
            //check if the overlapping level has existed
            if (overlapping_area_map.count(level)) { // key level is present
                overlapping_area_map[level] = overlapping_area_map[level] + area;
            }
            else {
                overlapping_area_map[level] = area;
            }

						// erase first R of Rects in each iteration
            R_iter = Rects.erase(R_iter);
            // call recursive function
            this->calculate_overlapping_area(overlapping_rect, Rects, level);
        }
        else {
            break;
        }
    }
    return;
}

int Area_Calculation::overlapping_rect_area() {

    overlapping_area = 0;
    int num_rects = get_num_rects();

    vector<struct Rectangle> Rects; // for calculating use
    Rects.reserve(num_rects);

    // unique all X coordinates //
    vector<int> uniqueX;
    uniqueX.reserve(num_rects * 2);
    struct Rectangle R;
    for (size_t i = 0; i < get_num_rects(); i++) {
        R = get_rect(i);

        Rects.push_back(R);
        uniqueX.push_back(R.x1);
        uniqueX.push_back(R.x2);
    }
    sort(uniqueX.begin(), uniqueX.end());
    vector<int>::iterator uniItr = unique(uniqueX.begin(), uniqueX.end());
    uniqueX.erase(uniItr, uniqueX.end());

		// Split all rects on X coordinates //
    for (const auto &x: uniqueX) {
        vector<struct Rectangle> processing_R;

        for (const auto &R: Rects) {
            //split recent Rect into two at X
            if (R.x1 >= x || R.x2 <= x) { // X is on or out of current Rect -> don't need to split
                processing_R.push_back(R);
                continue;
            }

            // create two Rectangle structure and please note the order of member should follow (x1, y1, x2, y2)
            struct Rectangle R_left = {
                R.x1,
                R.y1,
                x,
                R.y2,
            };
            struct Rectangle R_right= {
                x,
                R.y1,
                R.x2,
                R.y2,
            };
            processing_R.push_back(R_left);
            processing_R.push_back(R_right);
        }

        Rects = processing_R;
    }

		// start to calculate the overlapping area in different level //
    // calculate all rectangles that have same x1 and x2
    for (const auto &x: uniqueX) {
        // find Rect.x1 locate on x and store into vector
        vector<struct Rectangle> sameWidthRects;
        for (const auto &R: Rects) {
            if (x == R.x1) sameWidthRects.push_back(R);
        }

        // sort sameWidthRects by y1 (ascending order)
        sort(sameWidthRects.begin(), sameWidthRects.end(), compareRectY1);

        //for (const auto &R: sameWidthRects) {
        //  cout << "sameWidthRects sorted: x1 = " << R.x1 << " ,y1 = " << R.y1 << " ,x2 = " << R.x2 << " ,y2 = " << R.y2 << endl;
        //}
        if (sameWidthRects.size() <= 1) { continue; }
        int level = 1;
        vector<struct Rectangle>::iterator R_iter;
        for (R_iter = sameWidthRects.begin(); R_iter != sameWidthRects.end();) {
            struct Rectangle current_R = *R_iter;
            R_iter = sameWidthRects.erase(R_iter);
            calculate_overlapping_area(current_R, sameWidthRects, level);
        }

    }

		// calaulating every level of overlapping area -> area(level 2) - area(level 3) + area(level 4) - area(level 5) ... (inclusion-exclusion principle)
    for (auto iter = overlapping_area_map.begin(); iter != overlapping_area_map.end(); iter++) {
        if (iter->first % 2 == 0) {
            overlapping_area = overlapping_area + iter->second;
        }
        else {
            overlapping_area = overlapping_area - iter->second;
        }
        cout << "[" << iter->first << ","
                    << iter->second << "]\n";
    }
    cout << endl;

    return overlapping_area;
}

//// total covered area implementation ////
int Area_Calculation::total_rect_covered_area() {
    total_covered_area = total_area - overlapping_area;
    return total_covered_area;
}

//////////////////////////////////
// Container with vector define //
//////////////////////////////////
void PolyContainer_vector::Gen_Rect_vector (int rect_num, int range_per_rect) {
    int pre_x1, pre_y1, pre_x2, pre_y2;
    pre_x1 = pre_y1 = pre_x2 = pre_y2 = 0;

    struct Rectangle R;
    //struct Rectangle* R;
    //R->x1 = R->y1 = R->x2 = R->y2 = 0;

    for (int num = 0; num < rect_num; num++) {
        if (pre_x1 == 0 && pre_y1 == 0 && pre_x2 == 0 && pre_y2 == 0) {
            R.x1 = rand() % range_per_rect;
            R.y1 = rand() % range_per_rect;
            R.x2 = rand() % range_per_rect;
            R.y2 = rand() % range_per_rect;

            // make sure x1 != x2 and y1 != y2
            while (R.x1 == R.x2 || R.y1 == R.y2) {
                if (R.x1 == R.x2) R.x1 = rand() % range_per_rect;
                if (R.y1 == R.y2) R.y1 = rand() % range_per_rect;
            }

						// adjust x, y position
            if (R.x1 > R.x2) {
                int temp = R.x1;
                R.x1 = R.x2;
                R.x2 = temp;
            }
            if (R.y1 > R.y2) {
                int temp = R.y1;
                R.y1 = R.y2;
                R.y2 = temp;
            }
        }
        else {
            do {
                // set next R.x2 from range pre R.x1 to (preR.x2 + max_range_per_rect)
                R.x2 = (rand() % (range_per_rect + pre_x2 - pre_x1 + 1)) + pre_x1;
                // set next R.x1
                if (R.x2 >= pre_x2) {
                    R.x1 = pre_x2 - rand() % (range_per_rect - (R.x2 - pre_x2) + 1);
                }
                else {
                    R.x1 = R.x2 - (rand() % range_per_rect + 1);
                }
            } while (R.x1 == R.x2);

						do {
                // set next R.y2 from range pre R.y1 to (pre R.y2 + range_per_rect)
                R.y2 = (rand() % (range_per_rect + pre_y2 - pre_y1 + 1)) + pre_y1;
                // set next R.y1
                if (R.y2 >= pre_y2) {
                    R.y1 = pre_y2 - rand() % (range_per_rect - (R.y2 - pre_y2) + 1);
                }
                else {
                    R.y1 = R.y2 - (rand() % range_per_rect + 1);
                }
            } while (R.y1 == R.y2);


            if (R.x2 > max_range || R.y2 > max_range || R.x1 < max_range*(-1) || R.y1 < max_range*(-1)) {
                cout << "Break: x or y position exceed max range" << endl;
                break;
            }
        }

        pre_x1 = R.x1;
        pre_y1 = R.y1;
        pre_x2 = R.x2;
        pre_y2 = R.y2;
        // add generated R to polygons of vector
        polygons.push_back(R);
		}
    return;
}

////////////////////////////////
// Container with list define //
////////////////////////////////
void PolyContainer_list::Gen_Rect_list (int rect_num, int range_per_rect) {
    int pre_x1, pre_y1, pre_x2, pre_y2;
    pre_x1 = pre_y1 = pre_x2 = pre_y2 = 0;

    struct Rectangle R;

    for (int num = 0; num < rect_num; num++) {
        if (pre_x1 == 0 && pre_y1 == 0 && pre_x2 == 0 && pre_y2 == 0) {
            R.x1 = rand() % range_per_rect;
            R.y1 = rand() % range_per_rect;
            R.x2 = rand() % range_per_rect;
            R.y2 = rand() % range_per_rect;

            // make sure x1 != x2 and y1 != y2
            while (R.x1 == R.x2 || R.y1 == R.y2) {
                if (R.x1 == R.x2) R.x1 = rand() % range_per_rect;
                if (R.y1 == R.y2) R.y1 = rand() % range_per_rect;
            }

						// adjust x, y position
            if (R.x1 > R.x2) {
                int temp = R.x1;
                R.x1 = R.x2;
                R.x2 = temp;
            }
            if (R.y1 > R.y2) {
                int temp = R.y1;
                R.y1 = R.y2;
                R.y2 = temp;
            }
        }
        else {
            do {
                // set next R.x2 from range pre R.x1 to (preR.x2 + max_range_per_rect)
                R.x2 = (rand() % (range_per_rect + pre_x2 - pre_x1 + 1)) + pre_x1;
                // set next R.x1
                if (R.x2 >= pre_x2) {
                    R.x1 = pre_x2 - rand() % (range_per_rect - (R.x2 - pre_x2) + 1);
                }
                else {
                    R.x1 = R.x2 - (rand() % range_per_rect + 1);
                }
            } while (R.x1 == R.x2);

						do {
                // set next R.y2 from range pre R.y1 to (pre R.y2 + range_per_rect)
                R.y2 = (rand() % (range_per_rect + pre_y2 - pre_y1 + 1)) + pre_y1;
                // set next R.y1
                if (R.y2 >= pre_y2) {
                    R.y1 = pre_y2 - rand() % (range_per_rect - (R.y2 - pre_y2) + 1);
                }
                else {
                    R.y1 = R.y2 - (rand() % range_per_rect + 1);
                }
            } while (R.y1 == R.y2);


            if (R.x2 > max_range || R.y2 > max_range || R.x1 < max_range*(-1) || R.y1 < max_range*(-1)) {
                cout << "Break: x or y position exceed max range" << endl;
                break;
            }
        }

				pre_x1 = R.x1;
        pre_y1 = R.y1;
        pre_x2 = R.x2;
        pre_y2 = R.y2;
        // add generated R to polygons of vector
        polygons.push_back(R);

        // print out content of Rect
        //cout << "x1 = " << R.x1 << " ";
        //cout << "y1 = " << R.y1 << " ";
        //cout << "x2 = " << R.x2 << " ";
        //cout << "y2 = " << R.y2 << " ";
        //cout << "rect current num = " << polygons.size() << endl;
    }
		return;
}
