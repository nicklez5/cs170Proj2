#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;
#ifndef CLASS_OBJ_H
#define CLASS_OBJ_H
class Database;
class class_obj
{
public:
    class_obj();
    class_obj(const class_obj& xyz);
    class_obj(vector<int> weird_data);
    ~class_obj();
    class_obj& operator= (const class_obj& xyz);
    void set_vector_data(vector<int> xyz);
    void print_normalized_dvalue();
    void set_name(int xyz);
    void print_me();
    int return_min() const;
    int return_max() const;
    double return_d() const;
    void modify_data_by_index(vector<int> index, int num_cols);
    friend bool operator>(const class_obj& lhs, const class_obj& rhs);
    friend bool operator== (const class_obj& lhs, const class_obj& rhs);
    friend bool operator!=(const class_obj& lhs, const class_obj& rhs);
    vector<double> normalize_data(int min_value, int max_value);
    void print_normalized_data();
    friend class Database;

private:
    vector<int> feature_data;
    vector<double> normalized_data;
    vector<double> non_static_data;
    double d_value;
    int class_id;
};

#endif // CLASS_OBJ_H
