// TRIE.cpp : Defines the entry point for the console application.
//
#include <iostream>

using namespace std;

const int max_dlugosc = 16 + 1; //+1 dla znaku konca ciągu eg. \0

template <class T>
class vector
{
public:
	vector(): dane(nullptr), ilosc(0), pojemnosc(0) {}
	vector(char slowo[]) : dane(nullptr) { //konstruktor incjujacy moje słowo
		zmien_rozmiar(max_dlugosc); //tworzymy z banki tablice 16 plus jeden zeby wiadomo gdzie koniec
		for (int i = 0; i < max_dlugosc; i++) {
			if (slowo[i] == '\0') {
				ilosc = i;
				break;
			}
			else {
				dane[i] = slowo[i];
			}
		}
	}
	vector(vector<T> &kopia) {
		dane = new T[kopia.rozmiar()];
		pojemnosc = kopia.rozmiar();
		for (int i = 0; i < kopia.rozmiar(); i++) {
			dane[i] = kopia[i];
		}
		ilosc = kopia.rozmiar();
	}
	~vector() { czysc_tablice(); } //likwidacja talicy
	void zmien_rozmiar(int nowy_rozmiar) {
		T *nowa_tablica = new T[nowy_rozmiar];
		if (dane != nullptr) {
			for (int i = 0; i < ilosc; i++) {
				nowa_tablica[i] = dane[i];
			}
			delete[] dane;
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
	int rozmiar() const {
		return ilosc;
	}
	void wstaw(int pozycja, T wartosc) { //w dowolne miejsce a nie na koniec dla zachowania kolejności alfabetycznej
		if (ilosc == pojemnosc) {
			if (rozmiar() == 0) {
				zmien_rozmiar(2);
			}
			else {
				zmien_rozmiar(rozmiar() * 2);
			}
		}
		for (int i = rozmiar(); i > pozycja; i--) {
			dane[i] = dane[i - 1]; //do danych i przypisujemy dane wartosci z poprzednich komorek, przesuwajac w prawo
		}

		dane[pozycja] == wartosc;
		ilosc++;
	}
	void wstaw_na_koniec(T wartosc) {
		if (ilosc < pojemnosc) {
			dane[ilosc] = wartosc;
			ilosc++;
		}
		else {
			if (rozmiar() == 0) {
				zmien_rozmiar(2);
			}
			else {
				zmien_rozmiar(rozmiar() * 2);
			}
			dane[ilosc] = wartosc;
			ilosc++;
		}
	}
	void wyswietl() {
		for (int i = 0; i < rozmiar(); i++) {
			cout << dane[i];
		}
	}

	bool czy_pusta() {
		return ilosc == 0;
	}

	T& operator[](int index) {
		return dane[index];
	}

private:
	T *dane;
	int ilosc;
	int pojemnosc;
};

class wezel 
{
public:
	wezel() : litera('\0') {}
	wezel(char litera) : litera(litera) {}
	wezel(char litera, vector<char> tlum) : litera(litera) { tlumaczenie = tlum; }
	~wezel() { czysc_wezel(); }
	char litera;
	vector<wezel*> dziecko;
	vector<char> tlumaczenie;

	wezel* dodaj_dziecko(char znak) {
		int i;
		for (i = 0; i < dziecko.rozmiar(); i++) {
			//znajdz najwyzsza litera dla zachowania kolejnosci alfabetycznej
			if (dziecko[i]->litera > znak) {
				break;
			}
		}
		wezel* w = new wezel(znak);
		dziecko.wstaw(i, w);
		return w;
	}

	wezel* pobierz_dziecko(char znak) {
		for (int i = 0; i < dziecko.rozmiar(); i++) {
			if (dziecko[i]->litera == znak) {
				return dziecko[i];
			}
		}
		return nullptr;
	}
	void czysc_wezel() {
		for (int i = 0; i < dziecko.rozmiar(); i++) { //pozbywamy sie obiektowy na ktore wskazywały pointery
			delete dziecko[i];
		}

		dziecko.czysc_tablice(); //usuwamy te pointery
	}

};

class drzewo
{
public:
	~drzewo() { czysc_drzewo(); }
	void dodaj_tlumaczenie(vector<char>& slowo, vector<char>& tlumaczenie) {
		wezel* w = &root;
		wezel* temp;
		int dlugosc_slowa = slowo.rozmiar();
		for (int i = 0; i < dlugosc_slowa; i++) {
			temp = w->pobierz_dziecko(slowo[i]);
			if (temp != nullptr) {
				w = temp;
			}
			else {
				w = w->dodaj_dziecko(slowo[i]);
			}
		}
		w->tlumaczenie.czysc_tablice();
		for (int i = 0; i < tlumaczenie.rozmiar(); i++) {
			w->tlumaczenie[i] = tlumaczenie[i];
		}
	}
	vector<char> pobierz_tlumaczenie(vector<char>& slowo) {
		wezel* w = &root;
		int dlugosc_slowa = slowo.rozmiar();
		for (int i = 0; i < dlugosc_slowa; i++) {
			w = w->pobierz_dziecko(slowo[i]);
			if (w == nullptr) {
				return vector<char>("-");
			}
		}
		//skonczyl na w->litera;
		if (w->tlumaczenie.czy_pusta()) {
			return vector<char>("-");
		}
		else {
			return w->tlumaczenie;
		}
	}
	void wyswietl_z_prefixem(vector<char>& prefix) {
		wezel* w = &root;
		int wielkosc_prefixu = prefix.rozmiar();
		for (int i; i < wielkosc_prefixu; i++) {
			w = w->pobierz_dziecko(prefix[i]);
			if (w == nullptr) {
				cout << "-n\n";
				return;
			}
		}
		bool znajdz = false;
		dzieci_od_prefixu(w, znajdz);
		if (znajdz == false) {
			cout << "-\n";
		}
	}
	void dzieci_od_prefixu(wezel *w, bool& znajdz) {
		if (!w->tlumaczenie.czy_pusta())
		{
			znajdz = true;
			w->tlumaczenie.wyswietl();
			cout << "\n";
		}

		int ilosc_dzeci = w->dziecko.rozmiar();

		for (int i = 0; i < ilosc_dzeci; i++) {
			dzieci_od_prefixu(w->dziecko[i], znajdz);
		}
	}
	void czysc_drzewo() {
		root.czysc_wezel;
	}
private:	
	wezel root;
};


int main()
{
	return 0;
}

