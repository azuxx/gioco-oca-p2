//Andrea Zorzi 561818 gioco_oca.h

#ifndef GIOCO_OCA_H
#define GIOCO_OCA_H

#include<vector>
#include<string>
#include "impostazioni_gioco.h"
#include "giocatori.h"
#include "functrand.h"
#include "casella.h"

using std::string;
using std::vector;

class GiocoOca{
	private:
		class Nodo;
		class Smartp{
			public:
				Nodo*punt;
				Smartp(Nodo* p=0);
				~Smartp();
				Smartp(const Smartp&);
				Smartp& operator=(const Smartp&);
				Nodo* operator->()const;
				Nodo& operator*()const;
				bool operator==(const Smartp&)const;
				bool operator!=(const Smartp&)const;
		};
		class Nodo{
			public:
				CasellaBase*casella;
				int riferimenti;
				Smartp next;
				Nodo(CasellaBase*,const Smartp&);
				~Nodo();
		};
		Smartp start;
		vector<Smartp> posizione_giocatori;
		ImpostazioniGioco impo_gioco;
		GiocatoriBase*giocatorioca;
		Smartp inserisciInCoda(int,Smartp);
		Smartp cercaPosizione(int)const;//cerca la posizione del  di indice passato 
		vector<Smartp>::size_type getIteratoreGiocatoreDiTurno();
		bool arrivo(const Smartp &)const;
		bool partenza(const Smartp &)const;
	public:
		GiocoOca();//costruttore gioco con impostazioni di default
		~GiocoOca();//distruttore
		GiocoOca(const ImpostazioniGioco &,GiocatoriBase*);//costruttore gioco con impostazioni scelte dall'utente
		CasellaBase* getCasella(int)const;
		void costruisciPista();//crea una lista di Nodo lunghezza uguale al numero di caselle previste dalle impostazioni del gioco
		int posizioneGiocatore(int)const;//ritorna la posizione del giocatore di indice passato
		int giocataDado(int,bool&);/*sposta il giocatore di turno ad una certa casella in base all'uscita del dado e eventualmente, secondo il tipo di casella in cui si è finiti e/o la quantità d'oro posseduta dal giocatore*/ 
		bool finePartita();//stabilisce se la partita è finita, altrim imposta il prossimo giocatore di turno
		static void ordina(int*,int);//funzione di ordinamento (x classifica)
};
#endif
