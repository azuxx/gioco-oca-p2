#include <QApplication>

#include "guigioco.h"

/* da usare questo prototipo di main per eventuali parametri da
   linea di comando */
int main(int argc, char* argv[]) {   
  // La classe QApplication controlla il flusso di esecuzione della GUI
  QApplication app(argc, argv);
  //dialog
  GuiGioco giocoOca;
  // il main passa il controllo a QT
  return giocoOca.exec();
}
