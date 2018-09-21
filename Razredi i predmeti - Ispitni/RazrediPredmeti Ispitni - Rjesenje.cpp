#include<iostream>
#include<cstring>

using namespace std;
#pragma warning(disable:4996)

enum enumPredmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski };
enum enumRazredi { I, II, III, IV };
const char *predmetiChar[] = { "Matematika","Historija","Geografija","Hemija","Biologija","Engleski" };
const char *razrediChar[] = { "I","II","III","IV" };
char *crt = "\n--------------------------------------------\n";
char *AlocirajNizKaraktera(const char *a) {
	if (a == nullptr)
		return nullptr;
	int v = strlen(a) + 1;
	char *temp = new char[v];
	strcpy_s(temp, v, a);
	return temp;
}
struct Datum {
	int * _dan, *_mjesec, *_godina;
	void Unos(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	void Ispis() { 
		if (!prazniObjekti())
			cout << *_dan << "/" << *_mjesec << "/" << *_godina << endl;
		else
			cout << "NEMA DATUMA\n";
	}
	bool prazniObjekti() { return _dan == nullptr || _mjesec == nullptr || _godina == nullptr; }
	void Dealociraj() { 
		if(_dan!=nullptr)delete _dan;
	if(_mjesec!=nullptr)delete _mjesec;
	if(_godina!=nullptr)delete _godina; 
	_godina = _dan = _mjesec = nullptr;
	}
	int dani() { return *_dan + *_mjesec * 30 + *_godina * 365; }
};
int compareDate(Datum d1, Datum d2) {
	if (*d1._godina > *d2._godina)
		return 1;
	else if (*d1._godina < *d2._godina)
		return -1;
	else if (*d1._mjesec > *d2._mjesec)
		return 1;
	else if (*d1._mjesec < *d2._mjesec)
		return -1;
	else if (*d1._dan > *d2._dan)
		return 1;
	else if (*d1._dan < *d2._dan)
		return -1;
	else return 0;
}
struct Kurs {
	enumPredmeti _predmet;
	enumRazredi _razredi;
	Datum * _pocetak;
	Datum * _kraj;
	char * _imePredavaca;
	void Unos(enumPredmeti predmet, enumRazredi razred, Datum pocetak, Datum kraj, char * imePredavaca) {
		if (imePredavaca == nullptr || pocetak.prazniObjekti() || kraj.prazniObjekti())
			return;
		_predmet = predmet;
		_razredi = razred;
		_pocetak = new Datum;
		_kraj = new Datum;
		_pocetak->Unos(*pocetak._dan, *pocetak._mjesec, *pocetak._godina);
		_kraj->Unos(*kraj._dan, *kraj._mjesec, *kraj._godina);
		_imePredavaca = AlocirajNizKaraktera(imePredavaca);
	}
	bool prazniObjekti() { return _pocetak == nullptr || _kraj == nullptr || _imePredavaca == nullptr; }
	void Ispis() {
		if (prazniObjekti())
			return;
		cout << "-- Kurs info --\n";
		cout << "Predmet: " << predmetiChar[_predmet] << endl;
		cout << "Razred: " << razrediChar[_razredi] << endl;
		cout << "Pocetak: ";
		_pocetak->Ispis();
		cout << "Kraj: ";
		_kraj->Ispis();
		cout << "Ime predavaca: " << _imePredavaca << endl << endl;
	}
	void Dealociraj() {
		if (_imePredavaca != nullptr)
			delete[] _imePredavaca;
		_imePredavaca = nullptr;
		if (_pocetak != nullptr) {
			_pocetak->Dealociraj();
			delete _pocetak;
			_pocetak = nullptr;
		}
		if (_kraj != nullptr) {
			_kraj->Dealociraj();
			delete _kraj;
			_kraj = nullptr;
		}
	}
};
struct Polaznik {
	Datum * _datumRodjenja;
	char * _imePrezime;

