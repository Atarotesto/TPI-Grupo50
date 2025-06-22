#include <iostream>
#include "menus.h"
#include "conio.h"
#include "jueguito.h"
#include "rlutil.h"
using namespace std;

// solo muestra texto del menu
void mostrarMenu() {
	rlutil::locate(20,6);
	cout <<"         _______   _____________  _______   ________ _____   ____  ____  _____" << endl;
	rlutil::locate(20,7);
	cout <<"	   / ____/ | /  / ____/ __ |/ ____/ | /  / __ |/    |  / __ |/ __ |/ ___/" << endl;
	rlutil::locate(20,8);
	cout <<"	  / __/ /  |/  / /_  / /_/ / __/ /  |/  / / / / /|  | / / / / / / /|__ | " << endl;
	rlutil::locate(20,9);
	cout <<"	 / /___/ / |  / __/ / _, _/ /___/ / |  / /_/ / ___  |/ /_/ / /_/ /___/ /" << endl;
	rlutil::locate(20,10);
	cout <<"	/_____/_/  |_/_/   /_/ |_/_____/_/  |_/_____/_/   |_/_____/|____//____/" << endl;
	
	rlutil::locate(50,15);
    cout << " 1 - Jugar" << endl;
	rlutil::locate(50,16);
	cout << " 2 - Estadistica" << endl;
	rlutil::locate(50,17);
	cout << " 3 - Creditos" << endl;
	rlutil::locate(50,18);
	cout << " 4 - Reglas" << endl;
	rlutil::locate(50,19);
	cout << " ------------------ " << endl;
	rlutil::locate(50,20);
	cout << " 0 - Salir" << endl;
}

void mostrarCreditos() {
	rlutil::locate(50,10);
    cout<<"==============================" << endl;
	rlutil::locate(50,11);
    cout<< "          Creditos           " << endl;
	rlutil::locate(50,12);
    cout<<"=============================="<< endl << endl;
	rlutil::locate(48,13);
    cout<< "  Materia: Progamacion 1"<<endl;
	rlutil::locate(48,14);
    cout<< "  Profesor: Angel Simon"<< endl << endl;
	rlutil::locate(48,15);
    cout<< "  Integrantes de 'Los Pibes'"<<endl;
	rlutil::locate(48,16);
    cout<< "  1. Tomas Centurion     - 30926"<<endl;
	rlutil::locate(48,17);
    cout<< "  2. Franco Medero       - 27589"<< endl;
	rlutil::locate(48,18);
    cout<< "  3. Sebastian Gomez     - 28781"<< endl;
	rlutil::locate(48,19);
    cout<< "  4. Angel Diaz          - 33472"<< endl;

	rlutil::locate(48,20);
    cout << endl << endl << "2 - volver" << endl;

    volver();
}

// solo muestra el texto de estadisticas
void mostarEstadisticas (vector<int>& puntosEstadisticas, vector<string>& nombresEstadisticas) {
	rlutil::locate(50,10);
    cout << "---- ESTADISTICAS ----" << endl;
    for(int i=0; i<nombresEstadisticas.size(); i++) {
		rlutil::locate(50,12);
        cout << "# " << nombresEstadisticas[i] << " - " << puntosEstadisticas[i] << "pts" << endl;
    }
	rlutil::locate(55,18);
    cout << endl << endl << "2 - volver" << endl;

    volver();
}

void mostrarReglas() {
	rlutil::locate(50,10);
    cout << "agregar las reglas masomenos" << endl;
	rlutil::locate(55,18);
    cout << endl << "2 - volver";

    volver();
}

// es el mecanismo no toquen nada jeje
void mecanismoMenu() {

    vector<int> puntosEstadisticas = {};
    vector<string> nombresEstadisticas = {};

    // condicion para el while del menu
    // se va a ejecutar todo el programa hasta que salgas
    bool condicion = true;

    while (condicion) {
        char decision = getch();

        switch (decision) {
        case '1':
            jugar(puntosEstadisticas, nombresEstadisticas);
            break;
        case '2':
            espaciosBlancos();
            mostarEstadisticas(puntosEstadisticas, nombresEstadisticas);
            break;
        case '3':
            espaciosBlancos();
            mostrarCreditos();
            break;
        case '4':
            espaciosBlancos();
            mostrarReglas();
            break;
        case '0':
            condicion = false;
            break;
        default:
            break;
        }
    }

}

// Imprime líneas en blanco para "limpiar consola"
void espaciosBlancos() {

   rlutil::cls();

}

// boton de volver, si se elige 2 se vuelve al
// menu de inicio, sino sigue esperando que lo elijas :c
// se hizo para no repetir codigo ehje
void volver() {

    int i = 0;

    while (i == 0) {
        int volver = getch();

        if (volver == '2') {
            espaciosBlancos();
            mostrarMenu();
            i++;
        }
    }
}
