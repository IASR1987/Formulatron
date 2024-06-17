#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdio>
#include<string>
#include <cctype>



using namespace std;

//DECLARACIÓN DE NUESTRO STRUCT
struct elementos{
    string nombre;
    string siglas;
    int valencia;
    string prefijo;
    string tipo;
    string cantidad_valencias;
};


/////////////////////////////////////////////////////
//                    FUNCIONES                    //
/////////////////////////////////////////////////////
void cabecera();

///////////////////////////////////////////////////////
//               FORMULA A COMPUESTO                //
/////////////////////////////////////////////////////
void menu_compuesto_formula();
bool buscar_elemento1(string elemento1);
bool oxido_correcto(string elemento1, int valencia_oxido);
int indice_oxido(string indice1, string indice2);
string roma(int valencia_oxido);
string stock_oxido(string elemento1, string elemento2, int valencia_oxido, string numero_romano);
string tradicional_oxido(string elemento1, string elemento2, int valencia_oxido);
string sistematica_oxido(string elemento1, string indice1, string indice2);


///////////////////////////////////////////////////////
//               COMPUESTO A FÓRMULA                //
/////////////////////////////////////////////////////
void de_formula_a_nomenclatura();

int oxido_formula_escrita(string formula_escrita);
string formula_tradicional(string formula_escrita, int tipo_oxido);
string formula_stock(string formula_escrita);
string elemento_sistematica(string formula_escrita);
int indice2_int_siste(string formula_escrita);
bool valencia_correcta( string elemento1, int indice2_int);
string sistematica_nomenclatura_formula(string elemento1, int indice2_int);
void guardarFormulaEnFichero(string formula_escrita_F_N, string formula_escrita); 

void creditos();

/////////////////////////////////////////////////////
//                MAIN PRINCIPAL                   //
/////////////////////////////////////////////////////
int main(){
    string eleccionmenu, menu_principal_string;
    int menu_principal_int;
    bool salir_menu_principal=false;
    string presentacion="Bienvenido, a FORMULATRÓN. Este programa ha sido diseñado por mí, Ismael Soria, probablemente el mejor programador de su casa y también el único,jejejejeje. Espero que os guste y a Rufo más";
    SetConsoleOutputCP(CP_UTF8);

        for(int i=0; i<presentacion.size(); i++){
            cout<<presentacion[i];
            Sleep(50);
        }
        cout<<endl;
        system("PAUSE");
        system("cls");
        
        cabecera();
        system("PAUSE");
        system("cls");

    //menú del programa    
    do{
        do{
        cabecera();
                cout<<"                                    -------------------------------------------------------------------------------"<<endl;
                cout<<"                                    --------------------             *||*MENÚ*||*              --------------------"<<endl; 
                cout<<"                                    --------------------     1. Fórmula a compuesto.           --------------------"<<endl;
                cout<<"                                    --------------------     2. Compuesto a la fórmula.        --------------------"<<endl;
                cout<<"                                    --------------------     3. Salir.                         --------------------"<<endl;
                cout<<"                                    -------------------------------------------------------------------------------"<<endl;
                cin>>menu_principal_string;
                if(menu_principal_string != "1" && menu_principal_string != "2" && menu_principal_string != "3"){
                    cout<<"Introduce un valor comprendido entre 1 y 3"<<endl;
                    salir_menu_principal=false;
                }else{
                    salir_menu_principal=true;
                }
                    
                Sleep(1000);
                system("cls");
        }while(salir_menu_principal==false);

        //transfromamos en int para poder entrar en switch
        //cada opción nos permite entrar en una de las partes del programa
        menu_principal_int=stoi(menu_principal_string);

        switch (menu_principal_int)
        {
        case 1:
            menu_compuesto_formula();
            
            break;

        case 2:
            de_formula_a_nomenclatura();

        default:
            break;
        }

        //si selecionamos opcion salir
        if(menu_principal_string=="3"){
                eleccionmenu="salir";
            }else{//si la opcion fue formular, nos preguntará si queremos volver al menú o salir
                cout<<"¿Quieres volver al menú principal? Pulsa si o no"<<endl;
                cin>>eleccionmenu;
                Sleep(2000);
                system("cls");
            }
    }while(eleccionmenu=="si" || eleccionmenu=="SI" || eleccionmenu=="Si" ||eleccionmenu=="s" || eleccionmenu=="S");
    
    
    creditos();
}


/////////////////////////////////////////////////////
//             FUNCIÓN: cabecera                   //
// cabecera de nuestro programa                    //
// Entrada =                                       //
// Salida =                                        //
/////////////////////////////////////////////////////
void cabecera(){

    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------*---------------------------"<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------*----------------------------"<<endl;
    cout<<"------------   *******   *******   *******   *     *   *     *   *         ********   *******   *******   *******   **    *   ------------"<<endl;
    cout<<"------------   *         *     *   *     *   *** ***   *     *   *         *      *      *      *     *   *     *   * *   *   ------------"<<endl;
    cout<<"------------   *****     *     *   *******   * * * *   *     *   *         *      *      *      *******   *     *   *  *  *   ------------"<<endl;
    cout<<"------------   *         *     *   *   *     * *** *   *     *   *         ********      *      *   *     *     *   *   * *   ------------"<<endl;
    cout<<"------------   *         *     *   *    *    *  *  *   *     *   *         *      *      *      *    *    *     *   *    **   ------------"<<endl;
    cout<<"------------   *         *******   *     *   *     *   *******   *******   *      *      *      *     *   *******   *     *   ------------"<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
}

/*--------------------------------------------------------------------------------------------*/

/****************************************************/
/********************PRIMERA PARTE*******************/
/***************DE FÓRMULA A COMPUESTO***************/
/****************************************************/

