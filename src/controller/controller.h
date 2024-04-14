#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <vector>

#include "../model/calculator.h"
#include "../model/credit.h"
#include "../model/deposit.h"

namespace s21 {

class Controller {
 public:
  Controller(Calculator *m, Credit *c, Deposit *d);
  ~Controller();
  double CalculateValue(std::string expression, double x);
  Calculator::CoordinatesXY &CalculateGraph(std::string expression,
                                            int number_of_points,
                                            double x_start, double x_end,
                                            double y_min, double y_max);
  Credit::CreditResult CalculateCredit(bool type, double credit_amount,
                                       double period, double rate);

  Deposit::DepositResult CalculateDeposit(double deposit_amount,
                                          Date start_date, int deposit_term,
                                          int type_term, double interest_rate,
                                          double tax_rate, int payment_type,
                                          bool capitalization,
                                          Deposit::ListDA &replenisments,
                                          Deposit::ListDA &withdrawals);

 private:
  Calculator *calculator_model_;
  Credit *credit_model_;
  Deposit *deposit_model_;
};
}  // namespace s21

#endif  // CONTROLLER_H_
