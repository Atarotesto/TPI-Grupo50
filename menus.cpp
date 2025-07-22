#include <iostream>
#include "menus.h"
#include "conio.h"
#include "jueguito.h"
#include "rlutil.h"

using namespace std;

// texto del menu
void mostrarMenu() {
	rlutil::locate(20,6);
	cout <<"         _______   _____________  _______   ________ _____   ____  ____  _____";
	rlutil::locate(20,7);
	cout <<"	   / ____/ | /  / ____/ __ |/ ____/ | /  / __ |/    |  / __ |/ __ |/ ___/";
	rlutil::locate(20,8);
	cout <<"	  / __/ /  |/  / /_  / /_/ / __/ /  |/  / / / / /|  | / / / / / / /|__ | ";
	rlutil::locate(20,9);
	cout <<"	 / /___/ / |  / __/ / _, _/ /___/ / |  / /_/ / ___  |/ /_/ / /_/ /___/ /";
	rlutil::locate(20,10);
	cout <<"	/_____/_/  |_/_/   /_/ |_/_____/_/  |_/_____/_/   |_/_____/|____//____/";
	
	rlutil::locate(50,15);
    cout << " 1 - Jugar";
	rlutil::locate(50,16);
	cout << " 2 - Estadistica";
	rlutil::locate(50,17);
	cout << " 3 - Creditos";
	rlutil::locate(50,18);
	cout << " 4 - Reglas";
	rlutil::locate(50,19);
	cout << " ------------------ ";
	rlutil::locate(50,22);
	cout << " 0 - Salir";
}

// texto de creditos
void mostrarCreditos() {
	rlutil::locate(50,10);
    cout<<"==============================";
	rlutil::locate(50,11);
    cout<< "          Creditos           ";
	rlutil::locate(50,12);
    cout<<"==============================";
	rlutil::locate(48,13);
    cout<< "  Materia: Progamacion 1";
	rlutil::locate(48,15);
    cout<< "  * Integrantes de 'Los Pibes' *";
	rlutil::locate(48,16);
    cout<< "  1. Tomas Centurion     - 30926";
	rlutil::locate(48,17);
    cout<< "  2. Franco Medero       - 27589";
	rlutil::locate(48,18);
    cout<< "  3. Sebastian Gomez     - 28781";
	rlutil::locate(48,19);
    cout<< "  4. Angel Diaz          - 33472";

	rlutil::locate(48,23);
    cout << "2 - volver";

    volver();
}

// texto de estadisticas
void mostarEstadisticas (int puntosEstadisticas[], string nombresEstadisticas[]) {
	rlutil::locate(50,10);
    cout << "----------ESTADISTICAS----------";
	
    for(int i=0; i<5; i++) {
		rlutil::locate((50),(12+i));
		if (puntosEstadisticas[i] != -1) {
			cout << "# " << nombresEstadisticas[i] << "  -  " << puntosEstadisticas[i] << "pts";
		}
    }
	
	rlutil::locate(50,22);
	cout << "--------------------------------";
	
	rlutil::locate(50,23);
	cout << "2 - volver";

    volver();
}

// texto de reglamento / instrucciones
// AGREGAR REGLAS NUEVAS QUE SEAN SIMILARES A LAS DEL TP Y BORRAR ESTE COMENTARIOOOOOOO
void mostrarReglas() {
	rlutil::locate(50,3);
	cout << "====================================== ";
	rlutil::locate(50,4);
	cout << "             INSTRUCCIONES             ";
	rlutil::locate(50,5);
	cout << "====================================== ";
	
	rlutil::locate(50,7);
	cout << "Al inicio se decidira quien comienza el";
	rlutil::locate(50,8);
	cout << "juego tirando 2 dados de 12 caras, quien";
	rlutil::locate(50,9);
	cout << "saque el mayor numero es quien arranca.";
	rlutil::locate(50,11);
	cout << "Se tiraran 2 dados de 12 caras, la suma";
	rlutil::locate(50,12);
	cout << "de los numeros sacados es el objetivo a alcanzar.";
	rlutil::locate(50,14);
	cout << "Para alcanzar la meta se tiraran dados de 6 caras";
	rlutil::locate(50,15);
	cout << "y se tendran que elegir los numeros resultantes";
	rlutil::locate(50,16);
	cout << "hasta alcanzar el numero meta, si llegas a la meta";
	rlutil::locate(50,17);
	cout << "los dados utilizados se los transferis al rival.";
	rlutil::locate(50,19);
	cout << "En caso de no llegar a la meta, ya sea por sumar";
	rlutil::locate(50,20);
	cout << "de menos o de mas o saltear tu turno con la opcion";
	rlutil::locate(50,21);
	cout << "0 (cero), se te cedera un dado de tu rival ";
	rlutil::locate(50,23);
	cout << "Si llegases al numero objetivo y quedaste sin dados";
	rlutil::locate(50,24);
	cout << "automaticamente ganas el juego y si te conceden 1000 puntos";
	rlutil::locate(50,26);
	cout << "Los puntos se calculan multiplicando el objetivo con los dados usados";
	rlutil::locate(50,27);
	cout << "El juego lo gana quien acumule mayor cantidad de puntos";
	rlutil::locate(50,28);
	cout << "====================================== ";
	

	
	rlutil::locate(50,29);
    cout << "2 - volver";

    volver();
}

void mecanismoMenu() {

	// estas se modifican al jugar y luego se muestran en estadisticas
	const int VALOR_VECTOR_EST = 10;
    int puntosEstadisticas[VALOR_VECTOR_EST] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	const int VALOR_VECTOR_NOM = 10;
	string nombresEstadisticas[VALOR_VECTOR_NOM] = {};

    bool botonEncendido = true;

    while (botonEncendido) {
		
        char decision = getch();  // GET CHAR --> AGARRAR CARACTER

        switch (decision) {
        case '1':
            jugar(puntosEstadisticas, nombresEstadisticas);
            break;
        case '2':
			rlutil::cls();
            mostarEstadisticas(puntosEstadisticas, nombresEstadisticas);
            break;
        case '3':
			rlutil::cls();
            mostrarCreditos();
            break;
        case '4':
			rlutil::cls();
            mostrarReglas();
            break;
        case '0':
			salir(botonEncendido);
            break;
        default:
            break;
        }
    }
}

void salir(bool& botonEncendido) {
	rlutil::cls();
	
	rlutil::locate(50,10);
	cout << "Desea salir del juego?" ;
	rlutil::locate(50,11);
	cout << "1 - SI  /  2 - NO";
	
	bool condicion = true;
	
	while (condicion) {
		int volver = getch();
		
		if (volver == '2') {
			rlutil::cls();
			mostrarMenu();
			condicion = false;
		} 
		if (volver == '1') {
			botonEncendido = false;
			condicion = false;
		}
	}
}

// boton de volver, sin mas
// para usar solo en la navegacion del menu
void volver() {

	bool condicion = true;
	
	while (condicion) {
		int volver = getch();
		
		if (volver == '2') {
			rlutil::cls();
			mostrarMenu();
			condicion = false;
		}
	}
}
