#include "../model/credit.h"

void s21::Credit::CalculateAnnuityCredit(double credit_amount, double period,
                                         double rate) {
  ClearData();
  double mounthly_rate = rate / 12.0 / 100.0;
  result_.monthly_payment.push_back(credit_amount * mounthly_rate *
                                    powl(1 + mounthly_rate, period) /
                                    (powl(1 + mounthly_rate, period) - 1));
  result_.total_payment = result_.monthly_payment.back() * period;
  result_.overpayment = result_.total_payment - credit_amount;
}

void s21::Credit::CalculateDifferentiatedCredit(double credit_amount,
                                                double period, double rate) {
  ClearData();
  double mounthly_rate = rate / 12.0 / 100.0;
  for (int i = 0; i < period; ++i) {
    result_.monthly_payment.push_back(
        credit_amount / period +
        (credit_amount - credit_amount / period * i) * mounthly_rate);
    result_.total_payment += result_.monthly_payment.back();
  }
  result_.overpayment = result_.total_payment - credit_amount;
}

s21::Credit::CreditResult s21::Credit::GetResultValues() { return result_; }

void s21::Credit::ClearData() { result_ = {}; }