#include<iostream>
#include<cstdlib>
#include<cstring>
#include<functional>
#include<cctype>

using namespace std;

//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)

char *crt = "\n-------------------------------------------\n";

enum vrstaDokumenta { PDF, DOC, TXT, HTML };
enum prioritet { VISOK, SREDNJI, NIZAK };
const char *vrstaDokumentaChar[] = { "PDF","DOC","TXT","HTML" };
const char *prioritetChar[] = { "VISOK","SREDNJI","NIZAK" };

char *AlocirajNizKaraktera(const char *a) {
	if (a == nullptr)
		return nullptr;
	int v = strlen(a) + 1;
	char *temp = new char[v];
	strcpy_s(temp, v, a);
	return temp;
}
template<class T>    //template funkcija koja prima parametre -> (niz,brojElemenata) i prosiruje niz za jedan element i vraca tako prosiren' niz
T *exArray(T *niz, int brojElemenata) {
	if (brojElemenata < 0)
		return nullptr;
	if (brojElemenata == 0) {
		T *temp = new T[brojElemenata + 1];
		return temp;
	}
	else
	{
		if (niz == nullptr)
			return nullptr;
		T *temp = new T[brojElemenata + 1];
		for (int i = 0; i < brojElemenata; i++)
			swap(niz[i], temp[i]);
		delete[] niz;
		niz = temp;
		temp = nullptr;
		return niz;
	}
}
struct DatumVrijeme {
	int *_dan, *_mjesec, *_godina, *_sati, *_minuti;
	void Unos(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	bool emptyObjects() { return _dan == nullptr || _mjesec == nullptr || _godina == nullptr || _sati == nullptr || _minuti == nullptr; }
	void Dealociraj() {
		if (_dan != nullptr)
			delete _dan;
		_dan = nullptr;
		if (_mjesec != nullptr)	
			delete _mjesec;
		_mjesec = nullptr;
		if(_godina!=nullptr)
			delete _godina; 
		_godina = nullptr;
	if(_sati!=nullptr)	
		delete _sati; 
	_sati = nullptr;
	if(_minuti!=nullptr)	
		delete _minuti; 
	_minuti = nullptr;

	}
	void Ispis() {
		if (!emptyObjects())
			cout << *_dan << "." << *_mjesec << "." << *_godina << " " << *_sati << ":" << *_minuti << endl;
		else
			cout << "PRAZNO\n";
	}
};
int compareDate(DatumVrijeme d1, DatumVrijeme d2) {
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
	else if (*d1._sati > *d2._sati)
		return 1;
	else if (*d1._sati < *d2._sati)
		return -1;
	else if (*d1._minuti > *d2._minuti)
		return 1;
	else if (*d1._minuti < *d2._minuti)
		return -1;
	else return 0;
}
struct Filter {
	char * _sadrzaj;
	prioritet _prioritet;
	void Unos(char * sadrzaj, prioritet prioritet) {
		if (sadrzaj == nullptr)
			return;
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
		_prioritet = prioritet;
	}

	void Dealociraj() {
		if (_sadrzaj != nullptr)
			delete[] _sadrzaj;
		_sadrzaj = nullptr;
	}
	void Ispis() { 
		if (_sadrzaj == nullptr)
			return;
		cout << _sadrzaj << " (" << prioritetChar[_prioritet] << ")" << endl; }

};

struct Dokument {
	vrstaDokumenta _vrsta;
	char * _naziv;
	char * _sadrzaj;
	DatumVrijeme _kreiran;
	int _brojStranica;

	bool emptyObjects() { return _naziv == nullptr || _kreiran.emptyObjects(); }

