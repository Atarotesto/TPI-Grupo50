#include <iostream>
#include "jueguito.h"
#include "menus.h"
#include "conio.h"
#include "rlutil.h"

using namespace std;

void jugar(int (&puntosEstadisticas)[10], string (&nombresEstadisticas)[10]) {

	// ********* DATOS DE JUGADORES **********
	string nombreJugadorUno;
	int dadosJugadorUno = 6;
	int dadosUsadosJugadorUno = 0;
	int puntajeJugadorUno = 0;
	int puntajeDeRondaJugadorUno = 0;
	
	int dadosRestadosPorFallo = 0;
	
	string nombreJugadorDos;
	int dadosJugadorDos = 6;
	int dadosUsadosJugadorDos = 0;
	int puntajeJugadorDos = 0;
	int puntajeDeRondaJugadorDos = 0;
	// ********* FIN DATOS DE JUGADORES **********

	// pedir nombres y elegir que jugador comienza
	pedirNombre(nombreJugadorUno, nombreJugadorDos);
	decidirPrimerTurno(nombreJugadorUno, nombreJugadorDos);

    // total de 3 partidas si o si :D
	int contadorDeRondas = 1;
    while (contadorDeRondas < 4) {

    // turno jugador 1
        turno(nombreJugadorUno, dadosJugadorUno, puntajeJugadorUno, contadorDeRondas, dadosUsadosJugadorUno, puntajeDeRondaJugadorUno, dadosRestadosPorFallo);
		
		// suma los dados al contrincante
		dadosJugadorDos += dadosUsadosJugadorUno;
		dadosJugadorDos -= dadosRestadosPorFallo;
		
		if (puntajeJugadorUno >= 10000) {
			contadorDeRondas += 4;
			break;
		}
		
		menuEntreTirada(nombreJugadorUno, puntajeJugadorUno, dadosUsadosJugadorUno, puntajeDeRondaJugadorUno);
		
		// los reestablece para volver a contar los usados en el siguiente turno
		dadosUsadosJugadorUno = 0;
		dadosRestadosPorFallo = 0;

    // turno jugador 2
        turno(nombreJugadorDos, dadosJugadorDos, puntajeJugadorDos, contadorDeRondas, dadosUsadosJugadorDos, puntajeDeRondaJugadorDos, dadosRestadosPorFallo);
		
		// suma los dados al contrincante
		dadosJugadorUno += dadosUsadosJugadorDos;
		dadosJugadorUno -= dadosRestadosPorFallo;
		
		if (puntajeJugadorDos >= 10000) {
			contadorDeRondas += 4;
			break;
		}
		
		if (contadorDeRondas != 3) {
			menuEntreTirada(nombreJugadorDos, puntajeJugadorDos, dadosUsadosJugadorDos, puntajeDeRondaJugadorDos);
		}
		
		// los reestablece para volver a contarlos en el siguiente turno
		dadosUsadosJugadorDos = 0;
		dadosRestadosPorFallo = 0;

		contadorDeRondas++;
    };

    // agarra ambos puntajes y nombres
    int puntajes[2] = {puntajeJugadorUno, puntajeJugadorDos};
    string nombres[2] = {nombreJugadorUno, nombreJugadorDos};

	// pasa los datos de puntaje, transfiere al ganador a las estadisticas
	// y luego salta al cartel final con el dicho ganador
	compararPuntajes(puntajes, nombres, puntosEstadisticas, nombresEstadisticas);
}

void pedirNombre(string& jugadorUno, string& jugadorDos){
    
	rlutil::cls();
	
	rlutil::locate(45,10);
	cout << "Ingrese nombre de jugador 1";
	
	rlutil::locate(45,12);
	cout << "Nombre: ";
	getline(cin, jugadorUno);
	
	rlutil::cls();
	
	rlutil::locate(45,10);
	cout << "Ingrese nombre de jugador 2 ";
	
	rlutil::locate(45,12);
    cout << "Nombre: ";
    getline(cin, jugadorDos);
}

