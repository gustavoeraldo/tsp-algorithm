#include "vnd.h"

VND::VND(){
    this->adjacent_matrix;
    this->all_routes;
    this->solutions;
}

VND::~VND(){
    this->adjacent_matrix.clear();
    this->all_routes.clear();
    this->solutions.clear();
}

void VND::set_adjacent_matrix(vector<vector<int>> adjacent_matrix){
    this->adjacent_matrix = adjacent_matrix;
}

void VND::set_all_routes(vector<vector<int>> all_routes){
    this->all_routes = all_routes;
}

void VND::set_initial_solution(vector<int> solutions){
    this->solutions = solutions;
}

int VND::shuffle_vector(int value){ return rand()%value; }

void VND::start_vnd(){
    vector<int>::iterator it;
    vector< vector<int>>::iterator line_iter;
    vector<int> neighbor_structure = {1, 2, 3};
    int i = 0, k;

    for (line_iter = this->all_routes.begin(); line_iter != this->all_routes.end(); line_iter++){
        random_shuffle( neighbor_structure.begin(), neighbor_structure.end(), shuffle_vector );
        while (neighbor_structure.size() != 0){
            k = neighbor_structure.back();
            neighbor_structure.pop_back();
            
            switch (k){
                case 1:
                    this->swap(&(*line_iter), &this->solutions.at(i)); 
                    break;
                case 2:
                    this->two_opt(&(*line_iter), &this->solutions.at(i));
                    break;
                case 3:
                    this->re_insertion(&(*line_iter), &this->solutions.at(i));
                    break;
            }
        }
        
        neighbor_structure = {1, 2, 3};
        i++;        
    }
    
    this->display_solution();
}

void VND::swap(vector<int> *route, int *actual_solution){
    vector<int>::iterator i, j;
    int best_solution, cost, index_i, index_j, best_i, best_j;

    index_i = 1;
    index_j = 2;
    best_solution = *actual_solution;

    for(i = route->begin()+1; i != route->end()-1; i++){
        for(j = i+1; j != route->end()-1; j++){
            cost = *actual_solution - (
                    this->adjacent_matrix.at(*(i)).at(*(i-1)) + 
                    this->adjacent_matrix.at(*(i)).at(*(i+1)) +
                    this->adjacent_matrix.at(*(j)).at(*(j-1)) + 
                    this->adjacent_matrix.at(*(j)).at(*(j+1)) 
                ) +
                (
                    this->adjacent_matrix.at(*(j)).at(*(i-1)) + 
                    this->adjacent_matrix.at(*(j)).at(*(i+1)) +
                    this->adjacent_matrix.at(*(i)).at(*(j-1)) + 
                    this->adjacent_matrix.at(*(i)).at(*(j+1)) 
                );

            if (cost < best_solution){
                best_solution = cost;
                best_i = index_i;
                best_j = index_j;
            }
            index_j++;
        }
        index_i++;
        index_j = index_i+1;
    }

    if (best_solution < *actual_solution){
        iter_swap(&route->at(best_i), &route->at(best_j));
        // cout << "Best i: " << *next_i << "\tBest j: " << *next_j << endl;
        // cout << "Index i: " << best_i << "\tIndex j: " << best_j << endl;
        *actual_solution = best_solution;
    }
}

void VND::two_opt(vector<int> *route, int *actual_solution){
    vector<int>::iterator i, j, next_i, next_j;
    int best_solution, cost, route_size,
    index_i, index_j, best_i, best_j;
    
    index_i = 1;
    index_j = index_i + 3;
    best_solution = *actual_solution;
    route_size = route->size() - 1;

    for(i = route->begin() + 1; i != route->end() - 1; i++){
        for(j = i+3; j != route->end() - 1; j++){
            if(*j == 0) break;
            try {
                cost = *actual_solution - (
                    this->adjacent_matrix.at(*(i)).at(*(i-1)) +  
                    this->adjacent_matrix.at(*(j)).at(*(j+1)) 
                ) +
                (
                    this->adjacent_matrix.at(*(j)).at(*(i-1)) + 
                    this->adjacent_matrix.at(*(i)).at(*(j+1))
                );
            
                if (cost < best_solution){
                    best_solution = cost;
                    best_i = index_i;
                    best_j = index_j;
                    next_i = i; 
                    next_j = j;
                    // cout << "\n\nBest i node: " << *i << endl;
                    // cout << "Best j node: " << *j << endl;
                    // cout << "Best i index: " << best_i << endl;
                    // cout << "Best j index: " << best_j << endl;
                }
            
                index_j++;
            } catch (...) {
                break;
            }

        }
        index_i++;
        index_j = index_i+3;
        if (index_i >= route->size()-2) break;
    }

    if (best_solution < *actual_solution){
        // cout << "Best i: " << *next_i << "\tBest j: " << *next_j << endl;
        // cout << "Index i: " << best_i << "\tIndex j: " << best_j << endl;
        int distance = route_size - best_j;
        reverse(route->begin()+best_i, route->end()-distance);
        *actual_solution = best_solution;
        // cout << "\n\t2-OPT SOLUTION: " << best_solution << endl;
    }

}

void VND::re_insertion(vector<int> *route, int *actual_solution){
    vector<int>::iterator i, j;
    int best_solution, cost, best_i, best_j, node_i, node_j,
    index_i = 1, index_j = 2;

    best_solution = *actual_solution;

    for(i = route->begin() + 1; i != route->end() - 1; i++){
        for(j = i + 1; j != route->end() - 1; j++){
            if (*j == route->back()) break;

            cost = *actual_solution - (
                    this->adjacent_matrix.at(*(i)).at(*(i-1)) + 
                    this->adjacent_matrix.at(*(i)).at(*(i+1)) +
                    this->adjacent_matrix.at(*(j)).at(*(j+1))
                ) + (
                    this->adjacent_matrix.at(*(i-1)).at(*(i+1)) + 
                    this->adjacent_matrix.at(*(i)).at(*(j)) +
                    this->adjacent_matrix.at(*(i)).at(*(j+1)) 
                );

            if (cost < best_solution){
                best_solution = cost;
                best_i = index_i;
                best_j = index_j;
                node_i = *i; 
                node_j = *j;
            }
            index_j++;
        }
        index_i++;
        index_j = index_i+1;
    }

    if (best_solution < *actual_solution){
        *route->erase(route->begin()+best_i);
        *route->insert(route->begin()+best_j, node_i);
        // cout << "Best i: " << node_i << "\tBest j: " << node_j << endl;
        *actual_solution = best_solution;
    }
}

void VND::display_solution(){
    vector<vector<int>>::iterator it;
    vector<int>::iterator k;
    int best_solution = 0, solution = 0;
    
    for (int i : this->solutions)
        best_solution += i;
    
    cout << "Final solution: " << best_solution << "\nRoutes:\n";
    
    for (it = this->all_routes.begin(); it != this->all_routes.end(); it ++){
        for (int i : *it)
            cout << i << ", ";
        cout << ";" << endl;
        // for(k = it->begin(); k != it->end()-1; k++){
        //     solution += this->adjacent_matrix.at(*k).at(*(k+1));
        //     cout << *k << "->";   
        // }
        // cout << "\n";
    }
    // cout << "Real solution: " << solution;
}


