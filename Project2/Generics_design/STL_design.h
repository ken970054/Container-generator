#include <bits/stdc++.h>

using namespace std;

/////////////////////
// Rectangle class //
/////////////////////
struct Rectangle {
    int x1, y1, x2, y2;
};


//////////////////////
// Area calculation //
//////////////////////

//// total area ////
template<typename T>
int total_rect_area(const T &begin, const T &end) {
    int total_area{0};
    T R_iter;
    for (R_iter = begin; R_iter != end; R_iter++) {
        //cout << "x1, y1, x2, y2 = " << (*R_iter).x1 << ", " << (*R_iter).y1 << ", " << (*R_iter).x2 << ", " << (*R_iter).y2 << endl;
        total_area = total_area + ((*R_iter).x2 - (*R_iter).x1) * ((*R_iter).y2 - (*R_iter).y1);
    }

    return total_area;
}

//// overlapping area ////
// for sort vector use
bool compareRectY1(struct Rectangle R1, struct Rectangle R2) { return R1.y1 < R2.y1; }

// recursion function for calculating overlapping area
void calculate_overlapping_area(struct Rectangle current_R, vector<struct Rectangle> Rects, int level, map<int, int> & overlapping_area_map) {
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
            calculate_overlapping_area(overlapping_rect, Rects, level, overlapping_area_map);
        }
        else {
            break;
        }
    }
    return;
}

template<typename T>
int overlapping_rect_area(const T &begin, const T &end, int num_rects) {
    int overlapping_area{0};
    map<int, int> overlapping_area_map;
    T Rect_iter;

    vector<struct Rectangle> Rects; // for calculating use
    Rects.reserve(num_rects);

    // unique all X coordinates //
    vector<int> uniqueX;
    uniqueX.reserve(num_rects * 2);
    struct Rectangle R;
    for (Rect_iter = begin; Rect_iter != end; Rect_iter++) {
        Rects.push_back(*Rect_iter);
        uniqueX.push_back((*Rect_iter).x1);
        uniqueX.push_back((*Rect_iter).x2);
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
            calculate_overlapping_area(current_R, sameWidthRects, level, overlapping_area_map);
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


//// total coverd area ////
int total_rect_covered_area(int total_area, int overlapping_area) {
    return total_area - overlapping_area;
}

#endif