/////////////////////////////////////////////////////
//        FUNCIÓN: menu_compuesto_formula          //
// Cuerpo principal del programa en la parte       // 
// fórmula a compuesto                             //
// Entrada =                                       //
// Salida =                                        //
/////////////////////////////////////////////////////
void menu_compuesto_formula(){
    string eleccionmenu="s", elemento1, elemento2, indice1, indice2, numero_romano, formula,eleccion_nomenclaturas_oxidos_string, frase_guardado=".";
    bool elemento_valido=false, oxido_valido=false;
    int contador_elemento1=0, indice2_int, contador_oxidos=0, valencia_oxido, eleccion_nomenclaturas_oxidos_int=0, contador_ficheros=0;
    remove("formulacion.txt") == 0;
    do{   
        do{
                
            if(contador_elemento1>=1){
                cout<<"El elemento introducido es incorrecto"<<endl;//mensaje de error si no es un elemento posible
                Sleep(1000);
                system("cls");
            }
            //se introduce el primer elemento de la fórmula
            cout<<"introduce el primer elemento"<<endl;
            cin>>elemento1;
                
            for (int i = 0; i < elemento1.length(); i++){//un for que recorre el elemento para ponerlo en mayúsculas
                elemento1[i] = toupper(elemento1[i]);//funcion que pone todas las letras en mayúsculas
            }

            elemento_valido = buscar_elemento1(elemento1);//función que busca si los elementos se encuentran en el fichero metales.txt, nos devuelve un booleano

            contador_elemento1++;//es un contador de control para que salte un mensaje de error, cuando el elemento introducido por usuario sea incorrecto

            if(elemento_valido==true){
                Sleep(1000);
                system("cls"); 
            }

        }while(elemento_valido==false);

            contador_elemento1=0;//reiniciamos el contador por si introducimos más formulas no nos salte el mensaje de error 

        do{
            //se introduce el indice del elemento1
            cout<<"introduce su índice"<<endl;
            cin>>indice1;

            if(indice1 != "1" && indice1 != "2"){//en óxidos ese índice sólamente puede adoptar dos valores 1 y 2
                cout<<"Introduce un índice valido: 1-2";
            }
                
            Sleep(1000);
            system("cls");

        }while(indice1 != "1" && indice1 != "2");//sólo pueden ser 1 y 2 valores que puede tener el  O

        do {

            //se introduce el segundo elemento de la fórmula sólo puede ser oxígeno
            cout<<"introduce el segundo elemento"<<endl;
            cin>>elemento2;
            
            for (int i = 0; i < elemento2.length(); i++){ 
                elemento2[i] = toupper(elemento2[i]);/*funcion que pone todas las letras en mayúsculas*/
            }
            if(elemento2=="o" || elemento2=="O"){
                elemento_valido= true;
            }else{
                cout<<"El elemento introducido es incorrecto"<<endl;//mensaje de error
                elemento_valido=false;
                Sleep(1000);
                system("cls");
            }
            
            if(elemento_valido==true){
                Sleep(1000);
                system("cls"); 
            }
            

        }while(elemento_valido==false);


        do{
            //indice del elemento 2
            cout<<"introduce su índice"<<endl;
            cin>>indice2;

            if(indice2 != "1" && indice2 != "2" && indice2 != "3" && indice2 != "4" && indice2 != "5" && indice2 != "6" && indice2 != "7"){//valores posibles de indice2
                cout<<"Introduce un índice valido: valores comprendidos entre 1 y 7";
            }

                Sleep(1000);
                system("cls");

        }while(indice2 != "1" && indice2 != "2" && indice2 != "3" && indice2 != "4" && indice2 != "5" && indice2 != "6" && indice2 != "7");
        
        //se informa al usuario de la fórmula introducida no se valora si es correcta o no
        if(indice1=="1" && indice2=="1"){//cuando el valor de los índices es 1 no se muestra por pantalla
            cout<<"LA FÓRMULA INTRODUCIDA ES:"<< endl;/**/
            formula=elemento1+elemento2;
            cout<<formula<<endl;
            cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
        }else if(indice1=="1"){
            cout<<"LA FÓRMULA INTRODUCIDA ES:"<< endl;
            formula=elemento1+elemento2+indice2;
            cout<<formula<<endl;
            cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
        } else if(indice2=="1"){
            cout<<"LA FÓRMULA INTRODUCIDA ES:"<< endl;
            formula=elemento1+indice1+elemento2;
            cout<<formula<<endl;
            cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
        }else{
            cout<<"LA FÓRMULA INTRODUCIDA ES:"<< endl;
            formula=elemento1+indice1+elemento2+indice2;
            cout<<formula<<endl;
            cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
        }
        
            
        contador_oxidos=0;//reiniciamos la variable de control, para cuando el programa pase aquí por segunda vez

        //este if controla que se haga la primera vez que entre en el bucle y despúes se pueda entrar en el menú tantas veces como nos haga falta
        //sin necesidad de que el bucle se realice de nuevo 
        if(contador_oxidos==0){
            //esta función determina si las valencias a partir de los índices introducidos por el usuario pueden ser correctas
            //nos devuelve un int denominado valencia_oxido, si las valencias no son correctas y se devuelve un 0
            //en los demás casos devolverá el valor de la valencia, que debe tener el elemento
            valencia_oxido = indice_oxido(indice1,indice2);

            if(valencia_oxido==0){
                cout<<"los índices introducidos no se corresponde a las valencias de los elementos, has introducido una fórmula incorrecta"<<endl;//si valencia_oxido=0 mensaje de error
                cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
                Sleep(3000);
                system("cls");
                oxido_valido=false;//para que no entre en menú nomenclaturas
                eleccion_nomenclaturas_oxidos_string="1";
                }

                if(valencia_oxido!=0){
                    oxido_valido = oxido_correcto (elemento1, valencia_oxido);//esta funcion comprueba que la valencia que nos devolvió la anterior función se corresponde al elemento introducido
                    contador_oxidos;//al aumentar el contador conseguimos que ya no se vuelva a entrar en este bucle
                if(oxido_valido==true){
                    cout<<"Compuesto válido"<<endl;
                    cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
                }else{
                    cout<<"Compuesto no válido"<<endl;
                    cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
                }
                    
                eleccion_nomenclaturas_oxidos_string="1";
                Sleep(3000);
                system("cls");

                }
                    
            }

            //menu nomenclaturas que nos da distintas opciones
            while(eleccion_nomenclaturas_oxidos_string != "6" && oxido_valido==true){
                do{
                    if(oxido_valido==true){
                        cout<<"NOMENCLATURAS"<<endl;
                        cout<<"1. Stock"<<endl;
                        cout<<"2. Tradicional"<<endl;
                        cout<<"3. Sistemática"<<endl;
                        cout<<"4. Con las tres nomenclaturas"<<endl;
                        cout<<"5. Guardar en fichero"<<endl;
                        cout<<"6. Salir"<<endl;
                        cin>>eleccion_nomenclaturas_oxidos_string;
                        Sleep(2000);
                        system("cls");
                        
                        if(eleccion_nomenclaturas_oxidos_string!="1" && eleccion_nomenclaturas_oxidos_string!="2" && eleccion_nomenclaturas_oxidos_string!="3" && eleccion_nomenclaturas_oxidos_string!="4" && eleccion_nomenclaturas_oxidos_string!="5" && eleccion_nomenclaturas_oxidos_string!="6" ){
                            cout<<"---------------------------------------------------------"<<endl;
                            cout<<"La elección es incorrecta, volverás al menú Nomenclaturas"<<endl;/*mensaje de error si lo introducido en el menú es incorrecto*/
                            cout<<"---------------------------------------------------------"<<endl;
                            Sleep(2000);
                            system("cls");
                        }
                    
                    }
                }while(eleccion_nomenclaturas_oxidos_string!="1" && eleccion_nomenclaturas_oxidos_string!="2" && eleccion_nomenclaturas_oxidos_string!="3" && eleccion_nomenclaturas_oxidos_string!="4" && eleccion_nomenclaturas_oxidos_string!="5" && eleccion_nomenclaturas_oxidos_string!="6"  );
                    
                ofstream documento("formulacion.txt", ios::app);//lo abrimos para despúes poder guradar las fórmulas

                eleccion_nomenclaturas_oxidos_int=stoi(eleccion_nomenclaturas_oxidos_string);//puedan ser valores para entrar switvh

                switch (eleccion_nomenclaturas_oxidos_int){
                        case 1://stock
                            /*función que transforma la valencia de la función en numero romano*/
                            numero_romano=roma(valencia_oxido);
                            cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                            cout<<"La fórmula "<<formula<<" en nomenclatura stock es "<<stock_oxido(elemento1,elemento2, valencia_oxido, numero_romano)<<endl;
                            cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                            system("pause");
                            system("cls");
                            break;

                        case 2://tradicional
                            cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                            cout<<"La fórmula "<<formula<<" en nomenclatura tradicional es "<<tradicional_oxido(elemento1, elemento2, valencia_oxido)<<endl;
                            cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                            system("pause");
                            system("cls");
                            break;

                        case 3://sitemática
                            cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                            cout<<"La fórmula "<<formula<<" en nomenclatura sistemática es "<<sistematica_oxido(elemento1, indice1, indice2)<<endl;
                            cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                            system("pause");
                            system("cls");
                            break;

                        case 4://todas juntas
                            cout<<"Fórmula: "<<formula<<endl;
                            numero_romano=roma(valencia_oxido);
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            cout<<"Stock: "; 
                            cout<<stock_oxido(elemento1,elemento2, valencia_oxido, numero_romano)<<endl;
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            cout<<endl<<"Tradicional: ";
                            cout<<tradicional_oxido(elemento1, elemento2, valencia_oxido)<<endl;
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            cout<<endl<<"Sistemática: ";
                            cout<<sistematica_oxido(elemento1, indice1, indice2)<<endl;
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            system("pause");
                            system("cls");
                            break;
                        
                        case 5://guardar en fichero
                            numero_romano=roma(valencia_oxido);
                            stock_oxido(elemento1,elemento2, valencia_oxido, numero_romano);
                            sistematica_oxido(elemento1, indice1, indice2);
                            tradicional_oxido(elemento1, elemento2, valencia_oxido);
                            
                                if (documento.is_open()){
                                    documento << "Fórmula: " << formula << "  " << "Stock: " << stock_oxido(elemento1, elemento2, valencia_oxido, numero_romano)<< "       "  << "Tradicional: "<< tradicional_oxido(elemento1, elemento2, valencia_oxido)<< "       " << "Sistemática: " << sistematica_oxido(elemento1, indice1, indice2)<<endl;
                                } else {
                                    cout << "Error al abrir archivo";
                                }
                                documento.close();

                                //animación de guardar
                                for(int i=0; i<=25; i++){
                                    cout<<frase_guardado;
                                    Sleep(100);
                                }
                                cout<<"guardado correcto"<<endl;
                                Sleep(3000);
                                system("cls");
                            break;

                        default:
                            break;
                        }
                
            }; 

            cout<<"----------------------------------------------------------------------"<<endl;
            cout<<"Si quieres introducir otra fórmula pulsa Si, para salir introduzca No."<<endl;
            cout<<"----------------------------------------------------------------------"<<endl;
            cin>>eleccionmenu;
            Sleep(2000);
            system("cls");

    }while(eleccionmenu=="si" || eleccionmenu=="SI" || eleccionmenu=="Si" ||eleccionmenu=="s" || eleccionmenu=="S");
}

