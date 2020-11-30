#include <algorithm>
#include <iostream>

#include "Processor.h"
#include "Clock.h"

using namespace std;

int main() {
    Clock::time = 15;
    Processor processor;
    processor.exec("archivop.txt");
}