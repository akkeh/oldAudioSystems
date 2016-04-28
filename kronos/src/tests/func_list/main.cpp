#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void* funcA(int argc, void** argv) {
    if(argc < 1) return NULL;
    int* result = 0;
    result = (int*) argv[0];
    *result = *result*2;
    return (void*) result;
};

void* funcB(int argc, void** argv) {
    if(argc < 1) return NULL;
    int* res = 0;
    res = (int*) argv[0];
    *res = *res / 2;
    return (void*) res;
};

typedef void* (*func_t)(int, void**);

class FuncList {
public:
    FuncList();
    ~FuncList();
    func_t get_func(int func_id);
    void reload_list();
    int load_dir(const char* dir);
    int create_list();
private:
    func_t Funcs;
    unsigned int Func_c;
};

FuncList::FuncList() {
    

};

FuncList::~FuncList() {


};

int FuncList::create_list() {
    /*
    void* soLib = dlopen("./funcList.so", RTLD_NOW);
    if(!soLib) {
        std::cerr << "\nerror: so lib could not be opened \n";
        return -1;
    };
    */

    //open file with function names:
    std::string filename = "KRNS_funcList";
    openFuncFile:
    std::ifstream funcFile(filename.c_str());
    if(!funcFile) {
            std::cerr << "\nerror: function file could not be opened!\n";
            wrongFile:
            std::cout << "where is " << filename << "?:\n\t$ ";
            std::cin >> filename;
            goto openFuncFile;
    };
    std::cout << "file: " << filename << " succesfully opened\n";
   
    /* 
    // check specific header of file:
    getline(funcFile, line);
    std::cout << "first line: " << line << std::endl;
    if(line != "_KRNS_funcList_") {
        std::cerr << "\nerror: file not correct?\n";
        goto wrongFile;
    }
    */

    std::string line;
    std::vector<std::string> funcNames;
    while( !funcFile.eof() ) {  // while end of file not reached
        getline(funcFile, line);
        if((int)line.c_str()[0] != 0) { // is line not empty?
            std::cout << "function: " << line << " found\n";
            funcNames.push_back(line); 
        }
    }
    funcFile.close();   // close file
    // make  
};




int main() {

    FuncList fList;
    fList.create_list();
/*
    int func_c = 2;
    // list of functions:
    func_ptr* functions;
    functions = new func_ptr[func_c];
    functions[0] = funcA;
    functions[1] = funcB;
    char** func_names = new char*[func_c];
    func_names[0] = "funcA";
    func_names[1] = "funcB";

    int a = 5;
    int b = 10;
    void** argv = new void*[2];
    argv[0] = (void*) &a;
    argv[1] = (void*) &b;

    std::cout << "please choose a function: \n";
    for(int i=0; i<func_c; i++) std::cout << "\t" << i << ":\t" << func_names[i] << std::endl;

    std::cout << "\n$: ";
    std::string inp;
    std::cin >> inp;

    int func_id = atoi(inp.c_str());
    std::cout << "loading function: " << func_names[func_id] << std::endl;


    func_ptr func;
    func = functions[func_id];
    
    int* res = (int*)func(2, argv); 
    std::cout << "result: " << *res << std::endl;
*/
     
};
