#include <iostream>
#include "database.h"
using namespace std;
vector<int> random_vec_method();
int main()
{
    Database *xyz = new Database();
    cout << "Welcome to Jackson Lu's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: ";
    string filename = "";
    getline(cin, filename);
    //cout << endl;
    xyz->read_input(filename);
    cout << "This dataset has " << xyz->get_cols() << " features with " << xyz->get_instances() << " instances" << endl;
    xyz->normalize_data();

    xyz->search_algo();



    //xyz->print_map();
    //t.set_name(1);
    //xyz->leave_one_validator(random_vec);
    //xyz->print_pq();
    /*
    cout << "INCOMING TRAFFIC" << endl;
    xyz->print_pq();
    cout << "Class id(nearest neighbor classifier): " << xyz->neighbor_classifier(t) << " ";
    xyz->print_pq();
    */


    return 0;
}
vector<int> random_vec_method(){
    vector<int> xyz;
    xyz.push_back(3);
    xyz.push_back(5);
    xyz.push_back(1);
    xyz.push_back(1);
    xyz.push_back(2);
    xyz.push_back(3);
    xyz.push_back(2);
    xyz.push_back(1);
    xyz.push_back(1);
    xyz.push_back(4);
    return xyz;
}
