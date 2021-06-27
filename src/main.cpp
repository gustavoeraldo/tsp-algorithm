#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <cctype>
#include <vector>
#include <algorithm> 
#include <cstdlib>
#include <ctime>

#include "route.h"

using namespace std;

void read_instance(string file_name, int* max_num_addr, int* dimension, vector<vector<int>> * adjacent_matrix);
void show_matrix(vector< vector<int>> adjacent_matrix);

void create_mini_routes(int max_addr_qnt, int dimension, vector<vector<int>>* all_routes);
int myrandom (int number);

int main(int argc, char** argv) {
    string file_name = argv[1];
    vector<vector<int>> adjacent_matrix, all_routes;
    int max_num_addr, dimension;
    
    read_instance(file_name, &max_num_addr, &dimension, &adjacent_matrix);

    // cout << "dimension: " << max_num_addr << endl;
    create_mini_routes(max_num_addr, dimension, &all_routes);

    // show_matrix(adjacent_matrix);
    return 0;
}


void read_instance( string file_name, int* max_num_addr, 
    int* dimension, vector<vector<int>> *adjacent_matrix ) {
    
    stringstream parse_to_int;
    ifstream instance_file;
    string value, root_path, buffer;
    vector<int> cost_line;
    int line, v_time, cost;

    line = 0;
    root_path = "/home/gustavo/Downloads/P9/APA/tsp-apa/instances/";

    instance_file.open(root_path + file_name);
    if (!instance_file)
        cout << "Could not find or open the file " + file_name << endl;

    while(getline(instance_file, value)){
        if (value.rfind("DIMENSION:") != string::npos){
            parse_to_int << value;
            parse_to_int >> buffer >> *dimension;
        }

        if (value.find("P: ") != string::npos){
            buffer = value.substr(3);
            *max_num_addr = stoi(buffer);
        }
        
        
        if(line >= 3){ // Create Ajd matrix
            stringstream parse_line(value);
            while(parse_line >> cost){
                cost_line.push_back(cost);
            }

            adjacent_matrix->push_back(cost_line);
            cost_line.clear();
        }
        line++;
    }

    instance_file.close();
}


void create_mini_routes(int max_addr_qnt, int dimension, vector<vector<int>>* all_routes){
    srand (unsigned (time(0)));
    vector<int> random_vec, temporary_route;

    for (int i = 1; i < dimension; i++) random_vec.push_back(i);
    random_shuffle(random_vec.begin(), random_vec.end(), myrandom);

    while (random_vec.size() != 0){
        temporary_route.push_back(0);
        for(int i = 0; i < max_addr_qnt; i++){ 
            if (random_vec.size() == 0) break;

            temporary_route.push_back(random_vec.back());
            random_vec.pop_back();            
        }

        all_routes->push_back(temporary_route);
        temporary_route.clear();
    }

    show_matrix(*all_routes);
}

int myrandom (int i) { return rand()%i;}

void show_matrix(vector< vector<int>> adjacent_matrix){
    vector<int>::iterator it;
    vector< vector<int>>::iterator line_iter;
    
    for (line_iter = adjacent_matrix.begin(); line_iter != adjacent_matrix.end(); line_iter++){
        for (int it : *line_iter)
            cout << it << " ";
        cout << endl;
    }
}