/////////////////////////////////////////////////////
//        FUNCIÓN: buscar_elemento1                //
// Determina si el elemento introducido por        //
// teclado es válido                               //
// Entrada = elemmento introducida por teclado     //
// Salida = boolenao true o false                  //
/////////////////////////////////////////////////////
bool buscar_elemento1(string elemento1){
    ifstream archivo("elemento1.txt");
    elementos elemento;
    bool elemento_valido=false;

    //se busca si el elemento introducido se encuentra en nuestro fichero
    if (archivo.is_open()) {
        while (archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) {
            if(elemento1==elemento.siglas){
                elemento_valido=true;
            }
        }
    }

    archivo.close();

    return elemento_valido;
}


/////////////////////////////////////////////////////
//        FUNCIÓN: indice_oxido                    //
// Determina si los índices son correctos          //
// Entrada = los valores de ambos índices          //
// Salida = un entero que nos indica que matemati- //
// mente nuestos índices son válidos               //
/////////////////////////////////////////////////////
int indice_oxido(string indice1, string indice2){
    int valencia_oxido=0;
    
    //comprobamos si los índices pueden ser correctos
    if(indice1=="1"){
        if(indice2=="1"){
            valencia_oxido=2;
        }else if(indice2=="2"){
            valencia_oxido=4;
        }else if(indice2=="3"){
            valencia_oxido=6;
        }
    }else if(indice1=="2"){
        if(indice2=="1"){
            valencia_oxido=1;
        }else if(indice2=="3"){
            valencia_oxido=3;
        }else if(indice2=="5"){
            valencia_oxido=5;
        }else if(indice2=="7"){
            valencia_oxido=7;
        }
    }else{
        valencia_oxido=0;
    }
    return valencia_oxido;
}

