#include "STL_design.h"
#include "STL_design_class.h"

#include <bits/stdc++.h>
#include <ctime>
#include <chrono>


using namespace std;
using namespace std::chrono;


int main() {

    srand(time(NULL)); // make sure every time the content of random number can generate differently

//// Vector ////
    PolyContainer_vector PC_vect;

    PC_vect.Gen_Rect_vector(Rect_num, max_range_per_rect);

    int total_area_vect = total_rect_area(PC_vect.begin(), PC_vect.end());
    cout << "Vector total area = " << total_area_vect << endl;
    int overlapping_area_vect = overlapping_rect_area(PC_vect.begin(), PC_vect.end(), PC_vect.get_polygons_size());
    cout << "Vector overlapping area = " << overlapping_area_vect <<endl;
    int total_covered_area_vect = total_rect_covered_area(total_area_vect, overlapping_area_vect);
    cout << "Vector total covered area = " << total_covered_area_vect << endl;

//// List ////
    PolyContainer_list PC_list;

    PC_list.Gen_Rect_list(Rect_num, max_range_per_rect);

    int total_area_list = total_rect_area(PC_list.begin(), PC_list.end());
    cout << "List total area = " << total_area_list << endl;
    int overlapping_area_list = overlapping_rect_area(PC_list.begin(), PC_list.end(), PC_list.get_polygons_size());
    cout << "List overlapping area = " << overlapping_area_list  << endl;
    int total_covered_area_list = total_rect_covered_area(total_area_list, overlapping_area_list);
    cout << "List total covered area = " << total_covered_area_list << endl;

    return 0;
}
