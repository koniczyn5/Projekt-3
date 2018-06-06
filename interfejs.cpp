#include<string>
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<sstream>

void pozar(lista<klasa>& klasy, lista<sala>& sale, lista<uczen>& uczniowie, lista<pracownik>& pracownicy, lista<nauczyciel>& nauczyciele, lista<wychowawca>& wychowawcy, lista<planLekcji>& plany)
{
	klasy.clear();
	sale.clear();
	uczniowie.clear();
	pracownicy.clear();
	nauczyciele.clear();
	wychowawcy.clear();
	plany.clear();
}

void loading(const std::string& nazwaPliku, lista<klasa>& klasy, lista<sala>& sale, lista<uczen>& uczniowie, lista<pracownik>& pracownicy, lista<nauczyciel>& nauczyciele, lista<wychowawca>& wychowawcy, lista<planLekcji>& plany)
{
	try {
	std::fstream plik;
	plik.open(nazwaPliku, std::fstream::in | std::fstream::binary);
	while (!plik.eof())
	{
		char znak;
		plik.get(znak);
		switch(znak)
		{
			case 'k': 
			{
				std::stringstream hold;
				std::string w1, holder;
				getline(plik, holder);
				hold<<holder;
				hold>>w1;
				klasa pom(w1);
				klasy.push_back(pom);
				break;
			}
			case 's':
			{
				std::stringstream hold;
				std::string w1, holder;
				bool w2;
				getline(plik, holder);
				hold<<holder;
				hold>>w1;
				sala pom(w1);
				for (int i=0; i<5; i++)
				{
					for (int j=0; j<9; j++)
					{
						hold>>w2;
						if(w2) pom.zmienDostepnosc(i,j,1);
					}
				}
				sale.push_back(pom);
				break;
			}
			case 'u':
			{
				std::stringstream hold;
				std::string w1, w2, w3, holder;
				getline(plik,holder);
				hold<<holder;
				hold>>w1>>w2>>w3;
				uczen pom(w1,w2);
				if(w3!="pusty")
				{
					for(int i=0; i<klasy.length(); i++)
					{
						if(klasy[i+1].zwrocSymbol()==w3)
						{
							pom.zmienKlase(&klasy[i+1]);
							break;
						}
					}
				}
				uczniowie.push_back(pom);
				break;
			}
			case 'p':
			{
				std::stringstream hold;
				std::string w1,w2,w3, holder;
				double w4;
				getline(plik, holder);
				hold<<holder;
				hold>>w1>>w2>>w3>>w4;
				pracownik pom(w1,w2,w3);
				pom.zmienPensje(w4);
				pracownicy.push_back(pom);
				break;
			}
			case 'n':
			{
				std::stringstream hold;
				std::string w1,w2,w3, holder;
				double w4;
				getline(plik, holder);
				hold<<holder;
				hold>>w1>>w2>>w3>>w4;
				nauczyciel pom(w1,w2,w3);
				pom.zmienPensje(w4);
				nauczyciele.push_back(pom);
				break;
			}
			case 'w':
			{
				std::stringstream hold;
				std::string w1,w2,w3,w5, holder;
				double w4;
				getline(plik, holder);
				hold<<holder;
				hold>>w1>>w2>>w3>>w4>>w5;
				wychowawca pom(w1,w2,w3);
				pom.zmienPensje(w4);
				if(w5!="pusty")
				{
					for(int i=0; i<klasy.length(); i++)
					{
						if(klasy[i+1].zwrocSymbol()==w5)
						{
							pom.zmienKlase(&klasy[i+1]);
							break;
						}
					}
				}
				wychowawcy.push_back(pom);
				break;
			}
			case 'l':
			{
				std::stringstream hold;
				std::string w1, w2, w3, w4, holder;
				getline(plik, holder);
				hold<<holder;
				hold>>w1;
				klasa* wsk;
				for(int i=0; i<klasy.length(); i++)
				{
					if(klasy[i+1].zwrocSymbol()==w1)
					{
						wsk=&klasy[i+1];
						break;
					}
				}
				planLekcji pom(wsk);
				for(int i=0; i<4; i++)
				{
					for(int j=0; j<9; j++)
					{
						hold>>w1>>w2>>w3>>w4;
						if (w2=="pusty" || w3=="pusty" || w4=="pusty") continue;
						else
						{
							for(int x=0; x<sale.length(); x++)
							{
								if(sale[x+1].zwrocSymbol()==w2)
								{
									pom.wskazZajecia(i,j)->zmienSale(&sale[x+1]);
									break;
								}
							}
							for(int y=0; y<nauczyciele.length(); y++)
							{
								if(nauczyciele[y+1].zwrocNazwisko()==w3)
								{
									if(nauczyciele[y+1].zwrocImie()==w4)
									{
										pom.wskazZajecia(i,j)->zmienNauczyciela(&nauczyciele[y+1]);
										break;
									}
								}
								if(y+1==nauczyciele.length())
								{
									for(int z=0; z<wychowawcy.length(); z++)
									{
										if(wychowawcy[z+1].zwrocNazwisko()==w3)
										{
											if(wychowawcy[z+1].zwrocImie()==w4)
											{
												pom.wskazZajecia(i,j)->zmienNauczyciela(&wychowawcy[z+1]);
												break;
											}
										}
									}
								}
							}
						}
					}
				}
				plany.push_back(pom);
				break;
			}
			default:
			throw std::string("blad");
		}
	}
	plik.close();
	}
	catch(...)
	{
		throw;
	}
}

