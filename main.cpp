//
//  main.cpp
//  PROYECTO TOP
//
//  Created by Theo Almeida on 11/5/23.
//


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct tPolinomio{
    vector<double> coef;      /* Coeficientes */
    int grado;                /* Grado del polinomio */
};

void funcion_monom(string frase, vector<string> &polinomios);
void funcion_apart(vector<string> &polinomios,vector<string> &coeficientes,vector<string> &grados);
void funcion_stringtonum(vector<string> &coeficientes,vector<string> &grados,vector< double> &coeficientes_double,vector<int> &grados_int);
int funcion_maxgrado(vector<int> &grados_int);
void funcion_order_set(vector< double> &coeficientes_double,vector<int> &grados_int,int maximum,int contador, tPolinomio &Pol_num);
double funcion_Maxdegree(vector<tPolinomio> &Zpolinomio);
void funcion_definep(vector<tPolinomio> &DEFPolinom,vector<tPolinomio> &Zpolinomio,double tmax);
void funcion_add(vector<tPolinomio> &DEFPolinom, vector<double> &result,double tmax);
void funcion_print(vector<double> &result,double tmax);
bool validacion_polinomio(string cadena);

int main(int argc, const char * argv[]) {
    int cantidad=0;
    vector<tPolinomio> Zpolinomio;
        //PRIMER WHILE O FUNCION QUE VALIDE QUE EL NUMERO DE POLINOMIOS A SUMAR SEA UN NUMERO
    cout<<"Introduzca la cantidad de polinomios a sumar: ";
    cin>>cantidad;
    while (cin.fail()){ // Validacion del numero de polinomios.
        cin.clear();
        cout<<"Cantidad ingresada invalida. Ingresa un numero entero: ";
        while (cin.get() != '\n') continue;
        cin>>cantidad;
    }
    cin.ignore();
        //HASTA AQUI
    for(int f=0;f<cantidad;f++){
        //SEGUNDO WHILE O FUNCION QUE VALIDE QUE EL POLINOMIO INTRODUCIDO ESTE BIEN DIGITADO ( 5 3*x2 ≠ 53*x2)( 5 espacio 3*x2 == ERROR)
        bool e = false;
        string frase;
        cout<<" Ingrese la cadena del polinomio "<<f+1<<": ";
        while( e==false)
        {
        getline(cin,frase);
        e = validacion_polinomio(frase);
        if (e==false) cout<<"La cadena es incorrecta, procura ingresar cada monomio sin espacios: ";
        }
        //HASTA AQUI
    //..................................Inicio de la lectura de polinomios....................................//
        
        // PASO 1:  Separamos la frase en monomios dentro de un vector
        vector <string> polinomios;
        funcion_monom(frase, polinomios);
        
        //PASO 2:   Separamos cada monomio en su coeficiente y grado
        vector<string> coeficientes;
        vector<string> grados;
        funcion_apart(polinomios, coeficientes, grados);
        
        //PASO 3:   Convertimos cada coeficiente y grado expresado en strings a numeros
        vector< double> coeficientes_double;
        vector<int> grados_int;
        funcion_stringtonum(coeficientes, grados, coeficientes_double, grados_int);
        
        //PASO 4:   Hallamos el grado maximo de solo los monomios del polinomio ingresado
        int maximum=funcion_maxgrado(grados_int);
        
        //PASO 5:   Se ordena los coeficientes y se los asigna a una estructura.
        tPolinomio Pol_num;
        int contador=f;
        funcion_order_set(coeficientes_double, grados_int, maximum, contador, Pol_num);
        
        //PASO 6:   Asignamos el polinomio a un vector con más polinomios
        Zpolinomio.push_back(Pol_num);
        
        //PASO 7:   Vaciar todos los vectores que se han inicializado y creado a excepcion de Zpolinomio como vector madre
        polinomios.clear();
        coeficientes.clear();
        grados.clear();
        coeficientes_double.clear();
        grados_int.clear();
        Pol_num.coef.clear();
        
    }
//.......................................Fin de la lectura de un solo polinomio...................................................//
        //PASO 8:    Hallamos el grado maximo entre todos los polinomios ingresados
        double tmax=funcion_Maxdegree(Zpolinomio);
        //PASO 9:   Definimos a todos los polinomios con un tamaño igual al maximo
        vector<tPolinomio> DEFPolinom;
        funcion_definep(DEFPolinom, Zpolinomio, tmax);
        //PASO 10:  Se Suma todos los componentes del polinomio
        vector<double> result;
        funcion_add(DEFPolinom, result, tmax);
        //PASO 11: Se imprime la suma de los polinomios
        funcion_print(result, tmax);
        cout<<endl;
    return 0;
}
                                    //EJEMPLOS//
//                                                     grados ----> tamaño
//              -3*x5 + 5.12*x4 -32*x3+8*x7+44*x1-9               ---> 0 2 3 4 5 7 ----> 6
//               43*x5 + 50*x4 -12*x3+22*x7+22*x2+19             ---> 0 2 3 4 5 7 ----> 6
//               57*x5 + 3*x9 +3*x13+3*x7+3*x17+17               ---> 0 5 7 9 13 17 ----> 6
//               3*x5 -5.12*x4 +32*x3-8*x7-42*x1-9               ---> 0 2 3 4 5 7 ----> 6

