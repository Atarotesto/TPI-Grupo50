#include <iostream>
#include "jueguito.h"
#include "menus.h"
#include "conio.h"
#include "rlutil.h"
using namespace std;

void jugar(vector<int>& puntosEstadisticas, vector<string>& nombresEstadisticas) {

// ********* DATOS DE JUGADORES **********
    string jugador1 = "nombre";
    int dadosJugador1 = 6;
    int tiradasJugador1 = 0;

    string jugador2 = "nombre";
    int dadosJugador2 = 6;
    int tiradasJugador2 = 0;

    jugador1 = pedirnombre();
    jugador2 = pedirnombre();

// ********* FIN DATOS DE JUGADORES **********

    decidirPrimerTurno(jugador1, jugador2);
    vector<int> resultado = {};

    // total de 3 partidas si o si :D
    int contadorPartidas = 0;
    while (contadorPartidas < 3) {

    // turno jugador 1
        resultado = turno(jugador1, dadosJugador1, tiradasJugador1);

        tiradasJugador1 += resultado[2] * resultado[0];

    // turno jugador 2
        dadosJugador2 += resultado[1];
        resultado = turno(jugador2, dadosJugador2, tiradasJugador2);
        tiradasJugador2 += resultado[2] * resultado[0];

        contadorPartidas++;
		//if(){
		//	
		//}
    };

    // pasa los puntajes finales de cada jugador
    // guarda solo la mas alta en las estadisticas
    // despues se podran ver en el menu -> estadisticas
    vector<int> puntajes = {tiradasJugador1, tiradasJugador2};
    vector<string> nombres = {jugador1, jugador2};

    agregarEstadisticas(puntajes, nombres, puntosEstadisticas, nombresEstadisticas);

    // vuelve al menu de inicio al ternminar la partida
    espaciosBlancos();
	rlutil::locate(50,10);
    cout << "/// Fin del juego ///" << endl;
	rlutil::locate(55,18);
    cout << endl << "2 - volver a menu" << endl;
    volver();
}

string pedirnombre(){
    espaciosBlancos();
    string nombre;
	rlutil::locate(50,12);
    cout << "Ingrese nombre del jugador " << endl;
	rlutil::locate(50,13);
    getline(cin, nombre);
    return nombre;
}

void decidirPrimerTurno(string& jugador1, string& jugador2) {

    int dadoJugador1 = 0, dadoJugador2 = 0;

    // para que siga si es que salen dados iguales
    while (dadoJugador1 == dadoJugador2) {

        dadoJugador1 = tirardado6caras();
        dadoJugador2 = tirardado6caras();

        if (dadoJugador2 > dadoJugador1) {
            string guardado = jugador1;
            jugador1 = jugador2;
            jugador2 = guardado;
			cout << "Jugador 1: " << jugador1;
			cout << "Jugador 2: " << jugador1;
            break;
        } else break;
    };
}

vector<int> tiradaDados(int cantDados) {

    vector<int> dadosStock = {};

    for (int i=0; i< cantDados; i++) {
        int dado = tirardado6caras();
        dadosStock.push_back(dado);
    }

    return dadosStock;
}

vector<int> turno(string jugador, int cantDados, int& totalPuntaje) {

    int numeroMeta = tirardado12caras(jugador);

    vector<int> dadosStock = tiradaDados(cantDados);

    vector<int> resultado = elegirDadosTirados(dadosStock, numeroMeta, jugador, totalPuntaje);

    // resultado tendria {sumaDeDadosUsados, dadosSinUsar, sumaTotalHecha}
    return resultado;
}

// se pasa a la funcion la cantidad de numeros en un
// vector y tambien el numero meta
vector<int> elegirDadosTirados(vector<int> dadosStock, int numeroObjetivo, string jugadorActual, int& totalPuntaje) {

    // contador para la suma y dados usados
    int sumaTotal = 0;
    int sumaDadosUsados = 0;

    int largoDeLista = dadosStock.size();

    vector<int> dadosUsados = {};

    if (tiradaFallada(dadosStock, numeroObjetivo)) {
        vector<int> retorno = {sumaDadosUsados, 0, sumaTotal};
        return retorno;
    };

    if (tiradaExitosa(dadosStock, numeroObjetivo)) {
        vector<int> retorno = {sumaDadosUsados, 0, 10000};
        return retorno;
    };


    // se pueden elegir tantos dados como se quiera hasta llegar
    // al numero de meta
    while (largoDeLista > 0) {

        espaciosBlancos();
        mostrarDadosTirados(dadosStock, jugadorActual, numeroObjetivo, totalPuntaje);

        // va mostrando en pantalla los dados elegidos a sumar
		rlutil::locate(55,17);
        for (int i : dadosUsados) {
            cout << i << " ";
        }

        // cuando llegue a la suma meta, termina el ciclo
        if (sumaTotal >= numeroObjetivo) {
			
            cout << " = " << sumaTotal;
            break;
        }

        // elegis la posicion que quieras sumar
        char posicion = getch();
        int pos = stoi(string(1, posicion));

        // los botones tiene que ser menor o igual
        // al la cantidad de valores visibles
        if (pos > 0 && pos <= largoDeLista) {

            sumaTotal += dadosStock[pos - 1];

            dadosUsados.push_back(dadosStock[pos - 1]);
            sumaDadosUsados++;

            // va borrando los dados usados
            dadosStock.erase(dadosStock.begin() + (pos - 1));
            largoDeLista--;

        } else {continue;}

    };

    // devuelve la cantidad de dados usados, dados restantes y suma hecha relativamente
    vector<int> retorno = {sumaDadosUsados, dadosStock.size(), sumaTotal};

    return retorno;
}


