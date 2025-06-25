#pragma once

#include <iostream>
#include <vector>

using namespace std;

void jugar(vector<int>& puntosEstadisticas, vector<string>& nombresEstadisticas);

string pedirnombre();

void decidirPrimerTurno(string& jugador1, string& jugador2);

vector<int> tiradaDados(int cantDados);

vector<int> turno(string jugador, int cantDados, int& totalPuntaje, int contadorPartidas);

vector<int> elegirDadosTirados(vector<int> dadosStock, int numeroObjetivo, string jugadorActual, int& totalPuntaje, int contadorPartidas);

void mostrarDadosTirados(vector<int> dadosStock, string nombre, int numeroObjetivo, int sumaTotal, int contadorPartidas);

bool tiradaFallada (vector<int> dadosStock, int numeroObjetivo);

bool tiradaExitosa (vector<int> dadosStock, int numeroObjetivo);

int tirardado6caras();

int tirardado12caras(string nombre);

void ordenarVector (vector<int>& puntosEstadisticas, vector<string>& nombresEstadisticas);

void agregarEstadisticas(vector<int> puntajes, vector<string> nombres, vector<int>& puntosEstadisticas, vector<string>& nombresEstadisticas);

void mostrarganador(string jugador1, string jugador2, int tiradasJugador1, int tiradasJugador2);
