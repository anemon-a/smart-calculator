#ifndef DEPOSITCALCULATOR_H
#define DEPOSITCALCULATOR_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>

#include "../controller/controller.h"

namespace Ui {
class DepositWindow;
}
namespace s21 {

class DepositWindow : public QDialog {
  Q_OBJECT

 public:
  explicit DepositWindow(QWidget *parent = nullptr, Controller *d = nullptr);
  ~DepositWindow();

 private slots:
  void on_button_calculate_clicked();
  void on_add_replenishment_clicked();
  void on_add_withdrawal_clicked();

 private:
  double GetDepositAmount();
  Date GetStartDate();
  int GetDepositTerm();
  int GetTypeTerm();
  double GetInterestRate();
  double GetTaxRate();
  int GetPaymentPeriodicityType();
  bool GetCapitalization();
  Deposit::ListDA &GetReplenishment();
  Deposit::ListDA &GetWithdrawal();
  void SetChecksInput();
  void SetValues(s21::Deposit::DepositResult result);
  void ClearValues();

  Ui::DepositWindow *ui;
  Controller *deposit_controller_;
  Deposit::ListDA replenishment_;
  Deposit::ListDA withdrawal_;
  int count_replenishment_;
  int count_withdrawal_;
};
}  // namespace s21

#endif  // DEPOSITCALCULATOR_H
