#include "FinancialSimulation.h"
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  financialIdentity fl = {
    5000.0, // savings
    0.0, // checking
    52500.0, // debt
    0.0, //175000.0 mortgage
    0, // years with debt
    0, // years rented
    0.0, // debt paid
    false // owns house?
  };

  financialIdentity nfl = {
    5000.0, // savings
    0.0, // checking
    52500.0, // debt
    0.0, //175000.0 mortgage
    0, // years with debt
    0, // years rented
    0.0, // debt paid
    false // owns house?
  };

  FILE* fl_file = fopen(argv[1], "w");
  FILE* nfl_file = fopen(argv[2], "w");

  if(fl_file == NULL){
    printf("Could not open file for financiallyLiterate. (output_fl.txt)\n");
    return -1;
  }

  if(nfl_file == NULL){
    printf("Could not open file for not financiallyLiterate. (output_nfl.txt)\n");
    return -1;
  }
  


  printf("Test Simulate\n\n");
  int* fl_years = (int*)malloc(41*(sizeof(int)));
  fprintf(fl_file, "WEALTH RESULTS FOR FINANCIALLY LITERATE\n");
  fprintf(fl_file, "---------------------------------------------------------------\n");
  fprintf(fl_file, "Person's Statistics: \n");
  fprintf(fl_file, "Checking: %f\n", fl.checking);
  fprintf(fl_file, "Savings: %f\n", fl.savings);
  fprintf(fl_file, "Debt: %f\n", fl.debt);
  fprintf(fl_file, "Debt Paid: %f\n", fl.debtPaid);
  fprintf(fl_file, "Years With Debt: %d\n", fl.yearsWithDebt);
  fprintf(fl_file, "Mortgage: %f\n", fl.mortgage);
  fprintf(fl_file, "Years Rented: %d\n", fl.yearsRented);
  fprintf(fl_file, "Owns House (1 = True, 0 = False): %d\n", fl.ownsHouse);
  fprintf(fl_file, "---------------------------------------------------------------\n");
  fl_years = simulate(&fl,69000, true); //yearlySalary of $69,000
  for(int i = 0; i< 41;i++){
    fprintf(fl_file, "Year: %d, %d\n", i,fl_years[i]);
  }
  fprintf(fl_file, "---------------------------------------------------------------\n");
  fprintf(fl_file, "Person's Statistics: \n");
  fprintf(fl_file, "Checking: %f\n", fl.checking);
  fprintf(fl_file, "Savings: %f\n", fl.savings);
  fprintf(fl_file, "Debt: %f\n", fl.debt);
  fprintf(fl_file, "Debt Paid: %f\n", fl.debtPaid);
  fprintf(fl_file, "Years With Debt: %d\n", fl.yearsWithDebt);
  fprintf(fl_file, "Mortgage: %f\n", fl.mortgage);
  fprintf(fl_file, "Years Rented: %d\n", fl.yearsRented);
  fprintf(fl_file, "Owns House (1 = True, 0 = False): %d\n", fl.ownsHouse);
  fprintf(fl_file, "---------------------------------------------------------------\n");



  printf("Test Simulate\n\n");
  int* nfl_years = (int*)malloc(41*(sizeof(int)));
  fprintf(nfl_file, "WEALTH RESULTS FOR NOT FINANCIALLY LITERATE\n");
  fprintf(nfl_file, "---------------------------------------------------------------\n");
  fprintf(nfl_file, "Person's Statistics: \n");
  fprintf(nfl_file, "Checking: %f\n", nfl.checking);
  fprintf(nfl_file, "Savings: %f\n", nfl.savings);
  fprintf(nfl_file, "Debt: %f\n", nfl.debt);
  fprintf(nfl_file, "Debt Paid: %f\n", nfl.debtPaid);
  fprintf(nfl_file, "Years With Debt: %d\n", nfl.yearsWithDebt);
  fprintf(nfl_file, "Mortgage: %f\n", nfl.mortgage);
  fprintf(nfl_file, "Years Rented: %d\n", nfl.yearsRented);
  fprintf(nfl_file, "Owns House (1 = True, 0 = False): %d\n", nfl.ownsHouse);
  fprintf(nfl_file, "---------------------------------------------------------------\n");
  nfl_years= simulate(&nfl,69000, false); //yearlySalary of $69,000
  for(int i = 0; i< 41;i++){
    fprintf(nfl_file, "Year: %d, %d\n", i,nfl_years[i]);
  }
  fprintf(nfl_file, "---------------------------------------------------------------\n");
  fprintf(nfl_file, "Person's Statistics: \n");
  fprintf(nfl_file, "Checking: %f\n", nfl.checking);
  fprintf(nfl_file, "Savings: %f\n", nfl.savings);
  fprintf(nfl_file, "Debt: %f\n", nfl.debt);
  fprintf(nfl_file, "Debt Paid: %f\n", nfl.debtPaid);
  fprintf(nfl_file, "Years With Debt: %d\n", nfl.yearsWithDebt);
  fprintf(nfl_file, "Mortgage: %f\n", nfl.mortgage);
  fprintf(nfl_file, "Years Rented: %d\n", nfl.yearsRented);
  fprintf(nfl_file, "Owns House (1 = True, 0 = False): %d\n", nfl.ownsHouse);
  fprintf(nfl_file, "---------------------------------------------------------------\n");

  fclose(fl_file);
  fclose(nfl_file);
  return 0;
}

