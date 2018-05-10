#include"szkola.h"
#include<string>
#include<iostream>

klasa::klasa(const std::string& s): symbol(s), liczba_osob(0), czyWychowawca(0){};

std::string klasa::zwrocSymbol() const
{return symbol;}

unsigned short klasa::zwrocLiczbe() const
{return liczba_osob;}

const unsigned short klasa::zwrocMax() const
{return max;}

bool klasa::zwrocWychowawstwo() const
{return czyWychowawca;}

void klasa::dodajUcznia()
{
	//wyjatki
	if (liczba_osob>=max) /*wyjatek 1*/ return;
	liczba_osob++;
	return;
}

void klasa::usunUcznia()
{
	//wyjatki
	if (liczba_osob<=0) /*wyjatek 1*/ return;
	liczba_osob--;
	return;
}

void klasa::dodajWychowawce()
{
	//wyjatki
	if (czyWychowawca==1) /*wyjatek 1*/ return;
	czyWychowawca=1;
	return;
}

void klasa::usunWychowawce()
{
	//wyjatki
	if (czyWychowawca==0) /*wyjatek 1*/ return;
	czyWychowawca=0;
	return;
}

std::ostream &operator<<(std::ostream & out, const klasa& k)
{
	out<<"Klasa "<<k.symbol<<" sklada sie z "<<k.liczba_osob<<" uczniow\n";
	return out;
}

osoba::osoba(const std::string& i, const std::string& n): imie(i), nazwisko(n) {};

std::string osoba::zwrocImie() const
{return imie;}

std::string osoba::zwrocNazwisko() const
{return	nazwisko;}

std::ostream& operator<<(std::ostream& out, const osoba& o)
{
	out<<o.imie<<" "<<o.nazwisko<<"\n";
	return out;
}

pracownik::pracownik(const std::string& i, const std::string& n, const std::string& s, const double& p): osoba(i,n), stanowisko(s), pensja(p) {};

pracownik::pracownik(const osoba& o, const std::string& s, const double& p): osoba(o), stanowisko(s), pensja(p) {};

std::string pracownik::zwrocStanowisko() const
{return stanowisko;}
	
double pracownik::zwrocPensje() const
{return pensja;}
	
void pracownik::zmienPensje(const double& np)
{
	//wyjatki
	if (np<0) /*wyjatek 1*/ ;
	pensja=np;
	return;
}

std::ostream& operator<<(std::ostream& out, const pracownik& pr)
{
	out<<pr.imie<<" "<<pr.nazwisko<<" Stanowisko: " <<pr.stanowisko<<" Pensja: "<<pr.pensja<<" zl\n";
	return out;
}

nauczyciel::nauczyciel(const std::string& i, const std::string& n, const std::string& prze, const double& p): pracownik(i,n, "Nauczyciel", p), przedmiot(prze) {};

nauczyciel::nauczyciel(const osoba& o, const std::string& prze, const double& p): pracownik(o, "Nauczyciel", p), przedmiot(prze) {};

nauczyciel::nauczyciel(const pracownik& pr, const std::string& prze): pracownik(pr), przedmiot(prze)
{
	stanowisko="Nauczyciel";
}

std::string nauczyciel::zwrocPrzedmiot() const
{return przedmiot;}
	
std::ostream& operator<<(std::ostream& out, const nauczyciel& n)
{
	out<<n.imie<<" "<<n.nazwisko<<" Nauczyciel przedmiotu "<<n.przedmiot<<" Pensja: "<<n.pensja<<" zl\n";
	return out;
}

wychowawca::wychowawca(const std::string& i, const std::string& n, const std::string& prze, const double& p, klasa* k): nauczyciel(i, n, prze, p), k(k) {};

wychowawca::wychowawca(const osoba& o, const std::string& prze, const double& p, klasa* k): nauczyciel(o, prze, p), k(k) {};

wychowawca::wychowawca(const pracownik& pr, const std::string& prze, klasa* k): nauczyciel(pr, prze), k(k) {};

wychowawca::wychowawca(const nauczyciel& n, klasa* k): nauczyciel(n), k(k) {};

std::string wychowawca::zwrocKlase() const
{return k->zwrocSymbol();}

klasa* wychowawca::wskazKlase() const
{return k;}

void wychowawca::zmienKlase(klasa* kl)
{
	//wyjatki
	if(k==kl) /*wyjatek 1*/ return;
	if (k==nullptr)
	{
		if (kl) 
		{
			/*wyjatek 2*/
			kl->dodajWychowawce();
			k=kl;
			return;
		}
	}
	else
	{
		if(kl)
		{
			/*wyjatek 3*/
			kl->dodajWychowawce();
			k->usunWychowawce();
			k=kl;
			return;
			
		}
		else
		{
			k->usunWychowawce();
			k=kl;
			return;
		}
	}
}

std::ostream& operator<<(std::ostream& out, const wychowawca& w)
{
	out<<w.imie<<" "<<w.nazwisko<<" Nauczyciel przedmiotu "<<w.przedmiot;
	if(w.wskazKlase()) out<<", Wychowaca klasy "<<w.zwrocKlase();
	else out<<", obecnie brak wychowawstwa";
	out<<", Pensja: "<<w.pensja<<" zl\n";
	return out;
}

uczen::uczen(const std::string& i, const std::string& n, klasa* k): osoba(i,n), k(k) {};
uczen::uczen(const osoba& o, klasa* k): osoba(o), k(k) {};

std::string uczen::zwrocKlase() const
{ return k->zwrocSymbol();}

klasa* uczen::wskazKlase() const
{ return k;}

void uczen::zmienKlase(klasa* kl)
{
	//wyjatki
	if(k==kl) /*wyjatek 1*/ return;
	if(k==nullptr)
	{
		if(kl)
		{
			/*wyjatek 2*/
			kl->dodajUcznia();
			k=kl;
			return;
		}
	}
	else
	{
		if(kl)
		{
			/*wyjatek 3*/
			kl->dodajUcznia();
			k->usunUcznia();
			k=kl;
			return;
		}
		else
		{
			k->usunUcznia();
			k=kl;
			return;
		}
	}
}

std::ostream& operator<<(std::ostream& out, const uczen& u)
{
	out<<u.imie<<" "<<u.nazwisko;
	if(u.wskazKlase()) out<<" Uczeszcza do klasy "<<u.zwrocKlase()<<"\n";
	else out<<" Obecnie nie uczeszcza do zadnej klasy\n";
	return out;
}