	void Unos(vrstaDokumenta vrsta, char * naziv, DatumVrijeme kreiran) {
		if (naziv == nullptr || kreiran.emptyObjects())
			return;
		_sadrzaj = nullptr;
		_naziv = AlocirajNizKaraktera(naziv);
		_vrsta = vrsta;
		_kreiran.Unos(*kreiran._dan,*kreiran._mjesec,*kreiran._godina,*kreiran._sati,*kreiran._minuti);
		_brojStranica = 0;//broj stranica se odredjuje prilikom dodavanja svakog novog sadrzaja dokumentu
	}
	void Dealociraj() {
		if (_naziv != nullptr)
			delete[] _naziv;
		_naziv = nullptr;
		if (_sadrzaj != nullptr)
			delete[] _sadrzaj;
		_sadrzaj = nullptr;
		if(!_kreiran.emptyObjects())
			_kreiran.Dealociraj();
	}

	void Ispis() {
		if (emptyObjects())
			return;
		cout << crt <<"Naziv: "<< _naziv << "\nVrsta: " << vrstaDokumentaChar[_vrsta] << " \nKreiran: ";
		_kreiran.Ispis();
		cout << crt;
		if (_sadrzaj != nullptr)
			cout << _sadrzaj << crt << " br.stranica (" << _brojStranica << ")" << crt;
		else
			cout << "--> NEMA SADRZAJA..\nBroj stranica: 0" << crt;
	}


	void DodajSadrzaj(const char *sadrzaj) {
		if (sadrzaj == nullptr)
			return;
		if (_sadrzaj == nullptr)
			_sadrzaj = AlocirajNizKaraktera(sadrzaj);
		else {
			int v = strlen(_sadrzaj) + 1;
			char *temp = new char[v];
			strcpy_s(temp, v, _sadrzaj);
			delete[] _sadrzaj;
			v += strlen(sadrzaj) + 2;
			_sadrzaj = new char[v];
			strcpy_s(_sadrzaj, v, temp);
			strcat_s(_sadrzaj, v, " ");
			strcat_s(_sadrzaj, v, sadrzaj);
		}
		float brs = strlen(_sadrzaj) / (float)30;
		if (brs - (int)brs > 0)
			_brojStranica = (int)brs + 1;
		else
			_brojStranica = (int)brs;
	}
};
struct Printer {
	char * _proizvodjac;
	char * _model;
	Dokument * _dokumenti;
	int _trenutnoDokumenata;
	Filter * _filteri;
	int _trenutnoFiltera;

	bool emptyObjects() { return _proizvodjac == nullptr || _model == nullptr; }

	void Unos(char * proizvodjac, char * model) {
		if (proizvodjac == nullptr || model == nullptr)
			return;
		_proizvodjac = AlocirajNizKaraktera(proizvodjac);
		_model = AlocirajNizKaraktera(model);
		_trenutnoDokumenata = 0;
		_trenutnoFiltera = 0;
		_filteri = nullptr;
		_dokumenti = nullptr;
	}
	void Dealociraj() {
		if (_proizvodjac != nullptr)
			delete[] _proizvodjac;
		_proizvodjac = nullptr;
		if (_model != nullptr)
			delete[] _model; _model = nullptr;
		if (_trenutnoDokumenata > 0 && _dokumenti != nullptr) {
			for (size_t i = 0; i < _trenutnoDokumenata; i++)
				_dokumenti[i].Dealociraj();
			delete[]_dokumenti;
		}
		_dokumenti = nullptr;
		if (_trenutnoFiltera > 0 && _filteri != nullptr) {
			for (size_t i = 0; i < _trenutnoFiltera; i++)
				_filteri[i].Dealociraj();
			delete[]_filteri;
		}
		_filteri = nullptr;
	}

	bool DodajFilter(const char *sadrzaj, prioritet p) {
		if (sadrzaj == nullptr)
			return false;
		if (_trenutnoFiltera > 0 && _filteri != nullptr) {
			for (int i = 0; i < _trenutnoFiltera; i++)
				if (strcmp(_filteri[i]._sadrzaj, sadrzaj) == 0) {
					cout << "Filter sa istim sadrzaj vec postoji..\n";
					return false;
				}
			_filteri = exArray(_filteri, _trenutnoFiltera);
		}
		else if (_trenutnoFiltera == 0)
			_filteri = new Filter[_trenutnoFiltera + 1];
		_filteri[_trenutnoFiltera++].Unos((char*)sadrzaj, p);
		for (int i = 0; i < strlen(_filteri[_trenutnoFiltera - 1]._sadrzaj); i++)
			if (isalpha(_filteri[_trenutnoFiltera - 1]._sadrzaj[i]))
				_filteri[_trenutnoFiltera - 1]._sadrzaj[i] = toupper(+_filteri[_trenutnoFiltera - 1]._sadrzaj[i]);
		return true;
	}
	
