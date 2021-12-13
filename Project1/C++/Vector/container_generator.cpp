#include <bits/stdc++.h>
#include <ctime>
#include <chrono>

#include <fstream>

using namespace std;
using namespace std::chrono;

typedef long long int lli;
//const int m = 1e9 + 7;
const int max_range = 2000000000;
const int max_range_per_rect = 10;
const int Rect_num = 1000000;
//const int Rect_num = 3;

// Rectangle class
class Rectangle {
    public:
        // left_bottom(x1, y1)  right_top(x2, y2)
        int x1, y1, x2, y2;
};


int gen_xyPairs (int range_x1, int range_y1, int range_x2, int range_y2, Rectangle*& Rect) {

    // initial Rectangle xy pair
    if (range_x1 == 0 && range_y1 == 0 && range_x2 == 0 && range_y2 == 0 ) {
        Rect->x1 = rand() % max_range_per_rect;
        Rect->y1 = rand() % max_range_per_rect;
        Rect->x2 = rand() % max_range_per_rect;
        Rect->y2 = rand() % max_range_per_rect;

				// make sure x1 != x2 and y1 != y2
        while (Rect->x1 == Rect->x2 || Rect->y1 == Rect->y2) {
            if (Rect->x1 == Rect->x2) Rect->x1 = rand() % max_range_per_rect;
            if (Rect->y1 == Rect->y2) Rect->y1 = rand() % max_range_per_rect;
        }

        // adjust x, y position
        if (Rect->x1 > Rect->x2) {
            int temp = Rect->x1;
            Rect->x1 = Rect->x2;
            Rect->x2 = temp;
        }
        if (Rect->y1 > Rect->y2) {
            int temp = Rect->y1;
            Rect->y1 = Rect->y2;
            Rect->y2 = temp;
        }
    }
    else {
        do {
            // set nextRect->x2 from range preRect->x1 to (preRect->x2 + max_range_per_rect)
            Rect->x2 = (rand() % (max_range_per_rect + range_x2 - range_x1 + 1)) + range_x1;
            // set nextRect->x1
            if (Rect->x2 >= range_x2) {
                Rect->x1 = range_x2 - rand() % (max_range_per_rect - (Rect->x2 - range_x2) + 1);
            }
            else {
                Rect->x1 = Rect->x2 - (rand() % max_range_per_rect + 1);
            }
        } while (Rect->x1 == Rect->x2);

				do {
            // set nextRect->y2 from range preRect->y1 to (preRect->y2 + max_range_per_rect)
            Rect->y2 = (rand() % (max_range_per_rect + range_y2 - range_y1 + 1)) + range_y1;
            // set nextRect->y1
            if (Rect->y2 >= range_y2) {
                Rect->y1 = range_y2 - rand() % (max_range_per_rect - (Rect->y2 - range_y2) + 1);
            }
            else {
                Rect->y1 = Rect->y2 - (rand() % max_range_per_rect + 1);
            }
        } while (Rect->y1 == Rect->y2);


        if (Rect->x2 > max_range || Rect->y2 > max_range || Rect->x1 < max_range*(-1) || Rect->y1 < max_range*(-1)) {
            cout << "Break: x or y position exceed max range" << endl;
            return 1;
        }

        return 0;
    }
}

lli rectangleArea(vector<Rectangle*> &v) { //notice object type should be a pointer of object
    vector<int> xv;
    xv.reserve(v.size() * 2); //reserve xv size
    for (int i = 0; i < v.size(); i++) {
        xv.push_back(v[i]->x1);
        xv.push_back(v[i]->x2);
    }
    sort(xv.begin(), xv.end());
    vector<int>::iterator uniItr = unique(xv.begin(), xv.end());
    xv.erase(uniItr, xv.end()); //need to care memory number?
    map<int, int> index;
    //int idx = 0;
    for (int i = 0; i < xv.size(); i++) {
        index[xv[i]] = i;
    }

    vector<int> count(index.size());
    vector<vector<int> > x;
    x.reserve(v.size()*2);
    int x1, y1, x2, y2;
    for (int i = 0; i < Rect_num; i++) {
        x1 = v[i]->x1;
        y1 = v[i]->y1;
        x2 = v[i]->x2;
        y2 = v[i]->y2;
        x.push_back({y1, x1, x2, 1});
        x.push_back({y2, x1, x2, -1});
    }

		sort(x.begin(), x.end());
    lli ret = 0;
    lli sum = 0, currentY = 0;
    for (int i = 0; i < Rect_num * 2; i++) {
        lli y = x[i][0];
        x1 = x[i][1];
        x2 = x[i][2];
        int sig = x[i][3];
        ret = ret + (y - currentY) * sum;
        cout << "current ret = " << ret << endl;
        currentY = y;
        for (int i = index[x1]; i < index[x2]; i++) {
            count[i] += sig;
        }
        sum = 0;
        for (int i = 0; i < count.size(); i++) {
            if (count[i] > 0) {
                sum += (xv[i + 1] - xv[i]);
            }
        }
    }

    return ret;

}