/////////////////////////////////////////////////////
//        FUNCIÓN: oxido_correcto                  //
// Determina si los índices son correctos          //
// Entrada = los valores de ambos índices          //
// Salida = un entero que nos indica si es valido  //
// o no.                                           //
/////////////////////////////////////////////////////
bool oxido_correcto(string elemento1, int valencia_oxido){
    bool oxido_valido = false;
    ifstream archivo("elemento1.txt");
    elementos elemento;

    //comprobamos que las valencias y el elemento son correctos
    if (archivo.is_open()) {
        while (archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) {
            if (elemento1 == elemento.siglas) {
                if (valencia_oxido == elemento.valencia) {
                    oxido_valido = true;
                }
            }
            }
                }else{
                    cout<<"error al abrir archivo";
                    }

        archivo.close();

    return oxido_valido;
}

/*****************************************************/
/////////////////     STOCK      /////////////////////
/****************************************************/
/////////////////////////////////////////////////////
//                 FUNCIÓN: roma                   //
// transforma el indice del elemento en números    //
// romanos.                                        //
// Entrada = valencia que aparece en oxígeno.      //
// Salida = valor en números romanos.              //
//                                                 //
/////////////////////////////////////////////////////
string roma(int valencia_oxido){
    string numero_romano;
    
    //pasamos la valencia a numeros romanos.
    switch(valencia_oxido) {
    
        case 1:
            numero_romano = "(I)";
            break;
    
        case 2:
            numero_romano = "(II)";
            break;
    
        case 3:
            numero_romano = "(III)";
            break;
    
        case 4:
            numero_romano = "(IV)";
            break;
    
        case 5:
            numero_romano = "(V)";
            break;
    
        case 6:
            numero_romano = "(VI)";
            break;
    
        case 7:
            numero_romano = "(VII)";
            break;
    
        default:
            numero_romano = "Número inválido";
    }
    
    return numero_romano;
}

/////////////////////////////////////////////////////
//             FUNCIÓN: stock_oxido                //
// formula en nomenclatura stock                   //
// Entrada = los valores de ambos índices          //
// Salida = un entero que nos indica si es valido  //
// o no.                                           //
/////////////////////////////////////////////////////
string stock_oxido(string elemento1, string elemento2, int valencia_oxido, string numero_romano){
    ifstream archivo("elemento1.txt");
    elementos elemento;
    string stock_oxido, cantidad_valencias;

    //comprobamos si pueden ser válidos los índices y los elementos
    if (archivo.is_open()) {
        while (archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) {
            if(elemento1==elemento.siglas){
                elemento1=elemento.nombre;
                cantidad_valencias=elemento.cantidad_valencias;
            }
        }
    }
    archivo.close();

    //tenemos que tener en cuenta si el elemnto tiene una sola valencia o más, ya que se formula de manera distina
    if(cantidad_valencias=="una"){
        stock_oxido= "Óxido de " + elemento1;
    } else if(cantidad_valencias=="mas"){
        stock_oxido= "Óxido de " + elemento1 + numero_romano;
    }else{
        stock_oxido="Se ha producido un error";
    }
    

    return stock_oxido;
}

/*******************************************************/
/////////////////  TRADICIONAL       ////////////////////
/*******************************************************/

/////////////////////////////////////////////////////
//           FUNCIÓN: tradicional_oxido            //
// formula en nomenclatura tradiconal              //
// Entrada = recibe elemento                       //
// Salida = un entero que nos indica si es valido  //
// o no.                                           //
/////////////////////////////////////////////////////
string tradicional_oxido(string elemento1, string elemento2, int valencia_oxido){
    ifstream archivo("elemento1.txt");
    elementos elemento;
    string tradicional_oxido, tipo_de_elemento;

    //se determina si el elemento es correcto, después identificamos el prefijo con el que se va a formular
    if (archivo.is_open()) {
        while (archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) {
            if(elemento1==elemento.siglas){
                if(valencia_oxido==elemento.valencia){
                elemento1=elemento.prefijo;
                    tipo_de_elemento=elemento.tipo;
                }
            }
        }
    }

    archivo.close();

    //dependiendo de si es metal o no metal, se formula de uan forma u otra
    if (tipo_de_elemento=="metal")
    {
        tradicional_oxido= "Óxido " + elemento1;
    }if (tipo_de_elemento=="nometal"){
        tradicional_oxido= "Anhídrido " + elemento1;
    }
    
    

    return tradicional_oxido;
}

/*******************************************************/
/////////////////  SISTEMÁTICA       ////////////////////
/*******************************************************/

/////////////////////////////////////////////////////
//          FUNCIÓN: sistemática_oxido             //
// formula en nomenclatura stock                   //
// Entrada = los valores de ambos índices          //
// Salida = un entero que nos indica si es valido  //
// o no.                                           //
/////////////////////////////////////////////////////
string sistematica_oxido(string elemento1, string indice1, string indice2){
    ifstream archivo("elemento1.txt");
    elementos elemento;
    string prefijo_oxido, prefijo_elemento, sistematica_oxido, cantidad_valencias;
    int valencia_elemento = stoi(indice1);
    int valencia_oxigeno = stoi(indice2);

    //identificamos el elemento, tenemos en cuentas cuantas valencias tiene
    if (archivo.is_open()) {
        while (archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) {
            if(elemento1==elemento.siglas){
                elemento1=elemento.nombre;
                cantidad_valencias=elemento.cantidad_valencias;
            }
        }
    }
    archivo.close();

    //dependiendo de las valencias, habrá que ponerle un prefijo al óxido
    switch (valencia_oxigeno)
    {
    case 1:
        prefijo_oxido="Mon";
        break;
    case 2:
        prefijo_oxido="Di";
        break;
    case 3:
        prefijo_oxido="Tri";
        break;
    case 4:
        prefijo_oxido="Tetra";
        break;
    case 5:
        prefijo_oxido="Penta";
        break;
    case 6:
        prefijo_oxido="Hexa";
        break;
    case 7:
        prefijo_oxido="Hepta";
        break;
    default:
        break;
    }

    //dependiendo de las valencias, habrá que ponerle un prefijo al elemento
    switch (valencia_elemento)
    {
    case 1:
        prefijo_elemento="";
        break;
    case 2:
        prefijo_elemento="di";
        break;
    default:
        break;
    }

    //si el elemento sólo tiene una valencia no lleva prefijo el elemento
    if(cantidad_valencias=="una"){
        sistematica_oxido=prefijo_oxido+"óxido de " + elemento1;
    }else if(cantidad_valencias=="mas"){
        sistematica_oxido = prefijo_oxido+ "óxido de " + prefijo_elemento + elemento1; 
    }else{
        sistematica_oxido="Se ha producido un error";
    }
    
    return sistematica_oxido;
}