void funcion_monom(string frase, vector<string> &polinomios){
    int nada=0;
    string cadena="";
    for(int i=0;i<=frase.size();i++){
        //Eliminamos los espacios
        if(frase[i]==' ')
            nada=0;
        //Inicializar el signo//
        else if(frase[i]=='-' and i==0)
            cadena="-";
        else if(frase[i]=='+' and  i==0)
            cadena="";
        //Separamos los polinomios por -
        else if( frase[i]=='-' and i!=0){
            polinomios.push_back(cadena);
            cadena="-";}
        //Separamos los polinomios por +
        else if(frase[i]=='+' and  i!=0){
            polinomios.push_back(cadena);
            cadena="";}
        //Unimos los caracteres acotados entre + y -
        else if(frase[i]!= '+' and frase[i]!= '-' and i!=frase.size())
            cadena+=frase[i];
        if(i==frase.size())
            polinomios.push_back(cadena);}
};
void funcion_apart(vector<string> &polinomios,vector<string> &coeficientes,vector<string> &grados){
    int nada=0;
    for(int i=0;i<polinomios.size();i++)   {                //Leemos cada elemento del vector polinomios
       string cadena="";
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
        nada=0;}
};
void funcion_stringtonum(vector<string> &coeficientes,vector<string> &grados,vector< double> &coeficientes_double,vector<int> &grados_int){
    for(int i=0;i<coeficientes.size();i++){
        coeficientes_double.push_back(stod(coeficientes[i]));
        grados_int.push_back(stoi(grados[i]));}
};
int funcion_maxgrado(vector<int> &grados_int){
    int maximum=-1;
    for(int i=0;i<grados_int.size();i++){
        if(grados_int[i]>maximum)
            maximum=grados_int[i];}
    return maximum;
}
void funcion_order_set(vector< double> &coeficientes_double,vector<int> &grados_int,int maximum,int contador, tPolinomio &Pol_num){
    vector<double>coef_aux(maximum+1,0);
    for(int i=0;i<grados_int.size();i++){
        int k=grados_int[i];
        coef_aux[k]=coeficientes_double[i];
    }
    Pol_num.coef=coef_aux;
    Pol_num.grado=contador;
};
double funcion_Maxdegree(vector<tPolinomio> &Zpolinomio){
    double tmax=0;
    for(int i=0;i<Zpolinomio.size();i++){
        if(tmax<Zpolinomio[i].coef.size())
            tmax=Zpolinomio[i].coef.size();}
    return tmax;
};
void funcion_definep(vector<tPolinomio> &DEFPolinom,vector<tPolinomio> &Zpolinomio,double tmax){
    
    for(int f=0;f<Zpolinomio.size();f++){
        vector<double>coef2_aux(tmax,0);
        for(int i=0;i<Zpolinomio[f].coef.size();i++){
            coef2_aux[i]=Zpolinomio[f].coef[i];
        }
        tPolinomio Pol_aux;
        Pol_aux.coef=coef2_aux;
        Pol_aux.grado=f;
        DEFPolinom.push_back(Pol_aux);
    }
};
void funcion_add(vector<tPolinomio> &DEFPolinom, vector<double> &result,double tmax){
    for(int j=0;j<tmax;j++){
        double sumas=0;
        for(int i=0;i<DEFPolinom.size();i++){
            sumas+=DEFPolinom[i].coef[j];
        }
        result.push_back(sumas);
        sumas=0;
    }
};
void funcion_print(vector<double> &result,double tmax){
    int nada=0;
    cout<<endl<<"El polinomio suma es de grado "<<tmax-1<<" :"<<endl;
    for(int i=0;i<result.size();i++){
        if(result[i]!=0 and i==0 )
            cout<<result[i]<<" ";
        else if(result[i]!=0 and result[i]>0 )
            cout<<"+ "<<result[i]<<"*x"<<i<<" ";
        else if(result[i]!=0 and result[i]<0)
            cout<<result[i]<<"*x"<<i<<" ";
        else if(result[i]==0)
            nada=3.1416;}
};
bool validacion_polinomio(string cadena){
    vector<string> terminos;
        string temp;
        bool valido = true;
        
        for (auto car : cadena) {
            if (car == '+' || car == '-') {
                terminos.push_back(temp);
                temp = car;
            } else {
                temp += car;
            }
        }
        terminos.push_back(temp);
        
        for (auto& x : terminos) {
            if (!x.empty() and x[0]=='+' or x[0]=='-'){
                x = x.substr(1);
            }

            // Eliminar espacios en blanco al principio del string
            x.erase(x.begin(), find_if(x.begin(), x.end(), [](unsigned char ch) {
                return !isspace(ch);
            }));
            
            // Eliminar espacios en blanco al final del string
            x.erase(find_if(x.rbegin(), x.rend(), [](unsigned char ch) {
                return !isspace(ch);
            }).base(), x.end());
        }
        // Validacion para que no hayan espacios dentro de cada monomio y tampoco signos o letras demas
        for (auto i: terminos){
            size_t pos= i.find(" ");
            if (pos != string::npos){
                valido = false;
                break;
                }
            else {
                for (int j=0; j<i.size(); j++){
                    if ((int(i[j]!=43) and int(i[j]!=45)and int(i[j]!=46) and int(i[j]!=42) and int(i[j]!=120)) and !(int(i[j])>=48 and int(i[j])<=57))
                        valido=false;
                }
            }
        }
        if (valido==false) return valido;

        // Validacion de si no hay dos signos seguidos
        else {
        string ftemp;
        for(auto x:cadena){
            if(!isspace(x))
                ftemp+=x;
            else if(isspace(x) and (x+1)!=' ' and (x-1)!=' ')
                ftemp+=x;
        }
        cadena=ftemp;
    
        for(int i=0; i<cadena.size(); i++){
            if (((cadena[i]=='+' or cadena[i]=='-') and (cadena[i+1]=='+' or cadena[i+1]=='-')) or
            (cadena[i]=='*' and cadena[i+1]=='*') or (cadena[i]=='x' and cadena[i+1]=='x')){
                valido=false;
                break;}

        }
        return valido;
        }
 
}