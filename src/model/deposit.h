#ifndef MODEL_DEPOSIT_H_
#define MODEL_DEPOSIT_H_

#include <cmath>
#include <map>
#include <string>

#include "date.h"

enum periodicity {
  kDaily,
  kWeekly,
  kMonthly,
  kQuarterly,
  kHalfYear,
  kAnnually,
  kAtTheEnd
};

enum DateType { kDays, kMonths, kYears };

namespace s21 {
class Deposit {
 public:
  using ListDA = std::map<Date, double>;
  typedef struct {
    double accrued_interest;
    double tax_amount;
    double deposit_amount_by_end;

  } DepositResult;

  Deposit() = default;
  ~Deposit() = default;
  DepositResult GetResult();
  void CalculateDeposit(double deposit_amount, Date start_date,
                        int deposit_term, int type_term, double interest_rate,
                        double tax_rate, int payment_type, bool capitalization,
                        ListDA& replenisments, ListDA& withdrawals);

 private:
  void SetEndDate(int deposit_term, int type_term);
  void SetNextPaymentDate(int type_term);
  void CheckPaymentDate(double& payment_date, double& current_date);
  void AddAccruedInterest(double deposit_amount, double interest_rate);
  void AddReplenisments(ListDA& replenisments, Date current_date,
                        double& deposit_amount);
  void AddWithdrawals(ListDA& withdrawals, Date current_date,
                      double& deposit_amount);
  void ClearData();

  Date end_date_;
  Date payment_date_;
  double deposit_;
  DepositResult result_;
};
}  // namespace s21

#endif  // _MODEL_DEPOSIT_H_