/*--------------------------------------------------------------------------------------------*/

/****************************************************/
/********************SEGUNDA PARTE*******************/
/***************DE COMPUESTO A FÓRMULA***************/
/****************************************************/

/////////////////////////////////////////////////////
//      FUNCIÓN: de_formula_a_nomenclatura         //
// Cuerpo principal del programa                   //
// Entrada =                                       //
// Salida =                                        //
/////////////////////////////////////////////////////
void de_formula_a_nomenclatura(){
    string formula_escrita, subcadena1="oxido", subcadena2="anhidrido", eleccionmenu, elemento1;;
    int tipo_oxido, oxido_formula=0;
    string sistematica_F_N, tradicional_F_N, stock_F_N;
    int indice2_int, menu_opciones;
    bool valencia_correcta_sistematica;
    string formula_escrita_F_N;
    remove("nomenclaturas.txt") == 0;//borrar el fichero
    

    do{

        cin.ignore();

        cout<<"---------------------------------------------------------------------------"<<endl;
        cout<<"Introduce el compuesto"<<endl;//error la primera vez
        cout<<"---------------------------------------------------------------------------"<<endl;
        getline(cin,formula_escrita);
        cout<<"---------------------------------------------------------------------------"<<endl;
        Sleep(1000);
        system("cls");
        oxido_formula=oxido_formula_escrita(formula_escrita);

        //cada parte del switch, es de un tipo de nomenclatura.
        switch (oxido_formula){
            case 1:
                tradicional_F_N=formula_tradicional(formula_escrita, tipo_oxido);
                break;
            case 2:
                stock_F_N=formula_stock(formula_escrita);
                break;
            case 3:
                elemento1=elemento_sistematica(formula_escrita);
                indice2_int=indice2_int_siste(formula_escrita);
                valencia_correcta_sistematica=valencia_correcta(elemento1, indice2_int);
                    
                    if(valencia_correcta_sistematica==true){
                        sistematica_F_N=sistematica_nomenclatura_formula(elemento1, indice2_int);
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            cout<<formula_escrita<<" se corresponde a la fórmula "<<sistematica_F_N<<"."<<endl;
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            formula_escrita_F_N=sistematica_F_N;
                            guardarFormulaEnFichero(formula_escrita_F_N, formula_escrita);

                    }else if(valencia_correcta_sistematica==false){
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            cout<<"introducido un compuesto no válido"<<endl;
                            cout<<"---------------------------------------------------------------------------"<<endl;
                    }

                    
                break;
            case 4:
                cout<<"---------------------------------------------------------------------------"<<endl;
                cout<<"Tienes ganitas de reventarme el programa."<<endl;
                cout<<"---------------------------------------------------------------------------"<<endl;
                Sleep(2000);
                system("cls");
                break;
            default:
                break;
        }

        cout<<"---------------------------------------------------------------------------"<<endl;
        cout<<"Introducir otra fórmula pulsa Si, para salir pulsa cualquier otra cosa"<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
        cin>>eleccionmenu;
        cout<<"---------------------------------------------------------------------------"<<endl;
        Sleep(1000);
        system("cls");

    }while(eleccionmenu=="si" || eleccionmenu=="SI" || eleccionmenu=="Si" ||eleccionmenu=="s" || eleccionmenu=="S");

}

/////////////////////////////////////////////////////
//        FUNCIÓN: oxido_formula_escrita           //
// Determina en que nomenclatura esta la fórmula   //
// Entrada = compuesto introducida por teclado     //
// Salida = número entero entre 1-4                //
/////////////////////////////////////////////////////
int oxido_formula_escrita(string formula_escrita){
    ifstream archivo("elemento1.txt");
    int contador_palabras = 0, oxido_formula_escrita=0, contador_espacios=0, oxido_stock=0;
    string palabra;
    string lista_stock[7]={"monoxido","dioxido","trioxido","tetraoxido","pentaoxido","hexaoxido","heptaoxido"};
    elementos elemento;
    string primera_palabra, ultima_palabra;

    //contamos los espacios
    for(int i=0; i<formula_escrita.size(); i++){
        if(formula_escrita[i]==' '){
            contador_espacios++;
        }
    }
    //podemos determinar la nomenclatura por si tiene dos o tres palabras
    contador_palabras=contador_espacios+1;

    //determinamos la primera palabra y la última
        //utilizaremos la primera palabra para identicar
        primera_palabra = formula_escrita.substr(0, formula_escrita.find(' '));
        //co
        ultima_palabra = formula_escrita.substr(formula_escrita.find_last_of(' ') + 1);


    //nomenclatura tradicional tiene dos palabras
    if(contador_palabras==2){
        oxido_formula_escrita=1;
    //nomenclatura stock y sitematica contienen 3 palabras    
    }else if(contador_palabras==3){
        //en stock la primera palabra sólo puede tener 7 configuraciones por lo que creamos un arrays comprobando si se corresponde a alguna configuración válida
        for(int i=0; i<7; i++){
            if(primera_palabra==lista_stock[i]){
                oxido_stock=2;//esta variable indica que existe una configuración que es correcta
                              //como no puedo parar el bucle sin un break o poniendo otra condición creo una variable
            }else{//si no encontramos ninguna configuración valida de stock la formula_escrita sera sistemática
                oxido_formula_escrita=3;
            }
            if(oxido_stock==2){
                oxido_formula_escrita=oxido_stock;//oxido_stock se iguala a oxido_formula_escrita y asi ya entrara después en nuestro switch
            }
        }
    }else{
        oxido_formula_escrita=4;//cualquier configuración restante
    }

    return oxido_formula_escrita;
}


