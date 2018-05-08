#pragma once
#include<string>




class klasa
{
	string symbol;
	int liczba_osob;
	const int max=30;
	bool czyWychowawca;
public:
	klasa(const string&, const int&=0, const bool&=0);
	klasa(const klasa&) = default;
	klasa& operator=(const klasa&) = default;
	~klasa(){};
	string zwrocSymbol() const;
	int zwrocLiczbe() const;
	bool zwrocWychowawstwo() const;
	const int zwrocMax() const;
	void dodajUcznia();
	void usunUcznia();
	void dodajWychowawce();
	void usunWychowawce();
	friend std::ostream& operator<<(std::ostream&, const klasa&);
};

class osoba
{
	string imie;
	string nazwisko;
public:
	virtual osoba(const string&, const string&);
	virtual osoba(const osoba&) = default;
	virtual osoba& operator=(const osoba&) = default;
	virtual ~osoba(){};
	string zwrocImie() const;
	string zwrocNazwisko() const;
	friend std::ostream& operator<<(std::ostream&, const osoba&);
};

class pracownik: osoba
{
	string stanowisko;
	unsigned double pensja;
public:
	virtual pracownik(const string&, const string&, const string&, const unsigned double&=0);
	virtual pracownik(const osoba&, const string&, const unsigned double&=0);
	virtual pracownik(const pracownik&) = default;
	virtual pracownik& operator=(const pracownik&) = default;
	virtual ~pracownik(){};
	string zwrocStanowisko() const;
	int zwrocPensje() const;
	void zmienPensje(const unsigned double&);
	friend std::ostream& operator<<(std::ostream&, const pracownik&);	
};

class nauczyciel: pracownik
{
	string przedmiot;
public:
	virtual nauczyciel(const string&, const string&, const string&, const unsigned double&=0);
	virtual nauczyciel(const osoba&, const string&, const unsigned double&=0);
	virtual nauczyciel(const pracownik&, const string&);
	virtual nauczyciel(const nauczyciel&) = default;
	virtual nauczyciel& operator=(const nauczyciel&) = default;
	virtual ~nauczyciel(){};
	string zwrocPrzedmiot() const;
	friend std::ostream& operator<<(std::ostream&, const nauczyciel&);
};

class wychowawca: nauczyciel
{
	klasa* k;
public:
	virtual wychowawca(const string&, const string&, const string&, const unsigned double&=0, klasa*=nullptr);
	virtual wychowawca(const osoba&, const string&, const unsigned double&=0, klasa*=nullptr);
	virtual wychowawca(const pracownik&, const string&, klasa*=nullptr);
	virtual wychowawca(const nauczyciel&, klasa*=nullptr);
	virtual wychowawca(const wychowawca&) = default;
	virtual wychowawca& operator=(const wychowawca&) = default;
	virtual ~wychowawca(){};
	string zwrocKlase() const;
	klasa* wskazKlase() const;
	void zmienKlase(klasa*=nullptr);
	friend std::ostream& operator<<(std::ostream&, const wychowawca&);
}

class uczen: osoba
{
	klasa* k;
public:
	virtual uczen(const string&, const string&, klasa*=nullptr);
	virtual uczen(const osoba&, klasa*=nullptr);
	virtual uczen(const uczen&) = default;
	virtual uczen& operator=(cosnt uczen&) = default;
	virtual ~uczen(){};
	string zwrocKlase() const;
	klasa* wskazKlase() const;
	void zmienKlase(klasa*=nullptr);
	friend std::ostream& operator<<(std::ostream&, const uczen&);	
};
