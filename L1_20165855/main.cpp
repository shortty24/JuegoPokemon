#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define MAXF 60
#define MAXC 60
#define POKE_INI 20
#define POKE_DISPO 13
#define BLOQUEO 3
#define PTSREQUERIDOS 500


using namespace std;

void generaTablero(char tablero[][MAXC],int sizeMAXF,int NUMF,int NUMC,int numPokemones,int numPoke_paradas, char posiblesPokemones[]);
//void corrigeTablero(char tablero1[][MAXC], char tablero2[][MAXC], int sizeMAXF, int NUMF, int NUMC, char posiblesPokemones[], int numCasillas);
void colocaElemento(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, char letra, int numObjetos);
void imprimirTablero(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int numCasillas, char posiblesPokemones[]);
void ejecutaJugadaM(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int comando);
int ejecutaJugadaG(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int comando, int numCasillas, int PtsExperiencia, int numPokebolas, int xDePokeparada, int yDePokeparada, int Num_usado, int turno);
int ejecutaJugadaL(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int comando, int numCasillas, int PtsExperiencia, int numPokebolas, char posiblesPokemones[], int xDeCaptura, int yDeCaptura);
void actualizaDatos(int numPokemones, int numPoke_paradas, int numCasillas, int nivelJugador, int PtsExperiencia, int numPokebolas);
int verificaJugada(int nivelJugador,int numPokebolas);

int main() {
	/*Declarando mi arreglo bidimensional*/
	char tablero1[MAXF][MAXC];
	char posiblesPokemones[] = { 'A','B','C','D','E','F','N','O','P','Q','R','S','T' };
	int nivelJuego, NUMF, NUMC, PtsExperiencia = 0, numPokebolas = POKE_INI, numPokemones, numPoke_paradas, numCasillas, xDePokeparada, yDePokeparada, Usado, pokeAleatorio, Paso3turnos, turnoAct;
	int xDeCaptura, yDeCaptura;
	int nivelJugador = 1, Num_usado = 0, turno=0, capturado;

	srand(time(NULL)); /*Esto sirve para generar la aleatoriedad al momento de
						 obtener el valor de posI y posJ aleatorios*/

	cout << "Bienvenido a POKE-LPOO" << endl;
	cout << "Ingrese el nivel del juego (1 - Principiante, 2 - Intermedio, 3 - Avanzado): ";
	cin >> nivelJuego;

	if (nivelJuego > 0 && nivelJuego < 4) {
		/*Aquí si el nivel es correcto y toca avanzar*/
		/*Voy a definir la configuración de mi juego en base al nivel*/
		switch (nivelJuego) {
		case 1: {
			NUMF = 4;
			NUMC = 24;
			numPokemones = 10;
			numPoke_paradas = 10;
			numCasillas = 3;
			break;
		}
		case 2: {
			NUMF = 40;
			NUMC = 40;
			numPokemones = 60;
			numPoke_paradas = 15;
			numCasillas = 2;
			break;
		}
		case 3: {
			NUMF = 60;
			NUMC = 60;
			numPokemones = 120;
			numPoke_paradas = 30;
			numCasillas = 1;
			break;
		}
		}
	}

	generaTablero(tablero1, MAXF, NUMF, NUMC, numPokemones, numPoke_paradas, posiblesPokemones);
	cout << "El tablero es el siguiente: " << endl << endl;
	//corrigeTablero(tablero1, tablero2, MAXF, NUMF, NUMC, posiblesPokemones, numCasillas);
	imprimirTablero(tablero1, MAXF, NUMF, NUMC, numCasillas, posiblesPokemones);

	cout << "Nivel del jugador: " << nivelJugador << endl;
	cout << "Puntos de Experiencia: " << PtsExperiencia << endl;
	cout << "Número de Pokebolas: " << numPokebolas << endl << endl;

	char comando;
	int Espera3turnos = 0;

	while (nivelJugador < 5) {

		cout << "Ingrese su comando: ";
		cin >> comando;
		if (comando == 'M' || comando == 'G' || comando == 'L') {
			if (Num_usado!=0) {
				//turnoAct = turno;
				if (turno == (turnoAct + BLOQUEO)) {
					tablero1[xDePokeparada][yDePokeparada] = 'W';
					Num_usado = 0;
				}
			}
			if (comando == 'M') {
				ejecutaJugadaM(tablero1, MAXF, NUMF, NUMC, comando);

			}
			else if (comando == 'G') {
				cout << "Indique coordenada de la Pokeparada: ";
				cin >> xDePokeparada >> yDePokeparada;

				Usado = ejecutaJugadaG(tablero1, MAXF, NUMF, NUMC, comando, numCasillas, PtsExperiencia, numPokebolas, xDePokeparada, yDePokeparada, Num_usado, turno);
				if (Usado == 1) {
					pokeAleatorio = rand() % 5 + 1;
					numPokebolas += pokeAleatorio;
					PtsExperiencia += 50;
				}

				Num_usado = Usado;
				turnoAct = turno;
			}
			else if (comando == 'L') {

				cout << "Indique coordenada del pokemon: ";
				cin >> xDeCaptura >> yDeCaptura;

				capturado=ejecutaJugadaL(tablero1, MAXF, NUMF, NUMC, comando, numCasillas, PtsExperiencia, numPokebolas, posiblesPokemones, xDeCaptura, yDeCaptura);

				if (capturado) {
					PtsExperiencia += 100;
					tablero1[xDeCaptura][yDeCaptura] = '*';
				}
				else { cout << "No ha conseguido captura al Pokemon. Inténtelo de nuevo\n"; 
				}
				numPokebolas--;
			}

			if (PtsExperiencia > (PTSREQUERIDOS * nivelJugador)) {
				nivelJugador++;
			}

		actualizaDatos(numPokemones, numPoke_paradas, numCasillas, nivelJugador, PtsExperiencia, numPokebolas);
		
		imprimirTablero(tablero1, MAXF, NUMF, NUMC, numCasillas, posiblesPokemones);
		
		//corrigeTablero(tablero1, MAXF, NUMF, NUMC, posiblesPokemones, numCasillas);	
		/*int estado = verificaJugada(nivelJugador, numPokebolas);
		if (estado == 1) {
			cout << "Usted gano!!";
			fin = 1;
		}
		else {
			if (estado == 2) {
				cout << "Se quedó sin Pokebolas!!";
				fin = 1;
			}
		}*/
		}
		else {
			cout << "Comando ingresado es incorrecto\n";
		}
		turno++;

	}
	return 0;
}

