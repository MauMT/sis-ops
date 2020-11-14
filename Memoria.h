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
    discoDuro = vector<int>(4096);
    memoriaReal = vector<pair<int,int> > (2048);
}