#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
using namespace std;

enum Opstina { Opstina1, Opstina2, Opstina3, Opstina4 };
char * OpstineChar[] = { "Opstina1", "Opstina2", "Opstina3", "Opstina4" };
enum Kandidati { Kandidat1, Kandidat2, Kandidat3, Kandidat4 };
char * KandidatiChar[] = { "Kandidat1", "Kandidat2", "Kandidat3", "Kandidat4" };

struct Datum {
	int _dan, _mjesec, _godina;
	void Unos(int d, int m, int g) {_dan = d; _mjesec = m; _godina = g;}
	void Ispis() {cout << _dan << "/" << _mjesec << "/" << _godina << endl;}
};
int compareDate(Datum d1, Datum d2) {
	if (d1._godina > d2._godina)return 1;
	else if (d1._godina < d2._godina)return -1;
	else if (d1._mjesec > d2._mjesec)return 1;
	else if (d1._mjesec < d2._mjesec)return -1;
	else if (d1._dan > d2._dan)return 1;
	else if (d1._dan < d2._dan)return -1;
	else return 0;
}
struct Osoba {
	Datum _datumRodjenja;
	char * _imePrezime;
	char _JMBG[14];
	Opstina _Prebivaliste;
	void unos(Datum d, char * ip, char jmbg[], Opstina p) {
		if (ip == nullptr)
			return;
		_datumRodjenja.Unos(d._dan, d._mjesec, d._godina);
		_imePrezime = new char[strlen(ip) + 1];
		strcpy_s(_imePrezime,strlen(ip)+1, ip);
		strcpy_s(_JMBG,14, jmbg);
		_Prebivaliste = p;
	}
	void Dealociraj() {
		if (_imePrezime != nullptr)
			delete[] _imePrezime;
		_imePrezime = nullptr;
	}
	void Info() {
		if (_imePrezime == nullptr)
			return;
		_datumRodjenja.Ispis();
		cout << _imePrezime << " " << _JMBG << " " <<
			OpstineChar[_Prebivaliste] << endl;
	}
};
struct Glas {
	Osoba * _glasac;
	Kandidati * _glasZa;
	void Unos(Osoba o, Kandidati k) {
		_glasac = new Osoba();
		_glasac->unos(o._datumRodjenja, o._imePrezime, o._JMBG, o._Prebivaliste);
		_glasZa = new Kandidati(k);
	}
	void Ispis() {
		cout << "--INFO O GLASACU--\n";
		_glasac->Info();
		cout << "Glasao/la za: "<<KandidatiChar[*_glasZa] << endl;
	}
	void Dealociraj() {
		if (_glasac != nullptr) {
			_glasac->Dealociraj();
			delete _glasac;
			_glasac = nullptr;
		}
		if (_glasZa != nullptr) {
			delete _glasZa;
			_glasZa = nullptr;
		}
	}

};
struct Izbori2016 {
	Opstina * _glasackoMjesto;
	Glas * _glasovi[1000];
	int _doSadaGlasalo;
	void Unos(Opstina o) {
		_glasackoMjesto = new Opstina(o);
		for (int i = 0; i < 1000; i++)
			_glasovi[i] = nullptr;
		_doSadaGlasalo = 0;
	}
	void Dealociraj() {
		if (_glasackoMjesto != nullptr)
			delete _glasackoMjesto;
		_glasackoMjesto = nullptr;
		if(_doSadaGlasalo>0)
			for(int i=0;i<1000;i++)
				if (_glasovi[i] != nullptr) {
					_glasovi[i]->Dealociraj();
					delete _glasovi[i];
					_glasovi[i] = nullptr;
				}
	}
	bool DodajGlas(Glas g) {
		if(_doSadaGlasalo == 1000) {
			cout << "Nema vise mjesta za dodavanje novih glasova! Zao nam je..\n";
			return false;
		}
		int t = -1;
		if (_glasovi[_doSadaGlasalo] != nullptr) {
			int x = 0;
			if (_glasovi[x] != nullptr) {
				while (_glasovi[x] != nullptr && x < 1000) {
					if (_glasovi[x + 1] == nullptr)
						t = x + 1;
					x++;
				}
			}
			else t = x;
			if (t == -1) {
				cout << "Nema vise mjesta za dodavanje novih glasova! Zao nam je..\n";
				return false;
			}
		}
		else
			t = _doSadaGlasalo;
		int x = 0;
		while (_glasovi[x] != nullptr)
			if (strcmp(_glasovi[x++]->_glasac->_imePrezime, g._glasac->_imePrezime) == 0) {
				cout << "Ne moze se glasati vise od jednog puta!\n";
				return false;
			}
		if (g._glasac->_Prebivaliste != *_glasackoMjesto) {
			cout << "Nije moguce glasati u drugoj opstini!\n";
			return false;
		}
		if (g._glasac->_datumRodjenja._godina > 2000) {
			cout << "Morate imati 18 godina da biste glasali!\n";
			return false;
		}
		else if (g._glasac->_datumRodjenja._godina == 2000 && g._glasac->_datumRodjenja._mjesec > 9) {
			cout << "Morate imati 18 godina da biste glasali!\n";
			return false;
		}
		_glasovi[t] = new Glas;
		_glasovi[t]->Unos(*g._glasac, *g._glasZa);
		_doSadaGlasalo++;
		return true;
	}
	Opstina *Ispis() {
		int brojGlasova[4]{ 0 };
		for (int i = 0; i < 1000; i++)
			if (_glasovi[i] != nullptr)
				brojGlasova[*_glasovi[i]->_glasZa]++;
		struct rezultati {
			int brojGlasova;
			Kandidati k;
		};
		rezultati k[4];
		k[0] = { brojGlasova[0],Kandidat1 };
		k[1] = { brojGlasova[1],Kandidat2 };
		k[2] = { brojGlasova[2],Kandidat3 };
		k[3] = { brojGlasova[3],Kandidat4 };
		for (int i = 0; i < 3; i++)
			if (k[i].brojGlasova > k[i + 1].brojGlasova)
				swap(k[i], k[i + 1]);
		int naj = 0;
		for (int i = 1; i < 4; i++)
			if (k[i].brojGlasova > k[naj].brojGlasova)
				naj = i;
		cout << "--REZULTATI IZBORA--\n";
		for (int i = 0; i < 4; i++) {
			
			cout << "--> " << KandidatiChar[i] << ": " << ((double)k[i].brojGlasova / 1000) * 100 << " %\n";
		}
		cout << endl;
		return _glasackoMjesto;
	}
	int BrojGlasacaPoRodjenju(Datum OD, Datum DO) {
		int brojac = 0;
		for (int i = 0; i < 1000; i++) 
			if (_glasovi[i] != nullptr) {
				int u1 = compareDate(DO, _glasovi[i]->_glasac->_datumRodjenja), u2 = compareDate(OD, _glasovi[i]->_glasac->_datumRodjenja);
				if ((u1 == -1 && u2 == 1) || (u1 == 0 && u2 == 1) || (u1 == 1 && u2 == 0))
					brojac++;
			}
		return brojac;
	}
	
};
int PretragaRekurzivno(Izbori2016 iz,Kandidati k,int i=0) {
	if (iz._doSadaGlasalo <= 0)
		return 0;
	if (i == iz._doSadaGlasalo)
		return 0;
	if (iz._glasovi[i] != nullptr)
		if (*iz._glasovi[i]->_glasZa == k)
			return 1 + PretragaRekurzivno(iz, k, i + 1);
		else
			return PretragaRekurzivno(iz, k, i + 1);
	return PretragaRekurzivno(iz, k, i + 1);
}
void UpisiUBinarniFajl(Izbori2016 iz) {
	int v = strlen(OpstineChar[*iz._glasackoMjesto]) + 5;
	char *nazivFajla = new char[v];
	strcpy_s(nazivFajla, v, OpstineChar[*iz._glasackoMjesto]);
	strcat_s(nazivFajla, v, ".bin");
	ofstream upis(nazivFajla, ios::binary);
	if (!upis.fail()) {
		upis.write((char*)&iz, sizeof(iz));
		cout << "Uspjesno spaseni rezultati izbora u fajl " << nazivFajla << endl;
		upis.close();
	}
	else
		cout << "Greska pri otvaranju fajla..\n";
	delete[] nazivFajla; nazivFajla = nullptr;
}
void UcitajIzBinarnogFajla(Izbori2016 &iz,const char *nazivFajla) {
	if (nazivFajla == nullptr)
		return;
	int v = strlen(nazivFajla) + 5;
	char *novi = new char[v];
	strcpy_s(novi, v, nazivFajla);
	strcat_s(novi, v, ".bin");
	ifstream ispis(novi, ios::binary | ios::_Nocreate);
	if (!ispis.fail()) {
		ispis.read((char*)&iz, sizeof(iz));
		cout << "Uspjesno ucitani podaci iz fajla " << novi << endl;
		ispis.close();
	}
	else
		cout << "Greska pri otvaranju fajla..\n";
	delete[] novi; novi = nullptr;

}