void saving(const std::string& nazwaPliku, lista<klasa>& klasy, lista<sala>& sale, lista<uczen>& uczniowie, lista<pracownik>& pracownicy, lista<nauczyciel>& nauczyciele, lista<wychowawca>& wychowawcy, lista<planLekcji>& plany)
{
	std::fstream plik;
	plik.open(nazwaPliku, std::fstream::out | std::fstream::binary | std::fstream::trunc);
	std::stringstream pom1;
	std::string pom2;
	for (int i=0; i<klasy.length(); i++)
	{
		pom1=klasy[i+1].save();
		getline(pom1, pom2);
		plik<<pom2;
		plik<<"\n";
	}
	for (int i=0; i<sale.length(); i++)
	{
		pom1=sale[i+1].save();
		getline(pom1, pom2);
		plik<<pom2;
		plik<<"\n";
	}	
	for (int i=0; i<uczniowie.length(); i++)
	{
		pom1=uczniowie[i+1].save();
		getline(pom1, pom2);
		plik<<pom2;
		plik<<"\n";
	}
	for (int i=0; i<pracownicy.length(); i++)
	{
		pom1=pracownicy[i+1].save();
		getline(pom1, pom2);
		plik<<pom2;
		plik<<"\n";
	}
	for (int i=0; i<nauczyciele.length(); i++)
	{
		pom1=nauczyciele[i+1].save();
		getline(pom1, pom2);
		plik<<pom2;
		plik<<"\n";
	}
	for (int i=0; i<wychowawcy.length(); i++)
	{
		pom1=wychowawcy[i+1].save();
		getline(pom1, pom2);
		plik<<pom2;
		plik<<"\n";
	}
	for (int i=0; i<plany.length(); i++)
	{
		pom1=plany[i+1].save();
		getline(pom1, pom2);
		plik<<pom2;
		plik<<"\n";
	}
	plik.close();
}

void submenu_sale(std::istream& in, std::ostream& out, lista<sala>& sale, bool& changes, lista<planLekcji>& plany)
{
	int option=0;
	while(true)
	{
		out<<"Zarzadzanie salami\n";
		out<<"Wprowadz: \n";
		out<<"1 - aby dodac sale\n";
		out<<"2 - aby usunac sale\n";
		out<<"3 - aby wypisac sale\n";
		out<<"0 - aby wrocic do poprzedniego menu\n";
		if(in>>option) ;
		else
		{
			out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			continue;
		}
		switch(option)
		{
			case 0: return;
			case 1:
			{
				std::string pom;
				out<<"Wprowadz numer sali\n";
				if(in>>pom)
				{
					sala pom1(pom);
					sale.push_back(pom1);
					changes=1;
					out<<"Pomyslnie dodano sale\n";
					break;
				}
				else
				{
					out<<"Niepoprawny numer sali\n";
					break;
				}
			}
			case 2:
			{
				std::string pom;
				bool failure=1;
				int x=0;
				out<<"Wprowadz numer sali\n";
				if(in>>pom)
				{
					for(int i=1; i<=sale.length(); i++)
					{
						if(pom==sale[i].zwrocSymbol())
						{
							failure=0;
							for(int j=1; j<=plany.length(); j++)
							{
								for(int a=0; a<5; a++)
								{
									for(int b=0; b<9; b++)
									{
										std::string pom1;
										if(plany[j].wskazZajecia(a,b)->wskazSale())
										{
											pom1=plany[j].wskazZajecia(a,b)->zwrocSale();
										}
										else continue;
										if(pom==pom1)
										{
											plany[j].zmienZajecia(a,b);
											x++;
										}
									}
								}
							}
							sale.pop_at(i);
							changes=1;
							out<<"Pomyslnie usunieto sale "<<pom<<". Spowodowalo to usuniecie "<<x<<" zajec z obecnych planow lekcji\n";
							break;
						}
					}
					if(failure) out<<"Nie znaleziono takiej sali\n";
					break;
				}
				else
				{
					out<<"Niepoprawny numer sali\n";
					break;
				}
			}
			case 3:
			{
				out<<"Spis sal\n";
				for(int i=1; i<=sale.length(); i++)
				{
					out<<sale[i];
				}
				break;
			}
			default:
			{
				out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			}
		}
		
	}
}

nauczyciel* znajdz_nauczyciela(std::string przedmiot, lista<nauczyciel>& nauczyciele, lista<wychowawca>& wychowawcy)
{
	bool failure=1;
	int los=rand()%15;
	while(true)
	{
		for(int i=1; i<=nauczyciele.length(); i++)
		{
			if(przedmiot==nauczyciele[i].zwrocPrzedmiot())
			{
				failure=0;
				if(los==0)
				{
					return &nauczyciele[i];
				}
				los--;
			}
		}
		for(int i=1; i<=wychowawcy.length(); i++)
		{
			if(przedmiot==wychowawcy[i].zwrocPrzedmiot())
			{
				failure=0;
				if(los==0)
				{
					return &wychowawcy[i];
				}
				los--;
			}
		}
		if(failure)
		{
			return nullptr;
		}
	}
}

sala* znajdz_sale(int d, int g, lista<sala>& sale)
{
	int los=rand()%sale.length()+1;
	if(sale[los].zwrocDostepnosc(d,g)==0)
	{
		return &sale[los];
	}
	else
	{
		for(int i=1; i<=sale.length(); i++)
		{
			if(sale[i].zwrocDostepnosc(d,g)==0)
			{
				return &sale[i];
			}
		}
	}
	return nullptr;
}

void wyczysc_sale(planLekcji& plan, lista<sala>& sale)
{
	for(int d=0; d<5; d++)
	{
		for(int g=0; g<9; g++)
		{
			if(plan.wskazZajecia(d,g)->wskazSale())
			{
				plan.wskazZajecia(d,g)->wskazSale()->zmienDostepnosc(d,g);
			}
		}
	}
}

