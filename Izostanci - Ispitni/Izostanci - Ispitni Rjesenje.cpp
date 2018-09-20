#include<iostream>
#include<cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

char * crt = "\n----------------------------------------------------\n";
long int indeks = 150000;
struct Datum {
	int * _dan, *_mjesec, *_godina;
	void Unos(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	void Ispis() {
		if (_dan == nullptr || _mjesec == nullptr || _godina == nullptr)
			return;
		cout << *_dan << "/" << *_mjesec << "/" << *_godina << endl; 
	}
	void Dealociraj() {
		if (_dan != nullptr)
			delete _dan;
		if (_mjesec != nullptr)
			delete _mjesec;
		if (_godina != nullptr)
			delete _godina;
		_dan = _mjesec = _godina = nullptr;
	}
};
int compareDate(Datum d1, Datum d2) {
	if (*d1._godina > *d2._godina)return 1;
	else if (*d1._godina < *d2._godina)return -1;
	else if (*d1._mjesec > *d2._mjesec)return 1;
	else if (*d1._mjesec < *d2._mjesec)return -1;
	else if (*d1._dan > *d2._dan)return 1;
	else if (*d1._dan < *d2._dan)return -1;
	else return 0;
}
struct Izostanak {
	char * _razlogIzostanka;
	Datum _datumIzostanka;
	int _brojSati;
	bool _opravdano;//pravdanje zahtijeva da se evidentira i razlog izostanka	
	void Unos(Datum datumIzostanka, int brojSati) {
		if (datumIzostanka._dan == nullptr || datumIzostanka._mjesec == nullptr || datumIzostanka._godina == nullptr || brojSati<=0)
			return;
		_datumIzostanka.Unos(*datumIzostanka._dan, *datumIzostanka._mjesec, *datumIzostanka._godina);
		_brojSati = brojSati;
		_opravdano = false;
		_razlogIzostanka = nullptr;
	}
	void Dealociraj() {
		if (_razlogIzostanka != nullptr)
			delete[]_razlogIzostanka;
		_razlogIzostanka = nullptr;
	}
	void Ispis() {
		cout << "Datum izostanka: ";
		_datumIzostanka.Ispis();
		cout << "\nBroj sati: " << _brojSati << endl;
		if (_razlogIzostanka != nullptr)
			cout << _razlogIzostanka << "\nOPRAVDANO\n";
		else
			cout << "NEOPRAVDANO\n";
	}
	void Opravdaj(const char * razlogIzostanka) {
		if (razlogIzostanka == nullptr)
			return;
		if (_razlogIzostanka != nullptr)
			delete _razlogIzostanka;
		int vel = strlen(razlogIzostanka) + 1;
		_razlogIzostanka = new char[vel];
		strcpy_s(_razlogIzostanka, vel, razlogIzostanka);
		_opravdano = true;
	}
};
struct Student {
	//format broja indeksa: IB150051
	//osigurati automatsko generisanje broja indeksa pocevsi od IB150001
	char _brojIndeksa[9];
	char * _imePrezime;
	Izostanak * _izostanci;
	int _brojIzostanaka;
	void Unos(char *indeks,const char *imePrezime=nullptr) {
		if (indeks == nullptr || imePrezime == nullptr)
			return;
		if (strlen(indeks) > 9) 
			return;
		
		_imePrezime = new char[strlen(imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
		strcpy_s(_brojIndeksa, 9, indeks);
		_izostanci = nullptr;
		_brojIzostanaka = 0;
	}
	void Dealociraj() {
		if (_imePrezime != nullptr)
			delete[]_imePrezime;
		_imePrezime = nullptr;
		if (_brojIzostanaka > 0)
			for (int i = 0; i < _brojIzostanaka; i++)
				_izostanci[i].Dealociraj();
		if (_izostanci != nullptr)
			delete[] _izostanci;
		_izostanci = nullptr;
	}
	void DodajIzostanak(Izostanak iz) {
		if (_brojIzostanaka > 0 && _izostanci != nullptr) {
			for (int i = 0; i < _brojIzostanaka; i++)
				if (compareDate(_izostanci[i]._datumIzostanka, iz._datumIzostanka)==0) {
					_izostanci[i]._brojSati += iz._brojSati;
					return;
				}
			Izostanak *temp = new Izostanak[_brojIzostanaka + 1];
			for (int i = 0; i < _brojIzostanaka; i++)
				swap(temp[i], _izostanci[i]);
			delete[] _izostanci;
			_izostanci = temp;
			temp = nullptr;
		}
		else if (_brojIzostanaka == 0)
			_izostanci = new Izostanak[_brojIzostanaka + 1];
		_izostanci[_brojIzostanaka++].Unos(iz._datumIzostanka, iz._brojSati);
		if (iz._razlogIzostanka != nullptr)
			_izostanci[_brojIzostanaka-1].Opravdaj(iz._razlogIzostanka);
	}
	void Ispis() {
		cout <<crt<< "--STUDENT INFO--" << crt;
		if (_imePrezime == nullptr || _brojIndeksa[0]!='I')
			return;
		cout << "Ime i prezime: " << _imePrezime << endl;
		cout << "Broj indeksa: " << _brojIndeksa << endl;
		cout << "Broj izostanaka: " << _brojIzostanaka << endl;
		cout << "--LISTA IZOSTANAKA--" << crt;
		if (_brojIzostanaka <= 0 || _izostanci == nullptr)
			cout << "Nema izostanaka..\n";
		else
			for (int i = 0; i < _brojIzostanaka; i++)
				_izostanci[i].Ispis();
		cout << crt;
	}
	Izostanak *BinarnaPretraga(Datum d) {
		if (_brojIzostanaka <= 0 || _izostanci == nullptr)
			return nullptr;
		for (int i = 0; i < _brojIzostanaka-1; i++)
			if (compareDate(_izostanci[i]._datumIzostanka, _izostanci[i + 1]._datumIzostanka) == -1)
				swap(_izostanci[i], _izostanci[i + 1]);
		int prvi = 0, zadnji = _brojIzostanaka, srednji;
		bool nadjen = false;
		while (!nadjen && prvi <= zadnji) {
			srednji = (prvi + zadnji) / 2;
			if (compareDate(d, _izostanci[srednji]._datumIzostanka) == 1)zadnji = srednji - 1;
			if (compareDate(d, _izostanci[srednji]._datumIzostanka) == 0)nadjen = true;
			if (compareDate(d, _izostanci[srednji]._datumIzostanka) == -1)prvi = srednji + 1;
		}
		if (nadjen)
			return &_izostanci[srednji];
		else return nullptr;
	}

	
};
char *GenerisiSljedeciBrojIndeksa() {
	indeks += 1;
	int brc = 0;
	int temp = indeks;
	while (temp != 0) {
		temp /= 10;
		brc++;
	}
	if (brc!=6)
		return nullptr;
	temp = indeks;
	char *indekss = new char[9];
	_itoa_s((int)indeks, indekss, 9, 10);

	char *indeksss = new char[9];
	indeksss[0] = 'I', indeksss[1] = 'B';
	for (int i = 2; i < 8; i++)
		indeksss[i] = indekss[i-2];
	indeksss[8] = '\0';

	return indeksss;
}
Izostanak *PronadjiNajveciNeopravdaniIzostanak(Student st,int i=1,Izostanak *p=nullptr) {
	if (st._brojIzostanaka <= 0 || st._izostanci == nullptr)
		return nullptr;
	if (i == st._brojIzostanaka)
		return p;
	if (i == 1)
		p = &st._izostanci[0];
	if (st._izostanci[i]._brojSati > p->_brojSati)
		return PronadjiNajveciNeopravdaniIzostanak(st, i + 1, &st._izostanci[i]);
	else
		return PronadjiNajveciNeopravdaniIzostanak(st, i + 1, p);
}
//1. PronadjiNajveciNeopravdaniIzostanak - rekurzivna funkcija koja vraca pokazivac na neopravdani izostanak koji ima najveci broj sati
//2. GenerisiSljedeciBrojIndeksa - generise i vraca naredni broj indeksa

void main() {
	Datum jucer, prije5Dana, prije10Dana;
	jucer.Unos(12, 6, 2016);
	prije5Dana.Unos(8, 6, 2016);
	prije10Dana.Unos(3, 6, 2016);

	Student denis;
	denis.Unos(GenerisiSljedeciBrojIndeksa(), "Denis Music");

	Izostanak izostanakJucer, izostanakPrije5Dana, izostanakPrije10Dana;

	izostanakJucer.Unos(jucer, 5);
	denis.DodajIzostanak(izostanakJucer);

	izostanakPrije5Dana.Unos(prije5Dana, 3);
	izostanakPrije5Dana.Opravdaj("Odsutan zbog bolesti - gripa");
	denis.DodajIzostanak(izostanakPrije5Dana);
	izostanakPrije5Dana.Unos(prije5Dana, 2);
	denis.DodajIzostanak(izostanakPrije5Dana);

	izostanakPrije10Dana.Unos(prije10Dana, 1);
	denis.DodajIzostanak(izostanakPrije10Dana);
	izostanakPrije10Dana.Unos(prije10Dana, 1);
	denis.DodajIzostanak(izostanakPrije10Dana);

	denis.Ispis();


	Izostanak * p = denis.BinarnaPretraga(jucer);
	cout << "Binarnom pretragom pronadjen izostanak -> ";
	p->Ispis();
	denis.Ispis();
	Izostanak * p2 = PronadjiNajveciNeopravdaniIzostanak(denis);
	cout << "Rekurzivno pronadjen najveci neopravdani izostanak -> ";
	p2->Ispis();
	cout << endl;
	
	jucer.Dealociraj();
	prije5Dana.Dealociraj();
	prije10Dana.Dealociraj();
	izostanakJucer.Dealociraj();
	izostanakPrije10Dana.Dealociraj();
	izostanakPrije5Dana.Dealociraj();

	denis.Dealociraj();
	system("PAUSE");
	//dealocirati zauzetu memoriju
}