#include <iostream>
#include "Memoria.h"
#include <algorithm>

using namespace std;


void LRU(){}

void FIFO(){}

int main() {
  char inputPrimeraLetra;
  Memoria Memoria;
  cout<<"Enter a command:\n";
  do{
  
  cin>>inputPrimeraLetra;
  inputPrimeraLetra=toupper(inputPrimeraLetra);
   
  
  
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
    default:
      cout<<"comando inválido\n";
      break;
  }

 
  
  }while(inputPrimeraLetra!='E');

}