void decidirPrimerTurno(string& jugadorUno, string& jugadorDos) {
	
	rlutil::cls();

    int dadoJugadorUno = 0, dadoJugadorDos = 0;

    // para que siga si es que salen dados iguales
    while (dadoJugadorUno == dadoJugadorDos) {

		dadoJugadorUno = dadoDeSeisCaras();
		dadoJugadorDos = dadoDeSeisCaras();
		
		rlutil::locate(50,8);
		cout << "-------TIRANDO DADOS----------";
		
		rlutil::locate(50,10);
		cout << "* " << jugadorUno << "  --> Tirada de dados: " << "|" << dadoJugadorUno << "|";
		rlutil::locate(50,11);
		cout << "* " << jugadorDos << "  --> Tirada de dados: " << "|" << dadoJugadorDos << "|";

		// si el jugador 2 es mayor, voltea los nombres
		// sino sigue el mismo orden de jugador1 y jugador2
        if (dadoJugadorDos > dadoJugadorUno) {
            string nombreGuardado = jugadorUno;
			jugadorUno = jugadorDos;
			jugadorDos = nombreGuardado;
            break;
        }
    }
	
	rlutil::locate(50,13);
	cout << "---------RESULTADO------------";
	rlutil::locate(50,15);
	cout << "Jugador Uno: " << jugadorUno << endl;
	rlutil::locate(50,16);
	cout << "Jugador Dos: " << jugadorDos << endl;
	
	rlutil::locate(50,20);
	cout << "2 - avanzar";
	
	int botonAvanzar = 0;
	
	while (botonAvanzar == 0) {
		int boton = getch();
		
		if (boton == '2') {
			botonAvanzar++;
		}
	}
}

