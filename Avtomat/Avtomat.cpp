// Avtomat.cpp : Defines the entry point for the console application.
//

/* Karmen Unuk
OA_N0000819_sklop3_naloga2: Avtomat za vraèanje kovancev */

/* Napišite program, ki reši problem avtomata za vraèanje kovancev, kjer so zaloge kovancev
   v naprej znane. */


#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class CKovanec
{
public:
	CKovanec(int aV, int aZ);
	~CKovanec(void);
	int zaloga;
	int vrednost;
};

class CVracanje
{
public:
	CVracanje(int aV, int aDC);
	~CVracanje(void);
	int vplacilo;
	int DejanskaC;
};

class CAvtomat
{
public:
	CAvtomat(void);
	~CAvtomat(void);
	vector<CKovanec*> kovanci;
	vector<CKovanec*> vracilo;
	void Vrni(CVracanje* aP);
	void TvoriVektorKovanci(CKovanec* aK);
	void TvoriVektorVracilo(CKovanec* aK);
	int DolociStKovancev(int aV, int aVr);
	void IzpisVektorjaVracilo();
	void IzpisVektorjaKovanci();
	void UrediVektorVracilo();
};

CKovanec::CKovanec(int aV, int aZ)
{
	zaloga=aZ;
	vrednost=aV;
}

CKovanec::~CKovanec(void)
{
}

CVracanje::CVracanje(int aV, int aDC)
{
	vplacilo = aV;
	DejanskaC = aDC;
}

CVracanje::~CVracanje(void)
{
}

CAvtomat::CAvtomat(void)
{
	vector<CKovanec* > kovanci;
	vector<CKovanec* > vracilo;
}

CAvtomat::~CAvtomat(void)
{
}

void CAvtomat:: TvoriVektorKovanci(CKovanec * aK)
{
	kovanci.push_back(aK);
}

void CAvtomat:: TvoriVektorVracilo(CKovanec * aK)
{
	vracilo.push_back(aK);
}

void CAvtomat::Vrni(CVracanje* aP)
{
	int aV = (aP->vplacilo)-(aP->DejanskaC);
	for(int i = kovanci.size()-1; i>=0 ; i--){
		int aDo = DolociStKovancev(aV, kovanci.at(i)->vrednost);
		if(kovanci.at(i)->zaloga < aDo){
			while(kovanci.at(i)->zaloga < aDo){
				aDo--;
			}
		}
			CKovanec* aPr = new CKovanec(kovanci.at(i)->vrednost, aDo);
			TvoriVektorVracilo(aPr);
			aV = aV-((aPr->vrednost)*(aPr->zaloga));
	}
	if(aV>0){
		cout << "Ni dovolj denarja na zalogi!" << endl;
	}else{
		UrediVektorVracilo();
	}
}

int CAvtomat:: DolociStKovancev(int aV,int aVr)
{
	int aD = -1;
	while(aV >= 0){
		aV = aV-aVr;
		aD++;
	}
	if(aD == -1)
		aD++;

	return aD;
}

void CAvtomat:: IzpisVektorjaVracilo()
{
	for(int i = 0; i< vracilo.size(); i++){
		cout << vracilo.at(i)->vrednost;
		cout << ' ' << vracilo.at(i)->zaloga;
		cout << endl;
	}
}

void CAvtomat:: IzpisVektorjaKovanci()
{
	for(int i = 0; i< kovanci.size(); i++){
		cout << kovanci.at(i)->vrednost;
		cout << ' ' << kovanci.at(i)->zaloga;
		cout << endl;
	}
}

void CAvtomat:: UrediVektorVracilo()
{
	int j = 0;
	while(j < vracilo.size()){
		int i = vracilo.size()-1;
		while(i>j){
			if(vracilo.at(i)->vrednost < vracilo.at(i-1)->vrednost){
				CKovanec* aK = vracilo.at(i);
				vracilo.at(i) = vracilo.at(i-1);
				vracilo.at(i-1) = aK;
			}
			i--;
		}
		j++;
	}
}


CAvtomat* Ustvari(int aS)
{
	CAvtomat* aA = new CAvtomat();
	int aK;
	int aDeC;
	cout << "Vnesi kolicino vnesenega denarja: ";
	cin >> aK;
	cout << "Koliko je dejanska cena? ";
	cin >> aDeC;
	CVracanje* aP = new CVracanje(aK, aDeC); 
	cout << "Vrniti se torej mora: " << aK-aDeC << endl;
 	for(int i = 0; i < aS; i++){
		int aVre;
		int aZa;
		cout <<"Vnesi vrednost kovanca: ";
		cin >> aVre;
		cout <<"Vnesi zalogo kovanca: ";
		cin >> aZa;
		CKovanec* aK = new CKovanec(aVre, aZa);
		aA->TvoriVektorKovanci(aK);
	}
	aA->Vrni(aP);
	return aA;
}
vector<vector<CKovanec*>> Ustvari1(char* ime, int aS)
{
	ifstream dat(ime);	//odpreš za branje
	if(dat.is_open()){
		vector<vector<CKovanec*>> aVra;
		int i = 0;
		while(!dat.eof()){
			int aK;
			int aZa;
			int aVp;
			int aCe;
			CAvtomat* aA = new CAvtomat();
			for(int k = 0; k< aS; k++){
				dat >> aK;
				dat >> aZa;
				CKovanec* aP = new CKovanec(aK, aZa);
				aA->TvoriVektorKovanci(aP);	
			}
			cout << "Kolicina vnesenega denarja: ";
			dat >> aVp;
			cout << aVp << endl;
			cout << "Dejanska cena: ";
			dat >> aCe;
			cout << aCe << endl;
			CVracanje* aR = new CVracanje(aVp, aCe); 
			aA->Vrni(aR);
			cout << "Vrniti se torej mora: " << aVp-aCe << endl;
			cout << "Zaloga kovancev: " <<endl;
			aA->IzpisVektorjaKovanci();	
			aA->Vrni(aR);
			aVra.push_back(aA->vracilo);
			cout << endl;
			i++;
			cout << endl;
		}
		return aVra;
	}else{
		cout << "Napaka pri odpiranju!";
	}
}
void IzpisVektorja(vector<CKovanec*> aK)
{
	for(int i = 0; i< aK.size(); i++){
		cout << aK.at(i)->vrednost;
		cout << ' ' << aK.at(i)->zaloga;
		cout << endl;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	int aST = 6;
	/*CAvtomat* aAV = Ustvari(aST);
	cout << "Vracilo: "<<endl;
	aAV->IzpisVektorjaVracilo();
	cout << endl;*/
	vector<vector<CKovanec*>> aVracanje = Ustvari1("Kovanci.txt", aST);
			for(int i = 0; i < aVracanje.size(); i++){
				cout << "Vracilo: "<< i << ".vnos "<< endl;
				IzpisVektorja(aVracanje.at(i));
			}

	cin.ignore();
	cin.get();
	return 0;
}
