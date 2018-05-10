#pragma once
#include<string>
#include<iostream>

class klasa
{
protected:
	std::string symbol;
	unsigned short liczba_osob;
	const static unsigned short max=30;
	bool czyWychowawca;
public:
	klasa(const std::string&);
	klasa(const klasa&) = default;
	klasa& operator=(const klasa&) = default;
	~klasa(){};
	std::string zwrocSymbol() const;
	unsigned short zwrocLiczbe() const;
	bool zwrocWychowawstwo() const;
	const unsigned short zwrocMax() const;
	void dodajUcznia();
	void usunUcznia();
	void dodajWychowawce();
	void usunWychowawce();
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
	double zwrocPensje() const;
	void zmienPensje(const double&);
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
	friend std::ostream& operator<<(std::ostream&, const nauczyciel&);
};

std::ostream& operator<<(std::ostream&, const nauczyciel&);

class wychowawca: public nauczyciel
{
protected:
	klasa* k;
public:
	wychowawca(const std::string&, const std::string&, const std::string&, const double& =0, klasa* =nullptr);
	wychowawca(const osoba&, const std::string&, const double& =0, klasa* =nullptr);
	wychowawca(const pracownik&, const std::string&, klasa* =nullptr);
	wychowawca(const nauczyciel&, klasa* =nullptr);
	wychowawca(const wychowawca&) = default;
	wychowawca& operator=(const wychowawca&) = default;
	virtual ~wychowawca(){};
	std::string zwrocKlase() const;
	klasa* wskazKlase() const;
	void zmienKlase(klasa* =nullptr);
	friend std::ostream& operator<<(std::ostream&, const wychowawca&);
};

std::ostream& operator<<(std::ostream&, const wychowawca&);

class uczen: public osoba
{
protected:
	klasa* k;
public:
	uczen(const std::string&, const std::string&, klasa* =nullptr);
	uczen(const osoba&, klasa* =nullptr);
	uczen(const uczen&) = default;
	uczen& operator=(const uczen&) = default;
	virtual ~uczen(){};
	std::string zwrocKlase() const;
	klasa* wskazKlase() const;
	void zmienKlase(klasa* =nullptr);
	friend std::ostream& operator<<(std::ostream&, const uczen&);	
};

std::ostream& operator<<(std::ostream&, const uczen&);