	bool usloviPrintanja(Dokument d) {
		if (d.emptyObjects())
			return false;
		int x = 0;
		while (d._naziv[x] != '.') {
			if (!isalpha(d._naziv[x])) {
				cout << "Naziv dokumenta ne sadrzi samo slova!";
				return false;
			}
			
			x++;
		}
		char *ekstenzija = strstr(d._naziv, ".");
		ekstenzija += 1;
		char *temp = new char[strlen(ekstenzija) + 1];
		strcpy_s(temp, strlen(ekstenzija) + 1, ekstenzija);
		for (int i = 0; i < strlen(temp); i++)
			if (isalpha(temp[i]))
				temp[i] = toupper(temp[i]);
		bool uslovEks = false;
		for (int i = 0; i < 4; i++)
			if (strcmp(vrstaDokumentaChar[i], temp) == 0)
				uslovEks = true;
		if (!uslovEks) {
			cout << "Greska: Ekstenzija nije podrzana!";
			return false;
		}
		delete[] temp;
		temp = ekstenzija = nullptr;

		if (_trenutnoFiltera > 0 && _filteri != nullptr) {
			for (int i = 0; i < _trenutnoFiltera; i++) {
				if (_filteri[i]._sadrzaj != nullptr && _filteri[i]._prioritet != NIZAK) {
					int v = strlen(d._sadrzaj) + 1;
					char *temp = new char[v];
					strcpy_s(temp, v, d._sadrzaj);
					for (int j = 0; j < v; j++)
						if (isalpha(temp[j]))
							temp[j] = toupper(temp[j]);
					char *p = strstr(temp, _filteri[i]._sadrzaj);
					if (p != NULL) {
						cout << "Greska: Sadrzaj sadrzi zabranjene rijeci!";
						return false;
					}
				}
			}
		}
		return true;
	}
	void Printaj(Dokument d) {
		if (d.emptyObjects())
			return;
		if (d._sadrzaj == nullptr) {
			cout << "Greska: Sadrzaj prazan! --> Printanje otkazano!\n\n";
			return;
		}
		if (_trenutnoDokumenata > 0 && _dokumenti != nullptr) {
			_dokumenti = exArray(_dokumenti, _trenutnoDokumenata);
		}
		else if (_trenutnoDokumenata == 0)
			_dokumenti = new Dokument[_trenutnoDokumenata + 1];
		_dokumenti[_trenutnoDokumenata++].Unos(d._vrsta, d._naziv, d._kreiran);
		if (d._sadrzaj != nullptr)
			_dokumenti[_trenutnoDokumenata-1].DodajSadrzaj(d._sadrzaj);

		if (usloviPrintanja(d)) {
			cout << endl << endl << "---> Printanje dokumenta " << d._naziv << endl << endl;
			for (int i = 0; i < strlen(d._sadrzaj); i++) {
				cout << d._sadrzaj[i];
				if (i % 30 == 0 && i > 0)
					cout << crt;
				if (i % 10 == 0 && i > 0)
					cout << endl;
			}
			cout << endl << "---> Printanje zavrseno..\n";
		}
		else
			cout << "--> Printanje otkazano!\n\n";
	}
	//PROSJECAN BROJ STRANICA = UKUPAN BROJ STRANICA / BROJ PRINTANIH DOKUMENATA

