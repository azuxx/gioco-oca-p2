//Andrea Zorzi 561818 widgetpedina.h

#ifndef WIDGETPEDINA_H
#define WIDGETPEDINA_H

#include<QWidget>
#include<QString>
#include<QPainter>
#include "widgetcasella.h"
#include "functrand.h"

class WidgetPedina:public QWidget{
	Q_OBJECT
	public:
		WidgetPedina(QString,WidgetCasella*,QWidget*parent=0);//riceve il nome del giocatore e la casella in cui la pedina si trova
		void disegnaCasella(QPainter*painter);
		QString getNomePedina()const;
		int getValoreColore(int)const;
		WidgetCasella*riferimWidgetCasella;
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		QLinearGradient gradient;
		QString nomePedina;
		int colore[6];//r,g,b, per il colore1 e r,g,b per il colore2 ->dim=6
};
#endif
