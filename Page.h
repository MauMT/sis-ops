using namespace std;

class Page{
    int in_memory;
    int real_address_start;
    int virtual_address_start;
    //int swap adress;
    Process *processID;
    int last_use;
};