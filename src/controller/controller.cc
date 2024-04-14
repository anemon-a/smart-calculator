#include "../controller/controller.h"

s21::Controller::Controller(Calculator* m, Credit* c, Deposit* d)
    : calculator_model_(m), credit_model_(c), deposit_model_(d) {}

s21::Controller::~Controller() {}

double s21::Controller::CalculateValue(const std::string expression, double x) {
  calculator_model_->ParseToTokens(expression);
  calculator_model_->ConvertToPostfix();
  return calculator_model_->CalculatePostfix(x);
}

s21::Calculator::CoordinatesXY& s21::Controller::CalculateGraph(
    std::string expression, int number_of_points, double x_start, double x_end,
    double y_min, double y_max) {
  calculator_model_->ParseToTokens(expression);
  calculator_model_->ConvertToPostfix();
  calculator_model_->CalculateCoordinates(number_of_points, x_start, x_end,
                                          y_min, y_max);
  return calculator_model_->GetGraphCoordinates();
}

s21::Credit::CreditResult s21::Controller::CalculateCredit(bool type,
                                                           double credit_amount,
                                                           double period,
                                                           double rate) {
  if (type) {
    credit_model_->CalculateAnnuityCredit(credit_amount, period, rate);
  } else {
    credit_model_->CalculateDifferentiatedCredit(credit_amount, period, rate);
  }
  return credit_model_->GetResultValues();
}

s21::Deposit::DepositResult s21::Controller::CalculateDeposit(
    double deposit_amount, Date start_date, int deposit_term, int type_term,
    double interest_rate, double tax_rate, int payment_type,
    bool capitalization, Deposit::ListDA& replenisments,
    Deposit::ListDA& withdrawals) {
  deposit_model_->CalculateDeposit(
      deposit_amount, start_date, deposit_term, type_term, interest_rate,
      tax_rate, payment_type, capitalization, replenisments, withdrawals);
  return deposit_model_->GetResult();
}
