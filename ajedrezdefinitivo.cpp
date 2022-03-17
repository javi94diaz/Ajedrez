#include <iostream>
using namespace std;

class tablero;

class marcador {
private:
	bool turno = 1;		//Empieza por 1 para que al entrar por primera vez en el bucle do-while de la partida se cambie a 0 y empiecen blancas así
	char color_actual[8];
public:
	void cambia_turno() { turno = (!turno); }
	bool ver_turno() { return turno; }
	void imprime();
};

class pieza {
private:
	char color; 			// será 'b' si es una pieza blanca y 'n' si es una pieza negra
	char letra;

protected: 				// Pongo la fila y columna actuales de la pieza como protected para que cada pieza tenga el control de su posicion
	char columna_pieza; 	// Nota: La fila y la columna iniciales de cada pieza debe darlas el tablero (?)
	int fila_pieza;
	bool muerto;
public:
	pieza(char colour, char letter, char col, int fil) { color = colour; letra = letter; columna_pieza = col; fila_pieza = fil; muerto = 0; }
	char getletra() { return letra; }
	char getcolor() { return color; }
	char getcolumna() { return columna_pieza; }
	int getfila() { return fila_pieza; }
	virtual bool moverse(const char, const int) { cout << "hello"; return 0; }
};

class alfil : public pieza {
public:
	alfil(char colour, char letter, char col, int fil) : pieza(colour, letter, col, fil) {}
	bool moverse(const char, const int);
	bool capturar(const char, const int);

};

class caballo : public pieza {
public:
	caballo(char colour, char letter, char col, int fil) : pieza(colour, letter, col, fil) {}
	bool moverse(const char, const int);
};

class dama : public pieza {
public:
	dama(char colour, char letter, char col, int fil) : pieza(colour, letter, col, fil) {}
	bool moverse(const char, const int);
	bool capturar(const char, const int);

};

class rey : public pieza {
private:
	bool he_movido;

public:
	rey(char colour, char letter, char col, int fil) : pieza(colour, letter, col, fil) { he_movido = 0; }
	bool moverse(const char, const int);
};

class torre : public pieza {
private:
	bool he_movido;
public:
	torre(char colour, char letter, char col, int fil) : pieza(colour, letter, col, fil) {}
	bool moverse(const char, const int);
	bool capturar(const char, const int);
};

class peon : public pieza {
private:
	bool he_movido;
public:
	peon(char colour, char letter, char col, int fil) : pieza(colour, letter, col, fil) { he_movido = 0; }
	bool moverse(const char, const int);
	bool capturar(const char, const int);
};

class fantasma : public pieza {
public:
	fantasma(char colour, char letter, char col, int fil) : pieza(colour, letter, col, fil) {}
};

class casilla {
private:
	pieza *p;
public:
	pieza* punt() { return p; }
	void setp(pieza* una) { p = una; }
};

class tablero {

private:
	casilla **tabla;

public:
	tablero();		//constructor del tablero en el fichero tablero.cpp
	void imprimetablero();		//imprime el tablero 
	casilla gettabla(int fil, int col) { return tabla[fil][col]; }
	void cambio_casilla(int, char, int, char);
};

//declaracion de las piezas como variables globales

tablero mitablero; 	//declaro tablero

torre TN1('n', 'T', 'a', 8);		//creo una torre negra llamando al constructor de torre
torre TN2('n', 'T', 'h', 8);		//creo la otra torre negra llamando al constructor de torre
caballo CN1('n', 'C', 'b', 8);		//creo un caballo negro llamando al constructor de caballo
caballo CN2('n', 'C', 'g', 8);		//creo el otro caballo negro llamando al constructor de caballo
alfil AN1('n', 'A', 'c', 8);		//creo el alfil negro llamando al constructor de alfil
alfil AN2('n', 'A', 'f', 8);		//creo el otro alfil negro llamando al constructor de alfil
rey RN('n', 'R', 'e', 8);		//creo el rey negro llamando al constructor de rey
dama DN('n', 'D', 'd', 8);		//creo la dama negra llamando al constructor de dama
peon PN1('n', 'P', 'a', 7);
peon PN2('n', 'P', 'b', 7);
peon PN3('n', 'P', 'c', 7);
peon PN4('n', 'P', 'd', 7);
peon PN5('n', 'P', 'e', 7);		//creo los peones negros llamando al constructor de peon que a su vez llama al constructor de pieza
peon PN6('n', 'P', 'f', 7);
peon PN7('n', 'P', 'g', 7);
peon PN8('n', 'P', 'h', 7);

torre tb1('b', 't', 'a', 1);		//creo una torre blanca llamando al constructor de torre
torre tb2('b', 't', 'h', 1);		//creo la otra torre blanca llamando al constructor de torre
caballo cb1('b', 'c', 'b', 1);		//creo un caballo blanco llamando al constructor de caballo
caballo cb2('b', 'c', 'g', 1);		//creo el otro caballo blanco llamando al constructor de caballo
alfil ab1('b', 'a', 'c', 1);		//creo el alfil blanco llamando al constructor de alfil
alfil ab2('b', 'a', 'f', 1);		//creo el otro blanco negro llamando al constructor de alfil
rey rb('b', 'r', 'e', 1);		//creo el rey blanco llamando al constructor de rey
dama db('b', 'd', 'd', 1);		//creo la dama blanca llamando al constructor de dama
peon pb1('b', 'p', 'a', 2);
peon pb2('b', 'p', 'b', 2);
peon pb3('b', 'p', 'c', 2);
peon pb4('b', 'p', 'd', 2);
peon pb5('b', 'p', 'e', 2);		//creo los peones blancos llamando al constructor de peon que a su vez llama al constructor de pieza
peon pb6('b', 'p', 'f', 2);
peon pb7('b', 'p', 'g', 2);
peon pb8('b', 'p', 'h', 2);

