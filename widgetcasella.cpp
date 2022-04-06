//Andrea Zorzi 561818 widgetcasella.cpp
#include "widgetcasella.h"

WidgetCasella::WidgetCasella(CasellaBase*c,QWidget*parent):QWidget(parent),riferimCasella(c){
info=new int[2];
setFixedSize(80,80);
}


void WidgetCasella::disegnaCasella(QPainter*painter){
	QRadialGradient gradient(40,40,50,25,40);
	if(riferimCasella){
		CasellaForza*cf=dynamic_cast<CasellaForza*>(riferimCasella);
		CasellaOro*co=dynamic_cast<CasellaOro*>(riferimCasella);
		CasellaForzaOro*cfo=dynamic_cast<CasellaForzaOro*>(riferimCasella);
		if(cfo){
			if(cfo->getForzaCasella()!=0 && cfo->getOroCasella()!=0){
				gradient.setColorAt(0.0, Qt::gray);
				gradient.setColorAt(0.6, QColor(216, 144, 0));
				gradient.setColorAt(0.9, Qt::gray);
			}
			else{
				gradient.setColorAt(0.0, Qt::white);
				gradient.setColorAt(0.7, Qt::green);
				gradient.setColorAt(0.9, Qt::black);
			}
		}
		else if(co){
			if(co->getOroCasella()!=0){
				gradient.setColorAt(0.0, Qt::white);
				gradient.setColorAt(0.7, QColor(216, 144, 0));
				gradient.setColorAt(0.9, Qt::black);
			}
			else{
				gradient.setColorAt(0.0, Qt::white);
				gradient.setColorAt(0.7, Qt::green);
				gradient.setColorAt(0.9, Qt::black);
			}
		}
		else if(cf){
			if(cf->getForzaCasella()!=0){
				gradient.setColorAt(0.0, Qt::white);
				gradient.setColorAt(0.7, Qt::gray);
				gradient.setColorAt(0.9, Qt::black);
			}
			else{
				gradient.setColorAt(0.0, Qt::white);
				gradient.setColorAt(0.7, Qt::green);
				gradient.setColorAt(0.9, Qt::black);
			}
		}
		else{
			gradient.setColorAt(0.0, Qt::white);
			gradient.setColorAt(0.7, Qt::green);
			gradient.setColorAt(0.9, Qt::black);
		}
	}
	else{
		gradient.setColorAt(0.0, Qt::white);
		gradient.setColorAt(0.7, Qt::red);
		gradient.setColorAt(0.9, Qt::black);
	}
    QBrush background(gradient);
    QPen testoNumero(Qt::black,20,Qt::DashDotLine,Qt::RoundCap);
    QFont fontTestoNumero("OldEnglish",20,8,true);
	fontTestoNumero.setPixelSize(20);
    painter->setBrush(background);
    painter->drawRoundRect(rect());
    painter->setPen(testoNumero);
    painter->setFont(fontTestoNumero);
    QString stringaNumero;
	if(!riferimCasella)
		painter->drawText(rect(),Qt::AlignCenter,"Start");
	else{
		stringaNumero.setNum(riferimCasella->getNumeroCasella());
	    painter->drawText(rect(),Qt::AlignCenter,stringaNumero);
	}
}


void WidgetCasella::paintEvent(QPaintEvent * /* event */){
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setViewport(0,0,80,80);
    painter.setWindow(0,0,80,80);
    disegnaCasella(&painter);
}

int* WidgetCasella::getInfo(){
	if(riferimCasella){
		CasellaForza*cf=dynamic_cast<CasellaForza*>(riferimCasella);
		CasellaOro*co=dynamic_cast<CasellaOro*>(riferimCasella);
		if(cf)
			info[0]=cf->getForzaCasella();
		else
			info[0]=0;
		if(co)
			info[1]=co->getOroCasella();
		else
			info[1]=0;
		return info;
	}
	else
		return 0;
}