	bool prazniObjekti() {
		return _datumRodjenja == nullptr || _imePrezime == nullptr;
	}
	void Unos(Datum datumRodjenja, char * imePrezime=nullptr) {
		if (imePrezime == nullptr || datumRodjenja.prazniObjekti())
			return;
		_imePrezime = AlocirajNizKaraktera(imePrezime);
		_datumRodjenja = new Datum;
		_datumRodjenja->Unos(*datumRodjenja._dan, *datumRodjenja._mjesec, *datumRodjenja._godina);
	}
	void Dealociraj() {
		if (_imePrezime != nullptr)
			delete[] _imePrezime;
		_imePrezime = nullptr;
		if (_datumRodjenja != nullptr) {
			_datumRodjenja->Dealociraj();
			delete _datumRodjenja;
			_datumRodjenja = nullptr;
		}
	}

	void Ispis() {
		if (prazniObjekti())
			return;
		cout << "--Polaznik info--\n";
		cout << "Ime i prezime: " << _imePrezime << endl;
		cout << "Datum rodjenja: ";
		_datumRodjenja->Ispis();
		cout << endl;
	}
};
struct Polaganja {
	Polaznik * _polaznik;
	Kurs * _kurs;
	Datum * _datumPolaganja;
	int _ocjena; //ocjene su u rasponu od 1 do 5	

	void Unos(Polaznik p, Kurs k, Datum d, int uspjeh) {
		if (p.prazniObjekti() || k.prazniObjekti() || d.prazniObjekti())
			return;
		_polaznik = new Polaznik;
		_polaznik->Unos(*p._datumRodjenja, p._imePrezime);
		_kurs = new Kurs;
		_kurs->Unos(k._predmet, k._razredi, *k._pocetak, *k._kraj, k._imePredavaca);
		_datumPolaganja = new Datum;
		_datumPolaganja->Unos(*d._dan, *d._mjesec, *d._godina);
		_ocjena = uspjeh;
	}
	bool prazniObjekti() { return _polaznik == nullptr || _kurs == nullptr || _datumPolaganja == nullptr; }
	void Dealociraj() {
		if (_polaznik != nullptr) {
			_polaznik->Dealociraj();
			delete _polaznik;
			_polaznik = nullptr;
		}
		if (_kurs != nullptr) {
			_kurs->Dealociraj();
			delete _kurs;
		}
		_kurs = nullptr;
		if (_datumPolaganja != nullptr) {
			_datumPolaganja->Dealociraj();
			delete _datumPolaganja;
			_datumPolaganja = nullptr;
		}
	}
	void Ispis() {
		if (prazniObjekti())
			return;
		_polaznik->Ispis();
		_kurs->Ispis();
		cout << "Datum polaganja: ";
		_datumPolaganja->Ispis();
		cout << "Ocjena: " << _ocjena << endl;
	}
};

struct EdukacijskiCentar {
	char * _nazivCentra;
	Kurs * _kursevi[50];
	int _trenutnoKurseva;
	Polaganja * _polaganja;
	int _trenutnoPolaganja;

	void Unos(const char *nazivCentra) {
		if (nazivCentra == nullptr)
			return;
		_nazivCentra = AlocirajNizKaraktera(nazivCentra);
		for (int i = 0; i < 50; i++)
			_kursevi[i] = nullptr;
		_trenutnoKurseva = _trenutnoPolaganja = 0;
		_polaganja = nullptr;
	}
	bool prazniObjekti() { return _nazivCentra == nullptr || _trenutnoKurseva <= 0 || _trenutnoPolaganja <= 0 || _polaganja == nullptr; }

	void Dealociraj() {
		if (_nazivCentra != nullptr)
			delete[] _nazivCentra;
		_nazivCentra = nullptr;
		if (_trenutnoKurseva > 0) {
			for (int i = 0; i < 50; i++)
				if (_kursevi[i] != nullptr) {
					_kursevi[i]->Dealociraj();
					delete _kursevi[i];
					_kursevi[i] = nullptr;
				}
		}
		if (_trenutnoPolaganja > 0 && _polaganja != nullptr) {
			for (int i = 0; i < _trenutnoPolaganja; i++)
				_polaganja[i].Dealociraj();
			delete[] _polaganja;
			_polaganja = nullptr;
		}
	}
	bool DodajKurs(Kurs k) {
		if (k.prazniObjekti())
			return false;
		if (_trenutnoKurseva > 0) {
			for (int i = 0; i < 50; i++)
				if (_kursevi[i] != nullptr)
					if (_kursevi[i]->_predmet == k._predmet)
						if (compareDate(*k._pocetak, *_kursevi[i]->_kraj) != 1)
							return false;
		}
		int t = -1;
		if (_kursevi[0] != nullptr) {
			int x = 0;
			while (_kursevi[x] != nullptr && x < 50 && t == -1) {
				if (_kursevi[x + 1] != nullptr)
					t = x + 1;
				x++;
			}
		}
		else
			t = 0;
		if (t == -1) {
			cout << "Nema mjesta za nove kurseve..\n";
			return false;
		}
		_kursevi[t] = new Kurs;
		_kursevi[t]->Unos(k._predmet, k._razredi, *k._pocetak, *k._kraj, k._imePredavaca);
		_trenutnoKurseva++;
		return true;
	}

