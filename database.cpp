#include "database.h"

Database::Database()
{
    cur_maximum = 0;
    cur_minimum = 0;
    number_of_columns = 0;
    number_instances = 0;
}
void Database::add_class_obj(class_obj xyz){
    data.push_back(xyz);
    normalize_data();
}
void Database::read_input(string txtfile){
    ifstream infile;
    infile.open(txtfile.c_str());
    if(infile.is_open()){
        //cout << "File opened successfully" << endl;
    }
    string line;
    string delimiter = " ";
    string token;
    while(getline(infile >> ws,line)){
        class_obj new_obj;

        int i = 0;
        //cout << line << endl;
        vector<int> row_value;
        istringstream stm(line);
        while( stm >> token){
            int string_to_int = stoi(token);
            if(i == 0){
                new_obj.set_name(string_to_int);
                i = 99;
            }else{
                row_value.push_back(string_to_int);

            }
        }
        number_instances++;
        new_obj.set_vector_data(row_value);
        data.push_back(new_obj);
        number_of_columns = row_value.size();



    }
    //cout << "Number of columns: " << number_of_columns << endl;
    //cout << "Number of instances: " << number_instances << endl;
}
double Database::helper_classifier(vector<double> lhs, vector<double> rhs){
    double total = 0;
    double rhs_num = 0;
    int index = 0;
    //cout << "LHS size: " << lhs.size() << endl;
    //cout << "RHS size: " << rhs.size() << endl;
    if(lhs.size() == rhs.size()){
        for(vector<double>::iterator itr = lhs.begin(); itr != lhs.end() ; itr++){
            double lhs_num = *itr;
            rhs_num = rhs.at(index);
            if((lhs_num == 0) || (rhs_num == 0)){
                index++;
                continue;
            }
            double sub_sum = pow((lhs_num - rhs_num),2);
            total += sub_sum;
            index++;
        }
        total = sqrt(total);
        return total;
    }else{
        cout << "not the same size" << endl;
        return total;
    }
}
int Database::get_cols() const{
    return number_of_columns;
}
int Database::get_instances() const{
    return number_instances;
}
void Database::modify_data(vector<int> xyz){
    list<class_obj>::iterator itr = data.begin();
    list<class_obj> data2;
    for(; itr != data.end(); itr++){
        class_obj da_node = *itr;
        da_node.modify_data_by_index(xyz,number_of_columns);
        data2.push_back(da_node);

    }
    data.clear();
    data = data2;

}
void Database::clean_list(){

}
void Database::print_map(){
    vector<int> final_value;
    double highest_prob = 0;
    for(map<vector<int>, double >::const_iterator it = map_prob.begin(); it != map_prob.end(); ++it){
        vector<int> xyz = it->first;
        double prob = it->second;
        if(prob == 0){
            continue;
        }
        //cout << "Vector: ";
        for(size_t i = 0 ; i < xyz.size(); i++){
            if(i+1 == xyz.size()){
                //cout << xyz.at(i);
            }else{
                //cout << xyz.at(i) << ",";
            }
        }
        if(highest_prob == 0){
            highest_prob = prob;
            final_value = xyz;
        }else{
            if(prob > highest_prob){
                highest_prob = prob;
                final_value = xyz;
            }
        }
        //cout << " Probability: " << prob << endl;
    }
    cout << endl;
    cout << "Best Feature Set {";
    for(size_t i = 0 ; i < final_value.size(); i++){
        if(i+1 == final_value.size()){
            cout << final_value.at(i) << "}";
        }else{
            cout << final_value.at(i) << ",";
        }
    }
    cout << " Highest Probability: " << highest_prob << "%" << endl;
}
void Database::search_algo(){

    vector<int> feature_added;
    double highest_probability = 0;
    int highest_feature_num = 0;
    list<class_obj> data2;
    data2 = data;
    int index_counter = 0;
    while(feature_added.size() != number_of_columns){
        highest_feature_num = 0;
        highest_probability = 0;
        for(size_t i = 0 ; i < number_of_columns ;i++){
            double tmp_value = 0;

            if(find(feature_added.begin(), feature_added.end(),i) == feature_added.end()){
                feature_added.push_back(i);
                tmp_value = leave_one_validator(feature_added);
                cout << "Using feature(s){";
                for(size_t x = 0 ; x < feature_added.size(); x++){
                    if(x+1 == feature_added.size()){
                        cout << feature_added.at(x);
                    }else{
                        cout << feature_added.at(x) << ",";
                    }
                }
                cout << "} accuracy is "  << tmp_value << "%" << endl;
                if(highest_probability == 0){
                    highest_probability = tmp_value;
                    highest_feature_num = i;
                }else{
                    if(tmp_value > highest_probability){
                        highest_probability = tmp_value;
                        highest_feature_num = i;
                    }
                }
                feature_added.erase(remove(feature_added.begin(),feature_added.end(),i),feature_added.end());

                data.clear();
                data = data2;


            }
        }
        feature_added.push_back(highest_feature_num);
        index_counter += 1;
        pair<vector<int> , double> temp_pair;
        temp_pair.first = feature_added;
        temp_pair.second = highest_probability;
        map_prob.insert(temp_pair);
        cout << "Feature set {";
        for(size_t i = 0 ; i < feature_added.size(); i++){
            if(i+1 == feature_added.size()){
                cout << feature_added.at(i);
            }else{
                cout << feature_added.at(i) << ",";
            }
        }

        cout << "} was best, accuracy is " << highest_probability << "%" << endl;



    }
    cout << "==========================================================" << endl;
    print_map();


}
void Database::clear_pq(){
    while(!queue_stack.empty()){
        queue_stack.pop();
    }
}
void Database::remove_one(class_obj xyz){

    priority_queue<class_obj, vector<class_obj>, GreaterThanByD_value> queue_stack2 = queue_stack;

    data.clear();

    while(!queue_stack2.empty()){
        class_obj da_node = queue_stack2.top();
        if(da_node != xyz){
            data.push_back(da_node);
        }
        queue_stack2.pop();
        //cout << "something popped out" << endl;
    }
}
bool Database::find_class_obj(class_obj xyz){
    priority_queue<class_obj, vector<class_obj>, GreaterThanByD_value> queue_stack2 = queue_stack;
    xyz.normalized_data = xyz.normalize_data(cur_minimum,cur_maximum);
    while(!queue_stack2.empty()){
        class_obj da_node = queue_stack2.top();
        if(da_node == xyz){
            return true;
        }
        queue_stack2.pop();
    }
    return false;
}
double Database::leave_one_validator(vector<int> xyz){

    double _percentage;
    double num_correct = 0;
    double num_total = 0;

    int answer = 0;

    modify_data(xyz);

    list<class_obj> data2 = data;
    //cout << "Modified Data" << endl;
    //print_data();

    for(list<class_obj>::iterator itr = data2.begin(); itr != data2.end(); ++itr){
        class_obj xyz4 = *itr;
        int correct_class_id = xyz4.class_id;
        answer = neighbor_classifier(xyz4);  // look at the nearest class id.
        if(answer == correct_class_id){
            num_correct++;
        }
        num_total++;


    }

    //cout << "Num Correct: " << num_correct << endl;
    //cout << "Num Total: " << num_total << endl;
    _percentage = (num_correct / num_total) * 100;
    //cout << "Percentage: " << _percentage << "%" <<  endl;

    return _percentage;
}
void Database::print_pq(){
    priority_queue<class_obj, vector<class_obj>, GreaterThanByD_value> queue_stack2 = queue_stack;
    while(!queue_stack2.empty()){
        class_obj da_node = queue_stack2.top();
        da_node.print_normalized_data();
        queue_stack2.pop();
    }

}

