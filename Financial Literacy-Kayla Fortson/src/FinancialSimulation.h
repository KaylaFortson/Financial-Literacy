#include <stdio.h>
#include <stdbool.h>

typedef struct financialIdentity_struct{
  double savings;
  double checking;
  double debt;
  double mortgage;
  int yearsWithDebt;
  int yearsRented;
  double debtPaid;
  bool ownsHouse;
}financialIdentity;

//Prints all of the person's stats
void printPerson(financialIdentity *person);


//Takes in a person struct (either f.l. or n.f.l.) and a yearly interestRate, and modifies that financialIdentity_struct
//to reflect that person's savings after one year. Only savings should change
void savingsPlacement(financialIdentity *person, double interestRate);

//Applies monthly payments and updates the amount of remaining debt a person has and the amount of money they have left in
//savings and checkings accounts after one year. debt models credit card and student loan debt
void debt(financialIdentity *person, double interestRate, double addlPay);



//updates the amount of money a person will have left in their checking and savings accounts after  one year
//If in rented apartment rentAmount is the monthly rent. The yearsRented entry should be updated for the person
//each year. If F.l. or n.f.l. doesn't have enough money in checking they using savings to pay difference
void rent(financialIdentity *person, double rentAmount);



//updates amount of money a person will have in their checking and savings after one year, if they live in a house and thus pay
//mortage payments. mortgageAmount is the house price minus the down payment. InterestRate is the yearly interest rate, and
//mortgageTerm is the number of years that the mortgage has to be paid off by
void house(financialIdentity *person, double mortgageAmount,double interestRate, int mortgageTerm);


//FIXME
//Uses all previous functions as helper functions to simulate how much f.l. and n.f.l. will have after 40 years
//returns a struct containing an array (will apply once struct is created)
int* simulate(financialIdentity *person, double yearlySalary, bool financiallyLiterate);
