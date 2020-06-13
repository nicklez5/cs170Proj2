#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <string>
#include <list>
#include <queue>
#include <math.h>
#include <map>
#include "class_obj.h"
using namespace std;
#ifndef DATABASE_H
#define DATABASE_H

struct GreaterThanByD_value{
    bool operator()(class_obj const& lhs,class_obj const& rhs){
        return lhs.return_d() > rhs.return_d();
    }
};

class Database
{
public:
    Database();

    void search_algo();
    void read_input(string txtfile);
    void add_class_obj(class_obj xyz);
    void print_pq();
    void print_map();
    void clean_list();
    int get_cols() const;
    int get_instances() const;
    bool find_class_obj(class_obj xyz);
    void clear_pq();
    void print_data();
    void modify_data(vector<int> xyz);
    void normalize_data();
    void remove_one(class_obj xyz);
    double leave_one_validator(vector<int> xyz);
    int neighbor_classifier(class_obj xyz);
    double helper_classifier(vector<double> lhs, vector<double> rhs);
private:
    list<class_obj> data;
    map<vector<int>, double> map_prob;
    priority_queue<class_obj, vector<class_obj> , GreaterThanByD_value> queue_stack;
    int cur_maximum;
    int cur_minimum;
    size_t number_of_columns;
    size_t number_instances;
};

#endif // DATABASE_H
