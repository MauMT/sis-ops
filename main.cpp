#include <iostream>
#include "Memoria.h"

using namespace std;
int main() {
  char inputPrimeraLetra;
  Memoria Memoria();
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
      int numMarcosPag = tamProceso/16 + (tamProceso % 16 ? 1 : 0);
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


  }while(inputPrimeraLetra!='E');

}