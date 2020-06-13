#include "class_obj.h"

class_obj::class_obj()
{
    d_value = 0;
    class_id = 0;
}
class_obj::~class_obj(){
    feature_data.clear();
    normalized_data.clear();
    non_static_data.clear();
    d_value = 0;
    class_id = 0;
}
bool operator==(const class_obj& lhs, const class_obj& rhs){
    return lhs.normalized_data == rhs.normalized_data;
}
bool operator!=(const class_obj& lhs, const class_obj& rhs){
    return lhs.normalized_data != rhs.normalized_data;
}
bool operator>(const class_obj& lhs, const class_obj& rhs){
    return lhs.d_value > rhs.d_value;
}
void class_obj::set_vector_data(vector<int> xyz){
    feature_data = xyz;
}
double class_obj::return_d() const{
    return d_value;
}
void class_obj::modify_data_by_index(vector<int> index, int num_cols){
    for(int i = 0 ; i < num_cols ;i++){
        if(find(index.begin(),index.end(),i) == index.end()){
            normalized_data.at(i) = 0;
        }
    }

}
class_obj::class_obj(vector<int> weird_data){
    feature_data = weird_data;
    d_value = 0;
    class_id = 0;
}
class_obj& class_obj::operator= (const class_obj &xyz){


    normalized_data = xyz.normalized_data;
    feature_data = xyz.feature_data;
    class_id = xyz.class_id;
    d_value = xyz.d_value;
    return *this;
}
class_obj::class_obj(const class_obj& xyz){
    normalized_data = xyz.normalized_data;
    feature_data = xyz.feature_data;
    class_id = xyz.class_id;
    d_value = xyz.d_value;
}
int class_obj::return_min() const{
    int min = *min_element(feature_data.begin(), feature_data.end());
    return min;
}
int class_obj::return_max() const{
    int max = *max_element(feature_data.begin(), feature_data.end());
    return max;
}
void class_obj::set_name(int xyz){
    class_id = xyz;
}
void class_obj::print_me(){
    cout << "Class ID: " << class_id << " Features: ";
    for(vector<int>::iterator itr = feature_data.begin(); itr != feature_data.end(); itr++){
        int random_data = *itr;
        cout << " " << random_data;
    }
    cout << " D_value: " << d_value;
    cout << endl;
}

void class_obj::print_normalized_data(){
    cout << "Class ID: " << class_id << " Normalized Features: ";
    for(vector<double>::iterator itr = normalized_data.begin(); itr != normalized_data.end(); itr++){
        double random_data = *itr;
        cout  << " " << random_data;

    }
    cout << " d_value: " << d_value;
    cout << endl;
}

vector<double> class_obj::normalize_data(int min_value, int max_value){
    vector<double> xyz;
    for(vector<int>::iterator itr = feature_data.begin() ; itr != feature_data.end(); itr++){
        int random_data = *itr;
        if(random_data == 0){
            xyz.push_back(0.00);
            continue;
        }
        //cout << "Data: " << random_data << endl;
        //cout << "Maximum: " << max_value << endl;
        //cout << "Minimum: " << min_value << endl;
        double new_x = (double)(random_data - min_value) / (max_value - min_value) ;
        //cout << "Result: " << new_x << endl;
        xyz.push_back(new_x);
    }
    return xyz;

}
