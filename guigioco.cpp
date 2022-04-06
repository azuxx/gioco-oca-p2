//Andrea Zorzi 561818 guigioco.cpp
#include "guigioco.h"

#define MESSAGE \
	GuiGioco::tr("Sei sicuro di voler abbandonare il gioco?")\

#define MESSAGE2 \
	GuiGioco::tr("La partita e' finita. Tornare al menu' principale?")\

GuiGioco::GuiGioco(QWidget*parent):QDialog(parent){
	srand(time(NULL));
	im=new ImpostazioniGioco();
	g=new GiocatoriBase();
	for(int i=0;i<g->getNumeroGiocatori();i++){
		QString testo="Giocatore ";
		QString num;
		testo.append(num.setNum(i));
		arrNomi.push_back(testo);
	}
	createVerticalGroupBox();
	mainLayout=new QGridLayout(this);
	QRadialGradient gradient(320,320,100,310,320);
	gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(0.4, QColor(100,100,150));
    gradient.setColorAt(1.0, QColor(150,150,200));
    gradient.setSpread(QGradient::ReflectSpread);
    background =QBrush(gradient);
    textPen = QPen(QColor(216, 144, 0),30,Qt::DashDotLine,Qt::RoundCap);
    textFont=QFont("OldEnglish",20,10,true);
    textFont.setPixelSize(80);
    mainLayout->addWidget(vertGroupBox);
    mainLayout->setContentsMargins(200,180,200,180);
    setWindowTitle(tr("Gioco dell'oca. made by Andrea Zorzi"));
    setMinimumSize(800,600);
    setLayout(mainLayout);//sarebbe this->setLayout, cioè setta il layout principale della dialog a mainLayout
}





void GuiGioco::paintEvent(QPaintEvent * /*event*/){
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    //int side = qMin(width(), height());//ritorna il minimo tra larghezza e altezza
    painter.setViewport(0,0,width(),height());//la funzione riceve ( int "x", int "y", int "width", int "height").Il viewport specifica le "device coordinate system".
    painter.setWindow(0,0,width(),height());//Sets the painter's window to the rectangle beginning at (x, y) and the given width and height.(0,0) specifica l'origine logica, mentre quella fisica è anche in questo caso (0,0), che è quella della viewport
    disegna(&painter);
}


void GuiGioco::disegna(QPainter*painter){
	painter->fillRect(rect(),background);
	painter->setPen(textPen);
	painter->setFont(textFont);
	painter->drawText(rect(),Qt::AlignHCenter,tr("Gioco dell'Oca"));
	if(posizionePedine.isEmpty()==false){
		int x=2,y=2;
		for(int i=0;i<g->getNumeroGiocatori();i++){
			QPoint po=pedineInCasella[i]->riferimWidgetCasella->pos();
			if(i%3==0 && i!=0){
				x=2;
				y=y+50;
			}	
			posizionePedine[i]->setX(po.x()+x);
			posizionePedine[i]->setY(po.y()+y);
			pedineInCasella[i]->move(*posizionePedine[i]);
			x=x+28;
		}
	}
}

void GuiGioco::visualizzaMenu(){
	mainLayout->setAlignment(Qt::AlignCenter);
	if(sceltaLivello->isVisible())
		sceltaLivello->setVisible(false);
	if(nGiocatori->isVisible())
		nGiocatori->setVisible(false);
	if(nCaselle->isVisible())
		nCaselle->setVisible(false);
	if(nomiGiocatori->isVisible())
		nomiGiocatori->setVisible(false);
	if(indietro1->isVisible())
		indietro1->setVisible(false);
	if(spinGioc->isVisible())
		spinGioc->setVisible(false);
	if(sliderGioc->isVisible())
		sliderGioc->setVisible(false);
	if(spinCasel->isVisible())
		spinCasel->setVisible(false);
	if(sliderCasel->isVisible())
		sliderCasel->setVisible(false);
	if(base->isVisible())
		base->setVisible(false);
	if(forza->isVisible())
		forza->setVisible(false);
	if(oro->isVisible())
		oro->setVisible(false);
	if(forzaoro->isVisible())
		forzaoro->setVisible(false);
	if(arrLabel.isEmpty()==false){
		for(int i=0;i<arrLabel.size();i++){
			(arrLabel.at(i))->setVisible(false);
		}
	}
	if(arrInput.isEmpty()==false){
		for(int i=0;i<arrNomi.size();i++){
			arrNomi.replace(i, (arrInput.at(i))->text());
		}
		elencoGiocatori->setVisible(false);
		indietro2->setVisible(false);
		ok->setVisible(false);
		for(int i=0;i<arrInput.size();i++){
			(arrInput.at(i))->setVisible(false);
		}
	}
	//mainLayout->setContentsMargins(200,180,200,180);
	vertGroupBox->setVisible(true);
	pulsGioca->setVisible(true);
	pulsOpzioniGioco->setVisible(true);
	pulsEsci->setVisible(true);
	setLayout(mainLayout);
}


