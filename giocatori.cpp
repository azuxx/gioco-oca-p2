//Andrea Zorzi 561818 giocatori.cpp
#include "giocatori.h"


GiocatoriBase::GiocatoriBase(int g):giocatori(g){
	turno=new bool[giocatori];
	traguardo=new bool[giocatori];
	turno[0]=true;//di default è il primo giocatore che inizia a giocare
	for(int i=1;i<giocatori;i++)
		turno[i]=false;
	for(int i=0;i<giocatori;i++)
		traguardo[i]=false;
}

GiocatoriBase::~GiocatoriBase(){
	delete turno;
	delete traguardo;
};


void GiocatoriBase::setGiocatori(int g){
	giocatori=g;
}

int GiocatoriBase::getNumeroGiocatori()const{
	return giocatori;
}

void GiocatoriBase::impostaGiocatoreDiTurno(){//imposta a true il giocatore che sta giocando il suo turno
	bool fine=false, ok=false;
	int pos_turno=0,c=0;
	while(!ok){//ciclo per eventuale ricalcolo dell'impostazione del turno nel caso che il giocatore determinato sia già al traguardo
		for(int i=0;i<giocatori && !fine;i++){//for per impostazione del turno al giocatore successivo
			if(turno[i]==true)
				c++;
			else{
				fine=true;
				pos_turno=i;
				turno[pos_turno]=true;
			}
		}
		if(c==giocatori){//controllo se si è arrivati all'ultimo giocatore
			for(int i=0;i<giocatori;i++)
				turno[i]=false;
			pos_turno=0;
			turno[pos_turno]=true;
		}
		if(traguardo[pos_turno]==false)
			ok=true;
		else{
			fine=false;
			c=0;
		}
	}
}

int GiocatoriBase::getGiocatoreDiTurno()const{//ritorna il giocatore che sta giocando il suo turno
	int k=0;
	bool trov=false;
	for(int i=0;i<giocatori-1 && !trov;i++){
		if(turno[i]==true && turno[i+1]==false)
			trov=true;
		else
			k++;
	}
	return k;
}


bool GiocatoriBase::isGiocatoreAlTraguardo(int k)const{
	return traguardo[k];
}


void GiocatoriBase::setGiocatoreAlTraguardo(int i){
	traguardo[i]=true;
}


GiocatoriForza::GiocatoriForza(int g):GiocatoriBase(g){}


GiocatoriOro::GiocatoriOro(int g):GiocatoriBase(g){
	punteggio=new int[getNumeroGiocatori()];
	for(int i=0;i<getNumeroGiocatori();i++){
		punteggio[i]=0;
	}
}

int GiocatoriOro::peso_bloccante=180;//peso bloccante generale


int GiocatoriOro::rapporto_oro=50;

int GiocatoriOro::getRapportoOro()const{
	return rapporto_oro;
}

int GiocatoriOro::getPesoBloccante()const{
	return peso_bloccante;
}

bool GiocatoriOro::blocca(){//ritorna true se il punteggio del giocatore che deve muovere >=peso bloccante
	int i=getGiocatoreDiTurno();
	if(punteggio[i]>=peso_bloccante){
		punteggio[i]=0;
		return true;
	}
	else
		return false;
}

int GiocatoriOro::getPunteggioGiocatore(int i) const{
	return punteggio[i];
}

void GiocatoriOro::setPunteggio(int p){
	punteggio[getGiocatoreDiTurno()]+=p;
}

void GiocatoriOro::svuotaPunteggioGiocatore(int i){//funzionalità di sicurezza per la classifica
	punteggio[i]=-1;
}

int* GiocatoriOro::punteggiPerGiocatore(int*A)const{
	for(int i=0;i<getNumeroGiocatori();i++){
			A[i]=getPunteggioGiocatore(i);
	}
	return A;
}

GiocatoriForzaOro::GiocatoriForzaOro(int g):GiocatoriBase(g),GiocatoriForza(g),GiocatoriOro(g){}


