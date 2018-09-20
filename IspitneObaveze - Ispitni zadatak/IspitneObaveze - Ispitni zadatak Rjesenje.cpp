#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

enum VrstaObaveze { Seminarski, Parcijalni1, Parcijalni2, Integralni, Prakticni };
const char *vrstaObavezeChar[] = { "Seminarski","Parcijalni","Parcijalni2","Integralni","Prakticni" };
struct Datum {
	int * _dan, *_mjesec, *_godina;
	void Unos(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	void Ispis() { cout << *_dan << "/" << *_mjesec << "/" << *_godina << endl; }
	void Dealociraj() { delete _dan; delete _mjesec; delete _godina; }
	int dani() { return *_dan + *_mjesec * 30 + *_godina * 365; }
};
bool zabranaNapomena(const char *napomena) {
	if (napomena == nullptr)
		return false;
	if (strstr(napomena, "prepisivao") != NULL || strstr(napomena, "izbacen") != NULL)
		return true;
	return false;
}
int compareDate(Datum d1, Datum d2) {
	if (*d1._godina > *d2._godina)return 1;
	else if (*d1._godina < *d2._godina)return -1;
	else if (*d1._mjesec > *d2._mjesec)return 1;
	else if (*d1._mjesec < *d2._mjesec)return -1;
	else if (*d1._dan > *d2._dan)return 1;
	else if (*d1._dan < *d2._dan)return -1;
	else return 0;
}
struct ObavezeNaPredmetu {
	VrstaObaveze * _vrstaObaveze;
	Datum * _datumIzvrsenja;
	char * _napomena;
	int _ocjena; // 5 - 10 
	void Unos(VrstaObaveze vrsta, Datum * datum, int ocjena, char * napomena) {
		if (ocjena == NULL || datum == nullptr)
			return;
		_vrstaObaveze = new VrstaObaveze(vrsta);
		_datumIzvrsenja = new Datum;
		_datumIzvrsenja->Unos(*datum->_dan, *datum->_mjesec, *datum->_godina);
		_ocjena = ocjena;
		if (napomena != nullptr) {
			int size = strlen(napomena) + 1;
			_napomena = new char[size];
			strcpy_s(_napomena, size, napomena);
		}
		else _napomena = nullptr;
	}
	void Ispis() {
		if (_vrstaObaveze == nullptr || _ocjena == NULL || _datumIzvrsenja == nullptr)
			return;

		cout << "Vrsta obaveze: " << *_vrstaObaveze;
		if (_ocjena >= 5 || _ocjena <= 10)
			cout << "\nOcjena: " << _ocjena;
		else
			cout << "\nOcjena: NEPOZNATA";
		if (_napomena != nullptr)
			cout << "\nNapomena: " << _napomena;
		else
			cout << "Napomena: NEMA";
		cout << "\nDatum izvrsenja: ";
		_datumIzvrsenja->Ispis();
		cout << endl;
	}
	void Dealociraj() {
		if (_datumIzvrsenja != nullptr) {
			_datumIzvrsenja->Dealociraj();
			delete _datumIzvrsenja; _datumIzvrsenja = nullptr;
		}
		if (_vrstaObaveze != nullptr)
			delete _vrstaObaveze;
		_vrstaObaveze = nullptr;
		if (_napomena != nullptr)
			delete[] _napomena;
		_napomena = nullptr;
	}
};
struct PolozeniPredmet {
	Datum _datumPolaganja;//datum koji ce se evidentirati kao datum kada je predmet polozen tj. kada je formirana konacna ocjena
	char * _nazivPredmeta;
	ObavezeNaPredmetu * _listaIzvrsenihObaveza[10];
	int _trenutnoIzvrsenihObaveza;
	int _konacnaOcjena; //formira se na osnovu ocjena izvrsenih obaveza
	void Unos(const char *nazivPredmeta){
		if (nazivPredmeta == nullptr)
			return;
		int v = strlen(nazivPredmeta)+1;
		_nazivPredmeta = new char[v];
		strcpy_s(_nazivPredmeta, v, nazivPredmeta);
		for (int i = 0; i < 10; i++)
			_listaIzvrsenihObaveza[i] = nullptr;
		_trenutnoIzvrsenihObaveza = 0;
		_konacnaOcjena = 0;
	}
	void Dealociraj() {
		_datumPolaganja.Dealociraj();
		if (_nazivPredmeta != nullptr)
			delete[] _nazivPredmeta;
		_nazivPredmeta = nullptr;
		if (_trenutnoIzvrsenihObaveza > 0)
			for (int i = 0; i < _trenutnoIzvrsenihObaveza; i++)
				if (_listaIzvrsenihObaveza[i] != nullptr) {
					_listaIzvrsenihObaveza[i]->Dealociraj();
					delete _listaIzvrsenihObaveza[i];
					_listaIzvrsenihObaveza[i] = nullptr;
				}
	}
	void Ispis() {
		cout << "Datum polaganja: ";
		_datumPolaganja.Ispis();
		if (_nazivPredmeta == nullptr)
			return;
		cout << "Naziv predmeta: " << _nazivPredmeta << endl;
		cout << "--LISTA IZVRSENIH OBAVEZA--\n";
		if (_trenutnoIzvrsenihObaveza <= 0)
			cout << "--->PRAZNO<---\n";
		else
			for (int i = 0; i < _trenutnoIzvrsenihObaveza; i++)
				if (_listaIzvrsenihObaveza[i] != nullptr)
					_listaIzvrsenihObaveza[i]->Ispis();
		if (_konacnaOcjena == 0)
			cout << "Konacna ocjena: NEOCENJEN\n";
		else
			cout << "Konacna ocjena: " << _konacnaOcjena << endl;
	}
	bool DodajIzvrsenuObavezu(VrstaObaveze v, Datum d, int ocj, const char *napomena) {
		if (_trenutnoIzvrsenihObaveza == 10)
			return false;
		if (_trenutnoIzvrsenihObaveza > 0) {
			for (int i = 0; i < _trenutnoIzvrsenihObaveza; i++)
				if (_listaIzvrsenihObaveza[i] != nullptr)
					if (compareDate(d, *_listaIzvrsenihObaveza[i]->_datumIzvrsenja) == 0 && v == *_listaIzvrsenihObaveza[i]->_vrstaObaveze && *_listaIzvrsenihObaveza[i]->_vrstaObaveze!=Seminarski)
						return false;
			if (_listaIzvrsenihObaveza[_trenutnoIzvrsenihObaveza - 1] != nullptr)
				if (d.dani() - _listaIzvrsenihObaveza[_trenutnoIzvrsenihObaveza - 1]->_datumIzvrsenja->dani() < 7 && v!=Seminarski)
					return false;
			for (int i = _trenutnoIzvrsenihObaveza - 1; i >= 0; i--)
				if (_listaIzvrsenihObaveza[i] != nullptr)
					if (*_listaIzvrsenihObaveza[i]->_vrstaObaveze == v && v != Seminarski && _listaIzvrsenihObaveza[i]->_ocjena > 5)
						return false;
		}
		if (_listaIzvrsenihObaveza[_trenutnoIzvrsenihObaveza] != nullptr)
			return false;

		_listaIzvrsenihObaveza[_trenutnoIzvrsenihObaveza] = new ObavezeNaPredmetu;
		_listaIzvrsenihObaveza[_trenutnoIzvrsenihObaveza++]->Unos(v, &d, ocj, (char*)napomena);
		return true;
	}                   
	int FormirajKonacnuOcjenu() {
		if (_trenutnoIzvrsenihObaveza <= 0 || _listaIzvrsenihObaveza == nullptr)
			return 5;
		for (int i = 0; i < _trenutnoIzvrsenihObaveza; i++)
			if (_listaIzvrsenihObaveza[i]->_ocjena > 5) {
				if (*_listaIzvrsenihObaveza[i]->_vrstaObaveze == Integralni) {
					if (zabranaNapomena(_listaIzvrsenihObaveza[i]->_napomena)) {
						_konacnaOcjena = 5;
						return 5;

					}
					else {
						_konacnaOcjena = 5;
						return _listaIzvrsenihObaveza[i]->_ocjena;
					}
				}
			}
		ObavezeNaPredmetu *zahtjevaneObaveze[4]{ NULL };
		for (int i = 0; i < _trenutnoIzvrsenihObaveza; i++)
			if (_listaIzvrsenihObaveza[i]->_ocjena > 5) {
				if (*_listaIzvrsenihObaveza[i]->_vrstaObaveze == Parcijalni1)
					zahtjevaneObaveze[0] = _listaIzvrsenihObaveza[i];
				else if (*_listaIzvrsenihObaveza[i]->_vrstaObaveze == Parcijalni2)
					zahtjevaneObaveze[1] = _listaIzvrsenihObaveza[i];
				else if (*_listaIzvrsenihObaveza[i]->_vrstaObaveze == Seminarski)
					if (zahtjevaneObaveze[2] == NULL)
						zahtjevaneObaveze[2] = _listaIzvrsenihObaveza[i];
					else
						zahtjevaneObaveze[3] = _listaIzvrsenihObaveza[i];
			}
		for (int i = 0; i < 4; i++)
			if (zahtjevaneObaveze[i] == NULL) {
				_konacnaOcjena = 5;
				return 5;
			}
			else if (zabranaNapomena(zahtjevaneObaveze[i]->_napomena))
			{
				_konacnaOcjena = 5;
				return 5;
			}

		if ((zahtjevaneObaveze[1]->_datumIzvrsenja->dani() - zahtjevaneObaveze[0]->_datumIzvrsenja->dani()) <= 0) {
			_konacnaOcjena = 5;
			return 5;
		}

		int naj = 0;
		for (int i = 1; i < _trenutnoIzvrsenihObaveza; i++)
			if (_listaIzvrsenihObaveza[i]->_ocjena >= _listaIzvrsenihObaveza[naj]->_ocjena)
				naj = i;
		_datumPolaganja.Unos(*_listaIzvrsenihObaveza[naj]->_datumIzvrsenja->_dan, *_listaIzvrsenihObaveza[naj]->_datumIzvrsenja->_mjesec, *_listaIzvrsenihObaveza[naj]->_datumIzvrsenja->_godina);
		float prosjOcj = 0;
		for (int i = 0; i < 4; i++)
			prosjOcj += zahtjevaneObaveze[i]->_ocjena;
		prosjOcj /= 4;
		_datumPolaganja.Unos(*_listaIzvrsenihObaveza[naj]->_datumIzvrsenja->_dan, *_listaIzvrsenihObaveza[naj]->_datumIzvrsenja->_mjesec, *_listaIzvrsenihObaveza[naj]->_datumIzvrsenja->_godina);
		if (prosjOcj - (int)prosjOcj > 0) {
			_konacnaOcjena = (int)prosjOcj + 1;
			return (int)prosjOcj + 1;
		}
		else {
			_konacnaOcjena = (int)prosjOcj;
			return (int)prosjOcj;
		}
	}
};
int PretragaRekurzivno(PolozeniPredmet pp, int i=0) {
	if (pp._trenutnoIzvrsenihObaveza <= 0 || i==pp._trenutnoIzvrsenihObaveza)
		return 0;
	if (pp._listaIzvrsenihObaveza[i] != nullptr)
		if (pp._listaIzvrsenihObaveza[i]->_ocjena == 5)
			return 1 +PretragaRekurzivno(pp, i + 1);
		else
			return PretragaRekurzivno(pp, i + 1);
	else
		return PretragaRekurzivno(pp, i + 1);
}
void UpisiUBinarniFajl(PolozeniPredmet pp) {
	if (pp._konacnaOcjena == NULL || pp._nazivPredmeta == nullptr)
		return;
	
	int v = strlen(pp._nazivPredmeta) + 7;
	char *nazivFajla = new char[v];
	strcpy_s(nazivFajla, v, pp._nazivPredmeta);
	strcat_s(nazivFajla, v, "_");
	char a[2];
	_itoa_s(pp._konacnaOcjena, a, 10);
	strcat_s(nazivFajla, v, &a[0]);
	strcat_s(nazivFajla, v, ".bin");

    ofstream upis(nazivFajla,ios::binary);
	if (!upis.fail()) {
		upis.write((char*)&pp, sizeof(pp));
		cout << "Informacije o polaganju predmeta uspjesno spasene u fajl " << nazivFajla << "..\n";
		upis.close();
	}
	else
		cout << "Greska pri otvaranju fajla..\n";
}
void UcitajIzBinarnogFajla(PolozeniPredmet &pp, const char *nazivFajla) {
	if (nazivFajla == nullptr)
		return;
	ifstream ispis(nazivFajla,ios::binary| ios::_Nocreate);
	if (!ispis.fail()) {
		ispis.read((char*)&pp, sizeof(pp));
		ispis.close();
		cout << "Sadrzaj iz fajla " << nazivFajla << " uspjesno ucitan..\n";
	}
	else
		cout << "Greska pri otvaranju fajla..\n";
}
void main() {
	
	Datum datumSeminarski1, datumSeminarski2, datumParcijalni1, datumParcijalni2,datumIntegralni;
	datumSeminarski1.Unos(10, 6, 2016);
	datumSeminarski2.Unos(18, 6, 2016);
	datumParcijalni1.Unos(22, 3, 2016);
	datumParcijalni2.Unos(22, 6, 2016);

	//polozeni predmet
	PolozeniPredmet prII, prII_FromFile;
	prII.Unos("Programiranje II");
	if (prII.DodajIzvrsenuObavezu(Parcijalni1, datumParcijalni1, 6, "uslovno polozen"))
		cout << "Parcijalni 1...dodan" << endl;
	if (prII.DodajIzvrsenuObavezu(Parcijalni2, datumParcijalni2, 5, "previse gresaka"))
		cout << "Parcijalni 2...dodan" << endl;
	if (prII.DodajIzvrsenuObavezu(Seminarski, datumSeminarski1, 8, "implementirani svi algoritmi"))
		cout << "Seminarski1...dodan" << endl;
	if (prII.DodajIzvrsenuObavezu(Seminarski, datumSeminarski2, 6, "rad slican kao kod studenta IB150388"))
		cout << "Seminarski2...dodan" << endl;

	cout << "Konacna ocjena iz predmeta PRII je: " << prII.FormirajKonacnuOcjenu() << endl; // nije polozen Parcijalni2 --> ocjena 5

	datumParcijalni2.Unos(22, 7, 2016);
	if (prII.DodajIzvrsenuObavezu(Parcijalni2, datumParcijalni2, 6, ""))
		cout << "Parcijalni 2...dodan" << endl;
	cout << "Konacna ocjena iz predmeta PRII je: " << prII.FormirajKonacnuOcjenu() << endl; // sada je polozen --> ocjena 7

																							//rekurzija
	cout << "Broj negativnih ocjena je: " << PretragaRekurzivno(prII)<< endl;
	//manipulacija fajlovima
	UpisiUBinarniFajl(prII);
	prII.Ispis();
	UcitajIzBinarnogFajla(prII_FromFile, "Programiranje II_7.bin");

	prII_FromFile.Ispis();
	prII.Dealociraj();
	datumSeminarski1.Dealociraj();
	datumSeminarski2.Dealociraj();
	datumParcijalni1.Dealociraj();
	datumParcijalni2.Dealociraj();

	system("PAUSE");
}
