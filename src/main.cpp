#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cmath>
#include "../src/Loan.h"

using namespace std;


int main(int argc, char **argv)
{
  LoanCalculator calculator;
  
  if (argc < 7 || string(argv[1]) != "-cp") {
      cerr << "Usage: ./calc -cp -a <amount> -i <rate> -N <months>" << endl;
      cerr << "Error: Only Monthly Payment (-cp) calculation is supported." << endl;
      return 1;
  }

  try {
      for (int i = 1; i < argc; ++i) {
          string arg = argv[i];
          
          if (arg == "-a" && i + 1 < argc) {
              calculator.setAmount(stold(argv[i + 1])); 
          } else if (arg == "-i" && i + 1 < argc) {
              calculator.setInterest(stold(argv[i + 1]));
          } else if (arg == "-N" && i + 1 < argc) {
              calculator.setPeriodTotal(stoi(argv[i + 1]));
          }
      }
  } 
  catch (const std::exception& e) {
      cerr << "Input Error: Invalid number format used. " << e.what() << endl;
      return 1;
  }

  try {
    cout << endl;
    long double payment = calculator.calculatePayment();

    cout << "Monthly Payment    = " << payment << "\n"
         << "Total amt paid     = " << (payment * calculator.getPeriodTotal()) << endl;

    if(calculator.getOpeningPercent() != 0.0 || calculator.getOpeningFee() != 0.0) {
      cout << "Interest with fees = " << calculator.calculateEffectiveInterestRate() << "%" << endl;
    }

    cout << calculator.toString() << endl;
  }
  catch(const std::exception &e) {
    cerr << "Error executing loan calculator: " << e.what() << endl;
    return 1;
  }

  cout << endl;
  return 0;
}