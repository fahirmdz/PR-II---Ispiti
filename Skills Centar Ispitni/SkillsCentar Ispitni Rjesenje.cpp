#include<iostream>
#include<cstring>

using namespace std;

enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
const char *kurseviChar[] = { "HTML, CSS and JavaScript","Software Engeneering Fundamentals","MasteringSQL","Windows Security" };
char *crt = "\n--------------------------------------------\n";
char *AlocirajNizKaraktera(const char *a) {
	if (a == nullptr)
		return nullptr;
	char *temp = new char[strlen(a) + 1];
	strcpy_s(temp, strlen(a) + 1, a);
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
		if (_dan == nullptr || _mjesec == nullptr || _godina == nullptr)
			cout << "NEMA DATUMA\n";
		else
			cout << *_dan << "/" << *_mjesec << "/" << *_godina << endl;
	}
	void Dealociraj() {if(_dan!=nullptr) delete _dan; 
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
	enumKursevi _kurs;
	Datum _pocetak;
	Datum _kraj;
	char * _imePredavaca;
	bool _aktivan;//SVAKI KURS JE NA POCETKU AKTIVAN
	void Unos(enumKursevi ek,Datum pocetak,Datum kraj,const char *imePredavaca) {
		if (imePredavaca == nullptr)
			return;
		_imePredavaca = AlocirajNizKaraktera(imePredavaca);
		_aktivan = true;
		_pocetak.Unos(*pocetak._dan, *pocetak._mjesec, *pocetak._godina);
		_kraj.Unos(*kraj._dan, *kraj._mjesec, *kraj._godina);
		_kurs = ek;
	}
	void Dealociraj() {
		if(_imePredavaca!=nullptr)
			delete[] _imePredavaca; 
		_imePredavaca = nullptr;
	}
	void Ispis() {
		cout << "--KURS INFO--\n";
		cout << "Naziv kursa: " << kurseviChar[_kurs] << endl;
		cout << "Pocetak kursa: ";
		_pocetak.Ispis();
		cout << "Kraj kursa: ";
		_kraj.Ispis();
		if (_imePredavaca != nullptr)
			cout << "Predavac: " << _imePredavaca << endl;
		if (_aktivan)cout << "Aktivan: DA" << crt;
		else cout << "Aktivan: NE" << crt;
	}
};
struct Polaznik {
	int _polaznikID;
	char * _imePrezime;
	void Unos(int polaznikID, char * imePrezime) {
		if (imePrezime == nullptr)
			return;
		_polaznikID = polaznikID;
		_imePrezime = AlocirajNizKaraktera(imePrezime);
	}
	void Ispis() {
		if (_imePrezime != nullptr)
			cout << "ID: "<<_polaznikID << "\nIme i prezime: " << _imePrezime << endl;
	}
	void Dealociraj() {
		if (_imePrezime != nullptr)
			delete[] _imePrezime;
		_imePrezime = nullptr;
	}
};
struct Polaganja {
	Polaznik _polaznik;
	Kurs _kurs;
	Datum _datumPolaganja;
	float _ostvareniUspjeh;
	
	void Unos(Polaznik p, Kurs k, Datum d, int uspjeh) {
		_polaznik.Unos(p._polaznikID, p._imePrezime);
		_kurs.Unos(k._kurs, k._pocetak, k._kraj, k._imePredavaca);
		_datumPolaganja.Unos(*d._dan, *d._mjesec, *d._godina);
		_ostvareniUspjeh = uspjeh;
	}
	void Ispis() {
		cout << "--INFO POLAGANJE--\n";
		cout << "--> Podaci o polazniku" << crt;
		_polaznik.Ispis();
		_kurs.Ispis();
		cout << "Datum polaganja: ";
		_datumPolaganja.Ispis();
		cout << "Ostvareni uspjeh: " << _ostvareniUspjeh << endl << endl;
	}
	void Dealociraj() {
		_polaznik.Dealociraj();
		_kurs.Dealociraj();
		_datumPolaganja.Dealociraj();
	}
};
struct SkillsCentar {
	char * _nazivCentra;
	Kurs * _kursevi[50];//JEDAN EDUKACIJSKI CENTAR MOZE NUDITI NAJVISE 50 KURSEVA
	int _trenutnoKurseva;
	Polaganja * _polaganja;
	int _trenutnoPolaganja;