void GuiGioco::createVerticalGroupBox(){
	vertGroupBox=new QGroupBox(tr("Menu Principale"));
	QVBoxLayout*layout=new QVBoxLayout;
	pulsGioca=new QPushButton("Gioca");
	pulsGioca->setFixedSize(200,50);
	pulsGioca->setFont(QFont("Times", 18, true));
	layout->addWidget(pulsGioca);
	connect(pulsGioca,SIGNAL(clicked()),this,SLOT(iniziaPartita()));
	pulsOpzioniGioco=new QPushButton("Opzioni di gioco");
	pulsOpzioniGioco->setFixedSize(200,50);
	pulsOpzioniGioco->setFont(QFont("Times", 18,true));
	layout->addWidget(pulsOpzioniGioco);
	connect(pulsOpzioniGioco,SIGNAL(clicked()),this,SLOT(opzioni()));
	pulsEsci=new QPushButton("Esci dal gioco");
	pulsEsci->setFixedSize(200,50);
	pulsEsci->setFont(QFont("Times", 18, true));
	layout->addWidget(pulsEsci);
	connect(pulsEsci,SIGNAL(clicked()),this,SLOT(close()));
	layout->setAlignment(Qt::AlignCenter);
	vertGroupBox->setLayout(layout);
}

void GuiGioco::opzioni(){
	//nascondimento pulsanti, etc..
	if(vertGroupBox->isVisible())
		vertGroupBox->setVisible(false);
	if(pulsGioca->isVisible())
		pulsGioca->setVisible(false);
	if(pulsOpzioniGioco->isVisible())
		pulsOpzioniGioco->setVisible(false);
	if(pulsEsci->isVisible())
		pulsEsci->setVisible(false);
	if(arrLabel.isEmpty()==false){
		for(int i=0;i<arrLabel.size();i++){
			(arrLabel.at(i))->setVisible(false);
		}
	}
	if(arrInput.isEmpty()==false){
		elencoGiocatori->setVisible(false);
		indietro2->setVisible(false);
		ok->setVisible(false);
		for(int i=0;i<arrInput.size();i++){
			(arrInput.at(i))->setVisible(false);
		}
	}
	mainLayout->setContentsMargins(20,140,60,140);
	mainLayout->setAlignment(Qt::AlignCenter);
	//gruppo optionbutton scelta del livello
	sceltaLivello=new QGroupBox(tr("Scegliere il livello"));
	sceltaLivello->setMinimumSize(250,320);
	QVBoxLayout*leftLayout=new QVBoxLayout;
	base=new QRadioButton(tr(im->getLivelloStabilito(0).c_str()));
	forza=new QRadioButton(tr(im->getLivelloStabilito(1).c_str()));
	oro=new QRadioButton(tr(im->getLivelloStabilito(2).c_str()));
	forzaoro=new QRadioButton(tr(im->getLivelloStabilito(3).c_str()));
	const char*c=(im->getLivelloScelto()).c_str();
	QString qs(c);
	if(base->text()==qs)
		base->setChecked(true);
	else if(forza->text()==qs)
		forza->setChecked(true);
	else if(oro->text()==qs)
		oro->setChecked(true);
	else if(forzaoro->text()==qs)
		forzaoro->setChecked(true);
	leftLayout->addWidget(base);
	leftLayout->addWidget(forza);
	leftLayout->addWidget(oro);
	leftLayout->addWidget(forzaoro);
	sceltaLivello->setLayout(leftLayout);
	QHBoxLayout*topRightLayout=new QHBoxLayout;
	nGiocatori=new QGroupBox(tr("Scegliere il numero dei giocatori"));
	nGiocatori->setMinimumSize(125,175);
	spinGioc=new QSpinBox;
	sliderGioc=new QSlider(Qt::Horizontal);
	spinGioc->setRange(2,6);
	sliderGioc->setRange(2,6);
	connect(spinGioc,SIGNAL(valueChanged(int)),sliderGioc,SLOT(setValue(int)));
	connect(sliderGioc,SIGNAL(valueChanged(int)),spinGioc,SLOT(setValue(int)));
	spinGioc->setValue(g->getNumeroGiocatori());
	topRightLayout->addWidget(spinGioc);
	topRightLayout->addWidget(sliderGioc);
	nGiocatori->setLayout(topRightLayout);
	QHBoxLayout*bottomRightLayout=new QHBoxLayout;
	nCaselle=new QGroupBox(tr("Scegliere il numero di caselle"));
	nCaselle->setMinimumSize(125,175);
	spinCasel=new QSpinBox;
	sliderCasel=new QSlider(Qt::Horizontal);
	spinCasel->setRange(30,50);
	sliderCasel->setRange(30,50);
	connect(spinCasel,SIGNAL(valueChanged(int)),sliderCasel,SLOT(setValue(int)));
	connect(sliderCasel,SIGNAL(valueChanged(int)),spinCasel,SLOT(setValue(int)));
	spinCasel->setValue(im->getNumeroCaselle());
	bottomRightLayout->addWidget(spinCasel);
	bottomRightLayout->addWidget(sliderCasel);
	nCaselle->setLayout(bottomRightLayout);
	nomiGiocatori=new QPushButton("Ok");
	indietro1=new QPushButton("Indietro");
	nomiGiocatori->setSizePolicy(QSizePolicy());
	indietro1->setSizePolicy(QSizePolicy());
	mainLayout->addWidget(sceltaLivello,0,0,2,1);
	mainLayout->addWidget(nGiocatori,0,1,1,2);
	mainLayout->addWidget(nCaselle,1,1,1,2);
	mainLayout->addWidget(indietro1,2,1,Qt::AlignRight);
	mainLayout->addWidget(nomiGiocatori,2,2,Qt::AlignRight);
	connect(indietro1,SIGNAL(clicked()),this,SLOT(visualizzaMenu()));
	connect(nomiGiocatori,SIGNAL(clicked()),this,SLOT(setNomiGiocatori()));
	setLayout(mainLayout);
}

