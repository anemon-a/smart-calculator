#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QVector>

#include "../controller/controller.h"
#include "qcustomplot.h"

namespace Ui {
class GraphWindow;
}
namespace s21 {
class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget *parent = nullptr, Controller *gc = nullptr,
                       std::string *exp = nullptr);
  ~GraphWindow();

 private slots:

  void on_replot_clicked();

 private:
  Ui::GraphWindow *ui;
  Controller *graph_controller_;
  std::string *expression_;
  void SetStartValues();
  double GetMinX();
  double GetMaxX();
  double GetMinY();
  double GetMaxY();
  void PrintGraph();
};
}  // namespace s21

#endif  // GRAPHWINDOW_H
