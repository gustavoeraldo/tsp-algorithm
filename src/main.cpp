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

#include "vnd.h"

using namespace std;

void read_instance(string file_name, int* max_num_addr, int* dimension, vector<vector<int>> * adjacent_matrix);
void heuristic_building(
    vector< vector<int>> *routes, vector<vector<int>> adjacent_matrix, 
    int max_num_addr, int dimension, vector<int> *solutions);

void show_matrix(vector< vector<int>> adjacent_matrix);
void show_routes(vector< vector<int>> routes);


int main(int argc, char** argv) {
    string file_name = argv[1];
    vector<vector<int>> adjacent_matrix, all_routes;
    int max_num_addr, dimension, best_solution=0;
    vector<int> solutions;
    
    read_instance(file_name, &max_num_addr, &dimension, &adjacent_matrix);
    heuristic_building(
        &all_routes, adjacent_matrix, max_num_addr, dimension, &solutions);

    for(int i : solutions) best_solution += i;
    cout << "Best initial solution: " << best_solution << endl;
    
    VND local_search = VND();
    local_search.set_adjacent_matrix(adjacent_matrix);
    local_search.set_all_routes(all_routes);
    local_search.set_initial_solution(solutions);
    local_search.start_vnd();

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
    root_path = "/home/gustavo/Downloads/P9/APA/tsp-algorithm/instancias_apa_cup/";
    // root_path = "/home/gustavo/Downloads/P9/APA/tsp-algorithm/instances/";

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

void show_matrix(vector< vector<int>> adjacent_matrix){
    vector<int>::iterator it;
    vector< vector<int>>::iterator line_iter;
    
    for (line_iter = adjacent_matrix.begin(); line_iter != adjacent_matrix.end(); line_iter++){
        for (int it : *line_iter)
            cout << it << " ";
        cout << endl;
    }
}

void heuristic_building(
    vector< vector<int>> *routes, vector<vector<int>> adjacent_matrix, 
    int max_num_addr, int dimension, vector<int> *solutions) 
    {
    vector<int>::iterator it, remove_node;
    vector<int> matrix, temporary_route;
    int solution, min_cost = 99999, next_node_cost, next_node, next_i, solution_sum = 0;
    
    for (int i = 1; i < dimension; i++) matrix.push_back(i);

    while (matrix.size() != 0){
        temporary_route.push_back(0);
        next_i = 0;

        while (temporary_route.size() <= max_num_addr) {
            if (matrix.size() == 0) break;

            for(it = matrix.begin(); it != matrix.end(); it ++) {
                next_node_cost = adjacent_matrix.at(*it).at(next_i);

                if(next_node_cost < min_cost) {
                    min_cost = next_node_cost;
                    next_node = *it;
                    remove_node = it;
                }
            }
            
            solution_sum += min_cost;
            next_i = next_node;
            min_cost = 99999;
            temporary_route.push_back(next_node);
            matrix.erase(remove_node);
        }

        // last node
        temporary_route.push_back(0);
        routes->push_back(temporary_route);
        solution_sum += adjacent_matrix.at(0).at(next_i);
        temporary_route.clear();

        solutions->push_back(solution_sum);
        solution_sum = 0;
    }

    show_routes(*routes);
}

void show_routes(vector< vector<int>> routes) {
    vector<vector<int>>::iterator it;

    for(it = routes.begin(); it != routes.end(); it ++){
        for(int i: *it)
            cout << i << "->";
        cout << endl;
    }
}   
