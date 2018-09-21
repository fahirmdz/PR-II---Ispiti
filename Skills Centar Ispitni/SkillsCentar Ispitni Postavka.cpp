//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)

enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
char *crt = "\n--------------------------------------------\n";

struct Datum {
int * _dan, *_mjesec, *_godina;
void Unos(int d, int m, int g) {
_dan = new int(d);
_mjesec = new int(m);
_godina = new int(g);
}
void Ispis() { cout << *_dan << "/" << *_mjesec << "/" << *_godina << endl; }
void Dealociraj() { delete _dan; delete _mjesec; delete _godina; }
};

struct Kurs {
enumKursevi _kurs;
Datum _pocetak;
Datum _kraj;
char * _imePredavaca;
bool _aktivan;//SVAKI KURS JE NA POCETKU AKTIVAN

void Dealociraj() {
delete[] _imePredavaca; _imePredavaca = nullptr;	
}
};
struct Polaznik {
int _polaznikID;
char * _imePrezime;
void Unos(int polaznikID, char * imePrezime) {
_polaznikID = polaznikID;
int size = strlen(imePrezime) + 1;
_imePrezime = new char[size];
strcpy_s(_imePrezime, size, imePrezime);
}
void Ispis() { cout << _polaznikID << " " << _imePrezime << endl; }
void Dealociraj() {
delete[] _imePrezime; _imePrezime = nullptr;
}
};
struct Polaganja {
Polaznik _polaznik;
Kurs _kurs;
Datum _datumPolaganja;
float _ostvareniUspjeh;	
};
struct SkillsCentar {
char * _nazivCentra;
Kurs * _kursevi[50];//JEDAN EDUKACIJSKI CENTAR MOZE NUDITI NAJVISE 50 KURSEVA
int _trenutnoKurseva;
Polaganja * _polaganja;
int _trenutnoPolaganja;	
};

void main(){

/*
1. BROJ I TIPOVI PARAMETARA MORAJU BITI IDENTICNI ONIMA U TESTNOM CODE-U (OSIM UKOLIKO IMATE OPRAVDANU POTREBU ZA MODIFIKACIJOM). U SUPROTNOM SE RAD NECE BODOVATI
2. KREIRAJTE .DOC FAJL SA VA�IM BROJEM INDEKSA ( NPR. IB130030.DOC BEZ IMENA I PREZIMENA), TE NA KRAJU ISPITA U NJEGA KOPIRAJTE RJE�ENJA VA�IH ZADATAKA. NE PREDAVATI .TXT ILI .CPP FAJLOVE. TAKO�ER, UKLONITE SVE DIJELOVE CODE-A KOJI NISU IMPLEMENTIRANI
3. TOKOM IZRADE ISPITA NIJE DOZVOLJENO KORI�TENJE HELP-A
4. TOKOM IZRADE ISPITA MOGU BITI POKRENUTA SAMO TRI PROGRAMA: PDF READER (ISPITNI ZADACI), MS VISUAL STUDIO, MS WORD (U KOJI CETE KOPIRATI VA�A RJE�ENJA)
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URA�ENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD	
*/

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
denisHtml.Unos(denis, html, datum5, 61);
//61 predstavlja ostvareni uspjeh/procenat, a uspjesno polozenim se smatra svaki kurs na kome je polaznik ostvari vise od 55%
zaninHtml.Unos(zanin, html, datum6, 93);

SkillsCentar mostar;
mostar.Unos("Skills Center Mostar");
//jedan edukacijski centar moze nuditi vise istih kurseva (npr. MasteringSQL), ali se oni moraju realizovati u razlictim periodima (pocetak-kraj) tj. ne smiju se preklapati
//novi kurs istog tipa (npr. MasteringSQL) se mora realizovati nakon prethodno dodanog npr. ako prethodni kurs MasteringSQL traje 01.03.2016 - 01.04.2016, onda se novi kurs MasteringSQL moze dodati jedino ako pocinje nakon 01.04.2016
if (mostar.DodajKurs(softverski)) {
cout << crt << "KURS USPJESNO REGISTROVAN" << crt;
softverski.Ispis();
cout << crt;	
}
//nije moguce dodati polaganje onog kursa koji nije evidentiran (registrovan, ponudjen) u tom edukacijskom centru
//moguce je polagati samo aktivne kurseve i to najkasnije 5 dana od dana zavrsetka (kraja) posljednje dodanog (aktivnog) kursa iste vrste (npr. MasteringSQL)
//jedan polaznik moze vise puta polagati isti kurs, ali novi procenat mora biti veci od prethodno dodanog (na istom kursu)
if (mostar.DodajPolaganje(denisHtml)) {
cout << crt << "POLAGANJE EVIDENTIRANO" << crt;
denisHtml.Ispis();
}
Datum OD, DO;
int brojPolaganja = 0;
OD.Unos(1, 6, 2016);
DO.Unos(1, 8, 2016);
//PolaganjaByDatum � vraca niz polaganja koja su uspjesno realizovana u periodu OD-DO
Polaganja * polaganjaByDatum = mostar.PolaganjaByDatum(OD, DO, brojPolaganja);
cout << "U periodu od ";
OD.Ispis();
cout << " do ";
DO.Ispis();
cout << " uspjesno je realizovano " << brojPolaganja << " polaganja--->>>";
for (size_t i = 0; i < brojPolaganja; i++)	
polaganjaByDatum[i].Ispis();	

//PretragaRekurzivno - rekurzivna funkcija pronalazi prosjecni uspjeh koji su polaznici tokom godine (npr.2016) ostvarili na odredjenom kursu (npr. MasteringSQL)
cout << "Prosjecan uspjeh na kursu MasteringSQL u 2016 godini je " << PretragaRekurzivno(/*potrebni parametri*/)<<endl;
//Ispis - ispisuje sve informacije o edukacijskom centru. prije ispisa sortirati sve kurseve na osnovu pocetka odrzavanja kursa
mostar.Ispis();

//izvrsiti potrebne dealokacije
system("pause");
}