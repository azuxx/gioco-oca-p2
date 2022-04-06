//Andrea Zorzi 561818 widgetcasella.h

#ifndef WIDGETCASELLA_H
#define WIDGETCASELLA_H

#include<QWidget>
#include<QPainter>
#include<QString>
#include "casella.h"

class WidgetCasella: public QWidget{
	Q_OBJECT
	public:
		WidgetCasella(CasellaBase*,QWidget*parent=0);
		void disegnaCasella(QPainter*painter);
		int*getInfo();
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		CasellaBase*riferimCasella;
		int*info;
};
#endif
