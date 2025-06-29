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
		if (puntosEstadisticas[i] == 0) continue;
        cout << "# " << nombresEstadisticas[i] << "  -  " << puntosEstadisticas[i] << "pts";
    }
	
	rlutil::locate(50,22);
	cout << "--------------------------------";
	
	rlutil::locate(50,23);
	cout << "2 - volver";

    volver();
}

// texto de reglamento / instrucciones
void mostrarReglas() {
	rlutil::locate(50,3);
	cout << "====================================== ";
	rlutil::locate(50,4);
	cout << "             INSTRUCCIONES             ";
	rlutil::locate(50,5);
	cout << "====================================== ";
	/* CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR 
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
	CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR CAMBIAR */
	
	rlutil::locate(50,29);
    cout << "2 - volver";

    volver();
}

void mecanismoMenu() {

	// estas se modifican al jugar y luego se muestran en estadisticas
    int puntosEstadisticas[10] = {};
    string nombresEstadisticas[10] = {};

    bool botonEncendido = true;

    while (botonEncendido) {
		
        char decision = getch();

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