	int GetProsjecanBrojStranicaPoDatumuIVrsti(DatumVrijeme d1, DatumVrijeme d2, vrstaDokumenta vd) {
		if (d1.emptyObjects() || d2.emptyObjects())
			return 0;
		if (_dokumenti == nullptr || _trenutnoDokumenata == 0)
			return 0;
		int brd = 0, brs = 0;
		for (int i = 0; i < _trenutnoDokumenata; i++) {
			if (!_dokumenti[i].emptyObjects())
				if (_dokumenti[i]._vrsta == vd) {
					int u1 = compareDate(d1, _dokumenti[i]._kreiran), u2 = compareDate(d2, _dokumenti[i]._kreiran);
					if ((u1 == -1 && u2 == 1) || (u1 == 0 && u2 == 1) || (u1 == -1 && u2 == 0))
						if (usloviPrintanja(_dokumenti[i])) {
							brd++;
							brs += _dokumenti[i]._brojStranica;
						}
				}
		}
		float prosjecno = (float)brs / brd;
		if (prosjecno - (int)prosjecno > 0)
			return prosjecno + 1;
		else
			return prosjecno;
	}

	Filter *GetNakoristenijiFilter() {
		if (_trenutnoFiltera <= 0 || _filteri == nullptr || _trenutnoDokumenata <= 0 || _dokumenti == nullptr)
			return nullptr;
		int *brojacKoristenja = new int[_trenutnoFiltera] {0};
		for (int j = 0; j < _trenutnoDokumenata; j++)
			if (!_dokumenti[j].emptyObjects())
				for (int i = 0; i < _trenutnoFiltera; i++) {
					if (_filteri[i]._sadrzaj != nullptr) {
						int v = strlen(_dokumenti[j]._sadrzaj) + 1;
						char *temp = new char[v];
						strcpy_s(temp, v, _dokumenti[j]._sadrzaj);
						for (int j = 0; j < v; j++)
							if (isalpha(temp[j]))
								temp[j] = toupper(temp[j]);
						char *p = strstr(temp, _filteri[i]._sadrzaj);
						if (p != NULL) {
							brojacKoristenja[_filteri[i]._prioritet]++;
							p += 1;
							while (p != NULL) {
								p = strstr(p, _filteri[i]._sadrzaj);
								if (p != NULL) {
									brojacKoristenja[i]++;
									p += 1;
								}
							}
						}
						temp = nullptr;
					}
				}
		int naj = 0;
		for (int i = 1; i < _trenutnoFiltera; i++)
			if (brojacKoristenja[i] > brojacKoristenja[naj])
				naj = i;
		return &_filteri[naj];
	}

