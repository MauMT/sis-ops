using namespace std;
#include <vector>
#include <utility>

struct Memoria{

vector<int> discoDuro;
vector<pair<int,int> > memoriaReal;
Memoria();
};

Memoria::Memoria()
{
    memoriaReal = vector<int>(4096);
    discoDuro = vector<pair<int,int> > (2048);
}