void GuiGioco::setNomiGiocatori(){
	im->setNumeroCaselle(spinCasel->value());//imposto il numero di caselle a quello scelto nelle opzioni
	bool b1=base->isChecked();
	bool b2=forza->isChecked();
	bool b3=oro->isChecked();
	bool b4=forzaoro->isChecked();
	QString qscelta;
	if(b1)
		qscelta=base->text();
	else if(b2)
		qscelta=forza->text();
	else if(b3)
		qscelta=oro->text();
	else if(b4)
		qscelta=forzaoro->text();
	char*stringscelta;//puntatore a carattere
	int bytes=qscelta.length();//lunghezza Qstring
	stringscelta=(char*) malloc (bytes+1);//allocazione in memoria di una stringa(tipo char*) lunga bytes
	for(int j=0;j<bytes;j++){
		stringscelta[j]=qscelta.at(j).toLatin1();
	}
	stringscelta[bytes]=0; //ultimo carattere della stringa (è 0 nelle stringhe)
	string vecchioLivello=im->getLivelloScelto();
	int vecchioSetGioc=g->getNumeroGiocatori();
	if(stringscelta==vecchioLivello)
		g->setGiocatori(spinGioc->value());
	else{
		delete g;
		im->setLivelloScelto(stringscelta);//imposto il livello a quello scelto nelle opzioni
	}
	if(im->getLivelloScelto()==im->getLivelloStabilito(0))
		g=new GiocatoriBase(spinGioc->value());
	else if(im->getLivelloScelto()==im->getLivelloStabilito(1))
		g=new GiocatoriForza(spinGioc->value());
	else if(im->getLivelloScelto()==im->getLivelloStabilito(2))
		g=new GiocatoriOro(spinGioc->value());
	else if(im->getLivelloScelto()==im->getLivelloStabilito(3))
		g=new GiocatoriForzaOro(spinGioc->value());
	sceltaLivello->setVisible(false);
	nGiocatori->setVisible(false);
	nCaselle->setVisible(false);
	nomiGiocatori->setVisible(false);
	indietro1->setVisible(false);
	spinGioc->setVisible(false);
	sliderGioc->setVisible(false);
	spinCasel->setVisible(false);
	sliderCasel->setVisible(false);
	base->setVisible(false);
	forza->setVisible(false);
	oro->setVisible(false);
	forzaoro->setVisible(false);
	mainLayout->setAlignment(Qt::AlignCenter);
	mainLayout->setContentsMargins(40,150,20,150);
	int nuovoSetGioc=g->getNumeroGiocatori();
	if(nuovoSetGioc>vecchioSetGioc){
		int k=vecchioSetGioc;
		while(k<nuovoSetGioc){
			QString testo="Giocatore ";
			QString num;
			testo.append(num.setNum(k));
			arrNomi.push_back(testo);
			k++;
		}
	}
	else if(nuovoSetGioc<vecchioSetGioc){
		int k=nuovoSetGioc;
		QVector<QString>::iterator it=&arrNomi[k];
		while(k<vecchioSetGioc){
			it=arrNomi.erase(it);
			k++;
		}
	}
	elencoGiocatori=new QGroupBox(tr("Inserire i nomi dei giocatori"));
	QGridLayout*layout=new QGridLayout;
	for(int i=0;i<arrNomi.size();i++){
		arrInput.insert(i,new QLineEdit(arrNomi.at(i)));
	}
	for(int i=0;i<arrNomi.size();i++){
		QString testo="Giocatore ";
		QString num;
		testo.append(num.setNum(i));
		arrLabel.insert(i,new QLabel(testo));
	}
	for(int i=0;i<arrLabel.size();i++){
		layout->addWidget((arrLabel.at(i)),i,0);
	}
	layout->setHorizontalSpacing(50);
	for(int i=0;i<arrInput.size();i++){
		layout->addWidget((arrInput.at(i)),i,1);
	}
	layout->setAlignment(Qt::AlignCenter);
	elencoGiocatori->setLayout(layout);
	elencoGiocatori->setMinimumSize(450,250);
	indietro2=new QPushButton("Indietro");
	indietro2->setSizePolicy(QSizePolicy());
	ok=new QPushButton("Ok");
	ok->setSizePolicy(QSizePolicy());
	mainLayout->addWidget(elencoGiocatori,0,0,1,2);
	mainLayout->addWidget(indietro2,1,0,Qt::AlignRight);
	mainLayout->addWidget(ok,1,1,Qt::AlignRight);
	connect(indietro2,SIGNAL(clicked()),this,SLOT(opzioni()));
	connect(ok,SIGNAL(clicked()),this,SLOT(visualizzaMenu()));
	setLayout(mainLayout);
}