	bool DodajPolaganje(Polaganja p) {
		if (p.prazniObjekti() || _trenutnoKurseva<=0)
			return false;
		bool postoji = false;
		for (int i = 49; i >= 0; i--) 
			if(_kursevi[i]!=nullptr && !_kursevi[i]->prazniObjekti())
				if (_kursevi[i]->_predmet == p._kurs->_predmet) {
					if (p._datumPolaganja->dani() - _kursevi[i]->_kraj->dani() > 15)
						return false;
					else
						postoji = true;
				}
		if (!postoji) {
			cout << "Trazeni kurs nije u ponudi..\n";
			return false;
		}
		if (_trenutnoPolaganja > 0 && _polaganja != nullptr) {
			for (int i = _trenutnoPolaganja - 1; i >= 0; i--)
				if (!_polaganja[i].prazniObjekti())
					if (strcmp(_polaganja[i]._polaznik->_imePrezime, p._polaznik->_imePrezime) == 0)
						if (_polaganja[i]._ocjena >= p._ocjena)
							return false;
						else
							break;

			Polaganja *temp = new Polaganja[_trenutnoPolaganja + 1];
			for (int i = 0; i < _trenutnoPolaganja; i++)
				swap(_polaganja[i], temp[i]);
			delete[] _polaganja;
			_polaganja = temp;
			temp = nullptr;
		}
		else if (_trenutnoPolaganja == 0)
			_polaganja = new Polaganja[_trenutnoPolaganja + 1];
		_polaganja[_trenutnoPolaganja++].Unos(*p._polaznik, *p._kurs, *p._datumPolaganja, p._ocjena);
		return true;
	}

	Polaganja *PolaganjaByDatumIRazred(Datum OD, Datum DO, enumRazredi er, int &brp) {
		if (OD.prazniObjekti() || DO.prazniObjekti() || _trenutnoPolaganja<=0)
			return nullptr;

		Polaganja *niz = new Polaganja[_trenutnoPolaganja + 1];
		for (int i = 0; i < _trenutnoPolaganja; i++)
		{
			if (!_polaganja[i].prazniObjekti()) {
				int u1 = compareDate(OD, *_polaganja[i]._datumPolaganja), u2 = compareDate(DO, *_polaganja[i]._datumPolaganja);
				if (((u1 == -1 && u2 == 0) || (u1 == 0 && u2 == 1) || (u1 == -1 && u2 == 1)) && er == _polaganja[i]._kurs->_razredi && _polaganja[i]._ocjena>=55)
					niz[brp++].Unos(*_polaganja[i]._polaznik, *_polaganja[i]._kurs, *_polaganja[i]._datumPolaganja, _polaganja[i]._ocjena);
			}
		}
		return niz;
	}
	void Ispis() {
		if (_nazivCentra == nullptr)
			return;
		cout << "------Edukacijski centar '" << _nazivCentra << "'--------" << crt;
		cout << "Broj kurseva: " << _trenutnoKurseva << endl;
		cout << "--Lista kurseva--\n-----------------\n";
		if (_trenutnoKurseva > 0) {
			for (int i = 0; i < 50; i++)
				if (_kursevi[i] != nullptr && !_kursevi[i]->prazniObjekti())
					_kursevi[i]->Ispis();
		}
		else
			cout << "  --> Nema evidentiranih kurseva...\n\n";
		cout << "Broj polaganja: " << _trenutnoPolaganja << endl;
		if (_trenutnoPolaganja > 0) {
			for (int i = 0; i < _trenutnoPolaganja; i++)
				if (!_polaganja[i].prazniObjekti())
					_polaganja[i].Ispis();
		}
		else
			cout << "--> Nema evidentiranih polaganja..\n\n";
		cout << crt;
	}
};