//Prints all of the person's stats
void printPerson(financialIdentity *person){
  printf("---------------------------------------------------------------\n");
  printf("Person's Statistics: \n");
  printf("Checking: %f\n", person -> checking);
  printf("Savings: %f\n", person -> savings);
  printf("Debt: %f\n", person -> debt);
  printf("Debt Paid: %f\n", person -> debtPaid);
  printf("Years With Debt: %d\n", person -> yearsWithDebt);
  printf("Mortgage: %f\n", person -> mortgage);
  printf("Years Rented: %d\n", person -> yearsRented);
  printf("Owns House (1 = True, 0 = False): %d\n", person -> ownsHouse);
  printf("---------------------------------------------------------------\n");

}

//Takes in a person struct (either f.l. or n.f.l.) and a yearly interestRate, and modifies that financialIdentity_struct
//to reflect that person's savings after one year. Only savings should change
void savingsPlacement(financialIdentity *person, double interestRate){
  person -> savings = (1 + interestRate) * person->savings;
}

//Applies monthly payments and updates the amount of remaining debt a person has and the amount of money they have left in
//savings and checkings accounts after one year. debt models credit card and student loan debt
void debt(financialIdentity *person, double interestRate, double addlPay){
  int month = 1;
  double debtToBePaid = (person -> debt * .03)   + addlPay; //paying off 3% of debt each month  (Hardcoded)
  //printf("Debt to be paid per month: %f\n", debtToBePaid);



  if(person -> debt < 0){
    printPerson(person);
  }

  while((month <= 12) && (person -> debt > 0)){
    if (debtToBePaid > person -> debt){
      debtToBePaid = person -> debt; //Ensure there are no overcharges for the remaining year's debt
    }
    //printf("Person's Debt %f\n", person -> debt);
    if(person -> checking >= debtToBePaid){
      person -> checking -= debtToBePaid;
      person -> debt -= debtToBePaid;
      person -> debtPaid += debtToBePaid;
      //printf("Loop 1 %f\n",person -> debtPaid);
    } else {
      double diff = debtToBePaid - person -> checking;
      //printf("Difference: %f\n", diff);
      person -> checking = 0;
      if (person -> savings >= diff){ //pay remaining balance from savings
      person -> savings -= diff;
      person -> debt -= debtToBePaid;
      person -> debtPaid += debtToBePaid;
      //printf("Loop 2 %f\n",person -> debtPaid);
    } else { //savings did not have sufficient funds
      printf("Insufficuent funds in savings\n");
      double totalDebtAbleToPay = 0;
      if (person -> savings > 0){
      totalDebtAbleToPay = person -> savings;
      }
      printf("Total Debt Able to Pay: %f\n", totalDebtAbleToPay);
      person -> savings -= diff; // may enter negative values;
      person -> debt -= totalDebtAbleToPay; //still remaining debt balance
      person -> debtPaid += totalDebtAbleToPay;
      //printf("Loop 3 %f\n",person -> debtPaid);
    }

    }
    month += 1;
  }

  if(person -> debt > 0){
    person -> yearsWithDebt += 1;
  }
  person -> debt = person -> debt * (1 + interestRate);
}


//updates the amount of money a person will have left in their checking and savings accounts after  one year
//If in rented apartment rentAmount is the monthly rent. The yearsRented entry should be updated for the person
//each year. If F.l. or n.f.l. doesn't have enough money in checking they using savings to pay difference
void rent(financialIdentity *person, double rentAmount){
  //printf("Total Rent Amount for One Year: %f\n",rentAmount * 12);
  if(person -> checking >= rentAmount * 12){
    person -> checking -= rentAmount * 12;
  } else{
    double diff = (rentAmount * 12) - person -> checking;
    person -> checking = 0;
    if (person -> savings > diff){
      person -> savings -= diff;
    } else {
    printf("Insufficuent funds in savings\n");
    person -> savings -= diff; //may enter negative values
    }
  }
  person -> yearsRented += 1;

}