void utworz_plan(std::ostream& out, klasa& klas, bool& changes, lista<planLekcji>& plany, lista<sala>& sale, lista<nauczyciel>& nauczyciele, lista<wychowawca>& wychowawcy)
{
	planLekcji temp(&klas);
	int los, los1, los2;
	nauczyciel* n;
	sala* s;
	//matematyka 4 lekcje w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("matematyka"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela matematyki\n";
			return;
		}
		los=rand()%5;
		for(int i=0; i<5; i++)
		{
			if(i==los) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
				
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	//polski 4 lekcje w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("polski"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela jezyka polskiego\n";
			return;
		}
		los=rand()%5;
		for(int i=0; i<5; i++)
		{
			if(i==los) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	//angielski 4 lekcje w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("angielski"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela jezyka angielskiego\n";
			return;
		}
		los=rand()%5;
		for(int i=0; i<5; i++)
		{
			if(i==los) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	//fizyka 2 lekcje w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("fizyka"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela fizyki\n";
			return;
		}
		los1=rand()%5;
		los2=rand()%5;
		while(los1==los2)
		{
			los2=rand()%5;
		}
		for(int i=0; i<5; i++)
		{
			if(i!=los1 && i!=los2) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	//chemia 2 lekcje w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("chemia"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela chemii\n";
			return;
		}
		los1=rand()%5;
		los2=rand()%5;
		while(los1==los2)
		{
			los2=rand()%5;
		}
		for(int i=0; i<5; i++)
		{
			if(i!=los1 && i!=los2) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	//biologia 2 lekcje w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("biologia"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela biologii\n";
			return;
		}
		los1=rand()%5;
		los2=rand()%5;
		while(los1==los2)
		{
			los2=rand()%5;
		}
		for(int i=0; i<5; i++)
		{
			if(i!=los1 && i!=los2) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	//wf 2 lekcje w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("wf"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela wychowania fizycznego\n";
			return;
		}
		los1=rand()%5;
		los2=rand()%5;
		while(los1==los2)
		{
			los2=rand()%5;
		}
		for(int i=0; i<5; i++)
		{
			if(i!=los1 && i!=los2) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	//informatyka 1 lekcja w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("informatyka"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela informatyki\n";
			return;
		}
		los=rand()%5;
		for(int i=0; i<5; i++)
		{
			if(i!=los) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	//religia 1 lekcja w tygodniu
	{
		bool failure=1;
		n=znajdz_nauczyciela(std::string("religia"), nauczyciele, wychowawcy);
		if(n==nullptr)
		{
			wyczysc_sale(temp, sale);
			out<<"Nie znaleziono wolnego nauczyciela religii\n";
			return;
		}
		los=rand()%5;
		for(int i=0; i<5; i++)
		{
			if(i!=los) continue;
			for(int j=0; j<9; j++)
			{
				if(temp.wskazZajecia(i,j)->wskazSale())
				{
					continue;
				}
				s=znajdz_sale(i, j, sale);
				if(s)
				{
					failure=0;
					zajecia pom(klas.zwrocSymbol());
					pom.zmienSale(s);
					s->zmienDostepnosc(i,j,1);
					pom.zmienNauczyciela(n);
					temp.zmienZajecia(i,j,&pom);
					break;
				}
			}
			if(failure)
			{
				wyczysc_sale(temp, sale);
				out<<"Nie znaleziono wolnej sali\n";
				return;
			}
		}
	}
	plany.push_back(temp);
	klas.dodajPlan();
	changes=1;
	out<<"Pomyslnie dodano plan lekcji\n";
}

void submenu_plany(std::istream& in, std::ostream& out, klasa& klas, bool& changes, lista<planLekcji>& plany, lista<sala>& sale, lista<nauczyciel>& nauczyciele, lista<wychowawca>& wychowawcy)
{
	int option=0;
	while(true)
	{
		out<<"Zarzadzanie planem lekcji klasy "<<klas.zwrocSymbol()<<"\n";
		out<<"Wprowadz: \n";
		out<<"1 - aby utworzyc plan\n";
		out<<"2 - aby usunac plan\n";
		out<<"3 - aby wypisac plan\n";
		out<<"0 - aby wrocic do poprzedniego menu\n";
		if(in>>option) ;
		else
		{
			out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			continue;
		}
		switch(option)
		{
			case 0: return;
			case 1:
			{
				utworz_plan(out, klas, changes, plany, sale, nauczyciele, wychowawcy);
				break;
			}
			case 2:
			{
				if(klas.zwrocPlan()==0)
				{
					out<<"Ta klasa nie posiada planu lekcji\n";
					break;
				}
				int terminy=0;
				for(int j=1; j<=plany.length(); j++)
				{
					if(plany[j].zwrocKlase()==klas.zwrocSymbol())
					{
						for(int d=0; d<5; d++)
						{
							for(int g=0; g<9; g++)
							{
								if(plany[j].wskazZajecia(d,g)->wskazSale())
								{
									plany[j].wskazZajecia(d,g)->wskazSale()->zmienDostepnosc(d,g);
									terminy++;
								}
							}
						}
						plany.pop_at(j);
					}
				}
				klas.usunPlan();
				out<<"Pomyslnie usunieto plan lekcji klasy "<<klas.zwrocSymbol()<<" spowodowalo to zwolnienie "<<terminy<<" terminow w salach\n";
				break;
			}
			case 3:
			{
				if(klas.zwrocPlan())
				{
					for(int i=1; i<=plany.length(); i++)
					{
						if(klas.zwrocSymbol()==plany[i].zwrocKlase())
						{
							out<<plany[i];
						}
					}
				}
				else
				{
					out<<"Ta klasa nie posiada planu lekcji\n";
				}
				break;
			}
			default:
			{
				out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			}
		}
	}
}

