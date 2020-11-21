using namespace std;
#include "Page.h"

class Process{
    int id;
    int bytes;
    Page pages[];
    int init_timestamp;
    int fin_timestamp;
    int page_faults;

    virtual Page getPageByAddress();
};