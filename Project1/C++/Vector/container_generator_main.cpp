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
