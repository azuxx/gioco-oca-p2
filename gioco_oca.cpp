//Andrea Zorzi 561818 gioco_oca.cpp

#include "gioco_oca.h"


GiocoOca::Smartp::Smartp(Nodo*p):punt(p){
	if(punt)
		punt->riferimenti++;
}


GiocoOca::Smartp::~Smartp(){
	//cout<<"~Smartp"<<endl;
	if(punt){
		punt->riferimenti--;
		if(punt->riferimenti==0){
			delete punt;
			//cout<<"delete ~Smartp"<<endl;
		}
	}
}


GiocoOca::Smartp::Smartp(const Smartp & p):punt(p.punt){
	if(punt)
		punt->riferimenti++;
}


GiocoOca::Smartp& GiocoOca::Smartp::operator=(const Smartp& p){
	//cout<<"Smartp="<<endl;
 	if(this!=&p){
		Nodo*t=punt;
		punt=p.punt;
		if(punt)
			punt->riferimenti++;
		if(t){
			t->riferimenti--;
			if(t->riferimenti==0)
				delete t;
		}
	}
	return *this;
}


GiocoOca::Nodo& GiocoOca::Smartp::operator*()const{
	return const_cast<Nodo&>(*punt);
}

GiocoOca::Nodo* GiocoOca::Smartp::operator->()const{
	return const_cast<Nodo*>(punt);
}

bool GiocoOca::Smartp::operator==(const Smartp& p)const{
	return punt==p.punt;
}

bool GiocoOca::Smartp::operator!=(const Smartp& p)const{
	return punt!=p.punt;
}


GiocoOca::Nodo::Nodo(CasellaBase*c,const Smartp& p):casella(c),riferimenti(0),next(p){}

GiocoOca::Nodo::~Nodo(){
	delete casella;
}

GiocoOca::Smartp GiocoOca::inserisciInCoda(int k,Smartp p){
	if(p==0){
		if(impo_gioco.getLivelloScelto()==impo_gioco.getLivelloStabilito(3)){
			int x=getRand(1000);
			if(x>750 && k!=impo_gioco.getNumeroCaselle()){
				CasellaBase*cfo=new CasellaForzaOro(k,impo_gioco,giocatorioca);
				return new Nodo(cfo,0);
			}
			else if((x>500 && x<=750) && k!=impo_gioco.getNumeroCaselle()){
				CasellaBase*co=new CasellaOro(k,impo_gioco,giocatorioca);
				return new Nodo(co,0);		
			}
			else if(x>250 && x<=500){
				CasellaBase*cf=new CasellaForza(k,impo_gioco,giocatorioca);
				return new Nodo(cf,0);
			}
			else if((x>0 && x<=250) || k==impo_gioco.getNumeroCaselle()){
				CasellaBase*cb=new CasellaBase(k,impo_gioco,giocatorioca);
				return new Nodo(cb,0);	
			}
		}
		else if(impo_gioco.getLivelloScelto()==impo_gioco.getLivelloStabilito(2)){
			int x=getRand(1000);
			if(x>500 && k!=impo_gioco.getNumeroCaselle()){
				CasellaBase*co=new CasellaOro(k,impo_gioco,giocatorioca);
				return new Nodo(co,0);		
			}
			else{
				CasellaBase*cb=new CasellaBase(k,impo_gioco,giocatorioca);
				return new Nodo(cb,0);	
			}
		}
		else if(impo_gioco.getLivelloScelto()==impo_gioco.getLivelloStabilito(1)){
			int x=getRand(1000);
			if(x>500){
				CasellaBase*cf=new CasellaForza(k,impo_gioco,giocatorioca);
				return new Nodo(cf,0);
			}
			else{
				CasellaBase*cb=new CasellaBase(k,impo_gioco,giocatorioca);
				return new Nodo(cb,0);	
			}
		}
		else if(impo_gioco.getLivelloScelto()==impo_gioco.getLivelloStabilito(0)){
			CasellaBase*cb=new CasellaBase(k,impo_gioco,giocatorioca);
			return new Nodo(cb,0);
		}	
	}
	p->next=inserisciInCoda(k,p->next);
	return p;
}


GiocoOca::GiocoOca():start(0),impo_gioco(ImpostazioniGioco()),giocatorioca(new GiocatoriBase()){
	for(int i=0;i<giocatorioca->getNumeroGiocatori();i++)
		posizione_giocatori.push_back(start);
}

GiocoOca::GiocoOca(const ImpostazioniGioco& im,GiocatoriBase*g):start(0),impo_gioco(im),giocatorioca(g){
	for(int i=0;i<giocatorioca->getNumeroGiocatori();i++)
		posizione_giocatori.push_back(start);//i giocatori sono all'inizio nel parcheggio esterno alla pista
}

GiocoOca::~GiocoOca(){
	delete giocatorioca;
}


CasellaBase* GiocoOca::getCasella(int k)const{
	if(k==0)
		return 0;
	else{
		Smartp p=cercaPosizione(k);
		return p->casella;
	}
}


void GiocoOca::costruisciPista(){
	int numcaselle=impo_gioco.getNumeroCaselle();
	for(int i=1;i<numcaselle+1;i++){
		start=inserisciInCoda(i,start);
	}
}
	
	
bool GiocoOca::arrivo(const Smartp & p)const{
	if(p!=0 && p->casella->getNumeroCasella()==impo_gioco.getNumeroCaselle())
		return true;
	else
		return false;
}