void submenu_klasy(std::istream& in, std::ostream& out, lista<klasa>& klasy, bool& changes, lista<uczen>& uczniowie,lista<nauczyciel>& nauczyciele, lista<wychowawca>& wychowawcy, lista<planLekcji>& plany, lista<sala>& sale)
{
	int option=0;
	while(true)
	{
		out<<"Zarzadzanie klasami\n";
		out<<"Wprowadz: \n";
		out<<"1 - aby dodac klase\n";
		out<<"2 - aby usunac klase\n";
		out<<"3 - aby wypisac klasy\n";
		out<<"4 - aby zmienic wychowawce klasy\n";
		out<<"5 - aby wypisac wychowawce klasy\n";
		out<<"6 - aby dodac/usunac ucznia do klasy\n";
		out<<"7 - aby wypisac uczniow danej klasy\n";
		out<<"8 - aby edytowac plan lekcji wybranej klasy\n";
		out<<"0 - aby wrocic do poprzedniego menu\n";
		if(in>>option) ;
		else
		{
			out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			continue;
		}
		switch(option)
		{
			case 0: return;
			case 1:
			{
				std::string pom;
				out<<"Wprowadz oznaczenie klasy\n";
				if(in>>pom)
				{
					klasa pom1(pom);
					klasy.push_back(pom1);
					changes=1;
					out<<"Pomyslnie dodano klase\n";
					break;
				}
				else
				{
					out<<"Niepoprawne oznaczenie klasy\n";
					break;
				}
			}
			case 2:
			{
				std::string klas;
				bool failure=1;
				int terminy=0, ucz=0;
				out<<"Wprowadz oznaczenie klasy\n";
				if(in>>klas)
				{
					for(int i=1; i<=klasy.length(); i++)
					{
						if(klas==klasy[i].zwrocSymbol())
						{
							failure=0;
							if(klasy[i].zwrocWychowawstwo())
							{
								for(int j=1; j<=wychowawcy.length(); j++)
								{
									if(wychowawcy[j].wskazKlase()==&klasy[i])
									{
										wychowawcy[j].zmienKlase();
										break;
									}
								}
							}
							if(klasy[i].zwrocLiczbe()>0)
							{
								for(int j=1; j<=uczniowie.length(); j++)
								{
									if(uczniowie[j].wskazKlase()==&klasy[i])
									{
										uczniowie[j].zmienKlase();
										ucz++;
									}
								}
							}
							if(klasy[i].zwrocPlan())
							{
								for(int j=1; j<=plany.length(); j++)
								{
									if(plany[j].zwrocKlase()==klas)
									{
										for(int d=0; d<5; d++)
										{
											for(int g=0; g<9; g++)
											{
												if(plany[j].wskazZajecia(d,g)->wskazSale())
												{
													plany[j].wskazZajecia(d,g)->wskazSale()->zmienDostepnosc(d,g);
													terminy++;
												}
											}
										}
										plany.pop_at(j);
									}
								}
							}
							klasy.pop_at(i);
							changes=1;
							out<<"Pomyslne usunieto klase "<<klas<<" spowodowalo to wypisanie "<<ucz<<" uczniow z tej klasy oraz zwolnilo "<<terminy<<" terminow w salach\n";
							break;
						}
					}
					if(failure)
					{
						out<<"Nie znaleziono takiej klasy\n";
					}
				}
				else
				{
					out<<"Niepoprawne oznaczenie klasy\n";
				}
				break;
			}
			case 3:
			{
				out<<"Spis klas\n";
				for(int i=1; i<=klasy.length(); i++)
				{
					out<<klasy[i];
				}
				break;
			}
			case 4:
			{
				std::string klas, imie, nazwisko;
				bool failure1=1, failure2=1;
				out<<"Wprowadz symbol klasy\n";
				if(in>>klas)
				{
					for(int i=1; i<=klasy.length(); i++)
					{
						if(klas==klasy[i].zwrocSymbol())
						{
							failure1=0;
							bool opt=0;
							out<<"Wprowadz:\n1 - aby dodac wychowawce\n0 - aby usunac wychowawce\n";
							if(in>>opt)
							{
								if(opt)
								{
									out<<"Wprowadz imie nowego wychowawcy\n";
									if(in>>imie)
									{
										out<<"Wprowadz nazwisko nowego wychowawcy\n";
										if(in>>nazwisko)
										{
											for(int j=1; j<=wychowawcy.length(); j++)
											{
												if(nazwisko==wychowawcy[j].zwrocNazwisko())
												{
													if(imie==wychowawcy[j].zwrocImie())
													{
														failure2=0;
														if(klasy[i].zwrocWychowawstwo())
														{
															for(int x=1; x<=wychowawcy.length(); x++)
															{
																if(&klasy[i]==wychowawcy[x].wskazKlase())
																{
																	wychowawcy[x].zmienKlase();
																	klasy[i].usunWychowawce();
																	break;
																}
															}
														}
														wychowawcy[j].zmienKlase(&klasy[i]);
														changes=1;
														out<<"Pomyslnie zmieniono wychowawce\n";
													}
												}
											}
											if(failure2)
											{
												for(int j=1; j<=nauczyciele.length(); j++)
												{
													if(nazwisko==nauczyciele[j].zwrocNazwisko())
													{
														if(imie==nauczyciele[j].zwrocImie())
														{
															failure2=0;
															if(klasy[i].zwrocWychowawstwo())
															{
																for(int x=1; x<=wychowawcy.length(); x++)
																{
																	if(&klasy[i]==wychowawcy[x].wskazKlase())
																	{
																		wychowawcy[x].zmienKlase();
																		klasy[i].usunWychowawce();
																		break;
																	}
																}
															}
															wychowawca nowy(nauczyciele[j]);
															wychowawcy.push_back(nowy);
															nauczyciele.pop_at(j);
															wychowawcy[wychowawcy.length()].zmienKlase(&klasy[i]);
															changes=1;
															out<<"Pomyslnie zmieniono wychowawce\n";
														}
													}
												}
											}
											if(failure2) out<<"Nie znalezionog takiego nauczyciela\n";
										}
										else
										{
											out<<"Niepoprawne nazwisko\n";
										}
									}
									else
									{
										out<<"Niepoprawne imie\n";
									}
								}
								else
								{
									if(klasy[i].zwrocWychowawstwo())
									{
										for(int j=1; j<=wychowawcy.length(); j++)
										{
											if(&klasy[i]==wychowawcy[j].wskazKlase())
											{
												wychowawcy[j].zmienKlase();
												klasy[i].usunWychowawce();
												break;
											}
										}
									}
									else
									{
										out<<"Ta klasa nie posiada wychowawcy\n";
									}
								}
							}
							else
							{
								out<<"Niepoprawne polecenie\n";
							}
							break;
						}
					}
					if(failure1) out<<"Nie znaleziono takiej klasy\n";
				}
				else
				{
					out<<"Niepoprawne oznaczenie klasy\n";
				}
				break;
			}
			case 5:
			{
				std::string pom;
				bool failure=1;
				out<<"Wprowadz symbol klasy\n";
				if(in>>pom)
				{
					for(int i=1; i<=klasy.length(); i++)
					{
						if(pom==klasy[i].zwrocSymbol())
						{
							failure=0;
							if(klasy[i].zwrocWychowawstwo())
							{
								for(int j=1; j<=wychowawcy.length(); j++)
								{
									if(wychowawcy[j].wskazKlase()==&klasy[i])
									{
										out<<"Wychowawca klasy "<<pom<<" jest "<<wychowawcy[j].zwrocImie()<<" "<<wychowawcy[j].zwrocNazwisko()<<"\n";
										break;
									}
								}
							}
							else
							{
								out<<"Ta klasa nie posiada wychowawcy\n";
								break;
							}
						break;
						}
					}
					if(failure)
					{
						out<<"Nie znaleziono takiej klasy\n";
					}
				}
				else
				{
					out<<"Niepoprawne oznaczenie klasy\n";
				}
				break;
			}
			case 6:
			{
				std::string klas, imie, nazwisko;
				bool failure1=1, failure2=1;
				out<<"Wprowadz symbol klasy\n";
				if(in>>klas)
				{
					for(int i=1; i<=klasy.length(); i++)
					{
						if(klas==klasy[i].zwrocSymbol())
						{
							failure1=0;
							bool opt=0;
							out<<"Wprowadz:\n1 - aby dodac ucznia\n0 - aby usunac ucznia\n";
							if(in>>opt)
							{
								out<<"Wprowadz imie ucznia\n";
								if(in>>imie)
								{
									out<<"Wprowadz nazwisko ucznia\n";
									if(in>>nazwisko)
									{
										for(int j=1; j<=uczniowie.length(); j++)
										{
											if(nazwisko==uczniowie[j].zwrocNazwisko())
											{
												if(imie==uczniowie[j].zwrocImie())
												{
													failure2=0;
													if(opt)
													{
														if(&klasy[i]==uczniowie[j].wskazKlase())
														{
															out<<"Ten uczen juz nalezy do tej klasy\n";
														}
														else
														{
															try
															{
																uczniowie[j].zmienKlase(&klasy[i]);
																changes=1;
																out<<"Pomyslnie dodano ucznia do klasy\n";
															}
															catch(std::string kom)
															{
																out<<kom<<"\n";
															}
														}
													}
													else
													{
														if(&klasy[i]==uczniowie[j].wskazKlase())
														{
															uczniowie[j].zmienKlase();
															changes=1;
															out<<"Pomyslnie usunieto ucznia z kasy\n";
														}
														else
														{
															out<<"Ten uczen nie nalezy do tej klasy\n";
														}
													}
													break;
												}
											}
										}
										if(failure2)
										{
											out<<"Nie znaleziono takiego ucznia";
										}
									}
									else
									{
										out<<"Niepoprawne nazwisko\n";
									}
								}
								else
								{
									out<<"Niepoprawne imie\n";
								}
							}
							else
							{
								out<<"Niepoprawne polecenie\n";
							}
							break;
						}
					}
					if(failure1)
					{
						out<<"Nie znaleziono takiej klasy\n";
					}
				}
				else
				{
					out<<"Niepoprawne oznaczenie klasy\n";
				}
				break;
			}
			case 7:
			{
				std::string pom;
				bool failure=1;
				out<<"Wprowadz symbol klasy\n";
				if(in>>pom)
				{
					for(int i=1; i<=klasy.length(); i++)
					{
						if(pom==klasy[i].zwrocSymbol())
						{
							failure=0;
							if(klasy[i].zwrocLiczbe())
							{
								out<<"Klasa "<<pom<<" sklada sie z "<<klasy[i].zwrocLiczbe()<<" uczniow:\n";
								for(int j=1; j<=uczniowie.length(); j++)
								{
									if(uczniowie[j].wskazKlase()==&klasy[i])
									{
										out<<uczniowie[j].zwrocImie()<<" "<<uczniowie[j].zwrocNazwisko()<<"\n";
									}
								}
							}
							else
							{
								out<<"Ta klasa nie posiada zadnych uczniow\n";
								break;
							}
						break;
						}
					}
					if(failure)
					{
						out<<"Nie znaleziono takiej klasy\n";
					}
				}
				else
				{
					out<<"Niepoprawne oznaczenie klasy\n";
				}
				break;
			}
			case 8:
			{
				std::string pom;
				bool failure=1;
				out<<"Wprowadz symbol klasy\n";
				if(in>>pom)
				{
					for(int i=1; i<=klasy.length(); i++)
					{
						if(pom==klasy[i].zwrocSymbol())
						{
							failure=0;
							submenu_plany(in, out, klasy[i], changes, plany, sale, nauczyciele, wychowawcy);
							break;
						}
					}
					if(failure)
					{
						out<<"Nie znaleziono takiej klasy\n";
					}
				}
				else
				{
					out<<"Niepoprawne oznaczenie klasy\n";
				}
				break;
			}
			default:
			{
				out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			}
		}
		
	}
}