fantasma espacio(' ', ' ', ' ', ' '); //pieza fantasma para las casillas vacias

marcador m_turno;  //Se instancia el objeto m_turno que es de clase marcador_turno	

bool hay_equis=0;

tablero::tablero() {			//constructor de tablero, no recibe nada, crea la tabla,las piezas y las coloca en las posiciones iniciales
	int i;

	tabla = new casilla *[8];		//tabla de 8 filas
	for (i = 0; i<8; i++) {
		tabla[i] = new casilla[8];	//por cada fila 8 casillas (columnas)
	}

	tabla[7][0].setp(&TN1);		//asocio las casillas de las dos primeras filas a las direcciones de las piezas negras
	tabla[7][1].setp(&CN1);
	tabla[7][2].setp(&AN1);
	tabla[7][3].setp(&DN);
	tabla[7][4].setp(&RN);
	tabla[7][5].setp(&AN2);
	tabla[7][6].setp(&CN1);
	tabla[7][7].setp(&TN2);
	tabla[6][0].setp(&PN1);
	tabla[6][1].setp(&PN2);
	tabla[6][2].setp(&PN3);
	tabla[6][3].setp(&PN4);
	tabla[6][4].setp(&PN5);
	tabla[6][5].setp(&PN6);
	tabla[6][6].setp(&PN7);
	tabla[6][7].setp(&PN8);

	tabla[1][0].setp(&pb1);		 //asocio las casillas de las dos ultimas filas a las direcciones de las piezas blancas
	tabla[1][1].setp(&pb2);
	tabla[1][2].setp(&pb3);
	tabla[1][3].setp(&pb4);
	tabla[1][4].setp(&pb5);
	tabla[1][5].setp(&pb6);
	tabla[1][6].setp(&pb7);
	tabla[1][7].setp(&pb8);
	tabla[0][0].setp(&tb1);
	tabla[0][1].setp(&cb1);
	tabla[0][2].setp(&ab1);
	tabla[0][3].setp(&db);
	tabla[0][4].setp(&rb);
	tabla[0][5].setp(&ab2);
	tabla[0][6].setp(&cb2);
	tabla[0][7].setp(&tb2);

	for (i = 2; i<6; i++)
		for (int j = 0; j<8; j++) tabla[i][j].setp(&espacio); //las casillas vacias apuntan a una figura fantasma que imprimira un espacio
}

void tablero::imprimetablero() {		//funcion que imprime el tablero perteneciente a la clase tablero

	cout << "        a     b     c     d     e     f     g     h  " << endl;
	cout << "      _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;  //Casillas de 3x3
	cout << "     |     |     |     |     |     |     |     |     |" << endl;
	cout << "  8  |  " << tabla[7][0].punt()->getletra() << "  |  " << tabla[7][1].punt()->getletra() << "  |  " << tabla[7][2].punt()->getletra() << "  |  " << tabla[7][3].punt()->getletra() << "  |  " << tabla[7][4].punt()->getletra() << "  |  " << tabla[7][5].punt()->getletra() << "  |  " << tabla[7][6].punt()->getletra() << "  |  " << tabla[7][7].punt()->getletra() << "  |" << endl;
	cout << "     |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
	cout << "     |     |     |     |     |     |     |     |     |" << endl;
	cout << "  7  |  " << tabla[6][0].punt()->getletra() << "  |  " << tabla[6][1].punt()->getletra() << "  |  " << tabla[6][2].punt()->getletra() << "  |  " << tabla[6][3].punt()->getletra() << "  |  " << tabla[6][4].punt()->getletra() << "  |  " << tabla[6][5].punt()->getletra() << "  |  " << tabla[6][6].punt()->getletra() << "  |  " << tabla[6][7].punt()->getletra() << "  |" << endl;
	cout << "     |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
	cout << "     |     |     |     |     |     |     |     |     |" << endl;
	cout << "  6  |  " << tabla[5][0].punt()->getletra() << "  |  " << tabla[5][1].punt()->getletra() << "  |  " << tabla[5][2].punt()->getletra() << "  |  " << tabla[5][3].punt()->getletra() << "  |  " << tabla[5][4].punt()->getletra() << "  |  " << tabla[5][5].punt()->getletra() << "  |  " << tabla[5][6].punt()->getletra() << "  |  " << tabla[5][7].punt()->getletra() << "  |" << endl;
	cout << "     |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
	cout << "     |     |     |     |     |     |     |     |     |" << endl;
	cout << "  5  |  " << tabla[4][0].punt()->getletra() << "  |  " << tabla[4][1].punt()->getletra() << "  |  " << tabla[4][2].punt()->getletra() << "  |  " << tabla[4][3].punt()->getletra() << "  |  " << tabla[4][4].punt()->getletra() << "  |  " << tabla[4][5].punt()->getletra() << "  |  " << tabla[4][6].punt()->getletra() << "  |  " << tabla[4][7].punt()->getletra() << "  |" << endl;
	cout << "     |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
	cout << "     |     |     |     |     |     |     |     |     |" << endl;
	cout << "  4  |  " << tabla[3][0].punt()->getletra() << "  |  " << tabla[3][1].punt()->getletra() << "  |  " << tabla[3][2].punt()->getletra() << "  |  " << tabla[3][3].punt()->getletra() << "  |  " << tabla[3][4].punt()->getletra() << "  |  " << tabla[3][5].punt()->getletra() << "  |  " << tabla[3][6].punt()->getletra() << "  |  " << tabla[3][7].punt()->getletra() << "  |" << endl;
	cout << "     |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
	cout << "     |     |     |     |     |     |     |     |     |" << endl;
	cout << "  3  |  " << tabla[2][0].punt()->getletra() << "  |  " << tabla[2][1].punt()->getletra() << "  |  " << tabla[2][2].punt()->getletra() << "  |  " << tabla[2][3].punt()->getletra() << "  |  " << tabla[2][4].punt()->getletra() << "  |  " << tabla[2][5].punt()->getletra() << "  |  " << tabla[2][6].punt()->getletra() << "  |  " << tabla[2][7].punt()->getletra() << "  |" << endl;
	cout << "     |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
	cout << "     |     |     |     |     |     |     |     |     |" << endl;
	cout << "  2  |  " << tabla[1][0].punt()->getletra() << "  |  " << tabla[1][1].punt()->getletra() << "  |  " << tabla[1][2].punt()->getletra() << "  |  " << tabla[1][3].punt()->getletra() << "  |  " << tabla[1][4].punt()->getletra() << "  |  " << tabla[1][5].punt()->getletra() << "  |  " << tabla[1][6].punt()->getletra() << "  |  " << tabla[1][7].punt()->getletra() << "  |" << endl;
	cout << "     |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
	cout << "     |     |     |     |     |     |     |     |     |" << endl;
	cout << "  1  |  " << tabla[0][0].punt()->getletra() << "  |  " << tabla[0][1].punt()->getletra() << "  |  " << tabla[0][2].punt()->getletra() << "  |  " << tabla[0][3].punt()->getletra() << "  |  " << tabla[0][4].punt()->getletra() << "  |  " << tabla[0][5].punt()->getletra() << "  |  " << tabla[0][6].punt()->getletra() << "  |  " << tabla[0][7].punt()->getletra() << "  |" << endl;
	cout << "     |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|\n" << endl;

}