void turno(string jugador, int& cantDadosDelJugador, int& puntajeJugador, int contadorPartidas, int& dadosUsados, int& puntajeRonda, int& dadoFallo) {

	// tira los dos dados de 12 y muestra el texto correspondiente
    int numeroMeta = dadoDeDoceCaras(jugador);
	
	// declara y tira los dados de 6 del jugador
	int dadosStock[cantDadosDelJugador] = {};
	for (int i=0; i < cantDadosDelJugador; i++) {
		int dado = dadoDeSeisCaras();
		dadosStock[i] = dado;
	}
	
	// se pasa todo a la funcion de elegir dados y solo retorna el resultado 
	// de la ronda (solo la suma de los dados)
    int resultado = elegirDadosTirados(
		cantDadosDelJugador, dadosStock, numeroMeta, 
		jugador, puntajeJugador, contadorPartidas, dadosUsados, dadoFallo
	);

	// **** RESULTADOS DEL TURNO *****
	
	//   resultado =  puntos hechos  * cantidad de dados usados
	int totalPuntaje = resultado * dadosUsados;
	
	// se modifican los datos del jugador
	puntajeRonda = totalPuntaje;
	puntajeJugador += totalPuntaje; 
	
}
	
	
// muetra texto de dados tirados y dados elegidos para sumar
// y toda inf relevante, y realiza la seleccion de dichos dados
int elegirDadosTirados(int& cantDadosDelJugador, int dadosStock[], int numeroMeta, string jugador, int puntajeJugador, int contadorPartidas, int& cantDadosUsados, int& dadoFallo) {

	// para agregar los dados elegidos y mostrar en pantalla
    int dadosUsados[cantDadosDelJugador] = {};
	int indice = 0;
	
	const int DADOS_JUGADOR_FALLO = cantDadosDelJugador;
	
	// es lo que devuelve la funcion
	int puntaje = 0;

    if (tiradaExitosa(dadosStock, numeroMeta)) {
		cantDadosDelJugador = 1;
		cantDadosUsados = 1;
		puntaje = 10000;
		return puntaje;
    }

    while (cantDadosDelJugador > 0) {
		
		int posicionElegida;
		
		if (puntaje < numeroMeta && cantDadosDelJugador == 1) {
			rlutil::cls();
			
			dadoFallo++;
			
			rlutil::locate(38,17);
			cout << "Tus dados no son suficientes para alcanzar la meta";
			rlutil::locate(38,18);
			cout << "Se te concede un dado del rival";
			rlutil::locate(38,19);
			cout << "Dados extras recibidos en esta ronda = " << dadoFallo;
			rlutil::locate(38,20);
			cout << "Vuelve a repetir la jugada... ";
			
			rlutil::msleep(3000);
			
			for (int i = 0; i < 11; i++){
				if (dadosStock[i] == -1) {
					dadosStock[i] = rand() * 6 + 1;
					break;
				}
			}
			
			continue;
		}
		
		// texto de los dados del usuario, para visualizar la posicion y poder elegirla
		mostrarDadosTirados(dadosStock, jugador, numeroMeta, puntajeJugador, contadorPartidas); 
		
		rlutil::locate(38,19);
		cout << "---------------DADOS ELEGIDOS-------------- ";
		
		// muestra los dados que va eligiendo el usuario para sumar
        for (int i=0; i<10; i++) {
			if (dadosUsados[i] > 0 && dadosUsados[i] <= 6) {
				rlutil::locate((55 + (5*i)),21);
				cout << "|" << dadosUsados[i] << "| ";
			}
        }
		
        // cuando llegue a la suma meta, termina el ciclo
        if (puntaje == numeroMeta) {
            cout << " = " << puntaje;
			rlutil::locate(55,27);
			cout << "Pasando Turno... ";
			
			rlutil::msleep(3000);
            break;
        }
		
		// si se pasa de la meta, se penaliza
		if (puntaje > numeroMeta) {
			cout << " = " << puntaje;
			rlutil::locate(55,25);
			cout << " Te pasaste del objetivo, no sumas puntos :c";
			rlutil::locate(55,27);
			cout << "Pasando Turno... ";
			
			rlutil::msleep(3000);
			
			puntaje = 0;
			return puntaje;
		}
		
		rlutil::locate(38,17);
		cout << "Ingrese posicion de dado a sumar: ";
		cin >> posicionElegida;

        // la eleccion tiene que ser menor o igual
        // al la cantidad de valores visibles en pantalla
        if (posicionElegida > 0 && posicionElegida <= cantDadosDelJugador) {

			puntaje += dadosStock[posicionElegida - 1];
			
			int dadoElegido = dadosStock[posicionElegida - 1];
			
            dadosUsados[indice] = dadoElegido;
			dadosStock[posicionElegida - 1] = -1; // Eliminar de la lista el dado utilizado
			indice++;
			
			// Reordena la lista de dados del jugador
			for (int i = 0; i < 11; i++){
				if ((dadosStock[i] == -1) && dadosStock[i+1] > 0) {
					dadosStock[i] = dadosStock[i+1];
					dadosStock[i+1] = -1;
				}
			}

			cantDadosDelJugador--;
			cantDadosUsados++;
        } 
		
		if (posicionElegida == 0) {
			cout << " = " << puntaje;
			rlutil::locate(55,25);
			cout << " Salteando turno, no sumas puntos :c";
			rlutil::locate(55,27);
			cout << "Pasando Turno... ";
			
			rlutil::msleep(3000);
			
			puntaje = 0;
			return puntaje;
		}

    }
	
	// si no llega de ninguna manera, es como si se le hubiese saltado el turno
	// no suma puntos para el, ni transfiere dados al rival
	if (puntaje < numeroMeta) {
		dadoFallo = 0;
		cantDadosUsados = 0;
		cantDadosDelJugador = DADOS_JUGADOR_FALLO;
		puntaje = 0;
	}

    return puntaje;
}


