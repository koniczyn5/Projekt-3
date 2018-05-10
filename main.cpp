#include<iostream>
#include"szkola.h"

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
	klasa A1(string("1A"));
	u.zmienKlase(&A1);
	cout<<A1<<u;
	wychowawca w(n, &A1);
	cout<<w;
	return 0;
}
