#include "deposit.h"

void s21::Deposit::CalculateDeposit(double deposit_amount, Date start_date,
                                    int deposit_term, int type_term,
                                    double interest_rate, double tax_rate,
                                    int payment_type, bool capitalization,
                                    ListDA& replenisments,
                                    ListDA& withdrawals) {
  ClearData();
  double accrued_interest_receivable = 0;
  deposit_ = deposit_amount;
  end_date_ = start_date;
  payment_date_ = start_date;
  SetEndDate(deposit_term, type_term);
  AddReplenisments(replenisments, start_date, deposit_amount);
  AddWithdrawals(withdrawals, start_date, deposit_amount);
  SetNextPaymentDate(payment_type);
  start_date.Add(1, 0, 0);
  while (end_date_ >= start_date) {
    AddAccruedInterest(deposit_amount, interest_rate);
    if (start_date == payment_date_) {
      if (capitalization) {
        deposit_amount += round(result_.accrued_interest * 100.) / 100.;
      } else {
        accrued_interest_receivable +=
            round(result_.accrued_interest * 100.) / 100.;
      }
      result_.accrued_interest = 0;
      SetNextPaymentDate(payment_type);
    }
    AddReplenisments(replenisments, start_date, deposit_amount);
    AddWithdrawals(withdrawals, start_date, deposit_amount);
    start_date.Add(1, 0, 0);
  }
  result_.accrued_interest =
      accrued_interest_receivable + deposit_amount - deposit_;
  result_.deposit_amount_by_end = deposit_amount;
  result_.tax_amount =
      round(((result_.accrued_interest) * tax_rate / 100.) * 100.) / 100.;
}

void s21::Deposit::SetEndDate(int deposit_term, int type_term) {
  switch (type_term) {
    case kDays:
      end_date_.Add(deposit_term, 0, 0);
      break;
    case kMonths:
      end_date_.Add(0, deposit_term, 0);
      break;
    case kYears:
      end_date_.Add(0, 0, deposit_term);
      break;
  }
}

void s21::Deposit::AddAccruedInterest(double deposit_amount,
                                      double interest_rate) {
  result_.accrued_interest += deposit_amount * interest_rate / 100.0 / 365;
}

void s21::Deposit::AddReplenisments(ListDA& replenisments, Date current_date,
                                    double& deposit_amount) {
  auto it = replenisments.find(current_date);
  if (it != replenisments.end()) {
    deposit_amount += it->second;
    deposit_ += it->second;
    replenisments.erase(it);
  }
}

void s21::Deposit::AddWithdrawals(ListDA& withdrawals, Date current_date,
                                  double& deposit_amount) {
  auto it = withdrawals.find(current_date);
  if (it != withdrawals.end()) {
    deposit_amount -= it->second;
    deposit_ -= it->second;
    withdrawals.erase(it);
  }
}

void s21::Deposit::SetNextPaymentDate(int type_term) {
  switch (type_term) {
    case kDaily:
      payment_date_.Add(1, 0, 0);
      break;
    case kWeekly:
      payment_date_.Add(7, 0, 0);
      break;
    case kMonthly:
      payment_date_.Add(0, 1, 0);
      break;
    case kQuarterly:
      payment_date_.Add(0, 3, 0);
      break;
    case kHalfYear:
      payment_date_.Add(0, 6, 0);
      break;
    case kAnnually:
      payment_date_.Add(0, 0, 1);
      break;
    case kAtTheEnd:
      payment_date_ = end_date_;
      break;
  }
  if (payment_date_ >= end_date_) {
    payment_date_ = end_date_;
  }
}

s21::Deposit::DepositResult s21::Deposit::GetResult() { return result_; }

void s21::Deposit::ClearData() { result_ = {}; }
