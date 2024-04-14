#include "depositwindow.h"

#include <QDate>
#include <numeric>

#include "ui_depositwindow.h"

using namespace s21;

DepositWindow::DepositWindow(QWidget* parent, Controller* d)
    : QDialog(parent), ui(new Ui::DepositWindow), deposit_controller_(d) {
  ui->setupUi(this);
  ClearValues();
  SetChecksInput();
  ui->replenishments->horizontalHeader()->setStretchLastSection(true);
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::on_button_calculate_clicked() {
  Deposit::DepositResult result = deposit_controller_->CalculateDeposit(
      GetDepositAmount(), GetStartDate(), GetDepositTerm(), GetTypeTerm(),
      GetInterestRate(), GetTaxRate(), GetPaymentPeriodicityType(),
      GetCapitalization(), GetReplenishment(), GetWithdrawal());
  SetValues(result);
}

void DepositWindow::SetChecksInput() {
  ui->deposit_amount_by_end->setReadOnly(true);
  ui->tax_amount->setReadOnly(true);
  ui->accrued_interest->setReadOnly(true);
  ui->deposit_amount->setValidator(new QRegularExpressionValidator(
      QRegularExpression("^[0-9]*[.,]?[0-9]+$"), this));
  ui->tax_rate->setValidator(new QRegularExpressionValidator(
      QRegularExpression("^[0-9]*[.,]?[0-9]+$"), this));
  ui->interest_rate->setValidator(new QRegularExpressionValidator(
      QRegularExpression("^[0-9]*[.,]?[0-9]+$"), this));
  ui->replenishment->setValidator(new QRegularExpressionValidator(
      QRegularExpression("^[0-9]*[.,]?[0-9]+$"), this));
  ui->withdrawal->setValidator(new QRegularExpressionValidator(
      QRegularExpression("^[0-9]*[.,]?[0-9]+$"), this));
}

void DepositWindow::SetValues(Deposit::DepositResult result) {
  ui->deposit_amount_by_end->setText(
      QString::number(result.deposit_amount_by_end, 'd', 2));
  ui->tax_amount->setText(QString::number(result.tax_amount, 'd', 2));
  ui->accrued_interest->setText(
      QString::number(result.accrued_interest, 'd', 2));
}

void DepositWindow::ClearValues() {
  count_replenishment_ = -1;
  count_withdrawal_ = -1;
  replenishment_ = {};
  withdrawal_ = {};
}

void DepositWindow::on_add_replenishment_clicked() {
  count_replenishment_++;
  ui->replenishments->insertRow(count_replenishment_);
  ui->replenishments->setItem(
      count_replenishment_, 0,
      new QTableWidgetItem(ui->date_replenishment->date().toString()));

  ui->replenishments->setItem(count_replenishment_, 1,
                              new QTableWidgetItem(ui->replenishment->text()));
}

void DepositWindow::on_add_withdrawal_clicked() {
  count_withdrawal_++;
  ui->withdrawals->insertRow(count_withdrawal_);
  ui->withdrawals->setItem(
      count_withdrawal_, 0,
      new QTableWidgetItem(ui->date_withdrawal->date().toString()));

  ui->withdrawals->setItem(count_withdrawal_, 1,
                           new QTableWidgetItem(ui->withdrawal->text()));
}

double DepositWindow::GetDepositAmount() {
  return ui->deposit_amount->text().toDouble();
}

Date DepositWindow::GetStartDate() {
  QDate temp = ui->start_date->date();
  return Date(temp.day(), temp.month(), temp.year());
}

int DepositWindow::GetDepositTerm() { return ui->deposit_term->value(); }

int DepositWindow::GetTypeTerm() { return ui->type_term->currentIndex(); }

double DepositWindow::GetInterestRate() {
  return ui->interest_rate->text().toDouble();
}

double DepositWindow::GetTaxRate() { return ui->tax_rate->text().toDouble(); }

int DepositWindow::GetPaymentPeriodicityType() {
  return ui->payment_periodicity_type->currentIndex();
}

bool DepositWindow::GetCapitalization() {
  return ui->capitalization->isChecked();
}

Deposit::ListDA& DepositWindow::GetReplenishment() {
  QDate date_temp = {};
  double number_temp = 0;
  for (int i = count_replenishment_; i >= 0; i--) {
    date_temp = QDate::fromString(ui->replenishments->item(i, 0)->text());
    number_temp = ui->replenishments->item(i, 1)->text().toDouble();
    replenishment_.insert(std::make_pair(
        Date(date_temp.day(), date_temp.month(), date_temp.year()),
        number_temp));
  }
  return replenishment_;
}

Deposit::ListDA& DepositWindow::GetWithdrawal() {
  QDate date_temp = {};
  double number_temp = 0;
  for (int i = count_withdrawal_; i >= 0; i--) {
    date_temp = QDate::fromString(ui->withdrawals->item(i, 0)->text());
    number_temp = ui->withdrawals->item(i, 1)->text().toDouble();
    withdrawal_.insert(std::make_pair(
        Date(date_temp.day(), date_temp.month(), date_temp.year()),
        number_temp));
  }
  return withdrawal_;
}
