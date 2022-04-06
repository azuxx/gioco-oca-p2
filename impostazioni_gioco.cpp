//Andrea Zorzi 561818 impostazioni_gioco.cpp

#include "impostazioni_gioco.h"

ImpostazioniGioco::ImpostazioniGioco(int c,string liv):numerocaselle(c){

if(isLivelloAccettabile(liv))
	livelloscelto=liv;
else
	livelloscelto=livellistabiliti[0];
}


int ImpostazioniGioco::getNumeroCaselle()const{return numerocaselle;}

string ImpostazioniGioco::getLivelloScelto()const{return livelloscelto;}

void ImpostazioniGioco::setNumeroCaselle(int n){
	numerocaselle=n;
}

void ImpostazioniGioco::setLivelloScelto(string s){
	livelloscelto=s;
}


char * ImpostazioniGioco::livellistabiliti[]={"Base","Forza","Oro","Forza-Oro"};

bool ImpostazioniGioco::isLivelloAccettabile(string l)const{
	bool ok=false;
	for(int i=0;i<4;i++){
		if(l==livellistabiliti[i])
			ok=true;
	}
	return ok;
}

string ImpostazioniGioco::getLivelloStabilito(int i)const{
	return livellistabiliti[i];
}