void submenu_uczniowie(std::istream& in, std::ostream& out, lista<uczen>& uczniowie, bool& changes, lista<klasa>& klasy)
{
	int option=0;
	while(true)
	{
		out<<"Zarzadzanie uczniami\n";
		out<<"Wprowadz: \n";
		out<<"1 - aby dodac ucznia\n";
		out<<"2 - aby usunac ucznia\n";
		out<<"3 - aby wypisac uczniow\n";
		out<<"4 - aby przypisac/wypisac ucznia z klasy\n";
		out<<"0 - aby wrocic do poprzedniego menu\n";
		if(in>>option) ;
		else
		{
			out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			continue;
		}
		switch(option)
		{
			case 0: return;
			case 1:
			{
				std::string imie, nazwisko;
				out<<"Wprowadz imie ucznia\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko ucznia\n";
					if(in>>nazwisko)
					{
						uczen pom(imie, nazwisko);
						uczniowie.push_back(pom);
						changes=1;
						out<<"Pomyslnie dodano ucznia\n";
						break;
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
			}
			case 2:
			{
				std::string imie, nazwisko;
				bool failure=1;
				out<<"Wprowadz imie ucznia\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko ucznia\n";
					if(in>>nazwisko)
					{
						for(int i=1; i<=uczniowie.length(); i++)
						{
							if(nazwisko==uczniowie[i].zwrocNazwisko())
							{
								if(imie==uczniowie[i].zwrocImie())
								{
									failure=0;
									if(uczniowie[i].wskazKlase())
									{
										uczniowie[i].wskazKlase()->usunUcznia();
									}
									uczniowie.pop_at(i);
									changes=1;
									out<<"Pomyslnie usunieto ucznia\n";
									break;
								}
							}
						}
						if(failure) out<<"Nie znaleziono takiego ucznia\n";
						break;
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
			}
			case 3:
			{
				out<<"Spis uczniow\n";
				for(int i=1; i<=uczniowie.length(); i++)
				{
						out<<uczniowie[i];
				}
				break;
			}
			case 4:
			{
				std::string imie, nazwisko, klas;
				bool failure1=1, failure2=1, pom=0;
				out<<"Wprowadz imie ucznia\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko ucznia\n";
					if(in>>nazwisko)
					{
						for(int i=1; i<=uczniowie.length(); i++)
						{
							if(nazwisko==uczniowie[i].zwrocNazwisko())
							{
								if(imie==uczniowie[i].zwrocImie())
								{
									failure1=0;
									out<<"Wprowadz:\n1 - aby dodac ucznia do klasy\n0 - aby usunac ucznia z klasy\n";
									if(in>>pom)
									{
										if(pom)
										{
											out<<"Wprowadz symbol klasy\n";
											if(in>>klas)
											{
												for(int j=1; j<=klasy.length(); j++)
												{
													if(klas==klasy[j].zwrocSymbol())
													{
														failure2=0;
														try
														{
															uczniowie[i].zmienKlase(&klasy[j]);
															changes=1;
															out<<"Pomyslnie przypisano ucznia do klasy\n";
														}
														catch(std::string obj)
														{
															out<<obj<<"\n";
															break;
														}
														catch(...)
														{
															out<<"Cos poszlo nie tak\n";
															break;
														}
														break;
													}
												}
												if(failure2) out<<"Nie znaleziono takiej klasy\n";
											}
											else
											{
												out<<"Niepoprawne oznaczenie klasy\n";
											}
										}
										else
										{
											uczniowie[i].zmienKlase();
											out<<"Pomyslnie wypisano ucznia z klasy\n";
											changes=1;
										}
									}
									else
									{
										out<<"Niepoprawne polecenie\n";
									}
									break;
								}
							}
						}
						if(failure1) out<<"Nie znaleziono takiego ucznia\n";
						break;
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
			}
			default:
			{
				out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			}
		}
	}
}

void submenu_pracownicy(std::istream& in, std::ostream& out, lista<pracownik>& pracownicy, bool& changes)
{
	int option=0;
	while(true)
	{
		out<<"Zarzadzanie pracownikami\n";
		out<<"Wprowadz: \n";
		out<<"1 - aby dodac pracownika\n";
		out<<"2 - aby usunac pracownika\n";
		out<<"3 - aby wypisac pracownikow\n";
		out<<"4 - aby zmienic stanowisko pracownika\n";
		out<<"5 - aby zmienic pensje pracownika\n";
		out<<"0 - aby wrocic do poprzedniego menu\n";
		if(in>>option) ;
		else
		{
			out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			continue;
		}
		switch(option)
		{
			case 0: return;
			case 1:
			{
				std::string imie, nazwisko, stanowisko;
				out<<"Wprowadz imie pracownika\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko pracownika\n";
					if(in>>nazwisko)
					{
						out<<"Wprowadz stanowisko pracownika\n";
						if(in>>stanowisko)
						{
							if(stanowisko=="Nauczyciel")
							{
								out<<"Aby dodac nauczyciela nalezy skorzystac z innego menu\n";
								break;
							}
							pracownik pom(imie, nazwisko, stanowisko);
							pracownicy.push_back(pom);
							changes=1;
							out<<"Pomyslnie dodano pracownika\n";
							break;
						}
						else
						{
							out<<"Niepoprawne stanowisko\n";
							break;
						}
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
			}
			case 2:
			{
				std::string imie, nazwisko;
				bool failure=1;
				out<<"Wprowadz imie pracownika\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko pracownika\n";
					if(in>>nazwisko)
					{
						for(int i=1; i<=pracownicy.length(); i++)
						{
							if(nazwisko==pracownicy[i].zwrocNazwisko())
							{
								if(imie==pracownicy[i].zwrocImie())
								{
									failure=0;
									pracownicy.pop_at(i);
									changes=1;
									out<<"Pomyslnie usunieto pracownika\n";
									break;
								}
							}
						}
						if(failure) out<<"Nie znaleziono takiego pracownika\n";
						break;
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
			}
			case 3:
			{
				out<<"Spis pracownikow\n";
				for(int i=1; i<=pracownicy.length(); i++)
				{
					out<<pracownicy[i];
				}
				break;
			}
			case 4:
			{
				std::string imie, nazwisko, stanowisko;
				bool failure=1;
				out<<"Wprowadz imie pracownika\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko pracownika\n";
					if(in>>nazwisko)
					{
						for(int i=1; i<=pracownicy.length(); i++)
						{
							if(nazwisko==pracownicy[i].zwrocNazwisko())
							{
								if(imie==pracownicy[i].zwrocImie())
								{
									failure=0;
									out<<"Wprowadz nowe stanowisko\n";
									if(in>>stanowisko)
									{
										if(stanowisko=="Nauczyciel")
										{
											out<<"Aby dodac nauczyciela nalezy skorzystac z innego menu\n";
											break;
										}
										pracownicy[i].zmienStanowisko(stanowisko);
										changes=1;
										out<<"Pomyslnie zmieniono stanowisko pracownika\n";
										break;
									}
									else
									{
										out<<"Niepoprawne stanowisko\n";
										break;
									}
								}
							}
						}
						if(failure) out<<"Nie znaleziono takiego pracownika\n";
						break;
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
				break;
			}
			case 5:
			{
				std::string imie, nazwisko;
				double pensja;
				bool failure=1;
				out<<"Wprowadz imie pracownika\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko pracownika\n";
					if(in>>nazwisko)
					{
						for(int i=1; i<=pracownicy.length(); i++)
						{
							if(nazwisko==pracownicy[i].zwrocNazwisko())
							{
								if(imie==pracownicy[i].zwrocImie())
								{
									failure=0;
									out<<"Wprowadz nowa pensje\n";
									if(in>>pensja)
									{
										try
										{
											pracownicy[i].zmienPensje(pensja);
										}
										catch(std::string obj)
										{
											out<<obj<<"\n";
											break;
										}
										catch(...)
										{
											out<<"Cos poszlo nie tak\n";
											break;
										}
										changes=0;
										out<<"Pomyslnie zmieniono pensje pracownika\n";
										break;
									}
									else
									{
										out<<"Niepoprawna pensja\n";
										break;
									}
								}
							}
						}
						if(failure) out<<"Nie znaleziono takiego pracownika\n";
						break;
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
				break;
			}
			default:
			{
				out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			}
		}
	}
}

void submenu_nauczyciele(std::istream& in, std::ostream& out, lista<nauczyciel>& nauczyciele, bool& changes, lista<klasa>& klasy, lista<wychowawca>& wychowawcy, lista<planLekcji>& plany)
{
	int option=0;
	while(true)
	{
		out<<"Zarzadzanie nauczycielami\n";
		out<<"Wprowadz: \n";
		out<<"1 - aby dodac nauczyciela\n";
		out<<"2 - aby usunac nauczyciela\n";
		out<<"3 - aby wypisac nauczycieli\n";
		out<<"4 - aby zmienic pensje nauczyciela\n";
		out<<"0 - aby wrocic do poprzedniego menu\n";
		if(in>>option) ;
		else
		{
			out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			continue;
		}
		switch(option)
		{
			case 0: return;
			case 1:
			{
				std::string imie, nazwisko, przedmiot;
				out<<"Wprowadz imie nauczyciela\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko nauczyciela\n";
					if(in>>nazwisko)
					{
						out<<"Wprowadz przedmiot nauczany przez tego nauczyciela\n";
						if(in>>przedmiot)
						{
							nauczyciel pom(imie, nazwisko, przedmiot);
							nauczyciele.push_back(pom);
							changes=1;
							out<<"Pomyslnie dodano nauczyciela\n";
							break;
						}
						else
						{
							out<<"Niepoprawny przedmiot\n";
							break;
						}
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
			}
			case 2:
			{
				std::string imie, nazwisko;
				bool failure=1;
				int ilosc=0;
				out<<"Wprowadz imie nauczyciela\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko nauczyciela\n";
					if(in>>nazwisko)
					{
						for(int i=1; i<=nauczyciele.length(); i++)
						{
							if(nazwisko==nauczyciele[i].zwrocNazwisko())
							{
								if(imie==nauczyciele[i].zwrocImie())
								{
									failure=0;
									for(int j=1; j<=plany.length(); j++)
									{
										for(int x=0; x<5; x++)
										{
											for(int y=0; y<9; y++)
											{
												if(plany[j].wskazZajecia(x,y)->wskazNauczyciela()==&(nauczyciele[i]))
												{
													plany[j].zmienZajecia(x,y);
													ilosc++;
												}
											}
										}
									}
									nauczyciele.pop_at(i);
									changes=1;
									out<<"Pomyslnie usunieto nauczyciela, spowodowalo to usuniecie "<<ilosc<<" zajec przez niego prowadzonych\n";
									break;
								}
							}
						}
						if(failure)
						{
							for(int i=1; i<=wychowawcy.length(); i++)
							{
								if(nazwisko==wychowawcy[i].zwrocNazwisko())
								{
									if(imie==wychowawcy[i].zwrocImie())
									{
										failure=0;
										for(int j=1; j<=plany.length(); j++)
										{
											for(int x=0; x<5; x++)
											{
												for(int y=0; y<9; y++)
												{
													if(plany[j].wskazZajecia(x,y)->wskazNauczyciela()==&(wychowawcy[i]))
													{
														plany[j].zmienZajecia(x,y);
														ilosc++;
													}
												}
											}
										}
										if(wychowawcy[i].wskazKlase())
										{
											wychowawcy[i].wskazKlase()->usunWychowawce();
										}
										wychowawcy.pop_at(i);
										changes=1;
										out<<"Pomyslnie usunieto nauczyciela, spowodowalo to usuniecie "<<ilosc<<" zajec przez niego prowadzonych\n";
										break;
									}
								}
							}
						}
						if(failure) out<<"Nie znaleziono takiego nauczyciela\n";
						break;
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
			}
			case 3:
			{
				out<<"Spis nauczycieli\n";
				for(int i=1; i<=nauczyciele.length(); i++)
				{
					out<<nauczyciele[i];
				}
				for(int i=1; i<=wychowawcy.length(); i++)
				{
					out<<wychowawcy[i];
				}
				break;
			}
			case 4:
			{
				std::string imie, nazwisko;
				double pensja;
				bool failure=1;
				out<<"Wprowadz imie nauczyciela\n";
				if(in>>imie)
				{
					out<<"Wprowadz nazwisko nauczyciela\n";
					if(in>>nazwisko)
					{
						for(int i=1; i<=nauczyciele.length(); i++)
						{
							if(nazwisko==nauczyciele[i].zwrocNazwisko())
							{
								if(imie==nauczyciele[i].zwrocImie())
								{
									failure=0;
									out<<"Wprowadz nowa pensje\n";
									if(in>>pensja)
									{
										try
										{
											nauczyciele[i].zmienPensje(pensja);
										}
										catch(std::string obj)
										{
											out<<obj<<"\n";
											break;
										}
										catch(...)
										{
											out<<"Cos poszlo nie tak\n";
											break;
										}
										changes=0;
										out<<"Pomyslnie zmieniono pensje nauczyciela\n";
										break;
									}
									else
									{
										out<<"Niepoprawna pensja\n";
										break;
									}
								}
							}
						}
						if(failure)
						{
							for(int i=1; i<=wychowawcy.length(); i++)
						{
							if(nazwisko==wychowawcy[i].zwrocNazwisko())
							{
								if(imie==wychowawcy[i].zwrocImie())
								{
									failure=0;
									out<<"Wprowadz nowa pensje\n";
									if(in>>pensja)
									{
										try
										{
											wychowawcy[i].zmienPensje(pensja);
										}
										catch(std::string obj)
										{
											out<<obj<<"\n";
											break;
										}
										catch(...)
										{
											out<<"Cos poszlo nie tak\n";
											break;
										}
										changes=0;
										out<<"Pomyslnie zmieniono pensje nauczyciela\n";
										break;
									}
									else
									{
										out<<"Niepoprawna pensja\n";
										break;
									}
								}
							}
						}
						}
						if(failure) out<<"Nie znaleziono takiego nauczyciela\n";
						break;
					}
					else
					{
						out<<"Niepoprawne nazwisko\n";
						break;
					}
				}
				else
				{
					out<<"Niepoprawne imie\n";
					break;
				}
				break;
			}
			default:
			{
				out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			}
		}
	}
}

void MENU(std::istream& in, std::ostream& out, lista<klasa>& klasy, lista<sala>& sale, lista<uczen>& uczniowie, lista<pracownik>& pracownicy, lista<nauczyciel>& nauczyciele, lista<wychowawca>& wychowawcy, lista<planLekcji>& plany)
{
	srand(time(NULL));
	int option=0;
	bool changes=0;
	std::string nazwaPliku;
	while(true)
	{
		out<<"System zarzadzania szkola\n";
		out<<"Wprowadz: \n";
		out<<"1 - aby wczytac plik\n";
		out<<"2 - aby zapisac plik\n";
		out<<"3 - aby edytowac dane o salach\n";
		out<<"4 - aby edytowac dane o klasach\n";
		out<<"5 - aby edytowac dane o pracownikach\n";
		out<<"6 - aby edytowac dane o nauczycielach\n";
		out<<"7 - aby edytowac dane o uczniach\n";
		out<<"8 - aby policzyć koszt pensji pracownikow i nauczycieli\n";
		out<<"0 - aby zakonczyc dzialanie programu\n";
		if(in>>option) ;
		else 
		{
			out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			continue;
		}
		switch(option)
		{
			case 0:
			{
				return;
			}
			case 1:
			{
				if(changes)
				{
					bool pom=0;
					out<<"Czy chcesz zapisac obecny plik?\n 1 - tak 0 - nie\n";
					if(in>>pom)
					{
						if(pom)
						{
							saving(nazwaPliku, klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
							changes=0;
							out<<"Zapisywanie zakonczone\n";
						}
					}
					else
					{
						out<<"Niepoprawne polecenie\n";
						break;
					}
				}
				pozar(klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
				out<<"Wprowadz nazwe wczytywanego pliku\n";
				if(in>>nazwaPliku)
				{
					try {
						loading(nazwaPliku, klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
						out<<"Pomyslnie wczytano plik\n";
					}
					catch (...)
					{
						out<<"Wczytywany plik jest uszkodzony\n";
						pozar(klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
						changes=0;
						nazwaPliku.clear();
						break;
					}
					changes=0;
				}
				else
				{
					out<<"Niepoprawna nazwa pliku\n";
				}
				break;
			}
			case 2:
			{
				if(nazwaPliku.empty())
				{
					out<<"Wprowadz nazwe pliku: \n";
					if(in>>nazwaPliku)
					{
						saving(nazwaPliku, klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
						changes=0;
						out<<"Zapisywanie zakonczone\n";
					}
					else
					{
						out<<"Niepoprawna nazwa pliku\n";
					}
					break;
				}
				else
				{
					bool pom=0;
					out<<"Czy chcesz zapisac plik jako "<<nazwaPliku<<" 1- tak, 0 - nie?\n";
					if(in>>pom)
					{
						if(pom)
						{
							if(changes)
							{
								saving(nazwaPliku, klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
								changes=0;
								out<<"Zapisywanie zakonczone\n";
							}
							else
							{
								out<<"Nie dokonano zmian do zapisania\n";
							}
						}
						else
						{
							out<<"Wprowadz nazwe pliku: \n";
							if(in>>nazwaPliku)
							{
								saving(nazwaPliku, klasy, sale, uczniowie, pracownicy, nauczyciele, wychowawcy, plany);
								changes=0;
								out<<"Zapisywanie zakonczone\n";
							}
							else
							{
								out<<"Nepoprawna nazwa pliku\n";
							}
						}
					}
					else
					{
						out<<"Niepoprawne polecenie\n";
					}
					break;
				}
			}
			case 3:
			{
				submenu_sale(in, out, sale, changes, plany);
				break;
			}
			case 4:
			{
				submenu_klasy(in, out, klasy, changes, uczniowie, nauczyciele, wychowawcy, plany, sale);
				break;
			}
			case 5:
			{
				submenu_pracownicy(in, out, pracownicy, changes);
				break;
			}
			case 6:
			{
				submenu_nauczyciele(in, out, nauczyciele, changes, klasy, wychowawcy, plany);
				break;
			}
			case 7:
			{
				submenu_uczniowie(in, out, uczniowie, changes, klasy);
				break;
			}
			case 8:
			{
				double prac=0, naucz=0;
				for(int i=1; i<=pracownicy.length(); i++)
				{
					prac+=pracownicy[i].zwrocPensje();
				}
				for(int i=1; i<=nauczyciele.length(); i++)
				{
					naucz+=nauczyciele[i].zwrocPensje();
				}
				for(int i=1; i<=wychowawcy.length(); i++)
				{
					naucz+=wychowawcy[i].zwrocPensje();
				}
				out<<"Pensje pracownikow wynosza "<<prac<<" zl, a nauczycieli "<<naucz<<" zl\n";
				break;
			}
			default:
			{
				out<<"Niezrozumiale polecenie, sprobuj ponownie\n";
			}
		}
		
	}
}