// funcion solo estetica que muestra nombre, puntaje, meta, ronda, dados del usuario
void mostrarDadosTirados(int dadosStock[], string jugador, int numeroMeta, int puntajeJugador, int contadorPartidas) {
	
	rlutil::cls();
	
	rlutil::locate(30,9);
    cout << "Turno: " << jugador;
	
	rlutil::locate(55,9);
    cout <<"Puntos actuales: " << puntajeJugador;
	
	rlutil::locate(78,9);
    cout << "Meta: " << numeroMeta;
	
	rlutil::locate(88,9);
	cout << "Ronda: " << contadorPartidas;
	
	rlutil::locate(38,11);
    cout << "---------------DADOS TIRADOS---------------";
	
	rlutil::locate(55,20);
	cout << " |0 - Salir| ";
	
	rlutil::locate(40,13);
    for (int i=0; i<11; i++) {
		if (dadosStock[i] > 0 && dadosStock[i] <= 6) {
			cout << "|" << dadosStock[i] << "| ";
		};
    }
	
	rlutil::locate(38,15);
    cout << "********************************************";
}

// verifica si es posible llegar a la meta con los dados actuales
bool tiradaFallada (int dadosStock[], int numeroObjetivo) {
	
	int totalSumaDados = 0;
	
	for (int i=0; i<11; i++) {
		if (dadosStock[i] > 0 && dadosStock[i] <= 6) {
			totalSumaDados += dadosStock[i];
		};
	}

    if (totalSumaDados < numeroObjetivo) {
        return true;
    };

    return false;
}

// verifica si es TIRADA EXITOSAAAAAAAA
bool tiradaExitosa (int dadosStock[], int numeroObjetivo) {
	
	rlutil::cls();

    int totalDados = 0;

	for (int i=0; i<11; i++) {
		if (dadosStock[i] > 0 && dadosStock[i] <= 6) {
			totalDados += dadosStock[i];
		};
	}
	
    if (totalDados == numeroObjetivo) {
		rlutil::locate(47,9);
        cout << "       TIRADA EXITOSA :D      ";
		rlutil::locate(40,10);
        cout << "** tus dados son justos para llegar a la META **";
        cout << endl;
		rlutil::locate(55,14);
		for (int i=0; i<10; i++) {
			if (dadosStock[i] > 0 && dadosStock[i] <= 6) {
				cout << "|" << dadosStock[i] << "| ";
			};
		}
		
        cout << " = " << totalDados;
        cout << "  ///  " << "Meta: " << numeroObjetivo;
		
		rlutil::locate(41,16);
        cout << "Al tener la cantidad justa ganaste 10000 puntos";
		
		rlutil::locate(41,17);
		cout << "Felicidades!! has ganado la partida";
		
		rlutil::msleep(5000);
		
        return true;
    };

    return false;
}

// tira un numero al azar entre 1 - 6
int dadoDeSeisCaras(){

    int numeroRandom = rand() % 6 + 1;

    return numeroRandom;

}