void tablero::cambio_casilla(int fil, char col, int fila_pieza, char col_pieza) {
	tabla[fil - 1][col - 97].setp(tabla[fila_pieza - 1][col_pieza - 97].punt());
	tabla[fila_pieza - 1][col_pieza - 97].setp(&espacio);
}

bool torre::moverse(const char col, const int fil) {
	int i;

	if ((col<'a') || (col>'h') || (fil<1) || (fil>8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if ((col == columna_pieza) && (fil == fila_pieza)) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if ((col != columna_pieza) && (fil != fila_pieza)) return 0;
	if (hay_equis ? (mitablero.gettabla(fil - 1, col - 97).punt() == &espacio) : (mitablero.gettabla(fil - 1, col - 97).punt() != &espacio)) return 0; // Si el usuario ha ordenado capturar, debe haber pieza en el destino. Si ha ordenado mover, no debe haberla.
	if (col == columna_pieza) {								// ESTO ES UN POCO FOLLON PERO CREO QUE ESTA BIEN HECHO
		for (i = 1; i< abs(fil - fila_pieza); i++) {			// A grandes rasgos, he separado casos de que se mueva en vertical(misma columna) o en horizontal(misma fila)
			if (fil>fila_pieza) {							// y compruebe que no hay pieza en las casillas intermedias ni en la destino.
				if ((mitablero.gettabla(fil - 1 - i, col - 97).punt()) != &espacio) return 0;
			}
			if (fil<fila_pieza) {
				if ((mitablero.gettabla(fil - 1 + i, col - 97).punt()) != &espacio) return 0;
			}
		}
		mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
		columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
		fila_pieza = fil;
		if (he_movido == 0) he_movido = 1;
		return 1;
	}
	if (fil == fila_pieza) {
		for (i = 1; i< abs(col - columna_pieza); i++) {
			if (col>columna_pieza) {
				if ((mitablero.gettabla(fil - 1, col - 97 - i).punt()) != &espacio) return 0;
			}
			if (col<columna_pieza) {
				if ((mitablero.gettabla(fil - 1, col - 97 + i).punt()) != &espacio) return 0;
			}
		}
		mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
		columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
		fila_pieza = fil;
		if (he_movido == 0) he_movido = 1;
		return 1;
	}

}

bool torre::capturar(const char col, const int fil) {
	int i;

	if ((col<'a') || (col>'h') || (fil<1) || (fil>8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if ((col == columna_pieza) && (fil == fila_pieza)) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if ((col != columna_pieza) && (fil != fila_pieza)) return 0;
	if (mitablero.gettabla(fil-1,col-97).punt()==&espacio)return 0;

	else {
		if (col == columna_pieza) {								// ESTO ES UN POCO FOLLON PERO CREO QUE ESTA BIEN HECHO
			for (i = 1; i < abs(fil - fila_pieza); i++) {			// A grandes rasgos, he separado casos de que se mueva en vertical(misma columna) o en horizontal(misma fila)
				if (fil > fila_pieza) {							// y compruebe que no hay pieza en las casillas intermedias ni en la destino.
					if ((mitablero.gettabla(fil - 1 - i, col - 97).punt()) != &espacio) return 0;
				}
				if (fil < fila_pieza) {
					if ((mitablero.gettabla(fil - 1 + i, col - 97).punt()) != &espacio) return 0;
				}
			}
			mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
			columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
			fila_pieza = fil;
			if (he_movido == 0) he_movido = 1;
			return 1;
		}
		if (fil == fila_pieza) {
			for (i = 1; i < abs(col - columna_pieza); i++) {
				if (col > columna_pieza) {
					if ((mitablero.gettabla(fil - 1, col - 97 - i).punt()) != &espacio) return 0;
				}
				if (col < columna_pieza) {
					if ((mitablero.gettabla(fil - 1, col - 97 + i).punt()) != &espacio) return 0;
				}
			}
			mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
			columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
			fila_pieza = fil;
			if (he_movido == 0) he_movido = 1;
			return 1;
		}
	}
}

bool peon::moverse(const char col, const int fil) {
	if ((col<'a') || (col>'h') || (fil<1) || (fil>8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if (col == columna_pieza && fil == fila_pieza) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if (col != columna_pieza) return 0;
	if (getcolor() == 'b') {
		switch (he_movido) {
		case 0:		// Si el peon no se ha movido, puede avanzar una o dos casillas
			if ((fil < fila_pieza) || (fil > fila_pieza + 2)) return 0;	// Comprobamos que la casilla este delante del peon o dos posiciones delante (no detras ni mas alla)
			if ((fil - fila_pieza == 2) && ((mitablero.gettabla(fil - 1, col - 97).punt() != &espacio) || (mitablero.gettabla(fil - 2, col - 97).punt() != &espacio)))return 0; //Vemos si hay piezas en la trayectoria y en el destino cuando el movimiento es de dos casillas
			if ((fil - fila_pieza == 1) && (mitablero.gettabla(fil - 1, col - 97).punt() != &espacio))return 0; //si el movimiento es una casilla adelante comprueba que esta vacia
			else {
				mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
				columna_pieza = col;														//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
				fila_pieza = fil;
				if (he_movido == 0) he_movido = 1;
				return 1;
			}
		case 1:		// Si el peon ya se ha movido solo puede avanzar una casilla
			if ((fil < fila_pieza) || (fil > fila_pieza + 1)) return 0;  // Comprobamos que la casilla este delante del peon (no detras ni mas alla)
			if (mitablero.gettabla(fil - 1, col - 97).punt() != &espacio) return 0; //Vemos si hay pieza en el destino
			else {
				mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
				columna_pieza = col;														//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
				fila_pieza = fil;
				if (he_movido == 0) he_movido = 1;
				return 1;
			}
		}
	}
	else {		//si el peon es negro
		switch (he_movido) {
		case 0:		// Si el peon no se ha movido, puede avanzar una o dos casillas
			if ((fil > fila_pieza) || (fil < fila_pieza - 2)) return 0;	// Comprobamos que la casilla este delante del peon o dos posiciones delante (no detras ni mas alla)
			if ((fil - fila_pieza == 2) && ((mitablero.gettabla(fil - 1, col - 97).punt()!=&espacio) || (mitablero.gettabla(fil, col - 97).punt()!=&espacio)))return 0; //Vemos si hay piezas en la trayectoria y en el destino cuando el movimiento son dos casillas
			if ((fil - fila_pieza == 1) && (mitablero.gettabla(fil - 1, col - 97).punt()!=&espacio)) return 0; //si el movimiento es una casilla comprueba que este vacia
			else {
				mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
				columna_pieza = col;														//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
				fila_pieza = fil;
				if (he_movido == 0) he_movido = 1;
				return 1;
			}
		case 1:		// Si el peon ya se ha movido solo puede avanzar una casilla
			if ((fil > fila_pieza) || (fil < fila_pieza - 2)) return 0;  // Comprobamos que la casilla este delante del peon (no detras ni mas alla)
			else if (mitablero.gettabla(fil - 1, col - 97).punt()!=&espacio) return 0; //Vemos si hay pieza en el destino
			else {
				mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
				columna_pieza = col;														//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
				fila_pieza = fil;
				if (he_movido == 0) he_movido = 1;
				return 1;
			}
		}
	}
}

bool peon::capturar(const char col, const int fil) {
	if ((col < 'a') || (col > 'h') || (fil < 1) || (fil > 8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if (col == columna_pieza && fil == fila_pieza) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if ((abs(col - columna_pieza) != 1) && (abs(fil - fila_pieza) != 1)) return 0;  // Comprobamos que el destino este en una de las diagonales inmediatamente delanteras del peon
	if ((mitablero.gettabla(fil - 1, col - 97).punt()) == &espacio) return 0;
	else{
		mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
		columna_pieza = col;														//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
		fila_pieza = fil;
		if (he_movido == 0) he_movido = 1;
		return 1;
	}
}

bool caballo::moverse(const char col, const int fil) {
	if ((col < 'a') || (col > 'h') || (fil < 1) || (fil > 8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if ((col == columna_pieza) && (fil == fila_pieza)) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if ((hay_equis ? (mitablero.gettabla(fil - 1, col - 97).punt() == &espacio) : (mitablero.gettabla(fil - 1, col - 97).punt() != &espacio))) return 0; // Si el usuario ha ordenado capturar, debe haber pieza en el destino. Si ha ordenado mover, no debe haberla.
	if ((abs(col - columna_pieza) + abs(fil - fila_pieza)) != 3) return 0; // Restamos destino y posicion actual en filas y columnas, y la suma debe ser tres. Entonces la casilla esta en una "L" y el caballo puede moverse alli.
	else{
		mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
		columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
		fila_pieza = fil; 
		return 1;
	}
}

bool alfil::moverse(const char col, const int fil) {
	int i;

	if ((col<'a') || (col>'h') || (fil<1) || (fil>8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if ((col == columna_pieza) && (fil == fila_pieza)) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if (abs(col - columna_pieza) != abs(fil - fila_pieza)) return 0; //Comprobamos que la casilla destino esta en una de las diagonales del alfil
	else {
		if ((fil>fila_pieza) && (col>columna_pieza)) { // Si la casilla destino esta en la diagonal a 45 grados (arriba-derecha)
			for (i = 1; i<= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - i, col - 97 +1 - i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else { 
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 1

		if ((fil>fila_pieza) && (col<columna_pieza)) { // Si la casilla destino esta en la diagonal a 135 grados (arriba-izquierda)
			for (i = 1; i<= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - i, col - 97 -1 + i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 2

		if ((fil<fila_pieza) && (col<columna_pieza)) { // Si la casilla destino esta en la diagonal a 225 grados (abajo-izquierda)
			for (i = 1; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - 2 + i, col - 97 -1 + i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 3

		if ((fil<fila_pieza) && (col>columna_pieza)) { // Si la casilla destino esta en la diagonal a 315 grados (abajo-derecha)
			for (i = 1; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - 2 + i, col - 97 +1 - i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 4
	} //fin else
}

bool alfil::capturar(const char col, const int fil) {
	int i;
	if ((col<'a') || (col>'h') || (fil<1) || (fil>8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if ((col == columna_pieza) && (fil == fila_pieza)) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if (abs(col - columna_pieza) != abs(fil - fila_pieza)) return 0; //Comprobamos que la casilla destino esta en una de las diagonales del alfil
	if (mitablero.gettabla(fil - 1, col - 97).punt() == &espacio) return 0;	//comprobamos que la casilla de destino esta ocupada
	if (mitablero.gettabla(fil - 1, col - 97).punt()->getcolor() == getcolor())return 0; //no puedes comerte una pieza de tu color
	else {
		if ((fil>fila_pieza) && (col>columna_pieza)) { // Si la casilla destino esta en la diagonal a 45 grados (arriba-derecha)
			for (i = 2; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - i, col - 97 + 1 - i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 1

		if ((fil>fila_pieza) && (col<columna_pieza)) { // Si la casilla destino esta en la diagonal a 135 grados (arriba-izquierda)
			for (i = 2; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - i, col - 97 - 1 + i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 2

		if ((fil<fila_pieza) && (col<columna_pieza)) { // Si la casilla destino esta en la diagonal a 225 grados (abajo-izquierda)
			for (i = 2; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - 2 + i, col - 97 - 1 + i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 3

		if ((fil<fila_pieza) && (col>columna_pieza)) { // Si la casilla destino esta en la diagonal a 315 grados (abajo-derecha)
			for (i = 2; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - 2 + i, col - 97 + 1 - i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 4
	} //fin else


}

bool dama::moverse(const char col, const int fil) {
	if ((col<'a') || (col>'h') || (fil<1) || (fil>8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if ((col == columna_pieza) && (fil == fila_pieza)) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if (hay_equis ? (mitablero.gettabla(fil - 1, col - 97).punt() == &espacio) : (mitablero.gettabla(fil - 1, col - 97).punt() != &espacio)) return 0; // Si el usuario ha ordenado capturar, debe haber pieza en el destino. Si ha ordenado mover, no debe haberla.
	if (col == columna_pieza) {											// MOVIMIENTO EN VERTICAL COMO UNA TORRE
		for (int i = 1; i < abs(fil - fila_pieza); i++) {
			if (fil > fila_pieza) {
				if ((mitablero.gettabla(fil - 1 - i, col - 97).punt()) != &espacio) return 0;
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
			if (fil < fila_pieza) {
				if ((mitablero.gettabla(fil - 1 + i, col - 97).punt()) != &espacio) return 0;
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		}
	} //fin movimiento en vertical
	if (fil == fila_pieza) {										// MOVIMIENTO EN HORIZONTAL COMO UNA TORRE
		for (int i = 1; i< abs(col - columna_pieza); i++) {
			if (col>columna_pieza) {
				if ((mitablero.gettabla(fil - 1, col - 97 - i).punt()) != &espacio) return 0;
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
			if (col<columna_pieza) {
				if ((mitablero.gettabla(fil - 1, col - 97 + i).punt()) != &espacio) return 0;
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		}
	} //fin movimiento en horizontal
	if (abs(col - columna_pieza) == abs(fil - fila_pieza)) { 		// MOVIMIENTO EN DIAGONAL COMO UN ALFIL
		if ((fil>fila_pieza) && (col>columna_pieza)) { // Si la casilla destino esta en la diagonal a 45 grados (arriba-derecha)
			for (int i = 1; i<= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - i, col - 97 + 1 - i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 1

		if ((fil>fila_pieza) && (col<columna_pieza)) { // Si la casilla destino esta en la diagonal a 135 grados (arriba-izquierda)
			for (int i = 1; i<= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - i, col - 97 - 1 + i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 2

		if ((fil<fila_pieza) && (col<columna_pieza)) { // Si la casilla destino esta en la diagonal a 225 grados (abajo-izquierda)
			for (int i = 1; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - 2 + i, col - 97 - 1 + i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 3

		if ((fil<fila_pieza) && (col>columna_pieza)) { // Si la casilla destino esta en la diagonal a 315 grados (abajo-derecha)
			for (int i = 1; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - 2 + i, col - 97 + 1 - i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 4
	} //fin movimiento en diagonal
	else return 0;
}

bool dama::capturar(const char col, const int fil) {
	if ((col<'a') || (col>'h') || (fil<1) || (fil>8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if ((col == columna_pieza) && (fil == fila_pieza)) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if (mitablero.gettabla(fil - 1, col - 97).punt() == &espacio)return 0;	//en la captura la casilla destino tiene que estar ocupada
	if (mitablero.gettabla(fil - 1, col - 97).punt()->getcolor() == getcolor())return 0;	//el color de la pieza que vamos a capturar tiene que ser diferente

	if (col == columna_pieza) {											// MOVIMIENTO EN VERTICAL COMO UNA TORRE
		for (int i = 1; i < abs(fil - fila_pieza); i++) {
			if (fil > fila_pieza) {
				if ((mitablero.gettabla(fil - 1 - i, col - 97).punt()) != &espacio) return 0;
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
			if (fil < fila_pieza) {
				if ((mitablero.gettabla(fil - 1 + i, col - 97).punt()) != &espacio) return 0;
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		}
	} //fin movimiento en vertical
	if (fil == fila_pieza) {										// MOVIMIENTO EN HORIZONTAL COMO UNA TORRE
		for (int i = 1; i< abs(col - columna_pieza); i++) {
			if (col>columna_pieza) {
				if ((mitablero.gettabla(fil - 1, col - 97 - i).punt()) != &espacio) return 0;
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
			if (col<columna_pieza) {
				if ((mitablero.gettabla(fil - 1, col - 97 + i).punt()) != &espacio) return 0;
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		}
	} //fin movimiento en horizontal
	if (abs(col - columna_pieza) == abs(fil - fila_pieza)) { 		// MOVIMIENTO EN DIAGONAL COMO UN ALFIL
		if ((fil>fila_pieza) && (col>columna_pieza)) { // Si la casilla destino esta en la diagonal a 45 grados (arriba-derecha)
			for (int i = 2; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - i, col - 97 + 1 - i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 1

		if ((fil>fila_pieza) && (col<columna_pieza)) { // Si la casilla destino esta en la diagonal a 135 grados (arriba-izquierda)
			for (int i = 2; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - i, col - 97 - 1 + i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 2

		if ((fil<fila_pieza) && (col<columna_pieza)) { // Si la casilla destino esta en la diagonal a 225 grados (abajo-izquierda)
			for (int i = 2; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - 2 + i, col - 97 - 1 + i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 3

		if ((fil<fila_pieza) && (col>columna_pieza)) { // Si la casilla destino esta en la diagonal a 315 grados (abajo-derecha)
			for (int i = 2; i <= abs(fil - fila_pieza); i++) {
				if ((mitablero.gettabla(fil - 2 + i, col - 97 + 1 - i).punt()) != &espacio) return 0; // Comprobamos que no haya piezas en casillas intermedias
				else {
					mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
					columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
					fila_pieza = fil;
					return 1;
				}
			}
		} //fin if 4
	} //fin movimiento en diagonal
	else return 0;
}


bool rey::moverse(const char col, const int fil) {
	if ((col<'a') || (col>'h') || (fil<1) || (fil>8)) return 0; //Primero comprobamos que la casilla este dentro del limite del tablero
	if ((col == columna_pieza) && (fil == fila_pieza)) { cout << "La pieza ya esta en esa posicion"; return 0; }//Comprobamos que el usuario no haya introducido la casilla actual de la pieza
	if ((hay_equis ? (mitablero.gettabla(fil - 1, col - 97).punt() == &espacio) : (mitablero.gettabla(fil - 1, col - 97).punt() != &espacio))) return 0; // Si el usuario ha ordenado capturar, debe haber pieza en el destino. Si ha ordenado mover, no debe haberla.
	if ((abs(col - columna_pieza)>1) || (abs(fil - fila_pieza)>1)) return 0;			// El rey solo puede moverse a casillas contiguas, en cualquier direccion
	else {
		mitablero.cambio_casilla(fil, col, fila_pieza, columna_pieza);
		columna_pieza = col;															//Actualizamos los valores de fila y columna de la pieza a los de la casilla a la que se ha movido
		fila_pieza = fil;
		if (he_movido == 0) he_movido = 1;
		return 1;
	}
}

void marcador::imprime() {
	cout << " _______________________ \n";
	cout << "|                       |\n";

	cout << "| TURNO ACTUAL: ";
	if (ver_turno() == 0) cout << "BLANCAS |" << endl;
	else cout << "NEGRAS  |" << endl;

	cout << "|_______________________|\n";
}


int main() {
	
	char jugada[10];
	bool error = 0;			// Detección errores de sintaxis
	int exitojugada;		// Detección si se ha completado la jugada
	bool turno;				// Variable que almacena el turno en cada jugada tras una llamada al objeto de la clase marcador_turno
	int longitud;
	char columna;
	int fila;


	do {					   			//Bucle do-while de la partida al completo, de manera que se vuelva a entrar en el bucle de cada jugada cada vez que se cambie de turno
		m_turno.cambia_turno(); 			//Cada vez que se repite el bucle cambia de turno
		m_turno.imprime();
		turno = m_turno.ver_turno();   	//Vemos el turno una sóla vez por jugada
		mitablero.imprimetablero();
		do {							//Bucle do-while de cada jugada
			exitojugada = 0;
			error = 0;
			hay_equis = 0;
			cout << "Introduzca su jugada: ";
			cin >> jugada;
			longitud = strlen(jugada);
			if ((longitud < 2) || (longitud > 5)) error = 1;	// Ninguna jugada es de mas de 5 caracteres

			if (longitud == 2) {
				columna = jugada[0];
				fila = jugada[1] - 48;
				/*mover peon*/
				if (turno == 0) {		//Si es el turno de las blancas intenta mover todos los peones blancos
					exitojugada += pb1.moverse(columna, fila);
					exitojugada += pb2.moverse(columna, fila);
					exitojugada += pb3.moverse(columna, fila);
					exitojugada += pb4.moverse(columna, fila);
					exitojugada += pb5.moverse(columna, fila);
					exitojugada += pb6.moverse(columna, fila);
					exitojugada += pb7.moverse(columna, fila);
					exitojugada += pb8.moverse(columna, fila);
				}
				else {					//Si es el turno de las negras intenta mover todos los peones negros
					exitojugada += PN1.moverse(columna, fila);
					exitojugada += PN2.moverse(columna, fila);
					exitojugada += PN3.moverse(columna, fila);
					exitojugada += PN4.moverse(columna, fila);
					exitojugada += PN5.moverse(columna, fila);
					exitojugada += PN6.moverse(columna, fila);
					exitojugada += PN7.moverse(columna, fila);
					exitojugada += PN8.moverse(columna, fila);

				}
			}

			if (longitud == 3) {
					switch (jugada[0]) {
					case 'A': {columna = jugada[1];					//Intentamos mover las fichas según en el case que estemos
						fila = jugada[2] - 48;
						if (turno == 0) {
							exitojugada += ab1.moverse(columna, fila);
							exitojugada += ab2.moverse(columna, fila);
						}
						else {
							exitojugada += AN1.moverse(columna, fila);
							exitojugada += AN2.moverse(columna, fila);
						}
						break; }
					case 'C': {columna = jugada[1];
						fila = jugada[2] - 48;
						if (turno == 0) {
							exitojugada += cb1.moverse(columna, fila);
							exitojugada += cb2.moverse(columna, fila);
						}
						else {
							exitojugada += CN1.moverse(columna, fila);
							exitojugada += CN2.moverse(columna, fila);
						}
						break; }
					case 'D': {columna = jugada[1];
						fila = jugada[2] - 48;
						if (turno == 0) {
							exitojugada += db.moverse(columna, fila);
						}
						else {
							exitojugada += DN.moverse(columna, fila);
						}
						break; }
					case 'R': {columna = jugada[1];
						fila = jugada[2] - 48;
						if (turno == 0) {
							exitojugada += rb.moverse(columna, fila);
						}
						else {
							exitojugada += RN.moverse(columna, fila);
						}
						break; }
					case 'T': {columna = jugada[1];
						fila = jugada[2] - 48;
						if (turno == 0) {
							exitojugada += tb1.moverse(columna, fila);
							exitojugada += tb2.moverse(columna, fila);
						}
						else {
							exitojugada += TN1.moverse(columna, fila);
							exitojugada += TN2.moverse(columna, fila);
						}
						break; }
					default: error = 1;
					}
				
			}

			if (longitud == 4) {
				if ((jugada[0] >= 'a') && (jugada[0] <= 'h') && (jugada[1] == 'x')) { //Comprobamos si se ha escrito un peón capturando
					hay_equis = 1;
					columna = jugada[2];
					fila = jugada[3] - 48;
					if (turno == 0) {
						if (pb1.getcolumna() == jugada[0]) pb1.capturar(columna, fila); 
						else if (pb2.getcolumna() == jugada[0]) pb2.capturar(columna, fila);
						else if (pb3.getcolumna() == jugada[0]) pb3.capturar(columna, fila);
						else if (pb4.getcolumna() == jugada[0]) pb4.capturar(columna, fila);
						else if (pb5.getcolumna() == jugada[0]) pb5.capturar(columna, fila);
						else if (pb6.getcolumna() == jugada[0]) pb6.capturar(columna, fila);
						else if (pb7.getcolumna() == jugada[0]) pb7.capturar(columna, fila);
						else if (pb8.getcolumna() == jugada[0]) pb8.capturar(columna, fila);
					}
					else {
						if (PN1.getcolumna() == jugada[0]) PN1.capturar(columna, fila);
						else if (PN2.getcolumna() == jugada[0]) PN2.capturar(columna, fila);
						else if (PN3.getcolumna() == jugada[0]) PN3.capturar(columna, fila);
						else if (PN4.getcolumna() == jugada[0]) PN4.capturar(columna, fila);
						else if (PN5.getcolumna() == jugada[0]) PN5.capturar(columna, fila);
						else if (PN6.getcolumna() == jugada[0]) PN6.capturar(columna, fila);
						else if (PN7.getcolumna() == jugada[0]) PN7.capturar(columna, fila);
						else if (PN8.getcolumna() == jugada[0]) PN8.capturar(columna, fila);
					}
				}
				else if (jugada[1] == 'x') {				//Comprobamos si ha escrito una pieza capturando
					hay_equis = 1;
					switch (jugada[0]) {
					case 'A': {columna = jugada[2];			//Intentamos capturar con cada pieza
						fila = jugada[3] - 48;
						if (turno == 0) {
							exitojugada += ab1.capturar(columna, fila);
							exitojugada += ab2.capturar(columna, fila);
						}
						else {
							exitojugada += AN1.capturar(columna, fila);
							exitojugada += AN2.capturar(columna, fila);
						}
						break; }
					case 'C': {columna = jugada[2];
						fila = jugada[3] - 48;
						if (turno == 0) {
							exitojugada += cb1.moverse(columna, fila);
							exitojugada += cb2.moverse(columna, fila);
						}
						else {
							exitojugada += CN1.moverse(columna, fila);
							exitojugada += CN2.moverse(columna, fila);
						}
						break; }
					case 'D': {columna = jugada[2];
						fila = jugada[3] - 48;
						if (turno == 0) {
							exitojugada += db.capturar(columna, fila);
						}
						else {
							exitojugada += DN.capturar(columna, fila);
						}
						break; }
					case 'R': {columna = jugada[2];
						fila = jugada[3] - 48;
						if (turno == 0) {
							exitojugada += rb.moverse(columna, fila);
						}
						else {
							exitojugada += RN.moverse(columna, fila);
						}
						break; }
					case 'T': {columna = jugada[2];
						fila = jugada[3] - 48;
						if (turno == 0) {
							exitojugada += tb1.capturar(columna, fila);
							exitojugada += tb2.capturar(columna, fila);
						}
						else {
							exitojugada += TN1.capturar(columna, fila);
							exitojugada += TN2.capturar(columna, fila);
						}
						break; }
					default: error = 1;
					}//llave función switch
				}//llave función else if
				else if (((jugada[1] >= 'a') && (jugada[1] <= 'h')) || ((jugada[1] >= '1') && (jugada[1] <= '8'))) {
					//Comprobamos si se refiere el usuario a la ambigüedad de movimiento (dama, rey y alfil excluídos)
					switch (jugada[0]) {
						//En cada case debemos ver cuál es la pieza que está en la columna o fila introducidas

					case 'C': {columna = jugada[2];
						fila = jugada[3] - 48;
						if (turno == 0) {
							if ((cb1.getcolumna() == jugada[1]) || (cb1.getfila() == (jugada[1] - 48))) { exitojugada += cb1.moverse(columna, fila); }
							else if ((cb2.getcolumna() == jugada[1]) || (cb2.getfila() == (jugada[1] - 48))) { exitojugada += cb2.moverse(columna, fila); }
						}
						else {
							if ((CN1.getcolumna() == jugada[1]) || (CN1.getfila() == (jugada[1] - 48))) { exitojugada += CN1.moverse(columna, fila); }
							else if ((CN2.getcolumna() == jugada[1]) || (CN2.getfila() == (jugada[1] - 48))) { exitojugada += CN2.moverse(columna, fila); }
						}
						break; }

					case 'T': {columna = jugada[2];
						fila = jugada[3] - 48;
						if (turno == 0) {
							if ((tb1.getcolumna() == jugada[1]) || (tb1.getfila() == (jugada[1] - 48))) { exitojugada += tb1.moverse(columna, fila); }
							else if ((tb2.getcolumna() == jugada[1]) || (tb2.getfila() == (jugada[1] - 48))) { exitojugada += tb2.moverse(columna, fila); }
						}
						else {
							if ((TN1.getcolumna() == jugada[1]) || (TN1.getfila() == (jugada[1] - 48))) { exitojugada += TN1.moverse(columna, fila); }
							else if ((TN2.getcolumna() == jugada[1]) || (TN2.getfila() == (jugada[1] - 48))) { exitojugada += TN2.moverse(columna, fila); }
						}
						break; }
					default: error = 1;
					}
				}
				else error = 1;
			}//llave if longitud 4

			if (longitud == 5) {                                        //solamente  puede referirse a: enroque largo, la ambigüedad de comer piezas o la promoción del peón comiendo
				if ((jugada[2] == 'x') && (((jugada[1] >= 'a') && (jugada[1] <= 'h')) || ((jugada[1] >= '1') && (jugada[1] <= '8')))) {
					//Comprobamos si se refiere el usuario a la ambigüedad de captura (dama, rey y alfil excluídos)
					hay_equis = 1;
					switch (jugada[0]) {
						//En cada case debemos ver cuál es la pieza que está en la columna o fila introducidas
					case 'C': {columna = jugada[3];
						fila = jugada[4] - 48;
						if (turno == 0) {
							if ((cb1.getcolumna() == jugada[1]) || (cb1.getfila() == (jugada[1] - 48))) exitojugada += cb1.moverse(columna, fila); 
							else if ((cb2.getcolumna() == jugada[1]) || (cb2.getfila() == (jugada[1] - 48))) exitojugada += cb2.moverse(columna, fila);
						}
						else {
							if ((CN1.getcolumna() == jugada[1]) || (CN1.getfila() == (jugada[1] - 48))) { exitojugada += CN1.moverse(columna, fila); }
							else if ((CN2.getcolumna() == jugada[1]) || (CN2.getfila() == (jugada[1] - 48))) { exitojugada += CN2.moverse(columna, fila); }
						}
						break; }

					case 'T': {columna = jugada[3];
						fila = jugada[4] - 48;
						if (turno == 0) {
							if ((tb1.getcolumna() == jugada[1]) || (tb1.getfila() == (jugada[1] - 48))) { exitojugada += tb1.moverse(columna, fila); }
							else if ((tb2.getcolumna() == jugada[1]) || (tb2.getfila() == (jugada[1] - 48))) { exitojugada += tb2.moverse(columna, fila); }
						}
						else {
							if ((TN1.getcolumna() == jugada[1]) || (TN1.getfila() == (jugada[1] - 48))) { exitojugada += TN1.moverse(columna, fila); }
							else if ((TN2.getcolumna() == jugada[1]) || (TN2.getfila() == (jugada[1] - 48))) { exitojugada += TN2.moverse(columna, fila); }
						}
						break; }
					default: error = 1;
					}
				}
				else {
					error = 1;
				}
			}

		} while ((error == 1) && (exitojugada == 0)); //No se sale del bucle hasta que no haya errores de sintaxis y haya habido éxito en la jugada

	} while (1/*mate*/);

	return 0;
}
