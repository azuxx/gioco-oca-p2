//Andrea Zorzi 561818 casella.h

#ifndef CASELLA_H
#define CASELLA_H

#include "impostazioni_gioco.h"
#include "giocatori.h"
#include "functrand.h"


class CasellaBase{
	private:
		const int numero;
	protected:
		ImpostazioniGioco impo;
		GiocatoriBase*gio;
	public:
		CasellaBase(int,const ImpostazioniGioco &,GiocatoriBase*);
		int getNumeroCasella()const;
		virtual ~CasellaBase();
		virtual int mossa(int);//riceve un intero per determinare a quale casella ci si dovrà spostare dalla casella dell'oggetto di invocazione(dove si trova il giocatore nel momento precedente il lancio del dado)
};

class CasellaForza:virtual public CasellaBase{
	private:
		int valoreForza;
		static int rapporto_forza;//rapporto forza per determinare l'eventuale effetto accellerativo istantaneo sul giocatore
	public:
		CasellaForza(int,const ImpostazioniGioco &,GiocatoriBase*);
		int getForzaCasella()const;
		int getRapportoForza()const;
		void acquistaForza();//svuota la casella della forza che possiede
		virtual int mossa(int);//overriding
};


class CasellaOro:virtual public CasellaBase{
	private:
		int dobloniOro;
	public:
		CasellaOro(int,const ImpostazioniGioco &,GiocatoriBase*);
		int getOroCasella() const;
		void acquistaOro();//svuota la casella dell'oro che possiede
		virtual int mossa(int);//overriding
};


class CasellaForzaOro:public CasellaForza, public CasellaOro{
	public:
		CasellaForzaOro(int,const ImpostazioniGioco &,GiocatoriBase*);
		int mossa(int);//overriding
};

#endif