// funcion solo estetica que muestra los dados para sumar
// el nombre del turno actual y la meta a alcanzar
void mostrarDadosTirados(vector<int> dadosStock, string nombre, int numeroObjetivo, int sumaTotal) {
	rlutil::locate(36,9);
    cout << "Turno: " << nombre;
	rlutil::locate(52,9);
    cout <<"Puntos actuales: " << sumaTotal;
	rlutil::locate(77,9);
    cout << "meta: " << numeroObjetivo << endl;
	rlutil::locate(45,12);
    cout << "          DADOS TIRADOS           " << endl;
	rlutil::locate(34,15);
    cout << "** presionar solo posicion del numero a elegir **" << endl;
	
    cout << endl;
	// Centra los dados stock en pantalla
	rlutil::locate(55,14);
    for (int i : dadosStock) {
        cout << i << " ";
    }
    cout << endl;
	rlutil::locate(48,16);
    cout << "*************************";
    cout << endl;
}

// verifica si es posible llegar a la meta con los dados actuales
bool tiradaFallada (vector<int> dadosStock, int numeroObjetivo) {

    int totalDados = 0;

    for (int i : dadosStock) {
        totalDados += i;
    }

    if (totalDados < numeroObjetivo) {
		rlutil::locate(47,9);
        cout << "TIRADA FALLIDA D:" << endl;
		rlutil::locate(40,10);
        cout << "** tus dados no alcanzan para llegar a la meta **" << endl;
        cout << endl;
	
		rlutil::locate(55,14);
        for (int i : dadosStock) {
			
            cout << i << " ";
        }
		
        cout << " = " << totalDados;
		rlutil::locate(66,9);
        cout << " /// " << "Meta: " << numeroObjetivo;
        cout << endl;
		rlutil::locate(41,16);
        cout << "Pasando turno al siguiente jugador :c";
		
        cout << endl << endl;
		rlutil::locate(45,18);
       // cout << "2 - avanzar";

        int botonAvanzar = 0;

        while (botonAvanzar == 0) {
            int boton = getch();

            if (boton == '2') {
                botonAvanzar++;
            } else continue;
        }

        return true;
    };

    return false;
}

// verifica si es TIRADA EXITOSAAAAAAAA
bool tiradaExitosa (vector<int> dadosStock, int numeroObjetivo) {

    int totalDados = 0;

    for (int i : dadosStock) {
        totalDados += i;
    }

    if (totalDados == numeroObjetivo) {
		rlutil::locate(47,9);
        cout << "       TIRADA EXITOSA :D      " << endl;
		rlutil::locate(40,10);
        cout << "** tus dados son justos para llegar a la META **" << endl;
        cout << endl;
		rlutil::locate(55,14);
        for (int i : dadosStock) {
			
            cout << i << " ";
        }
		
        cout << " = " << totalDados;
		rlutil::locate(66,9);
        cout << " /// " << "Meta: " << numeroObjetivo;
		
        cout << endl;
		rlutil::locate(41,16);
        cout << "Al tener la cantidad justa ganaste 1000 puntos";
		
        cout << endl << endl;
		rlutil::locate(45,18);
        //cout << "2 - avanzar";
		
        int botonAvanzar = 0;
		
        while (botonAvanzar == 0) {
            int boton = getch();
			
            if (boton == '2') {
				volver();
            } else continue;
        }

        return true;
    };

    return false;
}

// tira un numero al azar entre 1 - 6
int tirardado6caras(){

    int numeroRandom = rand() % 6 + 1;

    return numeroRandom;

}

// tira los dados de 12 caras para el numero meta
// muestra el texto con el nombre del jugador que le toca
// y la el resultado de la suma
int tirardado12caras(string nombre){

    espaciosBlancos();

    int dado1, dado2, resultado;

    dado1 = rand() % 12 + 1;
    dado2 = rand() % 12 + 1;

    resultado = dado1 + dado2;
	rlutil::locate(50,12);
    cout << "Arranca el jugador: " << nombre << endl;
	rlutil::locate(50,15);
    cout << "Numero Objetivo: "	;
	rlutil::locate(67,15);
    cout << dado1 << " + ";
	rlutil::locate(72,15);
    cout << dado2 << " = ";
	rlutil::locate(76,15);
    cout << resultado;

    cout << endl << endl;
	rlutil::locate(55,18);
    cout << "2 - avanzar";

    int botonAvanzar = 0;

    while (botonAvanzar == 0) {
        int boton = getch();

        if (boton == '2') {
            botonAvanzar++;
        } else continue;
    }

    return resultado;

}

// agrega al ganador a Estadisticas, el orden no es de mayor a menor
// solo lo agrega al final de la lista je
void agregarEstadisticas(vector<int> puntajes, vector<string> nombres, vector<int>& puntosEstadisticas, vector<string>& nombresEstadisticas) {
    if (puntajes[0] > puntajes[1]) {
        puntosEstadisticas.push_back(puntajes[0]);
        nombresEstadisticas.push_back(nombres[0]);
    } else {
        puntosEstadisticas.push_back(puntajes[1]);
        nombresEstadisticas.push_back(nombres[1]);
    }
}