/*void corrigeTablero(char tablero1[][MAXC], char tablero2[][MAXC],int sizeMAXF, int NUMF, int NUMC, char posiblesPokemones[], int numCasillas) {
	int aparezcaPokemon;

	for (int i = 0; i < NUMF; i++) {
		for (int j = 0; j < NUMC; j++) {
			for (int k = 0; k < POKE_DISPO; k++) {
				if (tablero1[i][j] == 'W' || tablero1[i][j] == 'J' || tablero1[i][j] == posiblesPokemones[k]) {
					tablero2[i][j] = tablero1[i][j];
				}

				else {
					tablero2[i][j] = '*';
				}
			}
		}
	}
	
}*/
void generaTablero(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int numPokemones, int numPoke_paradas, char posiblesPokemones[]){
	int pokAleatorio;
	char Pokemon;
	
	
	/*Inicializar Tablero - Colocar vacio a todos los elementos del arreglo*/
	for (int i = 0; i < NUMF; i++) {
		for (int j = 0; j < NUMC; j++) {
			tablero1[i][j] = '*';
		}
	}

	/*Inicializamos tablero 2 (Auxiliar)*/
	for (int m = 0; m < NUMF; m++) {
		for (int n = 0; n < NUMC; n++) {
			tablero1[m][n] = '*';
		}
	}
	
	for (int k=0; k < numPokemones; k++) {
		pokAleatorio = rand() % POKE_DISPO;
		Pokemon = posiblesPokemones[pokAleatorio];
		colocaElemento(tablero1, sizeMAXF, NUMF, NUMC, Pokemon, 1);
	}
	
	colocaElemento(tablero1, sizeMAXF, NUMF, NUMC, 'W', numPoke_paradas);
	colocaElemento(tablero1, sizeMAXF, NUMF, NUMC, 'J', 1);
}

void colocaElemento(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, char letra, int numObjetos) {
	int posI, posJ;
	for (int i = 1; i <= numObjetos; i++) {
		posI = rand() % NUMF;
		posJ = rand() % NUMC;
		if (tablero1[posI][posJ] == '*') {
			tablero1[posI][posJ] = letra;
		}
		else {
			i--;
		}
	}
}

void imprimirTablero(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int numCasillas, char posiblesPokemones[]) {
	int aparezcaPokemon;

	for (int m = 0; m < NUMF; m++) {
		for (int n = 0; n < NUMC; n++) {
			if (n != 0) cout << " ";
			cout << tablero1[m][n];
		}
		cout << endl;
	}
	cout << endl;
}