void GuiGioco::gioca(int x){
	QString nome;
	QString infoGiocatoreBef="";
	QString infoGiocatoreAft="";
	QString numero;
	QString punteggio="";
	QString infoCasella="";
	int casellaGiocatoreTurno=0;
	int giocTurno=g->getGiocatoreDiTurno();
	nome=arrNomi.at(giocTurno);
	infoGiocatoreBef.append(nome);
	infoGiocatoreBef.append(" prima del lancio eri nella casella ");
	int posIniz=gioco->posizioneGiocatore(giocTurno);
	numero.setNum(posIniz);
	infoGiocatoreBef.append(numero);
	infoGiocatoreBef.append("\n");
	bool stop=false;
	while(!stop){
	    casellaGiocatoreTurno=gioco->giocataDado(x,stop);//giocata dado
		pedineInCasella[giocTurno]->riferimWidgetCasella=pistaCaselle[casellaGiocatoreTurno];
		update();
		QMessageBox::StandardButton ok4;
		int*a=pistaCaselle[casellaGiocatoreTurno]->getInfo();
		if(a){
			QString valori;
			infoCasella="";
			if(a[0]!=0 && a[1]!=0){
				infoCasella.append("La casella contiene: \n");
				valori.setNum(a[0]);
				infoCasella.append(valori);
				infoCasella.append("punti forza \n ");
				valori.setNum(a[1]);
				infoCasella.append(valori);
				infoCasella.append("dobloni d'oro \n");
				infoPartita->setText(infoCasella);
				ok4=QMessageBox::information(this,tr("Avviso"),tr("Hai acquisito forza e/o oro!"));
			}
			else if(a[0]!=0){
				infoCasella.append("La casella contiene: \n");
				valori.setNum(a[0]);
				infoCasella.append(valori);
				infoCasella.append("punti forza \n ");
				infoPartita->setText(infoCasella);
				ok4=QMessageBox::information(this,tr("Avviso"),tr("Hai acquisito forza!"));
			}
			else if(a[1]!=0){
				infoCasella.append("La casella contiene: \n");
				valori.setNum(a[1]);
				infoCasella.append(valori);
				infoCasella.append("dobloni d'oro \n");
				infoPartita->setText(infoCasella);
				ok4=QMessageBox::information(this,tr("Avviso"),tr("Hai acquisito oro!"));
			}
		}
		else{
			infoCasella="Sei stato bloccato! \n";
			infoPartita->setText(infoCasella);
		}
		pistaCaselle[casellaGiocatoreTurno]->update();//aggiorna la casella, poiche' il giocatore ha acquisito la forza e/o l'oro presente
	}
	GiocatoriOro*go=dynamic_cast<GiocatoriOro*>(g);
	if(go){
		int punteggioGioc=go->getPunteggioGiocatore(giocTurno);
		punteggio.setNum(punteggioGioc);
		infoGiocatoreAft.append(nome);
		infoGiocatoreAft.append("possiedi ben ");
		infoGiocatoreAft.append(punteggio);
		infoGiocatoreAft.append(" dobloni d'oro");
	}
	infoCasella.append("\n");
	infoGiocatoreAft.append("\n");
	infoGiocatoreAft.append(nome);
	if(casellaGiocatoreTurno==im->getNumeroCaselle())
		infoGiocatoreAft.append(" sei arrivato al traguardo!");
	else{
		infoGiocatoreAft.append(" ora sei nella casella ");
		numero.setNum(casellaGiocatoreTurno);
		infoGiocatoreAft.append(numero);
	}
	int spostamento=casellaGiocatoreTurno-posIniz;
	infoGiocatoreAft.append(". Ti sei spostato di ");
	numero.setNum(spostamento);
	infoGiocatoreAft.append(numero);
	infoGiocatoreBef.append(infoGiocatoreAft);
	infoCasella.append(infoGiocatoreBef);
	fine=gioco->finePartita();
	if(!fine){
		infoGiocatoreAft="";
		int giocSeguente=g->getGiocatoreDiTurno();
		nome=arrNomi.at(giocSeguente);
		infoGiocatoreAft.append("\n");
		infoGiocatoreAft.append(nome);
		infoGiocatoreAft.append(" ora e' il tuo turno!");
		infoCasella.append(infoGiocatoreAft);
		infoPartita->setText(infoCasella);
		lancia->setEnabled(true);
	}
	else{
		QString vincitore="";
		QString arrivo="";
		if(go){
			//rimozione oggetti per creazione classifica
			for(int j=0;j<g->getNumeroGiocatori();j++){
				pedineGrandi->removeWidget(coloreGiocatori[j]);
			}
			layoutStrumenti->removeItem(pedineGrandi);
			layoutStrumenti->removeWidget(infoPartita);
			infoPartita->setFixedSize(200,50);
			//creazione classifica
			QString num;
			int *punteggio=new int[g->getNumeroGiocatori()];
			punteggio=go->punteggiPerGiocatore(punteggio);
			GiocoOca::ordina(punteggio,g->getNumeroGiocatori());
			int riga=0;
			for(int i=0;i<g->getNumeroGiocatori();i++){//ciclo per l'array ordinato
			    int k=0;
			    bool trov=false;
			    while(k<g->getNumeroGiocatori() && !trov){
			        if(punteggio[i]==go->getPunteggioGiocatore(k)){
			            trov=true;
			            go->svuotaPunteggioGiocatore(k);
			            if(i==0){
			            	vincitore=pedineInCasella[i]->getNomePedina();
			            }
			            QString numOrdinale=num.setNum(i+1);
			            numOrdinale.append(QApplication::translate("","°",0,QApplication::UnicodeUTF8));
			            ordine.insert(i,new QLabel(numOrdinale));
			            pedineGrandi->addWidget(ordine[i],riga,1);
			            pedineGrandi->addWidget(coloreGiocatori[k],riga,2);
			            QString punti=num.setNum(punteggio[i]);
			            punti.append(" dobloni d'oro");
			            punteggioGiocatori.insert(i,new QLabel(punti));
			            pedineGrandi->addWidget(punteggioGiocatori[i],riga,3);
			            riga++;
			        }
			        else
			            k++;
			   }
			}
			arrivo="Il Vincitore è: ";
			arrivo.append(vincitore);
			infoPartita->setText("----Arrivo!!!----\n Ecco La classifica finale!");
			layoutStrumenti->addWidget(infoPartita);
			layoutStrumenti->addLayout(pedineGrandi);
		}
		else{
			arrivo="----Arrivo!!!----\n";
			for(int i=0;i<g->getNumeroGiocatori();i++){
				if(g->isGiocatoreAlTraguardo(i)){
					arrivo.append(pedineInCasella[i]->getNomePedina());
					arrivo.append(" hai vinto!\n");
				}
			}
			infoPartita->setText(arrivo);
		}
	}
}



