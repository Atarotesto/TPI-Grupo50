#include <iostream>
#include "menus.h"
#include "conio.h"
#include "jueguito.h"
#include "rlutil.h"
using namespace std;

// solo muestra texto del menu
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

void mostrarCreditos() {
	rlutil::locate(50,10);
    cout<<"==============================";
	rlutil::locate(50,11);
    cout<< "          Creditos           ";
	rlutil::locate(50,12);
    cout<<"==============================";
	rlutil::locate(48,13);
    cout<< "  Materia: Progamacion 1";
	rlutil::locate(48,14);
    cout<< "  Profesor: Angel Simon";
	rlutil::locate(48,17);
    cout<< "** Integrantes de 'Los Pibes' **";
	rlutil::locate(48,18);
    cout<< "  1. Tomas Centurion     - 30926";
	rlutil::locate(48,19);
    cout<< "  2. Franco Medero       - 27589";
	rlutil::locate(48,20);
    cout<< "  3. Sebastian Gomez     - 28781";
	rlutil::locate(48,21);
    cout<< "  4. Angel Diaz          - 33472";

	rlutil::locate(48,25);
    cout << "2 - volver";

    volver();
}

// solo muestra el texto de estadisticas
void mostarEstadisticas (vector<int>& puntosEstadisticas, vector<string>& nombresEstadisticas) {
	rlutil::locate(50,10);
    cout << "----------ESTADISTICAS----------";
	
    for(int i=0; i<nombresEstadisticas.size(); i++) {
		rlutil::locate((50),(12+i));
        cout << "# " << nombresEstadisticas[i] << "  -  " << puntosEstadisticas[i] << "pts";
    }
	
	rlutil::locate(50,22);
	cout << "--------------------------------";
	
	rlutil::locate(50,23);
	cout << "2 - volver";

    volver();
}

void mostrarReglas() {
	rlutil::locate(50,3);
	cout << "====================================== ";
	rlutil::locate(50,4);
	cout << "             INSTRUCCIONES             ";
	rlutil::locate(50,5);
	cout << "====================================== ";
	rlutil::locate(50,7);
	cout << " Inicia tirando 2 dados de 12 caras.   ";
	rlutil::locate(50,8);
	cout << " Sumados seran tu numero objetivo.     ";
	rlutil::locate(50,10);
	cout << " Luego tiras tus dados de 6 caras.     ";
	rlutil::locate(50,11);
	cout << " Elegi una combinacion que iguale      ";
	rlutil::locate(50,12);
	cout << " el numero objetivo y:                 ";
	rlutil::locate(50,14);
	cout << "  ** Si alcanzas la meta:              ";
	rlutil::locate(50,15);
	cout << "       suma puntos y transfieres los   ";
	rlutil::locate(50,16);
	cout << "       restantes al rival              ";
	rlutil::locate(50,18);
	cout << "  ** Si fallas:                        ";
	rlutil::locate(50,19);
	cout << "    no sumaras puntos y daras          ";
	rlutil::locate(50,20);
	cout << "    todos tus dados al rival           ";
	rlutil::locate(50,22);
	cout << "  ** Tirada Exitosa                    ";
	rlutil::locate(50,23);
	cout << "    si sumando todos tus dados es      ";
	rlutil::locate(50,24);
	cout << "    exactamente igual a la meta, ganas ";
	rlutil::locate(50,26);
	cout << " ** Gana quien tenga mas puntos **     ";
	rlutil::locate(50,27);
	cout << "====================================== ";
	
	
	rlutil::locate(50,29);
    cout << "2 - volver";

    volver();
}

// es el mecanismo no toquen nada jeje
void mecanismoMenu() {

    vector<int> puntosEstadisticas = {500, 500, 500, 300};
    vector<string> nombresEstadisticas = {"Tomas Centurion", "Franco Medero", "Sebastian Gomez", "Angel Diaz"};

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

// limpia la consola, no se cambio el nombre por fiaca
void espaciosBlancos() {

   rlutil::cls();

}

// boton de volver, si se elige 2 se vuelve al
// menu de inicio, sino sigue esperando que lo elijas como yo(?):c
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

// muestra los avances del jugador que tuvo el turno y los dados que transfiere
void menuEntreTirada(string nombre, int puntaje, int dadosRestantes) {
	
	espaciosBlancos();
	
	rlutil::locate(50,10);
	cout << "---------- FIN DEL TURNO ----------";
	
	rlutil::locate(50,13);
	cout << "Jugador: " << nombre;
	rlutil::locate(50,14);
	cout << "Puntaje total: " << puntaje;
	rlutil::locate(50,15);
	cout << "Dados transferidos al siguiente jugador: " << dadosRestantes;
	
	rlutil::locate(50,17);
	cout << "Pasando turno a siguiente jugador...";
	
	// tiempo de pausa hasta pasar a la siguiente pantalla
	rlutil::msleep(4500);
}