	void Dealociraj() {
		if (_nazivCentra != nullptr)
			delete[] _nazivCentra;
		_nazivCentra = nullptr;
		if (_trenutnoKurseva > 0)
			for (int i = 0; i < _trenutnoKurseva; i++)
				if (_kursevi[i] != nullptr) {
					_kursevi[i]->Dealociraj();
					delete _kursevi[i];
					_kursevi[i] = nullptr;
				}
		if (_trenutnoPolaganja > 0 && _polaganja != nullptr) {
			for (int i = 0; i < _trenutnoPolaganja; i++)
				_polaganja[i].Dealociraj();
			delete[] _polaganja;
			_polaganja = nullptr;
		}
	}
	void Unos(const char *nazivCentra) {
		if (nazivCentra == nullptr)
			return;
		_nazivCentra = AlocirajNizKaraktera(nazivCentra);
		for (int i = 0; i < 50; i++)
			_kursevi[i] = nullptr;
		_trenutnoKurseva = 0;
		_polaganja = nullptr;
		_trenutnoPolaganja = 0;
	}
	

	bool DodajKurs(Kurs k) {
		if (_trenutnoKurseva > 0) {
			for (int i = 0; i < 50; i++)
				if (_kursevi[i] != nullptr)
					if (k._kurs == _kursevi[i]->_kurs)
						if (compareDate(k._pocetak, _kursevi[i]->_kraj) <= 0)
							return false;
		}
		int t = -1;
		if (_kursevi[_trenutnoKurseva] != nullptr) {
			int x = 0;
			while (_kursevi[x] != nullptr) {
				if (_kursevi[x + 1] != nullptr)
					t = x + 1;
				x++;
			}
		}
		else
			t = _trenutnoKurseva;
		if (t == -1) {
			cout << "Nema mjesta za dodavanje novih kurseva..\n";
			return false;
		}
		_kursevi[t] = new Kurs;
		_kursevi[t]->Unos(k._kurs, k._pocetak, k._kraj, k._imePredavaca);
		_trenutnoKurseva++;
		return true;
	}
	
	bool DodajPolaganje(Polaganja p) {
		bool postoji = false;
		if (_trenutnoKurseva > 0)
			for (int i = 49; i >= 0; i--)
				if (_kursevi[i] != nullptr)
					if (p._kurs._kurs == _kursevi[i]->_kurs) {
						if (p._datumPolaganja.dani() - _kursevi[i]->_kraj.dani() < 5)
							return false;
						postoji = true;
					}

		if (!postoji) {
			cout << "Kurs koji trazite nemamo u ponudi..\n";
			return false;
		}
		if (_trenutnoPolaganja > 0 && _polaganja != nullptr) {
			for (int i = 0; i < _trenutnoPolaganja; i++) {
				if (strcmp(_polaganja[i]._polaznik._imePrezime, p._polaznik._imePrezime) == 0 && _polaganja[i]._kurs._kurs == p._kurs._kurs)
					if (p._ostvareniUspjeh <= _polaganja[i]._ostvareniUspjeh)
						return false;
			}
			Polaganja *temp = new Polaganja[_trenutnoPolaganja + 1];
			for (int i = 0; i < _trenutnoPolaganja; i++)
				swap(_polaganja[i], temp[i]);
			delete[] _polaganja;
			_polaganja = temp;
			temp = nullptr;
		}
		else if (_trenutnoPolaganja == 0)
			_polaganja = new Polaganja[_trenutnoPolaganja + 1];

		_polaganja[_trenutnoPolaganja++].Unos(p._polaznik, p._kurs, p._datumPolaganja, p._ostvareniUspjeh);
		return true;
	}
	Polaganja *PolaganjaByDatum(Datum OD, Datum DO, int &brp) {
		if (_trenutnoPolaganja <= 0)
			return nullptr;
		Polaganja *niz = new Polaganja[_trenutnoPolaganja];
		for (int i = 0; i < _trenutnoPolaganja; i++) {
			int u1 = compareDate(OD, _polaganja[i]._datumPolaganja), u2 = compareDate(DO, _polaganja[i]._datumPolaganja);
			if (((u1 == -1 && u2 == 0) || (u1 == 0 || u2 == 1) || (u1 == -1 && u2 == 1)) && _polaganja[i]._ostvareniUspjeh>=55)
				niz[brp++].Unos(_polaganja[i]._polaznik, _polaganja[i]._kurs, _polaganja[i]._datumPolaganja, _polaganja[i]._ostvareniUspjeh);
		}
		return niz;
			
	}

