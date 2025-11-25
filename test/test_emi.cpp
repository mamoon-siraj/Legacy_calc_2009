#include "gtest/gtest.h"
#include "../src/Loan.h" // Includes the corrected header file
#include <cmath>
#include <limits> 
#include <stdexcept> // For exception handling

namespace {

// Helper to set up the calculator for testing
LoanCalculator setup_calculator(long double principal, long double rate, int periods) {
    LoanCalculator calc;
    // Uses the validated setters you just fixed
    calc.setAmount(principal);
    calc.setInterest(rate);
    calc.setPeriodTotal(periods); 
    return calc;
}

// 1. Normal EMI Calculation Test
TEST(LoanCalculatorTest, NormalPaymentCalculation) {
    // 100,000 loan at 12% Annual Interest Rate for 10 years (120 months)
    long double principal = 100000.0;
    long double annual_rate = 12.0; 
    int tenure_months = 120;
    long double expected_payment = 1434.71; 
    
    LoanCalculator calc = setup_calculator(principal, annual_rate, tenure_months);
    long double calculated_payment = calc.calculatePayment();

    EXPECT_NEAR(calculated_payment, expected_payment, 0.01); 
}

// 2. Invalid Input Handling Test (Confirms Task 2 Bug Fix: Negative Input)
TEST(LoanCalculatorTest, HandlesInvalidInput) {
    // Test 1: Negative Principal (setAmount must throw invalid_argument)
    EXPECT_THROW({
        LoanCalculator calc;
        // This line attempts to set a negative amount, triggering the exception you added
        calc.setAmount(-10000.0);
    }, std::invalid_argument);

    // Test 2: Zero Tenure (setPeriodTotal must throw invalid_argument)
    EXPECT_THROW({
        LoanCalculator calc;
        // This line attempts to set a zero period, triggering the exception you added
        calc.setPeriodTotal(0);
    }, std::invalid_argument);
}

// 3. Large Tenure Calculations without Overflow Test (Confirms Task 2 Bug Fix: Long Double)
TEST(LoanCalculatorTest, NoOverflowWithLargeTenure) {
    // Test case: 30 years (360 months). Checks the long double fix and no crash.
    long double principal = 500000.0;
    long double annual_rate = 5.0; 
    int large_tenure_months = 360; 
    long double expected_payment = 2684.11; 
    
    LoanCalculator calc = setup_calculator(principal, annual_rate, large_tenure_months);
    long double result = calc.calculatePayment();
    
    // Check 1: Should not result in an error state (NaN/Inf)
    EXPECT_FALSE(std::isinf(result));
    EXPECT_FALSE(std::isnan(result));
    
    // Check 2: Check if it's close to the actual expected value
    EXPECT_NEAR(result, expected_payment, 0.01);
}

} // namespace