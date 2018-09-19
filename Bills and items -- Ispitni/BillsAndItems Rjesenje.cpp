#include <iostream>
#include<cstring>
using namespace std;
char * crt = "\n----------------------------------------------------\n";
long int racuni = 0;
struct Datum {
	int * _dan, *_mjesec, *_godina;
	void Unos(int d, int m, int g) {
		if (d == NULL || m == NULL || g == NULL)
			return;
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	void Ispis() {
		if (_dan != nullptr && _mjesec != nullptr && _godina != nullptr)
			cout << *_dan << "/" << *_mjesec << "/" << *_godina << endl;
		else cout << " NEMA DATUMA'n";
	}
	void Dealociraj() {
		if(_dan!=nullptr)
			delete _dan;
		if(_mjesec!=nullptr)
			delete _mjesec; 
		if(_godina!=nullptr)
			delete _godina;
		_dan = _mjesec = _godina = nullptr;
	}
};
struct Artikal {
	char * _naziv;
	float _cijena;
	void Unos(char * naziv, float cijena) {
		if (naziv == nullptr || cijena == NULL)
			return;
		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
		_cijena = cijena;
	}
	void Dealociraj() {
		if (_naziv != nullptr)
			delete[]_naziv;
		_naziv = nullptr;
	}
	void Ispis() { 
		if (_naziv == nullptr || _cijena == NULL)
			return;
		cout << _naziv << " " << _cijena << " KM\n\n";
	}
};
struct Racun {
	