// main
int main() {

    // File setting
    fstream file;
    file.open("Output_pointer.txt", ios::out | ios::app);
    if (!file) {
        cerr << "Can't open file!\n'";
        exit(1);
    }


    srand(time(NULL)); // make sure every time the content of random number can generate differently

    int isExceed = 0;
    int Rect_num_break = 0;

    int range_x1, range_y1, range_x2, range_y2;
    range_x1 = range_y1 = range_x2 = range_y2 = 0;

    // Create vector to store pointer of Rect
    vector<Rectangle*> Rect_ptr_set;
    // reserve Rect_ptr_set memory size
    Rect_ptr_set.reserve(Rect_num);

    for (int i = 0; i < Rect_num; ++i) {
        // create a new Rect object in every iteration and assign to a pointer
        Rectangle* Rect = new Rectangle();
        Rect->x1 = Rect->y1 = Rect->x2 = Rect->y2 = 0;

        isExceed = gen_xyPairs(range_x1, range_y1, range_x2, range_y2, Rect);
        if (isExceed == 1) {
            Rect_num_break = i;
            break;
        }

				// put new gen rect to the previous rect
        range_x1 = Rect->x1;
        range_y1 = Rect->y1;
        range_x2 = Rect->x2;
        range_y2 = Rect->y2;

        Rect_ptr_set.push_back(Rect); // push each pointer to vector
        cout << "x1 = " << Rect->x1 << " ";
        cout << "y1 = " << Rect->y1 << " ";
        cout << "x2 = " << Rect->x2 << " ";
        cout << "y2 = " << Rect->y2 << " ";
        cout << "rect current num = " << Rect_ptr_set.size() << endl;

        //cout << "range_x1 = " << range_x1 << " ";
        //cout << "range_y1 = " << range_y1 << " ";
        //cout << "range_x2 = " << range_x2 << " ";
        //cout << "range_y2 = " << range_y2 << endl;
    }

    // iterator Rect_set
    //for (vector<Rectangle>::iterator it = Rect_set.begin(); it != Rect_set.end(); ++it) {
    //  cout << (*it).x1 << endl;
    //}
    //for (int i = 0; i < 10; ++i) {
    //  cout << Rect_set[i].x1 << endl;
    //}
    auto start = high_resolution_clock::now();

    lli total_area = rectangleArea(Rect_ptr_set);
    cout << "Total area = " << total_area << endl;

		auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    // print Rect number
    if (Rect_num < 1000000 && Rect_num_break == 0) {
        cout << "Number of Rect in the container: " << Rect_num << endl;
    }
    else if (Rect_num >= 1000000 && Rect_num_break == 0) {
        double Rect_num_M = Rect_num / 1000000;
        cout << "Number of Rect in the container: " << Rect_num_M << "M" << endl;
    }
    else if (Rect_num_break > 0 && Rect_num_break < 1000000) {
        cout << "Number of Rect in the container: " << Rect_num_break << endl;
    }
    else {
        double Rect_num_break_M = Rect_num_break / 1000000;
        cout << "Number of Rect in the container: " << Rect_num_break_M << "M" << endl;
    }

    // print elapsed time
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    cout << "Time taken by function: " << duration.count() / 1000000 << " seconds" << endl;

    // Write data to file
    if (isExceed == 1) {
        file << "Rectangle number:" << Rect_num_break << "\n";
    }
    else {
        file << "Rectangle number: " << Rect_num << "\n";

		file << "Elasped time: " << duration.count() / 1000000 << " seconds\n";
    file << "Total area: " << total_area << "\n\n\n";

    return 0;
		}

}
