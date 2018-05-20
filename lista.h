#pragma once
#include<iostream>

template <class T>
class lista
{
	template <class Type=T>
	struct el
	{
		Type wartosc;
		el* poprzednik;
		el* nastepnik;
		el(const Type& w): wartosc(w) {}
	};
	int size;
	el<T>* pierwszy;
	el<T>* ostatni;
public:
	lista();
	lista(const lista&);
	lista& operator=(const lista&);
	~lista();
	int length() const;
	void push_top(const T&);
	void push_back(const T&);
	void pop_top();
	void pop_back();
	void pop_at(const int&);
	T& operator[](const int&);
	const T& zwrot(const int&) const;
};

template <class T>
lista<T>::lista()
{
	size=0;
	pierwszy=nullptr;
	ostatni=nullptr;
}

template <class T>
int lista<T>::length() const
{return size;}

template <class T>
void lista<T>::push_top(const T& w)
{
	size++;
	el<T>* pom=new el<T>(w);
	pom->poprzednik=nullptr;
	pom->nastepnik=pierwszy;
	if(pierwszy)
	{
		pierwszy->poprzednik=pom;
		pierwszy=pom;
	}
	else
	{
		pierwszy=pom;
		ostatni=pierwszy;
	}
}

template <class T>
void lista<T>::push_back(const T& w)
{
	size++;
	el<T>* pom=new el<T>(w);
	pom->poprzednik=ostatni;
	pom->nastepnik=nullptr;
	if(ostatni)
	{
		ostatni->nastepnik=pom;
		ostatni=pom;
	}
	else
	{
		pierwszy=pom;
		ostatni=pom;
	}
}

template <class T>
void lista<T>::pop_top()
{
	if(pierwszy)
	{
		size--;
		if(pierwszy==ostatni)
		{
			delete pierwszy;
			pierwszy=nullptr;
			ostatni=nullptr;
		}
		else
		{
			el<T>* pom=pierwszy->nastepnik;
			delete pierwszy;
			pierwszy=pom;
			pierwszy->poprzednik=nullptr;
		}
	}
}

template <class T>
void lista<T>::pop_back()
{
	if(ostatni)
	{
		size--;
		if(pierwszy==ostatni)
		{
			delete pierwszy;
			pierwszy=nullptr;
			ostatni=nullptr;
		}
		else
		{
			el<T>* pom=ostatni->poprzednik;
			delete ostatni;
			ostatni=pom;
			ostatni->nastepnik=nullptr;
		}
	}
}

template <class T>
void lista<T>::pop_at(const int& n)
{
	//wyjatki
	if(n>size || n<1) throw std::string("Lista nie posiada tylu elementow");
	if(n==1)
	{
		pop_top();
	}
	else
	{
		if(n==size)
		{
			pop_back();
		}
		else
		{
			size--;
			int i=1;
			el<T>* pom=pierwszy;
			while (i<n)
			{
				pom=pom->nastepnik;
				i++;
			}
			pom->poprzednik->nastepnik=pom->nastepnik;
			pom->nastepnik->poprzednik=pom->poprzednik;
			delete pom;
		}
	}
}

template <class T>
T& lista<T>::operator[](const int& n)
{
	//wyjatki
	if(n>size || n<1) throw std::string("Lista nie posiada tylu elementow");
	int i=1;
	el<T>* pom=pierwszy;
	while (i<n)
	{
		pom=pom->nastepnik;
		i++;
	}
	return pom->wartosc;
}

template <class T>
const T& lista<T>::zwrot(const int& n) const
{
	//wyjatki
	if(n>size || n<1) throw std::string("Lista nie posiada tylu elementow");
	int i=1;
	el<T>* pom=pierwszy;
	while (i<n)
	{
		pom=pom->nastepnik;
		i++;
	}
	return pom->wartosc;
}

template <class T>
lista<T>::lista(const lista<T>& l)
{
	size=l.size;
	for (int i=0; i<size; i++)
	{
		push_back(l[i]);
	}
}

template <class T>
lista<T>& lista<T>::operator=(const lista<T>& l)
{
	if(l!=this)
	{
		size=l.size;
	for (int i=0; i<size; i++)
		{
			push_back(l[i]);
		}
	}
}

template <class T>
lista<T>::~lista()
{
	while(pierwszy)
	{
		pop_top();
	}
}