//updates amount of money a person will have in their checking and savings after one year, if they live in a house and thus pay
//mortage payments. mortgageAmount is the house price minus the down payment. InterestRate is the yearly interest rate, and
//mortgageTerm is the number of years that the mortgage has to be paid off by
void house(financialIdentity *person, double mortgageAmount,double interestRate, int mortgageTerm){
  int n = mortgageTerm * 12; //number of payments
  double i = interestRate / 12; //monthly interest
  double d = ((pow((1+i),n) - 1)/(i*pow((1+i),n)));
  double monthlyPayment = mortgageAmount/d;
  //printf("Mortgage to be paid per month: %.15f\n", monthlyPayment);
  int month = 1;
  while((month <= 12) && (person -> mortgage > 0)){
    if (monthlyPayment > person -> mortgage){
      monthlyPayment = person -> mortgage; //Ensure there are no overcharges for the remaining year's debt
    }
    if(person -> checking > monthlyPayment){
      person -> checking -= monthlyPayment;
      person -> mortgage -= monthlyPayment;
    } else {
      double diff = monthlyPayment - person -> checking;
      if(person -> savings > diff){
        person -> savings -= diff;
        person -> mortgage -= monthlyPayment;
      } else {
        printf("Insufficient funds in savings. \n");
        double totalMortgageAbleToPay = 0;
        if (person -> savings > 0){
        totalMortgageAbleToPay = person -> savings;
        }
        person -> savings -= diff; // may enter negative values
        person -> mortgage -= totalMortgageAbleToPay; //still remaining mortgage
      }
    }
    month += 1;
  }
  person -> mortgage = person -> mortgage * (1 + interestRate);
}


//Uses all previous functions as helper functions to simulate how much f.l. and n.f.l. will have after 40 years
//returns a struct containing an array (will apply once struct is created)
int* simulate(financialIdentity *person, double yearlySalary, bool financiallyLiterate){
  printPerson(person);
  int size = 41;
  int* years = (int*)malloc(size*(sizeof(int)));
  int wealth; //checkings + savings - debt - mortgage per year
  years[0] = -47500; //Initialize to initial savings - debt;

  for(int i = 1; i < size; i++){
    person -> checking += yearlySalary * 0.3; //Income = $20700 per year
    person -> savings += yearlySalary * 0.2; //Income = $13800 per year
    if(financiallyLiterate==1){
      //printf("Financial Starting year with: \n");
      //printPerson(person);
      savingsPlacement(person, .07); //InterestRate of 7% due to mutual fund
      //printf("Check savings balance: %f\n", person -> savings);
      debt(person, .20, 100);   // 20% InterestRate with $100 additional pay
      //printf("Check balances after debt payments: \n");
      //printPerson(person);
      if(person -> ownsHouse == 1){ //pay mortgage
      house(person, person -> mortgage, 0.045, 30); //4.5% interestRate, mortgageTerm = 30 years
      //printf("Check balances after mortgage payments: \n");
      //printPerson(person);
    }else if ((person -> checking + person -> savings) > 42000) { //Check if can afford home with downpayment on 20% = $42000
      //printf("Just bought home!\n");
      person -> ownsHouse = 1;
      person -> mortgage = 168000;
      if(person -> checking > 42000){
        person -> checking -= 42000;
      } else {
        double diff = 42000 - person -> checking;
        person -> checking = 0;
        person -> savings -= diff;
      }
      //printPerson(person);
      }else { //pay rent
        //printf("Loop 3\n");
        rent(person, 950);
        //printf("Check balances after rent payments: \n");
        //printPerson(person);
      }
    }else { //Not financiallyLiterate Individual
      //printf("\nNon-Financial Starting year with: \n");
      //printPerson(person);
      savingsPlacement(person, 0.01); //InterestRate of 1% due to savings account
      debt(person, .20, 1); //20% InterestRate with $1 additional pay
      if(person -> ownsHouse == 1){ //pay mortgage
      house(person, person -> mortgage,0.05, 30); //5% InterestRate, mortgageTerm = 30 years
    }else if ((person -> checking + person -> savings) > 10500) { //Check if can afford home with downpayment on 5% = $10500
      //printf("Just bought home!\n");
      person -> ownsHouse = 1;
      person -> mortgage = 199500;
      if(person -> checking > 10500){
        person -> checking -= 10500;
      } else {
        double diff = 10500 - person -> checking;
        person -> checking = 0;
        person -> savings -= diff;
      }
      }else { //pay rent
        rent(person, 950);
      }
    }


    wealth = (person -> checking + person -> savings) - (person -> debt + person -> mortgage); //can be negative at initial years due to debt/mortgage outweighing savings and checkings
    years[i]=wealth;
  }

  printf("\n\n\n\n\nWEALTH RESULTS-------------------------------------------------\n");
  for(int i = 0; i< size;i++){
    printf("Year: %d, %d\n", i,years[i]);
  }
  printPerson(person);
  printf("\n\n\n\n\n");
  return years;
}
