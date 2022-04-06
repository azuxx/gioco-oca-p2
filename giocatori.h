//Andrea Zorzi 561818 giocatori.h
#ifndef GIOCATORI_H
#define GIOCATORI_H

class GiocatoriBase{
	private:
		int giocatori;
		bool*turno;
		bool*traguardo;
	public:
		GiocatoriBase(int=3);
		virtual ~GiocatoriBase();
		void setGiocatori(int);
		int getNumeroGiocatori()const;
		int getGiocatoreDiTurno()const;
		void impostaGiocatoreDiTurno();
		bool isGiocatoreAlTraguardo(int)const;
		void setGiocatoreAlTraguardo(int);
};


class GiocatoriForza: virtual public GiocatoriBase{
	public:
		GiocatoriForza(int);
};


class GiocatoriOro: virtual public GiocatoriBase{
	private:
		int*punteggio;
		static int peso_bloccante;
		static int rapporto_oro;
	public:
		GiocatoriOro(int);
		int getPunteggioGiocatore(int) const;
		int*punteggiPerGiocatore(int*)const;
		void setPunteggio(int);
		int getPesoBloccante()const;
		int getRapportoOro()const;
		bool blocca();
		void svuotaPunteggioGiocatore(int);
};

class GiocatoriForzaOro: public GiocatoriForza, public GiocatoriOro{
	public:
		GiocatoriForzaOro(int);
};

#endif