	void Ispis() {
		if (_nazivCentra == nullptr)
			return;
		if (_trenutnoKurseva > 0) {
			int iz, n = _trenutnoKurseva;
			do {
				iz = 1;
				for (int i = 0; i < n - 1; i++)
					if (compareDate(_kursevi[i]->_pocetak, _kursevi[i + 1]->_pocetak) == 1) {
						swap(_kursevi[i], _kursevi[i + 1]);
						iz = 0;
					}n -= 1;
			} while (iz == 0 && n > 1);
		}
		cout << crt << "--- Edukacijski centar: " << _nazivCentra << crt;
		cout << "Trenutno kurseva: " << _trenutnoKurseva << endl;
		cout << "--> Lista kurseva: \n\n";
		if (_trenutnoKurseva > 0) {
			for (int i = 0; i < _trenutnoKurseva; i++)
				if (_kursevi[i] != nullptr)
					_kursevi[i]->Ispis();
		}
		else cout << " trenutno nema kurseva..\n";
		cout << crt;
		cout << "Trenutno polaganja: " << _trenutnoPolaganja;
		if (_trenutnoPolaganja > 0 && _polaganja != nullptr)
			for (int i = 0; i < _trenutnoPolaganja; i++)
				_polaganja[i].Ispis();
		else
			cout << "Trenutno nema polaganja..\n";
		cout << crt << crt;
	}
};
double PretragaRekurzivno(SkillsCentar sc,enumKursevi ek,int godina,int i=0, double sum=0,int j=0) {
	if (sc._trenutnoPolaganja <= 0)
		return 0;
	if (i == sc._trenutnoPolaganja)
		return (double)sum/j;
	if (*sc._polaganja[i]._datumPolaganja._godina == godina && sc._polaganja[i]._kurs._kurs == ek)
		return PretragaRekurzivno(sc, ek, godina, i + 1,sum+=sc._polaganja[i]._ostvareniUspjeh,j+1);
	else PretragaRekurzivno(sc, ek, godina, i + 1,sum,j);
}
void main() {

	Datum datum1, datum2, datum3, datum4, datum5, datum6;
	datum1.Unos(26, 11, 2015);
	datum2.Unos(29, 5, 2016);
	datum3.Unos(5, 6, 2016);
	datum4.Unos(15, 8, 2016);
	datum5.Unos(13, 7, 2016);
	datum6.Unos(22, 9, 2016);

	Kurs softverski, html, sql, security;
	softverski.Unos(SoftwareEngeneeringFundamentals, datum1, datum2, "Emina Junuz");
	html.Unos(HtmlCSSJavaScript, datum2, datum3, "Larisa Tipura");
	sql.Unos(MasteringSQL, datum3, datum4, "Jasmin Azemovic");
	security.Unos(WindowsSecurity, datum3, datum4, "Adel Handzic");

	Polaznik denis, zanin, indira;
	denis.Unos(1, "Denis Music");
	zanin.Unos(2, "Zanin Vejzovic");
	indira.Unos(3, "Indira Hamulic");

	Polaganja denisHtml, zaninHtml, indiraSql;
	denisHtml.Unos(denis, softverski, datum5, 61);
	zaninHtml.Unos(zanin, softverski, datum6, 93);

	SkillsCentar mostar;
	mostar.Unos("Skills Center Mostar");

	if (mostar.DodajKurs(softverski)) {
		cout << crt << "KURS USPJESNO REGISTROVAN" << crt;
		softverski.Ispis();
		cout << crt;
	}

	if (mostar.DodajPolaganje(denisHtml)) {
		cout << crt << "POLAGANJE EVIDENTIRANO" << crt;
		denisHtml.Ispis();
	}
	mostar.DodajPolaganje(zaninHtml);
	Datum OD, DO;
	int brojPolaganja = 0;
	OD.Unos(1, 6, 2016);
	DO.Unos(1, 8, 2016);
	
	Polaganja * polaganjaByDatum = mostar.PolaganjaByDatum(OD, DO, brojPolaganja);
	cout << "U periodu od ";
	OD.Ispis();
	cout << " do ";
	DO.Ispis();
	cout << " uspjesno je realizovano " << brojPolaganja << " polaganja--->>>";
	for (size_t i = 0; i < brojPolaganja; i++)
		polaganjaByDatum[i].Ispis();

	
	cout << "Prosjecan uspjeh na kursu MasteringSQL u 2016 godini je " << PretragaRekurzivno(mostar, SoftwareEngeneeringFundamentals, 2016) << endl;

	mostar.Ispis();

	datum1.Dealociraj();
	datum2.Dealociraj();
	datum3.Dealociraj();
	datum4.Dealociraj();
	datum5.Dealociraj();
	datum6.Dealociraj();
	
	softverski.Dealociraj();
	html.Dealociraj();
	sql.Dealociraj();
	security.Dealociraj();

	denisHtml.Dealociraj();
	zaninHtml.Dealociraj();

	mostar.Dealociraj();
	system("pause");
}