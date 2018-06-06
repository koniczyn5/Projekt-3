#include"szkola.h"
#include<string>
#include<iostream>
#include<sstream>


template <class T>
tydzien<T>::tydzien()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tab[i][j] = T();
		}
	}
}


template <class T>
T* tydzien<T>::wskazObiekt(int a, int b)
{
	return &tab[a][b];
}

template<>
std::stringstream tydzien<bool>::save()
{
	std::stringstream result;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			result << tab[i][j];
			result<<" ";
		}
	}
	return result;
}

template<>
std::stringstream tydzien<zajecia>::save()
{
	std::stringstream result, pom;
	std::string pom1;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			pom=tab[i][j].save();
			pom>>pom1;
			result<<pom1;
			result << " ";
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& out, const tydzien<zajecia>& tydz)
{
	for (int i = 0; i < 5; i++)
	{
		switch(i)
		{
		case 0: out << "Poniedzialek: \n"; break;
		case 1: out << "Wtorek: \n"; break;
		case 2: out << "Sroda: \n"; break;
		case 3: out << "Czwartek: \n"; break;
		case 4: out << "Piatek: \n"; break;
		}
		for (int j = 0; j < 9; j++)
		{
			switch (j)
			{
			case 0: out << " 7:10- 7:55 "; break;
			case 1: out << " 8:00- 8:45 "; break;
			case 2: out << " 8:55- 9:40 "; break;
			case 3: out << " 9:50-10:35 "; break;
			case 4: out << "10:55-11:40 "; break;
			case 5: out << "11:50-12:35 "; break;
			case 6: out << "12:45-13:30 "; break;
			case 7: out << "13:40-14:25 "; break;
			case 8: out << "14:35-15:20 "; break;
			}
			out << tydz.tab[i][j]<<"\n";
		}
		out << "\n";
	}
	return out;
}

sala::sala(const std::string& s) : symbol(s){}

std::string sala::zwrocSymbol() const
{return symbol;}

bool sala::zwrocDostepnosc(int a, int b) const
{
	return dostepnosc.tab[a][b];
}

void sala::zmienDostepnosc(int a, int b, bool data)
{
	if (data)
	{
		if (!dostepnosc.tab[a][b])
		{
			dostepnosc.tab[a][b] = data;
			return;
		}
		else
		{
			throw std::string("Sala nie jest dostepna w tym terminie");
		}
	}
	else
	{
		if (dostepnosc.tab[a][b])
		{
			dostepnosc.tab[a][b] = data;
			return;
		}
		else
		{
			throw std::string("Sala juz jest dostepna w tym terminie");
		}
	}
}

std::stringstream sala::save()
{
	std::stringstream result, pom;
	std::string pom1;
	result <<"s "<< symbol<<" ";
	pom=dostepnosc.save();
	getline(pom, pom1);
	result<<pom1;
	result <<"\n";
	return result;
}

std::ostream& operator<<(std::ostream& out, const sala& s)
{
	int pom=0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++) if(s.dostepnosc.tab[i][j] == 0) pom++;
	}
	out << "Sala " << s.symbol << " jest dostepna w " << pom << " terminach.\n";
	return out;
}


klasa::klasa(const std::string& s): symbol(s), liczba_osob(0), czyWychowawca(0), czyPlan(0){};

std::string klasa::zwrocSymbol() const
{return symbol;}

unsigned short klasa::zwrocLiczbe() const
{return liczba_osob;}

const unsigned short klasa::zwrocMax() const
{return max;}

bool klasa::zwrocWychowawstwo() const
{return czyWychowawca;}

bool klasa::zwrocPlan() const
{return czyPlan;}

void klasa::dodajUcznia()
{
	//wyjatki
	if (liczba_osob>=max) throw std::string("Klasa jest juz pelna, wiec nie mozna dodac ucznia");
	liczba_osob++;
	return;
}

void klasa::usunUcznia()
{
	//wyjatki
	if (liczba_osob<=0) throw std::string("Klasa jest juz pusta, wiec nie mozna usunac ucznia");
	liczba_osob--;
	return;
}

