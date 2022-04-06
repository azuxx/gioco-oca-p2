//Andrea Zorzi 561818 impostazioni_gioco.h
#ifndef IMPOSTAZIONI_GIOCO_H
#define IMPOSTAZIONI_GIOCO_H
#include<string>

using std::string;

class ImpostazioniGioco{
	private:
		int numerocaselle;
		string livelloscelto;
		static char *livellistabiliti[]; 
		bool isLivelloAccettabile(string)const;
	public:
		ImpostazioniGioco(int=30,string="");
		void setNumeroCaselle(int);
		void setLivelloScelto(string);
		int getNumeroCaselle()const;
		string getLivelloScelto()const;
		string getLivelloStabilito(int)const;
};
#endif
		
