//
//  main.cpp
//  Proyecto Final J
//
//  Created by Theo Almeida on 4/5/23.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct tPolinomio {
    long double coef;      /* Coeficientes */
    long double grad;                /* Grado del polinomio */

};

int main(int argc, const char * argv[]) {
    int nada,cantidad=0;
    vector<vector<tPolinomio>> POLIM;
    cout<<"Introduzca la cantidad de polinomios a sumar: ";
    cin>>cantidad;
    cin.ignore();
    for(int f=0;f<cantidad;f++){
        //.............................Inicio de la lectura de polinomios.................................//
    //-----------------LECTURA DEL STRING FRASE SEPARANDO EN TERMINOS (ARREGLAR EL SIGNO NEGATIVO DE FRASE[0]) ---------------------//
        string frase,cadena="";
        vector <string> polinomios;
        cout<<" Ingrese la cadena del polinomio "<<f+1<<": ";
        getline(cin,frase);                 //Obtenemos una frase de texto leida caracter por caracter
        for(int i=0;i<=frase.size();i++){
            //Eliminamos los espacios
            if(frase[i]==' ')
                nada=0;
            //Separamos los polinomios por -
            else if( frase[i]=='-' and frase[0]!='-'){
                polinomios.push_back(cadena);
                cadena="-";}
            //Separamos los polinomios por +
            else if(frase[i]=='+' and frase[0]!='+'){
                polinomios.push_back(cadena);
                cadena="";}
            //Unimos los caracteres acotados entre + y -
            else if(frase[i]!= '+' and frase[i]!= '-' and i!=frase.size())
                cadena+=frase[i];
            else if(i==frase.size())
                polinomios.push_back(cadena);
            else if(frase[0]=='-')
                cadena="-";
            else if(frase[0]=='+')
                cadena="";
        }
        //-----------------------------SEPARAR EL ELEMENTO DEL VECTOR EN SUS DOS COMPONENTES-----------------------------------//
        vector<string> coeficientes;
        vector<string> grados;
        for(int i=0;i<polinomios.size();i++)   {                //Leemos cada elemento del vector polinomios
            cadena="";
            //Lectura de la constante//
            for(int j=0; j<=polinomios[i].size();j++){
                cadena+=polinomios[i][j];
                if(j==polinomios[i].size()){
                    coeficientes.insert(coeficientes.begin(), cadena);
                    cadena="0";
                    grados.insert(grados.begin(),cadena);
                    cadena="";
                    nada=10;
                }
                else if(polinomios[i][j]== 'x'){
                    cadena="";
                    break;}}
            //Fin de la constante//
            for(int j=0; j<=polinomios[i].size();j++){           //Leemos cada caracter del elemento
                if(polinomios[i][j]!= '*' and polinomios[i][j]!= 'x'){  //Obtenemos los coeficientes de cada expresion
                    cadena+=polinomios[i][j];
                    if(j==polinomios[i].size() and nada!=10)
                        grados.push_back(cadena);
                }
                else if(polinomios[i][j]== 'x'){
                    coeficientes.push_back(cadena);
                    cadena="";}}
            nada=0;
        }
        //-----------------------------TRANSFORMACION DE LOS ELEMENTOS DE STRINGS A FLOATS-----------------------------------//
        vector<long double> coeficientes_ldouble;
        vector<long double> grados_ldouble;
        for(int i=0;i<coeficientes.size();i++){
            coeficientes_ldouble.push_back(stold(coeficientes[i]));
            grados_ldouble.push_back(stold(grados[i]));
        }
        //-----------------------------ORDENAMIENTO Y ASIGNACION A UN VECTOR FIJO -----------------------------------//
        long double maximum=-999999999999999;
        for(int i=0;i<coeficientes.size();i++){
            if(grados_ldouble[i]>maximum)
                maximum=grados_ldouble[i];}
        vector<long double> polinom_c(maximum+1,0);           //Creacion de vectores del tamaño de su coeficiente máximo
        vector<long double> polinom_g(maximum+1,0);
        for(int i=0;i<coeficientes_ldouble.size();i++){
            long double k=grados_ldouble[i];
            polinom_g[k]=grados_ldouble[i];
            polinom_c[k]=coeficientes_ldouble[i];
        }
        //-----------------------------ASIGNACION AL VECTOR MADRE -----------------------------------//
        //Asignacion a una estructura//
        vector<tPolinomio> Zpolinomio;
        for(int i=0;i<polinom_c.size();i++){
            tPolinomio temporal;
            temporal.grad= {polinom_g[i]};
            temporal.coef= {polinom_c[i]};
            Zpolinomio.push_back(temporal);
            temporal={0,0};}
        //Asignacion de la estructura al vector madre//
        POLIM.push_back(Zpolinomio);
        for(int u=0;u<polinom_c.size();u++){
            cout<<"Vector "<<u<<" es: "<<polinom_c[u]<<"*x"<<polinom_g[u]<<endl;
        }
        
        polinomios.clear();
        coeficientes.clear();
        grados.clear();
        coeficientes_ldouble.clear();
        grados_ldouble.clear();
        polinom_c.clear();
        polinom_g.clear();
        Zpolinomio.clear();
        
        for(int u=0;u<polinom_c.size();u++){
            cout<<"Vector "<<u<<" es: "<<polinom_c[u]<<"*x"<<polinom_g[u]<<endl;
        }
    }
    //.............................Fin de la lectura de un solo polinomio.................................//
 
    return 0;
  }




//-3*x5 + 5.12*x4 -32*x3+8*x7+4*x2-9
// 43*x5 + 50*x4 -12*x3+22*x7+12*x2+11
// 57*x5 + 3*x9 +3*x13+3*x7+3*x17+13


//          REVISAR TAM DE TODOS LOS VECTORES
//cout<<"polinomios en string:    "<<polinomios.size()<<endl;
//cout<<"coeficientes en string:      "<<coeficientes.size()<<endl;
//cout<<"grados en string:        "<<grados.size()<<endl;
//cout<<"coeficientes en double:      "<<coeficientes_ldouble.size()<<endl;
//cout<<"grados en double:     "<<grados_ldouble.size()<<endl;
//cout<<"tamaño coeficiente final:        "<<polinom_c.size()<<endl;
//cout<<"tamaño grados final:     "<<polinom_g.size()<<endl;