bool GiocoOca::partenza(const Smartp & p)const{
	if(p==0)
		return true;
	else
		return false;
}

GiocoOca::Smartp GiocoOca::cercaPosizione(int pos_finale)const{
	int iaux=1;
	Smartp aux=start;
	while(iaux<pos_finale){
		aux=aux->next;
		iaux++;
	}
	return aux;
}



vector<GiocoOca::Smartp>::size_type GiocoOca::getIteratoreGiocatoreDiTurno(){
	int giocatore_di_turno=giocatorioca->getGiocatoreDiTurno();//1-ottiene il turno relativo al giocatore che deve muovere
	vector<Smartp>::size_type i=0;
	int k=0;
	bool selezionato=false;
	while(i!=posizione_giocatori.size() && !selezionato){
		if(k==giocatore_di_turno)
			selezionato=true;
		else{
			k++;
			i++;
		}
	}
	return i;
}

int GiocoOca::posizioneGiocatore(int i)const{
	int pos;
	if(partenza(posizione_giocatori[i]))
		pos=0;
	else
		pos=posizione_giocatori[i]->casella->getNumeroCasella();
	return pos;
}

int GiocoOca::giocataDado(int x,bool &stop){
	int pos_casella_gioc_diturno=0;
	vector<Smartp>::size_type i=getIteratoreGiocatoreDiTurno();//2-seleziono nell'array vettore_giocatori l'iteratore relativo al giocatore di turno
	if(partenza(posizione_giocatori[i])){
		CasellaBase*cb=new CasellaBase(0,impo_gioco,giocatorioca);//la partenza è in se di tipo base anche se non è una casella della pista
		pos_casella_gioc_diturno=cb->mossa(x);//mossa del dado dalla posizione di partenza
		Smartp p=cercaPosizione(pos_casella_gioc_diturno);
	    posizione_giocatori[i]=p;
	}
	else{
		GiocatoriOro*go=dynamic_cast<GiocatoriOro*>(giocatorioca);
	    pos_casella_gioc_diturno=((posizione_giocatori[i])->casella)->mossa(x);//mossa(binding dinamico)
	    if(go && go->blocca()){
		   	posizione_giocatori[i]=start;
		   	pos_casella_gioc_diturno=0;
		   	stop=true;
		}
	    else{
	       	Smartp p=cercaPosizione(pos_casella_gioc_diturno);
	       	posizione_giocatori[i]=p;
	    }
	}
	//controlli se ci si deve fermare
	if(pos_casella_gioc_diturno!=0){
		CasellaBase*cb=dynamic_cast<CasellaBase*>(posizione_giocatori[i]->casella);
		CasellaForza*cf=dynamic_cast<CasellaForza*>(posizione_giocatori[i]->casella);
		CasellaOro*co=dynamic_cast<CasellaOro*>(posizione_giocatori[i]->casella);
		if(cf){
			if(cf->getForzaCasella()==0){
			    stop=true;
			}
			//cè forza quindi di deve dare accellerazione al giocatore ->stop==false
		}
		else if(co){
			if(co->getOroCasella()==0){
			    stop=true;
			}
		}
		else if(cb){
			stop=true;
		}
	}
	return pos_casella_gioc_diturno;
}
	
			

bool GiocoOca::finePartita(){
	vector<Smartp>::size_type i=getIteratoreGiocatoreDiTurno();
	bool fine_partita=false;
	GiocatoriOro*go=dynamic_cast<GiocatoriOro*>(giocatorioca);
	if(arrivo(posizione_giocatori[i])){//controllo se il giocatore è arrivato alla fine della pista.se si imposto il giocatore sul traguardo
		giocatorioca->setGiocatoreAlTraguardo(giocatorioca->getGiocatoreDiTurno());
		if(go){
			int m=0;
			for(int i=0;i<giocatorioca->getNumeroGiocatori() && m<3;i++){
				if(giocatorioca->isGiocatoreAlTraguardo(i))
					m++;
			}
			int medaglia=60;
			go->setPunteggio(medaglia/m);//assegnazione medaglie
		}			
	}
	//controllo se ci sono vincitori
	int e=0;
	int h=0;
	while(h<giocatorioca->getNumeroGiocatori()){
		if(giocatorioca->isGiocatoreAlTraguardo(h))
			e++;
		h++;
	}
	if(go){//caso oro / forzaoro
		if(e==giocatorioca->getNumeroGiocatori()){
			fine_partita=true;
		}		
	}
	else{//caso forza / base
		if(e>0 && giocatorioca->getGiocatoreDiTurno()==giocatorioca->getNumeroGiocatori()-1)//se un giocatore ha vinto ed è l'ultimo dei giocatori a muovere allora la partita è finita
			fine_partita=true;
	}
	if(!fine_partita)/*se nessuno ha vinto o se qualcuno ha vinto ma ci sono giocatori ancora in gioco o caso oro/forzaOro tutti devono arrivare al traguardo, imposto il turno al giocatore successivo*/
		giocatorioca->impostaGiocatoreDiTurno();
	return fine_partita;
}

void GiocoOca::ordina(int*A,int dim){
	int i=0,c;
	while(i<dim-1){
    if(A[i]<A[i+1]){
      c = A[i]; 
      A[i] = A[i+1]; 
      A[i+1] =c;
      i=0;
    }
    else
      i++;
	}
}