void klasa::dodajWychowawce()
{
	//wyjatki
	if (czyWychowawca==1) throw std::string("Klasa juz ma wychowawce, wiec nie mozna przypisac nowego");
	czyWychowawca=1;
	return;
}

void klasa::usunWychowawce()
{
	//wyjatki
	if (czyWychowawca==0) throw std::string("Klasa nie ma wychowawcy, wiec nie mozna go usunac");
	czyWychowawca=0;
	return;
}

void klasa::dodajPlan()
{
	//wyjatki
	if (czyPlan == 1) throw std::string("Klasa juz ma plan, wiec nie mozna przypisac nowego");
	czyPlan = 1;
	return;
}

void klasa::usunPlan()
{
	//wyjatki
	if (czyPlan == 0) throw std::string("Klasa nie ma planu, wiec nie mozna go usunac");
	czyPlan = 0;
	return;
}

std::stringstream klasa::save()
{
	std::stringstream result;
	result<<"k "<< symbol << "\n";
	return result;
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

std::stringstream osoba::save()
{
	std::stringstream result;
	result << "o " << imie << " " << nazwisko << "\n";
	return result;
}

std::ostream& operator<<(std::ostream& out, const osoba& o)
{
	out<<o.imie<<" "<<o.nazwisko<<"\n";
	return out;
}

pracownik::pracownik(const std::string& i, const std::string& n, const std::string& s, const double& p): osoba(i,n), stanowisko(s), pensja(p) {};

pracownik::pracownik(const osoba& o, const std::string& s, const double& p): osoba(o), stanowisko(s), pensja(p) {};

std::string pracownik::zwrocStanowisko() const
{return stanowisko;}

void pracownik::zmienStanowisko(const std::string& s)
{
	stanowisko=s;
}
	
double pracownik::zwrocPensje() const
{return pensja;}
	
void pracownik::zmienPensje(const double& np)
{
	//wyjatki
	if (np<0) throw std::string("Pensja nie moze byc ujemna");
	pensja=np;
	return;
}

std::stringstream pracownik::save()
{
	std::stringstream result;
	result << "p " << imie << " " << nazwisko << " " << stanowisko << " " << pensja << "\n";
	return result;
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

std::stringstream nauczyciel::save()
{
	std::stringstream result;
	result << "n " << imie << " " << nazwisko << " " << przedmiot << " " << pensja << "\n";
	return result;
}
	
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

klasa* wychowawca::wskazKlase()
{return k;}

void wychowawca::zmienKlase(klasa* kl)
{
	//wyjatki
	if (k == kl)
	{ throw std::string("Ten nauczyciel jest wychowawca tej klasy"); return;}
	if (k == nullptr)
	{
		if (kl)
		{
			if (kl->zwrocWychowawstwo() == 1) throw std::string("Ta klasa juz ma wychowawce");
			kl->dodajWychowawce();
			k = kl;
			return;
		}
	}
	else
	{
		if (kl)
		{
			if (kl->zwrocWychowawstwo() == 1) throw std::string("Ta klasa juz ma wychowawce");
			kl->dodajWychowawce();
			k->usunWychowawce();
			k = kl;
			return;

		}
		else
		{
			k->usunWychowawce();
			k = kl;
			return;
		}
	}
}

std::stringstream wychowawca::save()
{
	std::stringstream result;
	result << "w " << imie << " " << nazwisko << " " << przedmiot << " " << pensja << " ";
	if (k) result << k->zwrocSymbol();
	else result << "pusty";
	result << "\n";
	return result;
}

std::ostream& operator<<(std::ostream& out, const wychowawca& w)
{
	out<<w.imie<<" "<<w.nazwisko<<" Nauczyciel przedmiotu "<<w.przedmiot;
	if(w.k)	out<<", Wychowawca klasy "<<w.zwrocKlase();
	else out<<", obecnie brak wychowawstwa";
	out<<", Pensja: "<<w.pensja<<" zl\n";
	return out;
}

uczen::uczen(const std::string& i, const std::string& n, klasa* k): osoba(i,n), k(k) {};
uczen::uczen(const osoba& o, klasa* k): osoba(o), k(k) {};

std::string uczen::zwrocKlase() const
{return k->zwrocSymbol();}

klasa* uczen::wskazKlase()
{return k;}

void uczen::zmienKlase(klasa* kl)
{
	//wyjatki
	if (k == kl)
	{throw std::string("Ten uczen juz jest przypisany do tej klasy"); return;}
	if (k == nullptr)
	{
		if (kl)
		{
			if (kl->zwrocLiczbe() >=kl->zwrocMax()) throw std::string("Ta klasa jest juz pelna");
			kl->dodajUcznia();
			k = kl;
			return;
		}
	}
	else
	{
		if (kl)
		{
			if (kl->zwrocLiczbe() >= kl->zwrocMax()) throw std::string("Ta klasa jest juz pelna");
			kl->dodajUcznia();
			k->usunUcznia();
			k = kl;
			return;
		}
		else
		{
			k->usunUcznia();
			k = kl;
			return;
		}
	}
}

std::stringstream uczen::save()
{
	std::stringstream result;
	result << "u " << imie << " " << nazwisko << " ";
	if (k) result << k->zwrocSymbol();
	else result << "pusty";
	result << "\n";
	return result;
}

std::ostream& operator<<(std::ostream& out, const uczen& u)
{
	out<<u.imie<<" "<<u.nazwisko;
	if(u.k) out<<" Uczeszcza do klasy "<<u.zwrocKlase()<<"\n";
	else out<<" Obecnie nie uczeszcza do zadnej klasy\n";
	return out;
}

zajecia::zajecia(const std::string& k) : symbolKlasy(k), s(nullptr), n(nullptr) {}

std::string zajecia::zwrocSale() const
{return s->zwrocSymbol();}

sala* zajecia::wskazSale() const
{return s;}

nauczyciel* zajecia::wskazNauczyciela() const
{return n;}

std::string zajecia::zwrocKlase() const
{return symbolKlasy;}

void zajecia::zmienSale(sala* sal)
{s = sal;}

void zajecia::zmienNauczyciela(nauczyciel* nau)
{n = nau;}

std::stringstream zajecia::save()
{
	std::stringstream result;
	result << symbolKlasy << " ";
	if (s) result << zwrocSale() << " ";
	else result << "pusty ";
	if (n) result << wskazNauczyciela()->zwrocNazwisko() << " " << wskazNauczyciela()->zwrocImie() << " ";
	else result << "pusty pusty ";
	return result;
}

std::ostream& operator<<(std::ostream& out, const zajecia& z)
{
	if (!z.s || !z.n)
	{
		out<<"Brak zajec\n";
		return out;
	}
	out << "Przedmiot: " << z.wskazNauczyciela()->zwrocPrzedmiot();
	out << " Sala: " << z.zwrocSale();
	out << " Nauczyciel: " << z.wskazNauczyciela()->zwrocNazwisko()<<" "<<z.wskazNauczyciela()->zwrocImie();
	out << "\n";
	return out;
}

planLekcji::planLekcji(klasa* kl): k(kl)
{
	zajecia pom(k->zwrocSymbol());
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++) rozklad.tab[i][j] = pom;
	}
}

std::string planLekcji::zwrocKlase() const
{return k->zwrocSymbol();}

klasa* planLekcji::wskazKlase() const
{return k;}

zajecia* planLekcji::wskazZajecia(int d, int g)
{return rozklad.wskazObiekt(d,g);}

void planLekcji::zmienZajecia(int d, int g, zajecia* z)
{
	if (z == rozklad.wskazObiekt(d, g)) throw std::string("Te zajecia sa juz wpisane w tym miejscu");
	if (z)	
	{
		zajecia pom=*z;
		rozklad.tab[d][g] = pom;
	}
	else rozklad.tab[d][g]= zajecia(k->zwrocSymbol());
}

std::stringstream planLekcji::save()
{
	std::stringstream result, pom;
	std::string pom1;
	result << "l " << zwrocKlase() << " ";
	pom=rozklad.save();
	pom>>pom1;
	result<<pom1;
	result<<"\n";
	return result;
}

std::ostream& operator<<(std::ostream& out, const planLekcji& pl)
{
	out << "Plan lekcji klasy " << pl.zwrocKlase()<<"\n";
	out << pl.rozklad;
	return out;
}
