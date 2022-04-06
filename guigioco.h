//Andrea Zorzi 561818 guigioco.h

#ifndef GUIGIOCO_H
#define GUIGIOCO_H

#include<QtGui>
#include<QVector>
#include<string>
#include <QScrollArea>
#include "gioco_oca.h"
#include "widgetcasella.h"
#include "widgetpedina.h"
#include "functrand.h"


class GuiGioco: public QDialog{
	Q_OBJECT
	public:
		GuiGioco(QWidget*parent=0);
		void disegna(QPainter*painter);
		void gioca(int);
	public slots:
		void iniziaPartita();
		void terminaPartita();
		void opzioni();
		void setNomiGiocatori();
		void visualizzaMenu();
		void lanciaDado();
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		bool fine;
		ImpostazioniGioco*im;
		GiocatoriBase*g;
		GiocoOca*gioco;
		void createVerticalGroupBox();
		QGridLayout*mainLayout;
		QGridLayout*pedineGrandi;
		QGridLayout*layoutPista;
		QGridLayout*layoutPedine;
		QVBoxLayout*layoutStrumenti;
		QScrollArea *area;
		QGroupBox*vertGroupBox;
		QGroupBox*sceltaLivello;
		QGroupBox*nGiocatori;
		QGroupBox*nCaselle;
		QGroupBox*pista;
		QBrush background;
        QFont textFont;
        QPen textPen;
        QPushButton*pulsGioca;
        QPushButton*pulsOpzioniGioco;
        QPushButton*pulsEsci;
        QRadioButton*base;
        QRadioButton*forza;
        QRadioButton*oro;
        QRadioButton*forzaoro;
        QSpinBox*spinGioc;
        QSlider*sliderGioc;
        QSpinBox*spinCasel;
        QSlider*sliderCasel;
        QPushButton*nomiGiocatori;
        QPushButton*indietro1;
        QPushButton*indietro2;
        QPushButton*ok;
        QGroupBox*elencoGiocatori;
        QVector<QString> arrNomi;
        QVector<QLineEdit*> arrInput;
        QVector<QLabel*> arrLabel;
       	QVector<WidgetCasella*> pistaCaselle;
       	QVector<WidgetPedina*> pedineInCasella;
       	QVector<QLabel*> coloreGiocatori;
       	QVector<QLabel*> ordine;
       	QVector<QLabel*> punteggioGiocatori;
		QVector<QPoint*>posizionePedine;
       	QLCDNumber*numero;
       	QPushButton*lancia;
       	QLabel*infoPartita;
       	QPushButton*esci;     	
};
#endif
