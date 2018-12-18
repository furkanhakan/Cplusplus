// cift_bagli_siralama.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <locale.h>

using namespace std;

struct node
{
	int data;
	node *next,*prev;
};

node *ekleme(node *r,int eklenecek_sayi){

	bool kontrol=true;
	//Eðer liste boþsa
	if (r==NULL)
	{
		r=new node;
		r->data=eklenecek_sayi;
		r->next=NULL;
		r->prev=NULL;
	}
	//Eðer liste doluysa
	else
	{
		node *yrd;
		yrd = r;
		//Eðer listede 1 eleman varsa
		if (yrd->next==NULL)
		{
			//Baþa ekleme
			if (yrd->data > eklenecek_sayi)
			{
				yrd->prev=new node;
				yrd->prev->data=eklenecek_sayi;
				yrd->prev->next=yrd;
				yrd->prev->prev=NULL;
				r=yrd->prev;
				yrd=NULL;
				delete yrd;
			}
			//Sona ekleme
			else
			{
				yrd->next=new node;
				yrd->next->data=eklenecek_sayi;
				yrd->next->prev=yrd;
				yrd->next->next=NULL;
				yrd=NULL;
				delete yrd;
			}
			
		}
		//Eðer listede 1 den fazla eleman varsa
		else
		{
			kontrol=true;
			while (kontrol)
			{
				if (yrd->next->next==NULL)
				{
					kontrol=false;
				}

				if (yrd->data < eklenecek_sayi)
				{
					if (yrd->next->data < eklenecek_sayi)
					{
						if (yrd->next->next==NULL)
						{

						}
						else
							yrd=yrd->next;
					}
					else
					{
						node *tmp;
						tmp=yrd->next;
						yrd->next=NULL;
						yrd->next=new node;
						yrd->next->data=eklenecek_sayi;
						yrd->next->prev=yrd;
						yrd->next->next=tmp;
						tmp=NULL;
						delete tmp;
						kontrol=false;
					}
					
				}
				else
				{
					yrd->prev=new node;
					yrd->prev->data=eklenecek_sayi;
					yrd->prev->next=yrd;
					yrd->prev->prev=NULL;
					r=yrd->prev;
					yrd=r;
					kontrol=false;

				}
				

			}
			if (yrd->next->next==NULL)
			{
				if (yrd->next->data < eklenecek_sayi)
				{
					yrd=yrd->next;
					yrd->next=new node;
					yrd->next->data=eklenecek_sayi;
					yrd->next->prev=yrd;
					yrd->next->next=NULL;
					yrd=NULL;
					delete yrd;
				}
				else if (yrd->next->data > eklenecek_sayi)			
				{
					node *tmp;
					tmp=yrd->next;
					yrd->next=NULL;
					yrd->next=new node;
					yrd->next->data=eklenecek_sayi;
					yrd->next->prev=yrd;
					yrd->next->next=tmp;
					yrd=tmp=NULL;
					delete tmp,yrd;
				}
			}
			else
			{
				yrd=NULL;
				
				delete yrd;
			}

		}
		
		
	}
	
	return r;

}

void yazdir(node *r){

	node *yrd;
	yrd=r;
	bool kontrol=true;
	while (kontrol)
	{
		cout<<yrd->data<<"  ";
		if (yrd->next==NULL)
			kontrol=false;
		else
			yrd=yrd->next;
		
	}
	
	yrd=NULL;
	delete yrd;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"Turkish");
	int sayi;
	char secim;
	node *root;
	root=NULL;
	do
	{
		cout<<"Sayi giriniz : ";
		cin>>sayi;
		root = ekleme(root,sayi);

		cout<<"Devam Etmek Istiyor musunuz(E-e)";
		cin>>secim;
		yazdir(root);
		cout<<endl;
		system("Pause");
		system("CLS");
	} while (secim=='E' || secim=='e');
	
	
	return 0;
}

