//Andrea Zorzi 561818 casella.cpp

#include "casella.h"


CasellaBase::CasellaBase(int n,const ImpostazioniGioco &im,GiocatoriBase*g):numero(n),impo(im),gio(g){}

CasellaBase::~CasellaBase(){};


int CasellaBase::getNumeroCasella()const{
	return numero;
}


int CasellaBase::mossa(int spostamento){//gestione mossa da una casella base
	GiocatoriOro*go=dynamic_cast<GiocatoriOro*>(gio);
	if(go){
		//si deve considerare l'oro attuale del giocatore
		int rallentamento=0;
		int rapp=(go->getPunteggioGiocatore(gio->getGiocatoreDiTurno()))/go->getRapportoOro();
    	if(rapp!=0){
	    	rallentamento=rapp;
	    	if(spostamento<=rallentamento)
	    		spostamento=0;
	    	else
	    		spostamento=spostamento-rallentamento;
	    }
	}
    int pos_casella;
    pos_casella=numero+spostamento;
	if(pos_casella>(impo.getNumeroCaselle())){
		int scarto=pos_casella-(impo.getNumeroCaselle());
		int diff=(impo.getNumeroCaselle())-numero;
		pos_casella=numero+(diff-scarto);
	}
	return pos_casella;
}


CasellaForza::CasellaForza(int n,const ImpostazioniGioco &im,GiocatoriBase*g):CasellaBase(n,im,g){
	valoreForza=getRand(150);
}


int CasellaForza::rapporto_forza=40;

int CasellaForza::getRapportoForza()const{
	return rapporto_forza;
}


int CasellaForza::getForzaCasella()const{
	return valoreForza;
}


void CasellaForza::acquistaForza(){
	valoreForza=0;
}


int CasellaForza::mossa(int spostamento){//gestione mossa da una casella forza(effetto accellerativo istantaneo e non cumulativo)
	int incremento=0;
	int rapp=valoreForza/rapporto_forza;
	if(valoreForza!=0){
		acquistaForza();
		if(rapp!=0)
			incremento=rapp;
		spostamento=incremento;
	}
	int pos_casella=CasellaBase::mossa(spostamento);
	return pos_casella;
}

CasellaOro::CasellaOro(int n,const ImpostazioniGioco &im,GiocatoriBase*g):CasellaBase(n,im,g){
	dobloniOro=getRand(50);
}



int CasellaOro::getOroCasella()const{
	return dobloniOro;
}


void CasellaOro::acquistaOro(){
	dobloniOro=0;
}


int CasellaOro::mossa(int spostamento){//gestione mossa da una casella oro
	GiocatoriOro*go=dynamic_cast<GiocatoriOro*>(gio);
	int pos_casella=getNumeroCasella();
	if(dobloniOro!=0){
			if(go){
				go->setPunteggio(dobloniOro);
			}
			acquistaOro();
	}
	else{
		pos_casella=CasellaBase::mossa(spostamento);
	}
	return pos_casella;
}


CasellaForzaOro::CasellaForzaOro(int n,const ImpostazioniGioco &im,GiocatoriBase*g):CasellaBase(n,im,g),CasellaForza(n,im,g),CasellaOro(n,im,g){}


int CasellaForzaOro::mossa(int spostamento){//gestione mossa da una casella forza-oro
	GiocatoriOro*go=dynamic_cast<GiocatoriOro*>(gio);
	if(getOroCasella()!=0){
			if(go){
				go->setPunteggio(getOroCasella());
			}
			acquistaOro();
	}
	int pos_casella=CasellaForza::mossa(spostamento);
	return pos_casella;
}
