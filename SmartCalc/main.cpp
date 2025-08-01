#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("Smart_Calc_V1.0");
  w.setFixedSize(w.geometry().width(), w.geometry().height());
  w.show();
  return a.exec();
}