// tira los dados de 12 caras para el numero meta
// muestra el texto con el nombre del jugador que le toca
// y la el resultado de la suma
int dadoDeDoceCaras(string nombrejugador){

    rlutil::cls();

    int dado1, dado2, resultado;

    dado1 = rand() % 12 + 1;
    dado2 = rand() % 12 + 1;

    resultado = dado1 + dado2;
	rlutil::locate(50,12);
    cout << "Turno de: " << nombrejugador;
	
	rlutil::locate(50,14);
	cout << "----------------------------";
	rlutil::locate(50,15);
	cout << "Tirando Dados de 12 caras...";
	
	rlutil::msleep(1000);
	
	rlutil::locate(50,16);
	cout << "----------------------------";

	rlutil::locate(50,18);
    cout << "Numero Objetivo: "	;
    cout << "|" << dado1 << "|" << " + ";
    cout << "|" << dado2 << "|" << " = ";
    cout << resultado;

	rlutil::locate(58,20);
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

// compara puntajes, agrega ganador a ESTADISTICAS y tira cartel de ganador o de empate
void compararPuntajes(int puntajes[], string nombres[], int puntosEstadisticas[], string nombresEstadisticas[]) {
	if (puntajes[0] > puntajes[1]) {
		agregarEstadisticas(puntajes[0], nombres[0], puntosEstadisticas, nombresEstadisticas);
		mostrarganador(puntajes[0], nombres[0]);
	} else if (puntajes[0] == puntajes[1]) {
		agregarEstadisticas(puntajes[0], nombres[0], puntosEstadisticas, nombresEstadisticas);
		agregarEstadisticas(puntajes[1], nombres[1], puntosEstadisticas, nombresEstadisticas);
		empate(puntajes[0], puntajes[1], nombres[0], nombres[1]);
	} else {
		agregarEstadisticas(puntajes[1], nombres[1], puntosEstadisticas, nombresEstadisticas);
		mostrarganador(puntajes[1], nombres[1]);
	}
}
	
// agrega al ganador a Estadisticas, el orden no es de mayor a menor
// solo lo agrega al final de la lista je
void agregarEstadisticas(int puntaje, string nombre, int puntosEstadisticas[], string nombresEstadisticas[]) {
    for (int i=0; i<10; i++) {
		if (puntosEstadisticas[i] == 0) {
			nombresEstadisticas[i] = nombre;
			puntosEstadisticas[i] = puntaje;
			break;
		}
	}
}

// cartel para mostrar el ganador
void mostrarganador(int puntaje, string nombre){
	
	rlutil::cls();
	
	rlutil::locate(50,15);
	cout << "----------FIN DE PARTIDA----------";
	
	rlutil::locate(50,18);
	cout << "Ganador: " << nombre;
	rlutil::locate(50,19);
	cout << "Puntaje final: " << puntaje;
	rlutil::locate(50,21);
	cout << "FELICIDADES";
	
	rlutil::locate(55,25);
	cout << "2 - volver a menu";
	
	volver();
}
	
void empate(int puntajeUno, int puntajeDos, string nombreUno, string nombreDos){
	
	rlutil::cls();
	
	rlutil::locate(50,15);
	cout << "----------FIN DE PARTIDA----------";
	rlutil::locate(50,16);
	cout << "--------------EMPATE--------------";
	
	rlutil::locate(50,18);
	cout << "Jugador 1: " << nombreUno;
	rlutil::locate(50,19);
	cout << "Jugador 2: " << nombreDos;
	rlutil::locate(50,21);
	cout << "Puntaje final jugador 1: " << puntajeUno;
	rlutil::locate(50,22);
	cout << "Puntaje final jugador 2: " << puntajeDos;
	rlutil::locate(50,25);
	cout << "*** AMBOS SE GUARDARAN EN LAS ESTADISTICAS ***";
	rlutil::locate(50,26);
	cout << "FIN DEL JUEGO";
	
	rlutil::locate(55,28);
	cout << "2 - volver a menu";
	
	volver();
}

// muestra los avances del jugador que tuvo en el turno y los dados que transfiere
void menuEntreTirada(string nombre, int puntaje, int dadosRestantes, int puntajeRonda) {
	
	rlutil::cls();
	
	rlutil::locate(50,10);
	cout << "---------- FIN DEL TURNO ----------";
	
	rlutil::locate(50,13);
	cout << "Jugador: " << nombre;
	rlutil::locate(50,14);
	cout << "Puntaje hecho en la ronda: " << puntajeRonda;
	rlutil::locate(50,15);
	cout << "Puntaje total: " << puntaje;
	rlutil::locate(50,16);
	cout << "Dados transferidos al siguiente jugador: " << dadosRestantes;
	
	rlutil::locate(50,18);
	cout << "Pasando turno a siguiente jugador...";
	
	// tiempo de pausa hasta pasar a la siguiente pantalla
	rlutil::msleep(6000);
}
