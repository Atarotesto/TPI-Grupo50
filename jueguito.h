#pragma once

#include <iostream>

using namespace std;

void jugar(int (&puntosEstadisticas)[10], string (&nombresEstadisticas)[10]);

void pedirNombre(string& jugadorUno, string& jugadorDos);

void decidirPrimerTurno(string& jugadorUno, string& jugadorDos);

void turno(string jugador, int& cantDadosDelJugador, int& puntajeJugador, int contadorPartidas, int& dadosUsados, int& puntajeRonda);

int elegirDadosTirados(int& cantDadosDelJugador, int dadosStock[], int numeroMeta, string jugador, int puntajeJugador, int contadorPartidas , int& cantDadosUsados);

void mostrarDadosTirados(int dadosStock[], string jugador, int numeroMeta, int puntajeJugador, int contadorPartidas);

bool tiradaFallada (int dadosStock[], int numeroObjetivo);

bool tiradaExitosa (int dadosStock[], int numeroObjetivo);

int dadoDeSeisCaras();

int dadoDeDoceCaras(string nombrejugador);
	
void compararPuntajes(int puntajes[], string nombres[], int puntosEstadisticas[], string nombresEstadisticas[]);

void empate(int puntajeUno, int puntajeDos, string nombreUno, string nombreDos);

void agregarEstadisticas(int puntaje, string nombre, int puntosEstadisticas[], string nombresEstadisticas[]);

void mostrarganador(int puntaje, string nombre);

void menuEntreTirada(string nombre, int puntaje, int dadosRestantes, int puntajeRonda);
