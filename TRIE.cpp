// TRIE.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

const int max_dlugosc = 16 + 1; //+1 dla znaku konca ciągu eg. \0

class vector
{
public:
	vector(): dane(nullptr), ilosc(0), pojemnosc(0) {}
	vector(char slowo[]) : dane(nullptr) { //konstruktor incjujacy moje słowo
		zmien_rozmiar(max_dlugosc); //tworzymy z banki tablice 16 plus jeden zeby wiadomo gdzie koniec
		for (int i; i <= max_dlugosc; i++) {
			if (slowo[i] == '\0') {
				ilosc = i;
				break;
			}
			else {
				dane[i] = slowo[i];
			}
		}
	}
	vector(vector &kopia) {
		dane = new int[kopia.rozmiar()];
		pojemnosc = kopia.rozmiar();
		for (int i = 0; i < kopia.rozmiar(); i++) {
			dane[i] = kopia[i];
		}
		ilosc = kopia.rozmiar();
	}
	~vector() { czysc_tablice(); } //likwidacja talicy
	void zmien_rozmiar(int nowy_rozmiar) {
		int *nowa_tablica = new int[nowy_rozmiar];
		if (dane != nullptr) {
			for (int i = 0; i <= ilosc; i++) {
				nowa_tablica[i] = dane[i];
				delete[] dane;
			}
		}
		else {
			dane = nowa_tablica;
			pojemnosc = nowy_rozmiar;
		}
	}
	void czysc_tablice() {
		if (dane != nullptr) {
			delete[] dane;
			dane = nullptr;
			pojemnosc = 0;
			ilosc = 0;
		}
	}
	int rozmiar() {
		return ilosc;
	}
	void wstaw(int pozycja, int wartosc) { //w dowolne miejsce a nie na koniec dla zachowania kolejności alfabetycznej
		if (ilosc == pojemnosc) {
			if (rozmiar() == 0) {
				zmien_rozmiar(2);
			}
			else {
				zmien_rozmiar(rozmiar() * 2);
			}
		}
		for (int i = 0; i <= rozmiar(); i++) {
			if (i < pozycja) {
				dane[i] = dane[i];
			}
			if (i == pozycja) {
				dane[i] == wartosc;
			}
			if (i > pozycja) {
				dane[i] = dane[i - 1];
			}
		}
		ilosc++;
	}
	void wyswietl() {
		for (int i = 0; i < rozmiar(); i++) {
			cout << dane[i];
		}
	}
	bool czy_pusta() {
		if (ilosc == 0) {
			return true;
		}
	}

private:
	int *dane;
	int ilosc;
	int pojemnosc;
};

class wezel 
{
public:
	wezel() : litera('\0') {}
	wezel(char litera): litera(litera) {}
	wezel(char litera, vector char tlum, )
	char litera;

};


int main()
{
	return 0;
}

