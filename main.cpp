#include <iostream>
#include "Memoria.h"
#include <algorithm>

using namespace std;

bool contains(vector<char> v1,char c1)
{
  return (std::find(v1.begin(), v1.end(), c1) != v1.end()); 
}

void LRU(){}

void FIFO(){}

int main() {
  char inputPrimeraLetra;
  Memoria Memoria;
  do{
  cin>>inputPrimeraLetra;
  inputPrimeraLetra=toupper(inputPrimeraLetra);
   vector<char> comandos={'P','A','L','C','F','E'};
  if(contains(comandos,inputPrimeraLetra)){
  
  switch(inputPrimeraLetra)
  {
    case 'P':
      int tamProceso, processID;
      cin>>tamProceso>>processID;
      if(tamProceso<=0)
        cout<<"TAMAÑO DE PROCESO INVÁLIDO\n";  
      int numMarcosPag; numMarcosPag  = (tamProceso/16) + (tamProceso % 16 ? 1 : 0);
      break;
    case 'A':
      break;
    case 'L':
      break;
    case 'C':
      break;
    case 'F':
      break;
    case 'E':
      break;
  }

  }else{cout<<"Comando inválido\n";}
  
  }while(inputPrimeraLetra!='E');

}