	void Ispis() {
		if (emptyObjects())
			return;
		cout << crt << "--- Printer " << _proizvodjac << " - Model: " << _model << crt;
		cout << "Broj filtera: " << _trenutnoFiltera << endl;
		cout << "--Lista filtera--\n\n";
		if (_trenutnoFiltera <= 0 || _filteri == nullptr)
			cout << "--->Lista prazna\n\n";
		else if (_filteri != nullptr && _trenutnoFiltera > 0)
			for (int i = 0; i < _trenutnoFiltera; i++) {
			cout << i + 1 << ". filter --> ";
					_filteri[i].Ispis();
				
			}
		cout << crt << "Broj dokumenata: " << _trenutnoDokumenata << endl;
		cout << "--Lista dokumenata--\n\n";
		if (_trenutnoDokumenata > 0 && _dokumenti != nullptr)
			for (int i = 0; i < _trenutnoDokumenata; i++)
				if (usloviPrintanja(_dokumenti[i]))
					_dokumenti[i].Ispis();
		cout << crt << crt;
	}
};

void main() {
	DatumVrijeme prije3Dana; prije3Dana.Unos(3, 2, 2017, 10, 15);
	DatumVrijeme danas1; danas1.Unos(6, 2, 2017, 10, 15);
	DatumVrijeme danas2; danas2.Unos(6, 2, 2017, 10, 16);
	DatumVrijeme za10Dana; za10Dana.Unos(16, 2, 2017, 10, 15);

	Dokument ispitPRII, ispitMAT, ispitUIT, ispitUITDrugiRok;
	ispitPRII.Unos(DOC, "ispitPRII.doc", prije3Dana);
	ispitMAT.Unos(DOC, "ispitMAT.doc", danas1);
	ispitUIT.Unos(DOC, "ispitUIT.doc", danas2);
	ispitUITDrugiRok.Unos(PDF, "ispitUITDrugiRok.pdf", za10Dana);
	
	ispitPRII.DodajSadrzaj("Programiranje ili racunarsko programiranje (engl. programming) jeste vjestina pomocu koje ");
	ispitPRII.DodajSadrzaj("korisnik stvara i izvrsava algoritme koristeci odredjene programske jezike da bi ... ");
	cout << "Broj stranica -> " << ispitPRII._brojStranica << endl;

	ispitPRII.Ispis();//ISPISUJE SVE PODATKE O DOKUMENTU

	ispitMAT.DodajSadrzaj("Matematika se razvila iz potrebe da se obavljaju proracuni u trgovini, vrse mjerenja zemljista i predvidjaju ");
	ispitMAT.DodajSadrzaj("astronomski dogadjaji, i ove tri primjene se mogu dovesti u vezu sa grubom podjelom matematike na dijelove..");


	Printer hp3200; hp3200.Unos("HP", "3200");
	if (hp3200.DodajFilter("RE", NIZAK)) //VISOK :)
		cout << "Filter dodan!" << endl;
	if (hp3200.DodajFilter("RAT", VISOK))
		cout << "Filter dodan!" << endl;
	if (hp3200.DodajFilter("UBITI", VISOK))
		cout << "Filter dodan!" << endl;
	if (hp3200.DodajFilter("MRZITI", SREDNJI))
		cout << "Filter dodan!" << endl;
	if (hp3200.DodajFilter("RE", SREDNJI))/* ONEMOGUCITI PONAVLJANJE FILTERA, BEZ OBZIRA STO SU RAZLICITOG PRIORITETA*/
		cout << "Filter dodan!" << endl;

	
	hp3200.Printaj(ispitPRII);
	hp3200.Printaj(ispitMAT);
	hp3200.Printaj(ispitUIT);
	hp3200.Printaj(ispitUITDrugiRok);

	cout << "Prosjecan broj printanih stranica je -> " << hp3200.GetProsjecanBrojStranicaPoDatumuIVrsti(prije3Dana, danas2, DOC) << crt;

	Filter * f = hp3200.GetNakoristenijiFilter();
	cout << "Najcesce koristeni sadrzaj filtera je -> " << f->_sadrzaj << crt;

	hp3200.Ispis();


	auto ZamijeniIPrintaj = [&hp3200](char a, char b,DatumVrijeme d) {
		int t = -1;
		if (hp3200._trenutnoDokumenata <= 0 || hp3200._dokumenti == nullptr)
			return 0;
		for (int i = 0; i <= hp3200._trenutnoDokumenata; i++)
			if (!hp3200._dokumenti[i].emptyObjects())
				if (compareDate(hp3200._dokumenti[i]._kreiran, d) == 0)
					t = i;
		if (t == -1)
			return 0;
		int brojZamijenjenih = 0;
		char *p = strstr(hp3200._dokumenti[t]._sadrzaj, &a);
		if (p != NULL) {
			p[0] = b;
			p += 1;
			brojZamijenjenih++;
			while (p != NULL) {
				p = strstr(p, &a);
				if (p != NULL) {
					p[0] = b;
					p += 1;
					brojZamijenjenih++;

				}
			}
		}


		return brojZamijenjenih;
	};
	//RAZMAK MIJENJA ZNAKOM CRTICA U SADRZAJU DOKUMENATA KOJI SU PRINTANI danas1
	int zamijenjeno = ZamijeniIPrintaj(' ', '-', danas1);
	cout << "Zamijenjeno -> " << zamijenjeno << " znakova" << endl;
	hp3200.Ispis();

	prije3Dana.Dealociraj(); danas1.Dealociraj(); danas2.Dealociraj(); za10Dana.Dealociraj();
	ispitMAT.Dealociraj(); ispitPRII.Dealociraj(); ispitUIT.Dealociraj(); ispitUITDrugiRok.Dealociraj();
	system("PAUSE");
}