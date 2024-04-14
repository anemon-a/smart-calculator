#include <QApplication>

#include "controller/controller.h"
#include "view/mainwindow.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Calculator model;
  Credit credit_model;
  Deposit deposit_model;
  Controller controller(&model, &credit_model, &deposit_model);
  MainWindow w(&controller);
  w.show();
  return a.exec();
}