	float PretragaRekurzivno(EdukacijskiCentar ec, enumPredmeti ep, int godina, int i = 0, float suma = 0, int j = 0) {
		if (ec.prazniObjekti())
			return 0;
		if (i == ec._trenutnoPolaganja)
			return (float)suma / j;
		if (!ec._polaganja[i].prazniObjekti()) {
			if (ec._polaganja[i]._kurs->_predmet == ep && *ec._polaganja[i]._datumPolaganja->_godina == godina)
				return PretragaRekurzivno(ec, ep, godina, i + 1, suma += ec._polaganja[i]._ocjena, j + 1);
			else
				return PretragaRekurzivno(ec, ep, godina, i + 1, suma, j);
		}
		else return PretragaRekurzivno(ec, ep, godina, i + 1, suma, j);
	}
void main() {

	Datum datum1, datum2, datum3, datum4, datum5, datum6;
	datum1.Unos(26, 11, 2015);
	datum2.Unos(29, 5, 2016);
	datum3.Unos(5, 6, 2016);
	datum4.Unos(15, 8, 2016);
	datum5.Unos(13, 7, 2016);
	datum6.Unos(22, 9, 2016);

	Kurs matematika, hemija, biologija, engleski;
	matematika.Unos(Matematika, II, datum1, datum2, "Nina Bijedic");
	hemija.Unos(Hemija, III, datum2, datum3, "Murat Praso");
	biologija.Unos(Biologija, IV, datum3, datum4, "Jasmin Azemovic");
	engleski.Unos(Engleski, II, datum3, datum4, "Iris Memic");

	Datum rodjenje1, rodjenje2 ;
	rodjenje2.Unos(22, 8, 1997);
	rodjenje1.Unos(22, 8, 1982);
	Polaznik denis, zanin, indira;
	denis.Unos(rodjenje1, "Denis Music");
	zanin.Unos(rodjenje2, "Zanin Vejzovic");


	Polaganja denisMatematika, zaninHemija, denisBiologija;
	denisMatematika.Unos(denis, matematika, datum3, 55);//3 predstavlja ostvareni uspjeh/ocjenu, a uspjesno polozenim se smatra svaki kurs na kome je polaznik ostvario ocjenu vecu od 1
	zaninHemija.Unos(zanin, hemija, datum6, 93);
	denisBiologija.Unos(denis, biologija, datum6,66);
	EdukacijskiCentar mostar;
	mostar.Unos("ECM - Edukacijski Center Mostar");
	

	if (mostar.DodajKurs(matematika)) {
		cout << crt << "KURS USPJESNO REGISTROVAN" << crt;
		matematika.Ispis();
		cout << crt;
	}

	
	if (mostar.DodajPolaganje(denisMatematika)) {
		cout << crt << "POLAGANJE EVIDENTIRANO" << crt;
		denisMatematika.Ispis();
	}
	Datum OD, DO;
	int brojPolaganja = 0;
	OD.Unos(1, 6, 2016);
	DO.Unos(1, 8, 2016);
	Polaganja * polaganjaByDatumiRazred = mostar.PolaganjaByDatumIRazred(OD, DO, II, brojPolaganja);
	cout << "U periodu od ";
	OD.Ispis();
	cout << " do ";
	DO.Ispis();
	cout << " uspjesno je polozeno " << brojPolaganja << " predmeta --->>> ";
	for (size_t i = 0; i < brojPolaganja; i++)
		polaganjaByDatumiRazred[i].Ispis();

	cout << "Prosjecan uspjeh na kursu iz predmeta Matematika u 2016 godini je " << PretragaRekurzivno(mostar,Matematika,2016) << endl;
	
	mostar.Ispis();

	datum1.Dealociraj();
	datum2.Dealociraj();
	datum3.Dealociraj();
	datum4.Dealociraj();
	datum5.Dealociraj();
	datum6.Dealociraj();

	matematika.Dealociraj();
	hemija.Dealociraj();
	biologija.Dealociraj();
	engleski.Dealociraj();

	rodjenje1.Dealociraj();
	rodjenje2.Dealociraj();

	denisMatematika.Dealociraj();
	zaninHemija.Dealociraj();
	denisBiologija.Dealociraj();

	mostar.Dealociraj();
	system("pause");
}