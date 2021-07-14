#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm> 
#include <ctime>        // std::time
#include <cstdlib> 

using namespace std;

class VND {
    public:
        vector<vector<int>> adjacent_matrix, all_routes;
        vector<int> solutions;

    VND();
    ~VND();

    void set_adjacent_matrix(vector<vector<int>> adjacent_matrix);
    void set_all_routes(vector<vector<int>> all_routes);
    void set_initial_solution(vector<int> solutions);

    void swap(vector<int> *route, int *actual_solution);
    void two_opt(vector<int> *route, int *actual_solution);
    void re_insertion(vector<int> *route, int *actual_solution);
    void start_vnd();
    static int shuffle_vector(int value);
    void display_solution();
};