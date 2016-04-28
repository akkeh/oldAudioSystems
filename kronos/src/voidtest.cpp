

#include <iostream>


int main() {
    void** test;
    test = new void*[1];
    int* a = new int;
    *a = 10;
    test[0] = (void*)a;
    
    std::cout << "test: " << *(int*)test[0] << std::endl;


};