	char _brojRacuna[10];
	Datum _datumKreiranja;
	Artikal * _artikli;
	int * _kolicine;
	int _brojArtikala;
	void Unos(char *brojRacuna, Datum d) {
		if (brojRacuna == nullptr)
			return;
		if (strlen(brojRacuna) > 9)
			return;
		strcpy_s(_brojRacuna, 10, brojRacuna);
		_datumKreiranja.Unos(*d._dan, *d._mjesec, *d._godina);
		_artikli = nullptr;
		_kolicine = nullptr;
		_brojArtikala = 0;
	}
	void Dealociraj() {
		_datumKreiranja.Dealociraj();
		if (_artikli != nullptr && _brojArtikala > 0) {
			for (int i = 0; i < _brojArtikala; i++)
				_artikli[i].Dealociraj();
			delete[] _artikli;
		}
		_artikli = nullptr;
		if (_kolicine != nullptr)
			delete[] _kolicine;
		_kolicine = nullptr;
	}
	void DodajArtikal(Artikal a, int kolicina) {
		if (kolicina <= 0 || a._naziv == nullptr)
			return;
		
		if (_brojArtikala > 0) {
			for (int i = 0; i < _brojArtikala; i++)
				if (_artikli[i]._naziv != nullptr) {
					if (strcmp(_artikli[i]._naziv, a._naziv) == 0) {
						if (_kolicine[i] != NULL)
							_kolicine[i] += kolicina;
						return;
					}
				}
			Artikal *temp = new Artikal[_brojArtikala+1];
			for (int i = 0; i < _brojArtikala; i++)
				swap(_artikli[i], temp[i]);
			delete[] _artikli;
			_artikli = temp;
			temp = nullptr;
			int *tempp = new int[_brojArtikala + 1];
			for (int i = 0; i < _brojArtikala; i++)
				swap(_kolicine[i], tempp[i]);
			delete[] _kolicine;
			_kolicine = tempp;
			tempp = nullptr;
		}
		else {
			_artikli = new Artikal[_brojArtikala + 1];
			_kolicine = new int[_brojArtikala + 1];
		}

		_artikli[_brojArtikala].Unos(a._naziv, a._cijena);
		_kolicine[_brojArtikala++] = kolicina;
	}
	void Ispis() {
		if (_brojRacuna == nullptr || _artikli == nullptr || _kolicine == nullptr || _brojArtikala <= 0)
		return;
		cout << crt << "--Racun broj: " << _brojRacuna << endl;
		cout << "Datum: ";
		_datumKreiranja.Ispis();
		cout << crt << "--LISTA ARTIKALA--\n";
		double ukupno = 0;
		for (int i = 0; i < _brojArtikala; i++) {
			cout << i + 1 << ". --> " << "Naziv artikla: " << _artikli[i]._naziv << " - "<<_artikli[i]._cijena<<"\n    Kolicina: " << _kolicine[i] << endl << "          Cijena: " << _kolicine[i] * _artikli[i]._cijena << " KM\n";
			ukupno += _kolicine[i] * _artikli[i]._cijena;
		}
		cout << crt << "Ukupno za platiti: " << ukupno <<crt<< "**HVALA NA POSJETI**" << crt;
	}
	Artikal *BinarnaPretraga(const char *nazivArtikla) {
		if (_brojArtikala <= 0 || _artikli == nullptr)
			return nullptr;
		bool nadjen = false;
		int prvi = 0, zadnji = _brojArtikala, srednji;
		for (int i = 0; i < _brojArtikala-1; i++)
			if (_artikli[i]._naziv != nullptr && _artikli[i + 1]._naziv != nullptr)
				if (strlen(_artikli[i]._naziv) > strlen(_artikli[i + 1]._naziv))
					swap(_artikli[i], _artikli[i + 1]);
		while (!nadjen && prvi <= zadnji) {
			srednji = (prvi + zadnji) / 2;
			if (strlen(nazivArtikla) < strlen(_artikli[srednji]._naziv))zadnji = srednji - 1;
			if (strcmp(nazivArtikla, _artikli[srednji]._naziv) == 0)nadjen = true;
			if (strlen(nazivArtikla) > strlen(_artikli[srednji]._naziv))prvi = srednji+1;
		}
		if (nadjen == true)
			return &_artikli[srednji];
		else return nullptr;
	}
	
};

char *GenerisiSljedeciBrojRacuna() {
	racuni += 1;
	int brc = 0;
	int temp = racuni;
	while (temp != 0) {
		temp /= 10;
		brc++;
	}
	temp = racuni;
	char *racun = new char[10];
	for (int i = 8; i >= 9 - brc; i--) {
		if (temp % 10 == 0)
			racun[i] = '0';
		else
			_itoa_s(temp % 10, &racun[i],10, 10);
		
			temp /= 10;
			if (temp == 0)
				break;
	}
	if (brc <= 8)
		for (int i = 0; i < 9 - brc; i++)
			racun[i] = '0';
	racun[9] = '\0';
	
	return racun;
}
Artikal *PronadjiNajskupljiArtikal(Racun r, int i = 1, Artikal *ar = nullptr) {
	if (r._brojArtikala <= 0 || r._artikli == nullptr)
		return nullptr;
	if (i == 1)
		ar = &r._artikli[0];
	if (i == r._brojArtikala)
		return ar;
	if (r._artikli[i]._cijena > ar->_cijena)
		return PronadjiNajskupljiArtikal(r, i + 1, &r._artikli[i]);
	else
		return PronadjiNajskupljiArtikal(r, i + 1, ar);

}
void main() {
	Datum danas; danas.Unos(13, 6, 2016);
	Artikal cigarete, cokolada, sok;
	cigarete.Unos("Cigarete", 2.23);
	cokolada.Unos("Cokolada", 1.23);
	sok.Unos("Cappy", 2.10);
	Racun racun;
	racun.Unos(GenerisiSljedeciBrojRacuna(), danas);
	racun.DodajArtikal(cokolada, 5);
	racun.DodajArtikal(sok, 10);
	racun.DodajArtikal(cigarete, 2);
	racun.DodajArtikal(cigarete, 5);
	racun.Ispis();
	
	Artikal * p1 = racun.BinarnaPretraga("Cokolada");
	cout << "Binarnom pretragom pronadjen artikal -> ";
	p1->Ispis();

	racun.Ispis();
	Artikal * p2 = PronadjiNajskupljiArtikal(racun);
	cout << "Rekurzivno pronadjen najskuplji artikal -> ";
	p2->Ispis();

	racun.Dealociraj();
	danas.Dealociraj();
	cigarete.Dealociraj();
	cokolada.Dealociraj();
	sok.Dealociraj();
	system("PAUSE");
	
}