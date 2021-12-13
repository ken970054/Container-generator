#include "STL_design_class.h"
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>


using namespace std;
using namespace std::chrono;


/////////////////////
// Rectangle class //
/////////////////////
struct Rectangle {
    int x1, y1, x2, y2;
};

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
    }
    return;
}