void main() {


	Datum datumGlasac1, datumGlasac2, datumGlasac3, datumGlasac4, datumIzbora;
	datumIzbora.Unos(14, 7, 2016);
	datumGlasac1.Unos(18, 5, 1990);
	datumGlasac2.Unos(5, 3, 1982);
	datumGlasac3.Unos(12, 8, 1958);
	datumGlasac4.Unos(22, 6, 2000);

	Osoba a, b, c, d, e;
	a.unos(datumGlasac1, "Denis Music", "1111111111111", Opstina1);
	b.unos(datumGlasac2, "Jasmin Azemovic", "1111111111112", Opstina1);
	c.unos(datumGlasac3, "Indira Hamulic", "1111111111113", Opstina1);
	d.unos(datumGlasac4, "Adel Handzic", "1111111111114", Opstina2);
	e.unos(datumGlasac4, "Zanin Vejzovic", "1111111111115", Opstina1);


	Glas g1, g2, g3, g4, g5;
	g1.Unos(a, Kandidat1);
	g2.Unos(b, Kandidat1);
	g3.Unos(c, Kandidat2);
	g4.Unos(d, Kandidat1);
	g5.Unos(e, Kandidat2);

	Izbori2016 izbori, izbori_FromFile;
	izbori.Unos(Opstina1);

	izbori.DodajGlas(g1);
	izbori.DodajGlas(g2);
	izbori.DodajGlas(g3);
	izbori.DodajGlas(g4);
	izbori.DodajGlas(g5);

	izbori.Ispis();
	Datum OD, DO;
	OD.Unos(17, 7, 1998);
	DO.Unos(17, 7, 1986);
	cout << "Glasaca u starost od 18 - 30 godina->" << izbori.BrojGlasacaPoRodjenju(OD, DO) << endl;

	cout << "Broj glasova za Kandidat1->" << PretragaRekurzivno(izbori,Kandidat1) << endl;
	UpisiUBinarniFajl(izbori);
	UcitajIzBinarnogFajla(izbori_FromFile, "Opstina1");
	izbori_FromFile.Ispis();

	a.Dealociraj();
	b.Dealociraj();
	c.Dealociraj();
	d.Dealociraj();
	e.Dealociraj();

	g1.Dealociraj();
	g2.Dealociraj();
	g3.Dealociraj();
	g4.Dealociraj();
	g5.Dealociraj();

	izbori.Dealociraj();
	system("PAUSE");
}