#pragma once
#include<string>
#include<iostream>
#include<sstream>

enum dzien { poniedzialek, wtorek, sroda, czwartek, piatek };
enum godzina { zero, pierwsza, druga, trzecia, czwarta, piata, szosta, siodma, osma };

template <class T>
class tydzien
{
public:
	T tab[5][9];
	tydzien();
	tydzien(const tydzien&) = default;
	tydzien& operator=(const tydzien&) = default;
	~tydzien() {};
	T* wskazObiekt(int = 0, int = 0);
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const tydzien<T>&);
};

template <class T>
std::ostream& operator<<(std::ostream&, const tydzien<T>&);

class sala
{
	std::string symbol;
	tydzien<bool> dostepnosc;
public:
	sala(const std::string&);
	sala(const sala&) = default;
	sala& operator=(const sala&) = default;
	~sala(){};
	std::string zwrocSymbol() const;
	void zmienDostepnosc(int, int, bool = 0);
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const sala&);
};

std::ostream& operator<<(std::ostream&, const sala&);

class klasa
{
protected:
	std::string symbol;
	unsigned short liczba_osob;
	const static unsigned short max=30;
	bool czyWychowawca;
	bool czyPlan;
public:
	klasa(const std::string&);
	klasa(const klasa&) = default;
	klasa& operator=(const klasa&) = default;
	~klasa(){};
	std::string zwrocSymbol() const;
	unsigned short zwrocLiczbe() const;
	bool zwrocWychowawstwo() const;
	bool zwrocPlan() const;
	const unsigned short zwrocMax() const;
	void dodajUcznia();
	void usunUcznia();
	void dodajWychowawce();
	void usunWychowawce();
	void dodajPlan();
	void usunPlan();
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const klasa&);
};

std::ostream& operator<<(std::ostream&, const klasa&);

class osoba
{
protected:
	std::string imie;
	std::string nazwisko;
public:
	osoba(const std::string&, const std::string&);
	osoba(const osoba&) = default;
	osoba& operator=(const osoba&) = default;
	virtual ~osoba(){};
	std::string zwrocImie() const;
	std::string zwrocNazwisko() const;
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const osoba&);
};

std::ostream& operator<<(std::ostream&, const osoba&);

class pracownik: public osoba
{
protected:
	std::string stanowisko;
	double pensja;
public:
	pracownik(const std::string&, const std::string&, const std::string&, const double& =0);
	pracownik(const osoba&, const std::string&, const double& =0);
	pracownik(const pracownik&) = default;
	pracownik& operator=(const pracownik&) = default;
	virtual ~pracownik(){};
	std::string zwrocStanowisko() const;
	void zmienStanowisko(const std::string&);
	double zwrocPensje() const;
	void zmienPensje(const double&);
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const pracownik&);	
};

std::ostream& operator<<(std::ostream&, const pracownik&);

class nauczyciel: public pracownik
{
protected:
	std::string przedmiot;
public:
	nauczyciel(const std::string&, const std::string&, const std::string&, const double& =0);
	nauczyciel(const osoba&, const std::string&, const double& =0);
	nauczyciel(const pracownik&, const std::string&);
	nauczyciel(const nauczyciel&) = default;
	nauczyciel& operator=(const nauczyciel&) = default;
	virtual ~nauczyciel(){};
	std::string zwrocPrzedmiot() const;
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const nauczyciel&);
};

std::ostream& operator<<(std::ostream&, const nauczyciel&);

class wychowawca: public nauczyciel
{
protected:
	klasa* k;
public:
	wychowawca(const std::string&, const std::string&, const std::string&, const double& =0, klasa* = nullptr);
	wychowawca(const osoba&, const std::string&, const double& =0, klasa* = nullptr);
	wychowawca(const pracownik&, const std::string&, klasa* = nullptr);
	wychowawca(const nauczyciel&, klasa* = nullptr);
	wychowawca(const wychowawca&) = default;
	wychowawca& operator=(const wychowawca&) = default;
	virtual ~wychowawca(){};
	std::string zwrocKlase() const;
	klasa* wskazKlase();
	void zmienKlase(klasa* = nullptr);
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const wychowawca&);
};

std::ostream& operator<<(std::ostream&, const wychowawca&);

class uczen: public osoba
{
protected:
	klasa* k;
public:
	uczen(const std::string&, const std::string&, klasa* = nullptr);
	uczen(const osoba&, klasa* = nullptr);
	uczen(const uczen&) = default;
	uczen& operator=(const uczen&) = default;
	virtual ~uczen(){};
	std::string zwrocKlase() const;
	klasa* wskazKlase();
	void zmienKlase(klasa* = nullptr);
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const uczen&);	
};
 
std::ostream& operator<<(std::ostream&, const uczen&);

class zajecia
{
	std::string symbolKlasy;
	sala* s;
	nauczyciel* n;
public:
	zajecia(const std::string& ="pusty");
	zajecia(const zajecia&) = default;
	zajecia& operator=(const zajecia&) = default;
	~zajecia(){};
	std::string zwrocSale() const;
	sala* wskazSale() const;
	nauczyciel* wskazNauczyciela() const;
	std::string zwrocKlase() const;
	void zmienSale(sala* =nullptr);
	void zmienNauczyciela(nauczyciel* =nullptr);
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const zajecia&);
};

std::ostream& operator<<(std::ostream&, const zajecia&);

class planLekcji
{
	klasa* k;
	tydzien<zajecia> rozklad;
public:
	planLekcji(klasa*);
	planLekcji(const planLekcji&)= default;
	planLekcji& operator=(const planLekcji&) = default;
	~planLekcji(){};
	std::string zwrocKlase() const;
	klasa* wskazKlase() const;
	zajecia* wskazZajecia(int, int);
	void zmienZajecia(int, int, zajecia* = nullptr);
	std::stringstream save();
	friend std::ostream& operator<<(std::ostream&, const planLekcji&);
};

std::ostream& operator<<(std::ostream&, const planLekcji&);
