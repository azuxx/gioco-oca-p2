//Andrea Zorzi 561818 widgetpedina.cpp
#include "widgetpedina.h"


WidgetPedina::WidgetPedina(QString nome,WidgetCasella*cas,QWidget*parent):QWidget(parent),riferimWidgetCasella(cas),nomePedina(nome){
	setFixedSize(25,25);
	for(int i=0;i<6;i++){
		colore[i]=getRand(256);
	}
	gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(0.4, QColor(colore[0],colore[1],colore[2]));
    gradient.setColorAt(1.0, QColor(colore[3],colore[4],colore[5]));
}


int WidgetPedina::getValoreColore(int i)const{
	return colore[i];
}


void WidgetPedina::disegnaCasella(QPainter*painter){
	gradient.setStart(3,5);
	gradient.setFinalStop(15,20);
	gradient.setColorAt(0.0, Qt::white);
    QBrush background(gradient);
    QPen testoNome(Qt::black,20,Qt::DashDotLine,Qt::RoundCap);
    QFont fontTestoNome("OldEnglish",1,1,true);
    fontTestoNome.setPixelSize(7);
    painter->setBrush(background);
    painter->drawEllipse(rect());
    painter->setPen(testoNome);
    painter->setFont(fontTestoNome);
    painter->drawText(rect(),Qt::AlignCenter | Qt::TextWordWrap,nomePedina);
}


void WidgetPedina::paintEvent(QPaintEvent * /* event */){
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setViewport(0,0,25,25);
    painter.setWindow(0,0,25,25);
    disegnaCasella(&painter);
}


QString WidgetPedina::getNomePedina()const{
	return nomePedina;
}

