#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm> 

using namespace std;

class VND {
    public:
        vector<int> route;

    VND();
    ~VND();

    void swap();
    void two_opt();
    void re_insertion();
    
};