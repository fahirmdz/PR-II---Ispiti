};


int main() {
    DatumVrijeme prije3Dana; prije3Dana.Unos(3, 2, 2018, 10, 15);
    DatumVrijeme danas1; danas1.Unos(6, 2, 2018, 10, 15);
    DatumVrijeme danas2; danas2.Unos(6, 2, 2018, 10, 16);
    DatumVrijeme za10Dana; za10Dana.Unos(16, 2, 2018, 10, 15);

    Dokument ispitPRII, ispitMAT, ispitUIT, ispitUITDrugiRok;
    ispitPRII.Unos(DOC, "ispitPRII.doc", prije3Dana);
    ispitMAT.Unos(DOC, "ispitMAT.doc", danas1);
    ispitUIT.Unos(DOC, "ispitUIT.doc", danas2);
    ispitUITDrugiRok.Unos(PDF, "ispitUITDrugiRok.pdf", za10Dana);

    /*BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREDJUJE PRILIKOM DODAVANJA SADRZAJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU
    STRANICU MOZE STATI BROJ_ZNAKOVA_PO_STRANICI ZNAKOVA UKLJUCUJUCI RAZMAKE I DRUGE VRSTE ZNAKOVA*/
    ispitPRII.DodajSadrzaj("Programiranje ili racunarsko programiranje (engl. programming) jeste vjestina pomocu koje ");
    ispitPRII.DodajSadrzaj("korisnik stvara i izvrsava algoritme koristeci odredjene programske jezike da bi ... ");
    cout << "Broj stranica -> " << ispitPRII._brojStranica << endl;

    ispitPRII.Ispis();//ISPISUJE SVE PODATKE O DOKUMENTU

    ispitMAT.DodajSadrzaj("Matematika se razvila iz potrebe da se obavljaju proracuni u trgovini, vrse mjerenja zemljista i predvidjaju ");
    ispitMAT.DodajSadrzaj("astronomski dogadjaji, i ove tri primjene se mogu dovesti u vezu sa grubom podjelom matematike ");

    Printer hp3200; hp3200.Unos("HP 3200");
    /*PRINTER NECE DOZVOLITI PRINTANJE DOKUMENATA U CIJEM SADRZAJU SE NALAZI NEKA OD ZABRANJENIH RIJECI DEFINISANIH FILTERIMA*/
    if (hp3200.DodajFilter("RE", NIZAK)) //VISOK :)
        cout << "Filter dodan!" << endl;
    if (hp3200.DodajFilter("RAT", VISOK))
        cout << "Filter dodan!" << endl;
    if (hp3200.DodajFilter("UBITI", VISOK))
        cout << "Filter dodan!" << endl;
    if (hp3200.DodajFilter("MRZITI", SREDNJI))
        cout << "Filter dodan!" << endl;
    if (!hp3200.DodajFilter("RE", SREDNJI))/* ONEMOGUCITI PONAVLJANJE FILTERA, BEZ OBZIRA STO SU RAZLICITOG PRIORITETA*/
        cout << "Filter nije dodan!" << endl;

    /*
    DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDECA PRAVILA:
    1. NAZIV DOKUMENTA MOZE SADRZAVATI SAMO SLOVA, A EKSTENZIJA MOZE BITI IDENTICNA ONOJ DEFINISANOJ VRIJEDNOSCU ATRIBUTA vrstaDokumenta
    2. SADRZAJ DOKUMENTA MOZE POSJEDOVATI RIJECI DEFINISANE FILTERIMA, ALI PREMA SLJEDECIM PRAVILIMA:
    - NITI JEDNU RIJEC OZNACENU FILTEROM PRIORITETA VISOK
    - NAJVISE 2 RIJECI OZNACENE FILTEROM PRIORITETA SREDNJI
    - NAJVISE 3 RIJECI OZNACENE FILTEROM PRIORITETA NIZAK
    UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA PRINTAJ DOKUMENT TREBA SACUVATI U NIZ _dokumenti, ALI TAJ DOKUMENT NE TREBA PRINTATI I FUNKCIJA VRACA FALSE.
    UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI SADRZAJ DOKUMENTA KOJI SE PRINTA, A SA CRT LINIJOM ODVAJATI STRANICE DOKUMENTA
    */
    if (hp3200.Printaj(ispitPRII))
        cout << "Printam -> " << ispitPRII._naziv << endl;
    if (hp3200.Printaj(ispitMAT))
        cout << "Printam -> " << ispitMAT._naziv << endl;
    if (hp3200.Printaj(ispitUIT))
        cout << "Printam -> " << ispitUIT._naziv << endl;
    if (hp3200.Printaj(ispitUITDrugiRok))
        cout << "Printam -> " << ispitUITDrugiRok._naziv << endl;

    //PROSJECAN BROJ STRANICA = UKUPAN BROJ STRANICA / BROJ PRINTANIH DOKUMENATA
    //REKURZIVNA FUNKCIJA VRACA PROSJECAN BROJ ISPRINTANIH STRANICA (KOJE SU ZADOVOLJILE POSTAVLJENE FILTERE) U PERIODU OD (npr.prije3Dana) - DO (npr.danas2), UKLJUCUJUCI I TAJ PERIOD
    cout << "Prosjecan broj printanih stranica je -> " << hp3200.GetProsjecanBrojStranicaUPeriodu_Od_Do(/**/) << crt;
    //VRACA SADRZAJ FILTERA KOJI SE NAJCESCE KORISTIO U DOKUMENTIMA
    Filter * f = hp3200.GetNakoristenijiFilter();
    if(f!=nullptr && f->_sadrzaj!=nullptr)
        cout << "Najcesce koristeni sadrzaj filtera je -> " << f->_sadrzaj << crt;
    //PORED VRIJEDNOSTI SVIH OSTALIH ATRIBUTA, ISPISUJE SAMO ONE DOKUMENTE KOJI ZADOVOLJAVAJU SVA PRETHODNO DEFINISANA PRAVILA
    hp3200.Ispis();

    /*NAPISATI LAMBDA FUNKCIJU ZamijeniIPrintaj KOJA U SADRZAJU DOKUMENTA MIJENJA PRVI POSLATI PARAMETAR SA VRIJEDNOSCU DRUGOG PARAMETRA, TE VRACA BROJ ZAMIJENJENIH ZNAKOVA*/
    auto ZamijeniIPrintaj = /**/;
    //RAZMAK MIJENJA ZNAKOM CRTICA U SADRZAJU DOKUMENATA KOJI SU PRINTANI danas1
    int zamijenjeno = ZamijeniIPrintaj(' ','-', danas1);
    cout << "Zamijenjeno -> " << zamijenjeno << " znakova" << endl;
    hp3200.Ispis();    

    prije3Dana.Dealociraj(); danas1.Dealociraj(); danas2.Dealociraj(); za10Dana.Dealociraj();
    ispitMAT.Dealociraj(); ispitPRII.Dealociraj(); ispitUIT.Dealociraj(); ispitUITDrugiRok.Dealociraj();

    hp3200.Dealociraj();
    
    return 0;
}