/*******************************************************/
/////////////////  TRADICIONAL       ////////////////////
/*******************************************************/

/////////////////////////////////////////////////////
//        FUNCIÓN: tradicional(F_N)                //
// Formula en nomenclatura tradicional             //
// Entrada = compuesto introducida por teclado     //
// Salida = fórmula en nomenclatura tradicional    //
/////////////////////////////////////////////////////
string formula_tradicional(string formula_escrita, int tipo_oxido){

    ifstream archivo("elemento1.txt");
    string primera_palabra, ultima_palabra,formula_tradicional,elemento1, indice1_string,indice2_string,formula_escrita_F_N;
    int indice2_int, indice1_int=2;
    elementos elemento;
    bool elemento_erroneo=false, elemento_identificado=false;

    //determinamos la primera palabra y la última con ello podremos identificar las valencias y el elemento que conforma el óxido
    //primera_palabra OXIDO-ANHIDRIDO
    primera_palabra = formula_escrita.substr(0, formula_escrita.find(' '));
    //en tradicional ultima_palabra tiene configuracion exclusiva para(ELEMENTO-VALENCIA)
    ultima_palabra = formula_escrita.substr(formula_escrita.find_last_of(' ') + 1);
    
    //comprobamos que la segund apalabra que debe hacer refeencia al elemento, es realmente un elemento y no cualqueir otra cosa
    if (archivo.is_open()){
        while ((archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) && elemento_identificado==false){
            if(ultima_palabra==elemento.prefijo){
                elemento_identificado=true;//salga del fichero, y nos permita saber si se tarta de un elemento
            }
        }
    }else{
        cout<<"error al abrir archivo";
        cout<<"---------------------------------------------------------------------------"<<endl;
    }    
    archivo.close();//reiniciar el fichero

    archivo.open("elemento1.txt");//abrirlo de nuebo 


    //si es un elemento reconocido continuamos el programa
    if(elemento_identificado==true){
    //los oxidos en nomenclatura tradicional dependiendo del elemento utilizado tienen dos posibles configuraciones//
    //elemento es metal => OXIDO                                                                                   //
    //elemento es no metal => ANHÍDRIDO                                                                            //
        if (archivo.is_open()){
            while (archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias){
                if (primera_palabra == "oxido"){//si la primera palabra es oxido debe ser un metal
                    if (ultima_palabra == elemento.prefijo){
                        if(elemento.tipo=="metal"){//se comprueba si es metal 
                            elemento1=elemento.siglas;// identificamos el elemento con su símbolo
                            indice2_int=elemento.valencia;// identificamos el elemento con su valencia
                            elemento_erroneo=true;//controla que en casos erroneos no nos haga la fórmula

                        }else{
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            cout<<"Has introducido un no metal, por lo cual no puede ser un óxido"<<endl;//has introducido un oxido+no metal
                        }
                    }
                }else if(primera_palabra == "anhidrido"){//si la primera palabra es anhídrido debe ser no metal
                    if (ultima_palabra == elemento.prefijo){
                        if(elemento.tipo=="nometal"){//se comprueba si es no metal, e identificamos, si es correcto, el elemento con su símbolo
                            elemento1=elemento.siglas;// identificamos el elemento con su símbolo
                            indice2_int=elemento.valencia;// identificamos el elemento con su valencia
                            elemento_erroneo=true;//controla que en casos erroneos no nos haga la fórmula
                        }else{
                            cout<<"---------------------------------------------------------------------------"<<endl;
                            cout<<"Has introducido un metal, por lo cual no puede ser un anhídrido"<<endl;        
                        }
                    }
                }
            }
        }else{
            cout<<"error al abrir archivo";
            cout<<"---------------------------------------------------------------------------"<<endl;
        }    
    }
    
    if(elemento_erroneo==true){
        //calculamos los valores de las valencias que se mostraran en pantalla
        //el oxígeno siempre es 2, con valencias de elementos pares se divide entre 2
        if(indice2_int == 2 || indice2_int == 4 || indice2_int == 6){
            indice1_int=indice2_int/2;
            indice2_int=1;
        }

        /*transformar el int_indice2_int en un string*/
        indice1_string = to_string(indice1_int);
        indice2_string = to_string(indice2_int);

        //si el valor de los índices es 1, no se muestran por pantalla
            if(indice1_string=="1"){
                indice1_string="";
            }
            if(indice2_string=="1"){
                indice2_string="";
            }

        //ya formulamos con los datos obtenidos
        formula_tradicional=elemento1+indice1_string+"O"+indice2_string;
        cout<<"El compuesto "<<formula_escrita<<" se corresponde a la fórmula "<<formula_tradicional<<"."<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
        formula_escrita_F_N=formula_tradicional;
        guardarFormulaEnFichero(formula_escrita_F_N, formula_escrita);
        
    }else if(elemento_erroneo==false){//ultima palabra no era válida
        cout<<"---------------------------------------------------------------------------"<<endl;
        cout<<"Has introducido un compuesto no válido"<<endl;
        cout<<"---------------------------------------------------------------------------"<<endl;
        Sleep(3000);
        system("cls");
    }
    archivo.close();
    
        return formula_tradicional;
}
    

/*****************************************************/
/////////////////     STOCK      /////////////////////
/****************************************************/

