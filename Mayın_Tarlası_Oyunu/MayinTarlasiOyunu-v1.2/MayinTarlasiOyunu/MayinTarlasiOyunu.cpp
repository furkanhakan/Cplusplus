// MayinTarlasiOyunu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <locale.h>
#include <time.h>
#include <string>
#include "ConsoleColor.h"
#include <stdlib.h> //int to string and string to int

using namespace std;

int etraf[2][8] = { 	{-1,-0,+1,-1,-0,+1,-1,+1},
						{-1,-1,-1,+1,+1,+1,-0,-0}	};
int skor=0;//yazýlacak skor
int skor2=0;//dosyadan çekilen skor
string bolum1,bolum2;

//Kolay Bölüm - 10x10 luk matris 10 mayýn

struct kolay
{
			string yer[12][12];
			string yeracilan[12][12];
			int acilacaklar[500];
			int acilacaksayisi;
			int acilankutu;
			int nerdeyim;
			void MayinTarlasi();
			void Oyun();
			void Etrafiniacma(int nerde);
			void Ekle(int y, int x);
}k;
void kolay::MayinTarlasi()
{
	int bomba[10];
	int sorgulama[10];
	int x,y;
	int tekrar;
	int varmiyokmu;
	int gecici;
	int sayi;
	// Bomba yerlerini rastgele olarak ayarlama
	for (int i = 0; i < 10; i++)
	{
		do
		{
			varmiyokmu=0;
			sayi=rand()%100;
			for (int j = 0; j < i; j++)
			{
				if (sayi==sorgulama[j])
				{
					varmiyokmu++;
				}
			}
			if (varmiyokmu>0)
			{
				tekrar=1;
			}
			else
			{
				bomba[i]=sayi;
				sorgulama[i]=sayi;
				tekrar=0;
			}
		} while (tekrar==1);
	}

	// Bombalarý yerleþtirme
	for (int i = 0; i < 10; i++)
	{
		y=(bomba[i]/10)+1;
		x=(bomba[i]%10)+1;
		yer[y][x]='*';
	}

	//0 larý yerleþtirme
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (yer[i][j]!="*")
			{
				yer[i][j]="0";
			}
		}
	}
	
	//Bomba etrafý sayma
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (yer[i][j]=="*")
			{
				for (int k = i-1; k <= i+1; k++)
				{
					for (int l = j-1; l <= j+1; l++)
					{
						if (yer[k][l]!="*")
						{
							gecici=atoi(yer[k][l].c_str());//string ifadeyi inte çevirme
							gecici++;
							yer[k][l]=to_string(gecici);//int ifadeyi stringe çevirme
						}
					}
				}
			}
		}
	}


	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (i==0||i==11||j==0||j==11)
			{
				yer[i][j]="6";
			}
		}
	}
}
void kolay::Oyun()
{
	nerdeyim=0;
	acilankutu=0;
	acilacaksayisi=0;
	skor=0;
	MayinTarlasi();
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			yeracilan[i][j]="X";
		}
	}
	int acx,acy;

		for (int i = 1; i < 11; i++)
		{
			for (int j = 1; j < 11; j++)
			{
				if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
			}
			cout<<endl;
		}
			cout<<"Skorunuz : "<<skor<<endl;
		while (acilankutu<90)
	{
		cout<<"Açýlacak Kutu Kordinatý(x) : ";
		cin>>acx;
		cout<<"Açýlacak Kutu Kordinatý(y) : ";
		cin>>acy;
		if (acx>0 && acx<11 && acy>0 && acy<11)
		{
			if (yeracilan[acy][acx]=="X")
			{
				if (yer[acy][acx]=="*")
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu=100;
				}
				else if (atoi(yer[acy][acx].c_str())>0)
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu++;
					skor+=atoi(yer[acy][acx].c_str());
				}
				else if (atoi(yer[acy][acx].c_str())==0)
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu++;
					Ekle(acy,acx);

					while (nerdeyim < acilacaksayisi)
					{
						Etrafiniacma(nerdeyim);
					}
				}
				system("CLS");
				for (int i = 1; i < 11; i++)
				{
					for (int j = 1; j < 11; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
					cout<<"Skorunuz : "<<skor<<endl;
			}
			else
			{
				cout<<"Açýlmýþ kare kordinatýný girdiniz..!";
				system("pause");
			system("CLS");
			for (int i = 1; i < 11; i++)
				{
					for (int j = 1; j < 11; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
				cout<<"Skorunuz : "<<skor<<endl;
			}
		}
		else
		{
			cout<<"Yanlýþ Kordinat Girdiniz..!";
			system("pause");
			system("CLS");
			for (int i = 1; i < 11; i++)
				{
					for (int j = 1; j < 11; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
				cout<<"Skorunuz : "<<skor<<endl;
		}
	}
	if (acilankutu==100)
	{
		system("CLS");
		for (int i = 1; i < 11; i++)
		{
			for (int j = 1; j < 11; j++)
			{
				if (yer[i][j]=="*")
				{
					yeracilan[i][j]=yer[i][j];
				}
			}
		}
		for (int i = 1; i < 11; i++)
				{
					for (int j = 1; j < 11; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							if (yeracilan[i][j]!="*")
							{
								cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
							}
							else
							{
								cout<<red<<" "<<yeracilan[i][j]<<" "<<white<<"|";
							}
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
		cout<<"Oyunu Kaybettiniz..."<<endl;
	}
	if (acilankutu==90)
	{
		cout<<"Kazandýnýz...";
		skor=skor*2;
	}
	cout<<"Skorunuz : "<<skor<<endl;
	fstream puan;
	fstream puandegisim;
	puan.open("puan.txt",ios::out|ios::in|ios::app);
	puandegisim.open("puandegis.txt",ios::out|ios::in|ios::app);
	for (int i = 0; i < 3; i++)
	{
		puan>>bolum1>>bolum2>>skor2;
		if (bolum1=="Kolay")
		{
			if (skor2>skor)
			{
				puandegisim<<"Kolay Bölüm "<<skor2<<endl;
			}
			else
			{
				puandegisim<<"Kolay Bölüm "<<skor<<endl;
			}
		}
		else
		{
			puandegisim<<bolum1<<" "<<bolum2<<" "<<skor2<<endl;
		}
	}
	puan.close();
	puandegisim.close();
	remove("puan.txt");
	rename("puandegis.txt","puan.txt");
		
}
void kolay::Etrafiniacma(int nerde)
{
	int x,y;
	for (int i = 0; i < 8; i++)
	{
		y=acilacaklar[nerde]+etraf[0][i];
		x=acilacaklar[nerde+1]+etraf[1][i];
		if (yeracilan[y][x]=="X")
		{
			yeracilan[y][x]=yer[y][x];
			acilankutu++;
			skor+=atoi(yer[y][x].c_str());
			if (atoi(yer[y][x].c_str())==0)
			{
				Ekle(y,x);
			}
		}
			
			
		
		
	}
	nerdeyim+=2;
}
void kolay::Ekle(int y, int x)
{
	for (int i = 0; i < acilacaksayisi; i++)
	{
		if(acilacaklar[i]==y && acilacaklar[i+1]==x)
		{
			continue;
		}
	}
	acilacaklar[acilacaksayisi]=y;
	acilacaksayisi++;
	acilacaklar[acilacaksayisi]=x;
	acilacaksayisi++;
}

//Orta Bölüm - 16x16 lýk matris 40 Mayýn

struct orta
{
			string yer[18][18];
			string yeracilan[18][18];
			int acilacaklar[500];
			int acilacaksayisi;
			int acilankutu;
			int nerdeyim;
			void MayinTarlasi();
			void Oyun();
			void Etrafiniacma(int nerde);
			void Ekle(int y, int x);
}o;
void orta::MayinTarlasi()
{
	int bomba[40];
	int sorgulama[40];
	int x,y;
	int tekrar;
	int varmiyokmu;
	int gecici;
	int sayi;
	// Bomba yerlerini rastgele olarak ayarlama
	for (int i = 0; i < 40; i++)
	{
		do
		{
			varmiyokmu=0;
			sayi=rand()%160;
			for (int j = 0; j < i; j++)
			{
				if (sayi==sorgulama[j])
				{
					varmiyokmu++;
				}
			}
			if (varmiyokmu>0)
			{
				tekrar=1;
			}
			else
			{
				bomba[i]=sayi;
				sorgulama[i]=sayi;
				tekrar=0;
			}
		} while (tekrar==1);
	}

	// Bombalarý yerleþtirme
	for (int i = 0; i < 40; i++)
	{
		x=(bomba[i]/10)+1;
		y=(bomba[i]%16)+1;
		yer[x][y]='*';
	}

	//0 larý yerleþtirme
	for (int i = 1; i < 17; i++)
	{
		for (int j = 1; j < 17; j++)
		{
			if (yer[i][j]!="*")
			{
				yer[i][j]="0";
			}
		}
	}
	
	//Bomba etrafý sayma
	for (int i = 1; i < 17; i++)
	{
		for (int j = 1; j < 17; j++)
		{
			if (yer[i][j]=="*")
			{
				for (int k = i-1; k <= i+1; k++)
				{
					for (int l = j-1; l <= j+1; l++)
					{
						if (yer[k][l]!="*")
						{
							gecici=atoi(yer[k][l].c_str());//string ifadeyi inte çevirme
							gecici++;
							yer[k][l]=to_string(gecici);//int ifadeyi stringe çevirme
						}
					}
				}
			}
		}
	}


	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (i==0||i==17||j==0||j==17)
			{
				yer[i][j]="6";
			}
		}
	}
}
void orta::Oyun()
{
	nerdeyim=0;
	acilankutu=0;
	acilacaksayisi=0;
	skor=0;
	MayinTarlasi();
	for (int i = 1; i < 17; i++)
	{
		for (int j = 1; j < 17; j++)
		{
			yeracilan[i][j]="X";
		}
	}
	int acx,acy;

		for (int i = 1; i < 17; i++)
		{
			for (int j = 1; j < 17; j++)
			{
				if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
			}
			cout<<endl;
		}
			cout<<"Skorunuz : "<<skor<<endl;
		while (acilankutu<216)
	{
		cout<<"Açýlacak Kutu Kordinatý(x) : ";
		cin>>acx;
		cout<<"Açýlacak Kutu Kordinatý(y) : ";
		cin>>acy;
		if (acx>0 && acx<17 && acy>0 && acy<17)
		{
			if (yeracilan[acy][acx]=="X")
			{
				if (yer[acy][acx]=="*")
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu=256;
				}
				else if (atoi(yer[acy][acx].c_str())>0)
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu++;
					skor+=atoi(yer[acy][acx].c_str());
				}
				else if (atoi(yer[acy][acx].c_str())==0)
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu++;
					Ekle(acy,acx);

					while (nerdeyim < acilacaksayisi)
					{
						Etrafiniacma(nerdeyim);
					}
				}
				system("CLS");
				for (int i = 1; i < 17; i++)
				{
					for (int j = 1; j < 17; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
					cout<<"Skorunuz : "<<skor<<endl;
			}
			else
			{
				cout<<"Açýlmýþ kare kordinatýný girdiniz..!";
				system("pause");
			system("CLS");
			for (int i = 1; i < 17; i++)
				{
					for (int j = 1; j < 17; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
				cout<<"Skorunuz : "<<skor<<endl;
			}
		}
		else
		{
			cout<<"Yanlýþ Kordinat Girdiniz..!";
			system("pause");
			system("CLS");
			for (int i = 1; i < 17; i++)
				{
					for (int j = 1; j < 17; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
				cout<<"Skorunuz : "<<skor<<endl;
		}
	}
	if (acilankutu==256)
	{
		system("CLS");
		for (int i = 1; i < 17; i++)
		{
			for (int j = 1; j < 17; j++)
			{
				if (yer[i][j]=="*")
				{
					yeracilan[i][j]=yer[i][j];
				}
			}
		}
		for (int i = 1; i < 17; i++)
				{
					for (int j = 1; j < 17; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							if (yeracilan[i][j]!="*")
							{
								cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
							}
							else
							{
								cout<<red<<" "<<yeracilan[i][j]<<" "<<white<<"|";
							}
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
		cout<<"Oyunu Kaybettiniz..."<<endl;
	}
	if (acilankutu==216)
	{
		cout<<"Kazandýnýz...";
		skor=skor*2;
	}
		cout<<"Skorunuz : "<<skor<<endl;
		fstream puan;
	fstream puandegisim;
	puan.open("puan.txt",ios::out|ios::in|ios::app);
	puandegisim.open("puandegis.txt",ios::out|ios::in|ios::app);
	for (int i = 0; i < 3; i++)
	{
		puan>>bolum1>>bolum2>>skor2;
		if (bolum1=="Orta")
		{
			if (skor2>skor)
			{
				puandegisim<<"Orta Bölüm "<<skor2<<endl;
			}
			else
			{
				puandegisim<<"Orta Bölüm "<<skor<<endl;
			}
		}
		else
		{
			puandegisim<<bolum1<<" "<<bolum2<<" "<<skor2<<endl;
		}
	}
	puan.close();
	puandegisim.close();
	remove("puan.txt");
	rename("puandegis.txt","puan.txt");
}
void orta::Etrafiniacma(int nerde)
{
	int x,y;
	for (int i = 0; i < 8; i++)
	{
		y=acilacaklar[nerde]+etraf[0][i];
		x=acilacaklar[nerde+1]+etraf[1][i];
		if (yeracilan[y][x]=="X")
		{
			yeracilan[y][x]=yer[y][x];
			acilankutu++;
			skor+=atoi(yer[y][x].c_str());
			if (atoi(yer[y][x].c_str())==0)
			{
				Ekle(y,x);
			}
		}
			
			
		
		
	}
	nerdeyim+=2;
}
void orta::Ekle(int y, int x)
{
	for (int i = 0; i < acilacaksayisi; i++)
	{
		if(acilacaklar[i]==y && acilacaklar[i+1]==x)
		{
			continue;
		}
	}
	acilacaklar[acilacaksayisi]=y;
	acilacaksayisi++;
	acilacaklar[acilacaksayisi]=x;
	acilacaksayisi++;
}

//Zor Bölüm - 16x24 lýk matris 80 Mayýn

struct zor
{
			string yer[18][26];
			string yeracilan[18][26];
			int acilacaklar[500];
			int acilacaksayisi;
			int acilankutu;
			int nerdeyim;
			void MayinTarlasi();
			void Oyun();
			void Etrafiniacma(int nerde);
			void Ekle(int y, int x);
}z;
void zor::MayinTarlasi()
{
	int bomba[80];
	int sorgulama[80];
	int x,y;
	int tekrar;
	int varmiyokmu;
	int gecici;
	int sayi;
	// Bomba yerlerini rastgele olarak ayarlama
	for (int i = 0; i < 80; i++)
	{
		do
		{
			varmiyokmu=0;
			sayi=rand()%160;
			for (int j = 0; j < i; j++)
			{
				if (sayi==sorgulama[j])
				{
					varmiyokmu++;
				}
			}
			if (varmiyokmu>0)
			{
				tekrar=1;
			}
			else
			{
				bomba[i]=sayi;
				sorgulama[i]=sayi;
				tekrar=0;
			}
		} while (tekrar==1);
	}

	// Bombalarý yerleþtirme
	for (int i = 0; i < 80; i++)
	{
		y=(bomba[i]/10)+1;
		x=(bomba[i]%24)+1;
		yer[y][x]='*';
	}

	//0 larý yerleþtirme
	for (int i = 1; i < 17; i++)
	{
		for (int j = 1; j < 25; j++)
		{
			if (yer[i][j]!="*")
			{
				yer[i][j]="0";
			}
		}
	}
	
	//Bomba etrafý sayma
	for (int i = 1; i < 17; i++)
	{
		for (int j = 1; j < 25; j++)
		{
			if (yer[i][j]=="*")
			{
				for (int k = i-1; k <= i+1; k++)
				{
					for (int l = j-1; l <= j+1; l++)
					{
						if (yer[k][l]!="*")
						{
							gecici=atoi(yer[k][l].c_str());//string ifadeyi inte çevirme
							gecici++;
							yer[k][l]=to_string(gecici);//int ifadeyi stringe çevirme
						}
					}
				}
			}
		}
	}


	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (i==0||i==17||j==0||j==25)
			{
				yer[i][j]="6";
			}
		}
	}
}
void zor::Oyun()
{
	nerdeyim=0;
	acilankutu=0;
	acilacaksayisi=0;
	skor=0;
	MayinTarlasi();
	for (int i = 1; i < 17; i++)
	{
		for (int j = 1; j < 25; j++)
		{
			yeracilan[i][j]="X";
		}
	}
	int acx,acy;

		for (int i = 1; i < 17; i++)
		{
			for (int j = 1; j < 25; j++)
			{
				if (yeracilan[i][j]!="X")
				{
					cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
				}
				else
				{
					cout<<" "<<yeracilan[i][j]<<" "<<"|";
				}
				
			}
			cout<<endl;
		}
			cout<<"Skorunuz : "<<skor<<endl;

		while (acilankutu<304)
	{
		cout<<"Açýlacak Kutu Kordinatý(x) : ";
		cin>>acx;
		cout<<"Açýlacak Kutu Kordinatý(y) : ";
		cin>>acy;
		if (acx>0 && acx<25 && acy>0 && acy<17)
		{
			if (yeracilan[acy][acx]=="X")
			{
				if (yer[acy][acx]=="*")
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu=384;
				}
				else if (atoi(yer[acy][acx].c_str())>0)
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu++;
					skor+=atoi(yer[acy][acx].c_str());
				}
				else if (atoi(yer[acy][acx].c_str())==0)
				{
					yeracilan[acy][acx]=yer[acy][acx];
					acilankutu++;
					Ekle(acy,acx);

					while (nerdeyim < acilacaksayisi)
					{
						Etrafiniacma(nerdeyim);
					}
				}
				system("CLS");
				for (int i = 1; i < 17; i++)
				{
					for (int j = 1; j < 25; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
					cout<<"Skorunuz : "<<skor<<endl;
			}
			else
			{
				cout<<"Açýlmýþ kare kordinatýný girdiniz..!";
				system("pause");
			system("CLS");
			for (int i = 1; i < 17; i++)
				{
					for (int j = 1; j < 25; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
				cout<<"Skorunuz : "<<skor<<endl;
			}
		}
		else
		{
			cout<<"Yanlýþ Kordinat Girdiniz..!";
			system("pause");
			system("CLS");
			for (int i = 1; i < 17; i++)
				{
					for (int j = 1; j < 25; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
				cout<<"Skorunuz : "<<skor<<endl;
		}
	}
	if (acilankutu==384)
	{
		system("CLS");
		for (int i = 1; i < 17; i++)
		{
			for (int j = 1; j < 25; j++)
			{
				if (yer[i][j]=="*")
				{
					yeracilan[i][j]=yer[i][j];
				}
			}
		}
		for (int i = 1; i < 17; i++)
				{
					for (int j = 1; j < 25; j++)
					{
						if (yeracilan[i][j]!="X")
						{
							if (yeracilan[i][j]!="*")
							{
								cout<<green<<" "<<yeracilan[i][j]<<" "<<white<<"|";
							}
							else
							{
								cout<<red<<" "<<yeracilan[i][j]<<" "<<white<<"|";
							}
						}
						else
						{
							cout<<" "<<yeracilan[i][j]<<" "<<"|";
						}
					}
				cout<<endl;
				}
		cout<<"Oyunu Kaybettiniz..."<<endl;
	}
	if (acilankutu==304)
	{
		cout<<"Kazandýnýz...";
		skor=skor*2;
	}
		cout<<"Skorunuz : "<<skor<<endl;
	fstream puan;
	fstream puandegisim;
	puan.open("puan.txt",ios::out|ios::in|ios::app);
	puandegisim.open("puandegis.txt",ios::out|ios::in|ios::app);
	for (int i = 0; i < 3; i++)
	{
		puan>>bolum1>>bolum2>>skor2;
		if (bolum1=="Zor")
		{
			if (skor2>skor)
			{
				puandegisim<<"Zor Bölüm "<<skor2<<endl;
			}
			else
			{
				puandegisim<<"Zor Bölüm "<<skor<<endl;
			}
		}
		else
		{
			puandegisim<<bolum1<<" "<<bolum2<<" "<<skor2<<endl;
		}
	}
	puan.close();
	puandegisim.close();
	remove("puan.txt");
	rename("puandegis.txt","puan.txt");
}
void zor::Etrafiniacma(int nerde)
{
	int x,y;
	for (int i = 0; i < 8; i++)
	{
		y=acilacaklar[nerde]+etraf[0][i];
		x=acilacaklar[nerde+1]+etraf[1][i];
		if (yeracilan[y][x]=="X")
		{
			yeracilan[y][x]=yer[y][x];
			acilankutu++;
			skor+=atoi(yer[y][x].c_str());
			if (atoi(yer[y][x].c_str())==0)
			{
				Ekle(y,x);
			}
		}
			
			
		
		
	}
	nerdeyim+=2;
}
void zor::Ekle(int y, int x)
{
	for (int i = 0; i < acilacaksayisi; i++)
	{
		if(acilacaklar[i]==y && acilacaklar[i+1]==x)
		{
			continue;
		}
	}
	acilacaklar[acilacaksayisi]=y;
	acilacaksayisi++;
	acilacaklar[acilacaksayisi]=x;
	acilacaksayisi++;
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"Turkish");
	srand(time(NULL));
	int secim,zorluksecim,silsecim;

	do
	{
	system("CLS");
	cout<<"1 - YENÝ OYUN"<<endl;
	cout<<"2 - SKOR TABELASI"<<endl;
	cout<<"3 - SIFIRLA"<<endl;
	cout<<"Seçiminiz ->"; cin>>secim;
	
		if (secim==1)
		{
			do
			{
				system("CLS");
				cout<<"1 - Kolay Bölüm(10x10)"<<endl;
				cout<<"2 - Orta Bölüm(16x16)"<<endl;
				cout<<"3 - Zor Bölüm(16x24)"<<endl;
				cout<<"Seçiminiz ->"; cin>>zorluksecim;
				if (zorluksecim==1)
				{
					system("CLS");
					k.Oyun();
				}
				else if (zorluksecim==2)
				{
					system("CLS");
					o.Oyun();
				}
				else if(zorluksecim==3)
				{
					system("CLS");
					z.Oyun();
				}
				else
				{
					cout<<"Yanlýþ Seçim Yaptýnýz..!";
					system("Pause");
				}
			} while (zorluksecim>3 || zorluksecim<1);
		}
		if (secim==2)
		{
			fstream puan;
			puan.open("puan.txt",ios::out|ios::in|ios::app);
			for (int i = 0; i < 3; i++)
			{
				puan>>bolum1>>bolum2>>skor;
				cout<<bolum1<<" "<<bolum2<<" "<<skor<<endl;
			}
			puan.close();
	
		}
		if (secim==3)
		{
				fstream dosya;
				dosya.open("puan.txt",ios::out|ios::in|ios::app);
				fstream dosyasil;
				dosyasil.open("puansil.txt",ios::in|ios::out|ios::app);
				system("CLS");
				cout<<"1 - Kolay Bölüm(10x10)"<<endl;
				cout<<"2 - Orta Bölüm(16x16)"<<endl;
				cout<<"3 - Zor Bölüm(16x24)"<<endl;
				cout<<"4 - TÜMÜMNÜ SIFIRLA"<<endl;
				cout<<"Seçiminiz ->"; cin>>silsecim;
				switch (silsecim)
				{
				case 1:
					while (dosya>>bolum1>>bolum2>>skor)
					   {
						   if (bolum1=="Kolay")
						   {
							   dosyasil<<bolum1<<" "<<bolum2<<" "<<"0"<<endl;
						   }
						   else
						   {
							   dosyasil<<bolum1<<" "<<bolum2<<" "<<skor<<endl;
						   }
					   }
					break;
				case 2:
					while (dosya>>bolum1>>bolum2>>skor)
					   {
						   if (bolum1=="Orta")
						   {
							   dosyasil<<bolum1<<" "<<bolum2<<" "<<"0"<<endl;
						   }
						   else
						   {
							   dosyasil<<bolum1<<" "<<bolum2<<" "<<skor<<endl;
						   }
					   }
					break;
				case 3:
					while (dosya>>bolum1>>bolum2>>skor)
					   {
						   if (bolum1=="Zor")
						   {
							   dosyasil<<bolum1<<" "<<bolum2<<" "<<"0"<<endl;
						   }
						   else
						   {
							   dosyasil<<bolum1<<" "<<bolum2<<" "<<skor<<endl;
						   }
					   }
					break;
				case 4:
					while (dosya>>bolum1>>bolum2>>skor)
					   {	
							   dosyasil<<bolum1<<" "<<bolum2<<" "<<"0"<<endl;
					   }
					break;
				default:cout<<"Yanlýþ seçim yaptýnýz.";
					break;
				}
				dosya.close();
				dosyasil.close();
				remove("puan.txt");
				rename("puansil.txt","puan.txt");
		}
	} while (secim>3 || secim<1);

	return 0;
}
