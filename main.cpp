#include<iostream>
#include"szkola.h"
#include"lista.h"
#include"interfejs.cpp"

//napisz biblioteke "interfejs"

using namespace std;

int main()
{
	osoba o(string("Adam"), string("Bieniek"));
	uczen u(o);
	pracownik p(string("Jan"), string("Kowalski"), string("Wozny"));
	cout<<o<<u<<p;
	p.zmienPensje(2000);
	cout<<p;
	nauczyciel n(p, string("matematyka"));
	cout<<n;
	n.zmienPensje(3472);
	cout<<n;
	system("pause");
	lista<uczen> uczniowie;
	uczniowie.push_top(u);
	uczniowie.push_back(uczen("sadasd", "sdasda"));
	cout<<"Ilosc uczniow: "<<uczniowie.length()<<"\n";
	uczniowie.pop_at(2);
	cout<<"Ilosc uczniow: "<<uczniowie.length()<<"\n";
	//uczniowie.pop_top();
	cout<<"Ilosc uczniow: "<<uczniowie.length()<<"\n";
	lista<klasa> klasy;
	lista<sala> sale;
	lista<pracownik> pracownicy;
	lista<nauczyciel> nauczyciele;
	lista<wychowawca> wychowawcy;
	lista<planLekcji> plany;
	klasa k(string("1A"));
	sala s(string("05"));
	klasy.push_back(k);
	wychowawca w(n,&klasy[1]);
	sale.push_back(s);
	uczniowie[1].zmienKlase(&klasy[1]);
	cout<<klasy[1];
	cout<<uczniowie[1];
	pracownicy.push_back(p);
	nauczyciele.push_back(n);
	wychowawcy.push_back(w);
	//saving(klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
	//klasy.pop_back();
	//nauczyciele.pop_back();
	//wychowawcy.pop_back();
	//loading(klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
	//cout<<sale[2];
	//cout<<uczniowie[2];
	//cout<<uczniowie[1];
	//cout<<pracownicy[1];
	//cout<<pracownicy[2];
	//cout<<nauczyciele[1];
	//cout<<wychowawcy[1];
	MENU(cin, cout, klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
	return 0;
}