void GuiGioco::lanciaDado(){
	srand(time(NULL));
	int x=getRand(6);
	numero->display(x);
	lancia->setEnabled(false);
	gioca(x);
}

void GuiGioco::terminaPartita(){
	QMessageBox::StandardButton reply;
	if(!fine)
		reply=QMessageBox::question(this,tr("Termina"),MESSAGE,QMessageBox::Yes | QMessageBox::No);
	else
		reply=QMessageBox::question(this,tr("Uscita"),MESSAGE2,QMessageBox::Yes | QMessageBox::No);
	if(reply==QMessageBox::Yes){
		for(int i=0;i<g->getNumeroGiocatori();i++){
			delete posizionePedine[i];
			delete coloreGiocatori[i];
			delete pedineInCasella[i];
		}
		for(int i=0;i<im->getNumeroCaselle()+1;i++){
			delete pistaCaselle[i];
		}
		if(punteggioGiocatori.isEmpty()==false){
			for(int i=0;i<g->getNumeroGiocatori();i++){
				delete punteggioGiocatori[i];
				delete ordine[i];
			}
			punteggioGiocatori.clear();
			ordine.clear();
		}
		posizionePedine.clear();
		coloreGiocatori.clear();
		pistaCaselle.clear();
		pedineInCasella.clear();
		//distruzione in ordine inverso a costruzione
		delete layoutPedine;
		delete layoutPista;
		delete pista;
		delete area;
		delete pedineGrandi;
		//
		int n=g->getNumeroGiocatori();
		delete gioco;
		delete lancia;
		delete numero;
		delete infoPartita;
		delete esci;
		delete layoutStrumenti;
		vertGroupBox->setVisible(true);
		pulsGioca->setVisible(true);
		pulsOpzioniGioco->setVisible(true);
		pulsEsci->setVisible(true);
		if(im->getLivelloScelto()==im->getLivelloStabilito(0))
			g=new GiocatoriBase(n);
		else if(im->getLivelloScelto()==im->getLivelloStabilito(1))
			g=new GiocatoriForza(n);
		else if(im->getLivelloScelto()==im->getLivelloStabilito(2))
			g=new GiocatoriOro(n);
		else if(im->getLivelloScelto()==im->getLivelloStabilito(3))
			g=new GiocatoriForzaOro(n);
		mainLayout->setContentsMargins(200,180,200,180);
		setLayout(mainLayout);
	}
}