/////////////////////////////////////////////////////
//              FUNCIÓN: stock(F_N)                //
// Formula en nomenclatura stock                   //
// Entrada = compuesto introducida por teclado     //
// Salida = fórmula en nomenclatura stock          //
/////////////////////////////////////////////////////
string formula_stock(string formula_escrita){
    ifstream archivo("elemento1.txt");
    elementos elemento;
    string lista_stock[7]={"monoxido","dioxido","trioxido","tetraoxido","pentaoxido","hexaoxido","heptaoxido"};
    string subcadena[2]={"","di"};
    string elemento1, prefijo_elemento, indice1_string, indice2_string, formula_stock,formula_escrita_F_N;
    int indice2_int, indice1_int, posicion1, posicion_prefijo;
    bool oxido_valido=false;
    bool elemento_extrano=false;
    string primera_palabra, ultima_palabra;
    
    //identificamos la primera palabra de formula escrita;
    primera_palabra = formula_escrita.substr(0, formula_escrita.find(' '));
    //debe encontrarse en el arrays lista_stock, lo recorremos aprovechamos para sacar la valencia del elemento, la cual será la posición en el arrays más uno
        for(int i=0; i<7; i++){
            if(primera_palabra==lista_stock[i]){
                indice2_int=i+1;//valencia del elemento
            }
        }

    //identificamos la última palabra de fórmula_escrita
    ultima_palabra = formula_escrita.substr(formula_escrita.find_last_of(' ') + 1);
    //ultima palabra, tiene obligatoriamente, el prefijo mono o di
        for(int i=0; i<ultima_palabra.size(); i++){
            posicion1 = ultima_palabra.find(subcadena[i]);

            if (posicion1 != string::npos) {//nos dice si palabra mono o di aparecen en la segunda palabra
                indice1_int=i+1;//se determina la valencia del oxigeno a partir de la posicion en el arrays
                elemento_extrano=true;//control para determinar si entramos en la parte del programa
                break;
            }
        };

        //mensaje de haber introducido compuesto erroneo
        if(elemento_extrano==false){
            cout<<"---------------------------------------------------------------------------"<<endl;
            cout<<"Has introducido un compuesto que no existe"<<endl;
            cout<<"---------------------------------------------------------------------------"<<endl;
            Sleep(1000);
            system("cls");
        }

        //
        while(elemento_extrano==true){
            //indica el prefijo que viene en la segunda palabra;
            //hay dos posibilidades del prefijo del elemento(DI-MONO)
            prefijo_elemento=subcadena[indice1_int-1];
            
            //buscamos el prefijo anterior en  ultima_palabra que es la que nos va indicar el elemento que conforma el óxido
            //usamos una funcion que borra el prefijo(DI-MONO)
            //asi obendremos el elemento
            posicion_prefijo = ultima_palabra.find(prefijo_elemento);
            if (posicion_prefijo != string::npos) {
                ultima_palabra.erase(posicion_prefijo, prefijo_elemento.length());
            }
            
            //tenemos que comprobar que la valencia que nos dan es la correcta
            
            //si es mono+elemento el oxígeno actuaría con valencia 1, lo cual es imposible, ya que sólo actúa con valencia 2
            //teniendo esto en cuenta; hay que multiplicar indice2_int obtenido por 2 en el caso que indice_int1=1;
                if(indice1_int==1){
                    indice2_int=indice2_int*2;       
                }

            //comprobar que la valencia que se refiere al elemento indice2_int es una valencia correcta para ese elemento
            //recorremos el fichero elemento1.txt
            if (archivo.is_open()) {
                while (archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) {
                    if(elemento.nombre==ultima_palabra){//verificar que hemos introducido un elemento válido
                        elemento1=elemento.siglas;//definimos elemento1 por su símbolo asi lo tendremos disponible para despues hacer nuestra fórmula
                        if(indice2_int==elemento.valencia){//comprobamos que el elemento identificado puede tener el valor de la valencia que hemos obtenido
                            oxido_valido=true;//el óxido es correcto
                        }else if(oxido_valido==false){//la valencia no se corresponde con el elemento por lo cual no es un óxido válido
                                                    // la condicion del else if es necesaria, para cuando encontremos el elemento y la valencia;
                                                    //sea posible, se corte el flujo; porque puede pasar que un elemento tenga varias valencias;
                                                    //lo que si leemos el fichero entero, origina que se sobreescriba el resultado de oxido_valido
                            oxido_valido=false;
                        }
                    }
                }
            }else{
                cout<<"---------------------------------------------------------------------------"<<endl;
                cout<<"Error al abrir el archivo";
                cout<<"---------------------------------------------------------------------------"<<endl;
            }
            archivo.close();

            //anteriormente indice2_int tuvo que ser modificado cuando indice1_int=1, para poder comprobar si la valencia era correcta
            //lo multiplicamos por 2 y ahora lo dividimos para devolverle su valor anterior
            indice2_int=indice2_int/2;


            //convertimos los indices en string
            indice1_string = to_string(indice1_int);
            indice2_string = to_string(indice2_int);


            //si el valor de los índices es 1, no se muestran por pantalla
            if(indice1_string=="1"){
                indice1_string="";
            }
            if(indice2_string=="1"){
                indice2_string="";
            }

            //
            if(oxido_valido==true){
                formula_stock=elemento1+indice1_string+"O"+indice2_string;
                cout<<"---------------------------------------------------------------------------"<<endl;
                cout<<"El compuesto "<<formula_escrita<<" se corresponde a la fórmula "<<formula_stock<<"."<<endl;
                cout<<"---------------------------------------------------------------------------"<<endl;
                formula_escrita_F_N=formula_stock;
                guardarFormulaEnFichero(formula_escrita_F_N, formula_escrita); 
            }if(oxido_valido==false){
                cout<<"---------------------------------------------------------------------------"<<endl;
                cout<<"Has introducido un compuesto que no existe"<<endl;
                cout<<"---------------------------------------------------------------------------"<<endl;
                Sleep(1000);
                system("cls");
            }
            elemento_extrano=false;//reiniciamos la variable de control para salir del bucle;
        };

    return formula_stock;    
}


/*******************************************************/
/////////////////  SISTEMÁTICA       ////////////////////
/*******************************************************/

////////////////////////////////////////////////////////
//        FUNCIÓN: elemento_sistematica               //
// Identifica un elemento en nomenclatura sistemática //
// Entrada = compuesto introducida por teclado        //
// Salida = fórmula en nomenclatura stock             //
////////////////////////////////////////////////////////
string elemento_sistematica(string formula_escrita){
    string elemento1, elemento_sistematica,simbolo;
    ifstream archivo("elemento1.txt");
    elementos elemento;
    bool respuesta=true;
    
        //utilizando el fichero elemento1.txt, lo recorremos entero buscando elemento por elemento para ellos utilizamos dos variables:
        //elemento1 qque ira cogiendo todos los posibles valores de elemento.nombre
        //simbolo que cogerá el símbolo del elemento 
        while ((archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) && respuesta==true){
        elemento1=elemento.nombre;
        simbolo=elemento.siglas;
        
        //comprobamos que elemento1, se encuentra denntro de formula escrita
        if (formula_escrita.find(elemento1) != string::npos) {
                simbolo=elemento.siglas;
                elemento_sistematica = simbolo;//si identificamos el elemento dentro de formula_escrita le indicamos ya su símbolo
                                               // utilizamos variable elemento_sistemática = símbolo
                respuesta=false;//cerramos nuestro while
            }
        }

    return elemento_sistematica;
}