void ejecutaJugadaM(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int comando) {
	int direccion;

	cout << "Ingrese la dirección (1:LEFT, 2:RIGHT, 3:UP, 4:DOWN): ";
	cin >> direccion;

	for (int i = 0; i < NUMF; i++) {
		for (int j = 0; j < NUMC; j++) {
			
			if (tablero1[i][j] == 'J') {
				switch (direccion) {
				
					/*Iquierda*/
				case 1: {
					if (tablero1[i][j - 1] == '*') {
						tablero1[i][j - 1] = 'J';
						tablero1[i][j] = '*';
						j--;
					}				
					break;				
				}
					 
					 /*Derecha*/
				case 2: {
					if (tablero1[i][j + 1] == '*') {
						tablero1[i][j + 1] = 'J';
						tablero1[i][j] = '*';
						j++;
					}
					break;
				}
					 /*Arriba*/
				case 3: {
					if (tablero1[i - 1][j] == '*') {
						tablero1[i - 1][j] = 'J';
						tablero1[i][j] = '*';
						i--;
					}
					break;
				}
					 /*Abajo*/
				case 4: {
					if (tablero1[i + 1][j] == '*') {
						tablero1[i + 1][j] = 'J';
						tablero1[i][j] = '*';
						i++;
					}
					break;
				}
				}
			}
		}
	}
}

void actualizaDatos(int numPokemones, int numPoke_paradas, int numCasillas, int nivelJugador, int PtsExperiencia, int numPokebolas) {
	//cout << "\nLa posicion del jugador es (fila:columna)=(" << PosXJug << ":" << PosYJug << ")" << endl;
	cout << "Nivel del jugador: " << nivelJugador << endl;
	cout << "Puntos de experiencia: " << PtsExperiencia << endl;
	cout << "Pokebolas: " << numPokebolas << "\n\n";
}

int ejecutaJugadaG(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int comando, int numCasillas, int PtsExperiencia, int numPokebolas, int xDePokeparada, int yDePokeparada, int Num_usado, int turno){

if ((xDePokeparada < NUMF) && (xDePokeparada >= 0) && (yDePokeparada >= 0) && (yDePokeparada < NUMC)) {
		if ((tablero1[xDePokeparada][yDePokeparada] == 'W') || (tablero1[xDePokeparada][yDePokeparada] == 'X')) {
			if (tablero1[xDePokeparada][yDePokeparada] == 'W') {
				tablero1[xDePokeparada][yDePokeparada] = 'X';
				Num_usado++;
			}
			else if (tablero1[xDePokeparada][yDePokeparada] == 'X') {
				if (Num_usado < 3) {
					cout << "Esta Pokeparada ya ha sido girada. Intente luego de " << (3 - Num_usado) << " turnos.\n";
					Num_usado++;
				}
				else {
					tablero1[xDePokeparada][yDePokeparada] = 'W';
					Num_usado = 0;
				}
			}
		}
		else {
			cout << "Las coordenadas ingresadas no corresponden a una Pokeparada. Inténtelo nuevamente.\n";
		}
	}
	return Num_usado;
}

int ejecutaJugadaL(char tablero1[][MAXC], int sizeMAXF, int NUMF, int NUMC, int comando, int numCasillas, int PtsExperiencia, int numPokebolas, char posiblesPokemones[], int xDeCaptura, int yDeCaptura) {
	int capturado, EsPokemon=0;
	char Pokemon;

	if ((xDeCaptura < NUMF) && (xDeCaptura >= 0) && (yDeCaptura >= 0) && (yDeCaptura < NUMC)) {
		for (int z = 0; z < POKE_DISPO; z++) {
			if (tablero1[xDeCaptura][yDeCaptura] == posiblesPokemones[z]) {
				Pokemon = posiblesPokemones[z];
				EsPokemon = 1;
			}
		}

		if (EsPokemon) {
			capturado = rand() % 2;
			if (capturado) {
				cout << "Felicidades a capturado al pokemon " << Pokemon << endl;
			}
		}
		else {
			cout << "En esa coordenada no hay pokemon\n"; 
		}
	}
	else{ 
	cout << "Coordenadas invalidas\n"; 
	}
	return capturado;
}


/*int verificaJugada(char tablero[][MAXC], int sizeMAXF, int NUMF, int NUMC, int direccion) {
	int pacman = 0, estado;
	for (int i = 0; i < NUMF; i++) {
		for (int j = 0; j < NUMC; j++) {
			if (tablero[i][j] == 'P')
				pacman++;
		}
	}

	if (pacman > 0) {
		int monedas = 0;
		for (int i = 0; i < NUMF; i++) {
			for (int j = 0; j < NUMC; j++) {
				if (tablero[i][j] == 'B')
					monedas++;
			}
		}
		if (monedas > 0) {
			estado = 3;
		}
		else {
			estado = 1;
		}
	}
	else {
		estado = 2;
	}
	return estado;
}*/