int Database::neighbor_classifier(class_obj xyz){
    vector<double> lhs_vec = xyz.normalized_data;
    if(lhs_vec.empty()){
         lhs_vec = xyz.normalize_data(cur_minimum,cur_maximum);
    }
    clear_pq();
    list<class_obj>::iterator itr = data.begin();
    for(; itr != data.end(); itr++){
        class_obj temp_x = *itr;
        if(temp_x == xyz){
            temp_x.d_value = 99;
            queue_stack.push(temp_x);  
            continue;
        }
        temp_x.d_value = helper_classifier(lhs_vec,temp_x.normalized_data);
        queue_stack.push(temp_x);
    }

    if(queue_stack.empty()){
        cout << "i am currently empty" << endl;
        return 0;
    }
    class_obj top_node = queue_stack.top();

    return top_node.class_id;


}

void Database::normalize_data(){
    list<class_obj> data2 = data;
    bool init_state = true;

    list<class_obj>::iterator itr = data.begin();
    for(; itr != data.end() ; itr++){
        class_obj xyz = *itr;
        if(init_state){
            cur_minimum = xyz.return_min();
            init_state = false;
        }else{
            if(xyz.return_min() < cur_minimum){
                cur_minimum = xyz.return_min();
            }
        }
    }
    init_state = true;
    cout << "Smallest value: " << cur_minimum << endl;
    itr = data.begin();
    for(; itr != data.end() ; itr++){
        class_obj xyz = *itr;
        if(init_state){
            cur_maximum = xyz.return_max();
            init_state = false;
        }else{
            if(xyz.return_max() > cur_maximum){
                cur_maximum = xyz.return_max();
            }
        }
    }
    data.clear();
    clear_pq();
    cout << "Largest value: " << cur_maximum << endl;
    itr = data2.begin();
    for(; itr != data2.end(); itr++){
        class_obj xyz2 = *itr;
        xyz2.normalized_data = xyz2.normalize_data(cur_minimum,cur_maximum);
        data.push_back(xyz2);
        //queue_stack.push(xyz2);

    }


    cout << "Finished normalizing data" << endl;
    //print_data();

}
void Database::print_data(){
    list<class_obj>::iterator itr = data.begin();
    for(; itr != data.end() ; itr++){
        class_obj xyz = *itr;
        xyz.print_me();
    }
}