////////////////////////////////////////////////////////
//        FUNCIÓN: indice2_int_siste                  //
// Identifica la valencia del elemento                //
// Entrada = compuesto introducida por teclado        //
// Salida = valencia elemento                         //
////////////////////////////////////////////////////////
int indice2_int_siste(string formula_escrita){
    string valencia, lista_valencias[7]={"(I)","(II)","(III)","(IV)","(V)","(VI)","(VII)"};
    int indice2_int;

    //recorremos un arrays con los 7 posibles valores que pueden aparecer en nomenclatura sistemática
    for(int i=0; i<7; i++){
        valencia = lista_valencias[i];//variable que adopta los valores que tiene el arrays, para despúes buscar si aparecen en formula_escrita
        //utilizando la funcion .find() nos informa de si valencia se encuentra en formula_escrita
        if (formula_escrita.find(valencia) != string::npos) {
                indice2_int = i+1;//indice2_int(valencia del elemento) se consigue con la posicion i del arrays más uno
        }
    }
    return indice2_int;
}

////////////////////////////////////////////////////////
//        FUNCIÓN: valencia_correcta                  //
// comprueba que el elemento pueda tener la valencia  //
// que se introdujo por teclado                       //
// Entrada = compuesto introducida por teclado        //
// Salida = booleano valencia_correcta                //
////////////////////////////////////////////////////////
bool valencia_correcta( string elemento1, int indice2_int){
    ifstream archivo("elemento1.txt");
    elementos elemento;
    bool valencia_correcta=false, respuesta=false;

    //recorremos el fichero elementos1.txt comprobamos que el elemento(SIMBOLO) y la valencia que hemos calculado son correctas
    while ((archivo >> elemento.nombre >> elemento.siglas >> elemento.valencia >> elemento.prefijo >> elemento.tipo >> elemento.cantidad_valencias) && valencia_correcta == false){
        if (elemento1==elemento.siglas) {
                if(indice2_int==elemento.valencia){
                    valencia_correcta=true;
                }else{
                    valencia_correcta=false;
                }
            }
        }

    return valencia_correcta;
}

////////////////////////////////////////////////////////
//      FUNCIÓN: sistematica_nomenclatura_formula     //
// formula en nomenclatura sitemática                 //
// Entrada = compuesto introducida por teclado        //
// Salida = valencia elemento                         //
////////////////////////////////////////////////////////
string sistematica_nomenclatura_formula(string elemento1, int indice2_int){
    string indice1_string, indice2_string, sistematica_nomenclatura_formula;
    int indice1_int=2;

        //calculamos los valores de las valencias que se mostraran en pantalla
        //el oxígeno siempre es 2, con valencias de elementos pares se divide entre 2
        if(indice2_int == 2 || indice2_int == 4 || indice2_int == 6){
            indice1_int=indice2_int/2;
            indice2_int=1;
        }

        /*transformar el los indices entero en string*/
        indice1_string = to_string(indice1_int);
        indice2_string = to_string(indice2_int);

        //si el valor de los índices es 1, no se muestran por pantalla
            if(indice1_string=="1"){
                indice1_string="";
            }
            if(indice2_string=="1"){
                indice2_string="";
            }

    sistematica_nomenclatura_formula=elemento1+indice1_string+"O"+indice2_string;

    return sistematica_nomenclatura_formula;
}


/////////////////////////////////////////////////////
//        FUNCIÓN: Fichero_nomenclaturas           //
// guardar el compuesto añadido por teclado y su   //
// fórmula correspondiente.                        //
// Entrada =                                       //
// Salida =                                        //
/////////////////////////////////////////////////////
void guardarFormulaEnFichero(string formula_escrita_F_N, string formula_escrita) {
    string respuesta, frase_guardado=".";
    

    // Preguntar al usuario si desea guardar la fórmula
    cout << "Si quieres guardar la fórmula, pulsa Si en caso contrario pulsa No : "<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;
    cin >> respuesta;
    
    for(int i=0; i<=25; i++){
        cout<<frase_guardado;
        Sleep(100);
    }
    cout<<"guardado correcto"<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;
    Sleep(1000);
    system("cls");
    
    

    if (respuesta == "s" || respuesta == "S" || respuesta=="si" || respuesta=="SI" || respuesta=="Si") {
        // Abrir el fichero para escribir y comienza a escribie en la primera linea libre
        ofstream archivo("nomenclaturas.txt", ios::app);

        // Verificar si el archivo se abrió correctamente
        if (archivo.is_open()) {
            // Escribir la fórmula en el archivo
            archivo << "El compuesto " << formula_escrita << " se corresponde a la fórmula " << formula_escrita_F_N<< "."<<endl;
            // Cerrar el archivo
            archivo.close();
        } else {
            cout << "Error al abrir el archivo" << endl;
        }
    }
}
/*--------------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////
//      FUNCIÓN: creditos                             //
// titulos de credito de nuestro programa             //
// Entrada =                                          //
// Salida =                                           //
////////////////////////////////////////////////////////
void creditos(){
    string frase="                      MUCHAS GRACIAS POR CONFIAR EN FORMULATRÓN";
    string frase2="                            Desarrollada por IASR";
    string frase3="                          ESTE PROGRAMA SE AUTODESTRUIRÁ           ";
    string frase4="BOO0000000000000000000000000000000000000000000000OOOOOOOOOMMMMMMMMMMMM";

    for(int i=0; i<frase.size(); i++){
        cout<<frase[i];
        Sleep(50);
    }
    cout<<endl;
    for(int i=0; i<frase2.size(); i++){
        cout<<frase2[i];
        Sleep(50);
    }
    cout<<endl;
    for(int i=0; i<frase3.size(); i++){
        cout<<frase3[i];
        Sleep(50);
    }
    system("cls");
    for(int i=5; i>0; i--){
        cout<<i;
        Sleep(1000);
        system("cls");
    }
    cout<<endl;
    for(int i=0; i<frase3.size(); i++){
        cout<<frase4[i];
        Sleep(1);
    }
    system("cls");
}