void GuiGioco::iniziaPartita(){
	mainLayout->setContentsMargins(10,120,10,10);
	if(vertGroupBox->isVisible())
		vertGroupBox->setVisible(false);
	if(pulsGioca->isVisible())
		pulsGioca->setVisible(false);
	if(pulsOpzioniGioco->isVisible())
		pulsOpzioniGioco->setVisible(false);
	if(pulsEsci->isVisible())
		pulsEsci->setVisible(false);
	gioco=new GiocoOca(*im,g);/*im e g (impostazioni del gioco e giocatori) rimangono sempre allocati sullo heap da quando si avvia il gioco(per via dei settaggi di default) perchè l'utente potrebbe fare altre partite con quei settaggi o semplicemente cambiandoli andando sulle opzioni. in gioco invece im è dereferenziato è passato per riferimento costante xk l'oggetto GiocoOca ha come campo proprio l' oggetto ImpostazioniGioco perchè è proprio di quella partita ma si riferisce alle impostazioni settate nel menu. g viene passato invece come puntatore perchè in GiocoOca vi sono dei cast dinamici che nel caso g fosse passato per riferimento constante implicherebbe un cast const prima del cast dinamico.*/
	fine=false;
	layoutPista=new QGridLayout;
	layoutPedine=new QGridLayout;
	layoutStrumenti=new QVBoxLayout;
	area = new QScrollArea();
	pista=new QGroupBox(area);
	QVBoxLayout *larea = new QVBoxLayout;
	larea->addWidget(pista);//inserisco il groupbox della pista dentro il layout dell'area di scroll
	area->setLayout(larea);//imposto il layout all'oggetto area di tipo QScrollArea
	area->setWidget(pista);//applico al groupbox le scroll bar
	area->setAutoFillBackground(true);
	QColor q(255,255,255,0);//alpha=0 per via che l'area soggetta a scroll deve essere trasparente
	QPalette pal(q);
	area->setPalette(pal);
	gioco->costruisciPista();//costruzione logica pista
	//creazione ed inserimento Widgetpedine e Widgetcaselle nei rispettivi QVector
	for(int i=0;i<im->getNumeroCaselle()+1;i++){
		CasellaBase*c=gioco->getCasella(i);
		pistaCaselle.insert(i,new WidgetCasella(c));
		if(i==0){
			for(int j=0;j<g->getNumeroGiocatori();j++){
				pedineInCasella.insert(j,new WidgetPedina(arrNomi.at(j),pistaCaselle[i]));
			}
		}
	}
	//inserimento pedine nel apposito layout 
	int riga=0;//riga nella grid
	int pedinePerRiga=3;
	for(int i=0;i<pedineInCasella.size();i++){
		if(i%pedinePerRiga==0)
			riga++;
		layoutPedine->addWidget(pedineInCasella.at(i),riga,i%pedinePerRiga);
		//layoutPista->setHorizontalSpacing(2);
	}
	//inserimento caselle nel apposito layout (costruzione percorso "a serpentina")
	riga=0;
	int casellePerRiga=10;
	int colonna=casellePerRiga;
	bool inverti=false;
	bool left=false;
	for(int i=0;i<pistaCaselle.size();i++){
		if(i%casellePerRiga==0 && i!=0){
			inverti=true;
			riga++;
			if(!left){
				layoutPista->addWidget(pistaCaselle.at(i),riga,casellePerRiga-1);
				left=true;
			}
			else{
				layoutPista->addWidget(pistaCaselle.at(i),riga,1);
				left=false;
			}
			riga++;
		}
		if(colonna==0){
			colonna=casellePerRiga;
			inverti=false;
		}
		if(!inverti){
			layoutPista->addWidget(pistaCaselle.at(i),riga,i%casellePerRiga);
		}
		else{
			layoutPista->addWidget(pistaCaselle.at(i),riga,colonna);
			colonna--;
		}
		layoutPista->setVerticalSpacing(3);
		layoutPista->setHorizontalSpacing(3);
	}
	layoutPista->addLayout(layoutPedine,0,0);//posizionamento layout pedine sopra lo "start"
	pista->setLayout(layoutPista);
	pista->setFixedSize(1000,800);
	lancia=new QPushButton("Lancia");
	infoPartita=new QLabel();
	//messaggio iniziale
	infoPartita->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	infoPartita->setWordWrap(true);
	infoPartita->setAlignment(Qt::AlignTop);
	infoPartita->setFixedSize(200,200);
	//messaggio turno giocatore
	int giocTurno=g->getGiocatoreDiTurno();
	QString nome=arrNomi.at(giocTurno);
	QString info("Benvenuti giocatori! \n");
	info.append(nome);
	info.append(" e' il tuo turno! \n Lancia il dado!");
	infoPartita->setText(info);
	//creazione quadratini che rappresentano l'associazione giocatori e loro colore
	pedineGrandi=new QGridLayout();
	pedineGrandi->setSizeConstraint(QLayout::SetFixedSize);
	for(int j=0;j<g->getNumeroGiocatori();j++){
		coloreGiocatori.insert(j,new QLabel(arrNomi[j]));
	}
	int pedineRiga=3;
	for(int j=0;j<g->getNumeroGiocatori();j++){
		coloreGiocatori[j]->setAutoFillBackground(true);
		QLinearGradient gradient;
		gradient.setStart(8,25);
		gradient.setFinalStop(35,40);
   	 	gradient.setColorAt(0.0, Qt::white);
	    gradient.setColorAt(0.4, QColor(pedineInCasella[j]->getValoreColore(0),pedineInCasella[j]->getValoreColore(1),pedineInCasella[j]->getValoreColore(2)));
    	gradient.setColorAt(1.0, QColor(pedineInCasella[j]->getValoreColore(3),pedineInCasella[j]->getValoreColore(4),pedineInCasella[j]->getValoreColore(5)));
		QPalette p;
		p.setBrush(QPalette::Window,gradient);
		coloreGiocatori[j]->setPalette(p);
		coloreGiocatori[j]->setFixedSize(55,55);
		QFont fontTestoNome("OldEnglish",11,5,true);
		fontTestoNome.setPixelSize(10);
		coloreGiocatori[j]->setFont(fontTestoNome);
		coloreGiocatori[j]->setWordWrap(true);
		coloreGiocatori[j]->setAlignment(Qt::AlignCenter);
		pedineGrandi->addWidget(coloreGiocatori[j],j/pedineRiga,j%pedineRiga);
	}
	esci=new QPushButton("Esci");
	numero=new QLCDNumber(1);
	numero->setSegmentStyle(QLCDNumber::Flat);
	numero->setFixedSize(200,200);
	layoutStrumenti->addWidget(numero);
	layoutStrumenti->addWidget(lancia);
	layoutStrumenti->setSpacing(5);
	layoutStrumenti->addLayout(pedineGrandi);
	layoutStrumenti->setSpacing(2);
	layoutStrumenti->addWidget(infoPartita);
	layoutStrumenti->setSpacing(2);
	layoutStrumenti->addWidget(esci);
	connect(lancia,SIGNAL(clicked()),this,SLOT(lanciaDado()));
	connect(esci,SIGNAL(clicked()),this,SLOT(terminaPartita()));
	mainLayout->setVerticalSpacing(2);
	mainLayout->addWidget(area,1,0);
	mainLayout->setVerticalSpacing(2);
	mainLayout->addLayout(layoutStrumenti,1,1);
	//mainLayout->setAlignment(Qt::AlignCenter);
	for(int i=0;i<g->getNumeroGiocatori();i++){//for per salvare la posizione iniziale delle pedine
		posizionePedine.insert(i,new QPoint((pedineInCasella[i]->riferimWidgetCasella)->pos()));
	}
	setLayout(mainLayout);
}

