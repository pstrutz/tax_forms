#include <iostream>
#include <stdlib.h>
#include <map>


void get_user_input(char& user_char) {
  std::cout << "Please enter y for yes and n for no.\n";
  while (1){
    std::cin >> user_char;
    if (user_char == 'y' || user_char == 'n') {
      break;
    }
  std::cout << "\nPoor input, try again.\n";
  }
}

int substantialPresenceTest() {
  char user_char;
  int user_num;
  std::cout << "\nHow long have you been in the USA? \n"
  << "Please enter a number in years. Include partial years and the year for which you are filing taxes.\n";
  std::cin >> user_num;
  if (user_num > 5) {
    std::cout << "\nWere you physically present (including partial days) in the US on at least\n"
    << "a) 31 days during the tax year and \n"
    << "b) 183 days during the tax year and the two years before that, counting 1/3 of days the year before and 1/6 of days two years before\n";
    get_user_input(user_char);
    if (user_char == 'y') return 1;
    if (user_char == 'n') return 0;
  } else {
    return 0;
  }
  abort();
}

void compile_forms(std::map<std::string, bool>& forms) {
  std::cout << "\n\nThe forms you need to fill out are: \n";
  std::map<std::string, bool>::iterator it;
  for (it = forms.begin(); it != forms.end(); ++it) {
    if (it->second) {
        std::cout << "Form " << it->first << std::endl;
    }
  }
  std::cout << "Nothing else is needed. Thank you for using this program.";
  exit(0);
}

void is_nonresident_alien(std::map<std::string, bool>& forms) {
  char user_char;
  forms["8843"] = true; 
  
  std::cout << "Did you receive a Form W-2 or Form 1099?\n";
  get_user_input(user_char);
  if (user_char == 'y') {
    forms["1040-NR"] = true; 
    forms["Schedule OI"] = true; 

    std::cout << "Did you receive taxable scholarships or fellowships?\n";
    get_user_input(user_char);
    if (user_char == 'y') {
      forms["1042-S"] = true;
      forms["Schedule 1"] = true;
    } 

    std::cout << "Are you from a country that has a tax-treaty with the US and want to claim benefits related to this?\n";
    get_user_input(user_char);
    if (user_char == 'y') forms["Schedule OI"] = true;
  
    std::cout << "Did you receive interest from a US corporate bond or non-bank source?\n";
    get_user_input(user_char);
    if (user_char == 'y') forms["Schedule NEC"] = true;

    std::cout << "Do you want to itemize deductions?\n";
    get_user_input(user_char);
    if (user_char == 'y') forms["Schedule A 1040-NR"] = true;

    compile_forms(forms);

  } else if (user_char == 'n') compile_forms(forms);

}

void is_resident_alien(std::map<std::string, bool>& forms) {
  char user_char; 
  
  std::cout << "Did you receive a Form W-2 or Form 1099, and did your taxable income exceed the standard deduction threshold?\n";
  get_user_input(user_char);
  if (user_char == 'y') {
    forms["1040"] = true; 

    std::cout << "Did you receive taxable scholarships or fellowships?\n";
    get_user_input(user_char);
    if (user_char == 'y') {
      forms["Schedule 1"] = true;
    } 

    std::cout << "Did you have income from self-employment?\n";
    get_user_input(user_char);
    if (user_char == 'y') forms["Schedule 2"] = true;
  
    std::cout << "Did you receive interest or dividends of more than $1500 or interests from a foreign bank?\n";
    get_user_input(user_char);
    if (user_char == 'y') forms["Schedule B"] = true;

    std::cout << "Do you want to itemize deduction or use the standard deductions?\n";
    get_user_input(user_char);
    if (user_char == 'y') forms["Schedule A 1040"] = true;

    std::cout << "Do you have nonrefundable or refundable tax credits to report?\n";
    get_user_input(user_char);
    if (user_char == 'y') forms["Schedule 3"] = true;

    compile_forms(forms);

  } else if (user_char == 'n') compile_forms(forms);

}


int main(){
  std::string user_name = "";
  int user_num;
  char user_char;

  // All forms supported by this program
  // Map can be expanded
  std::map<std::string, bool> forms;
  forms["1040"] = false;
  forms["8843"] = false;
  forms["1040-NR"] = false;
  forms["Schedule 1"] = false;
  forms["Schedule 2"] = false;
  forms["Schedule 3"] = false;
  forms["Schedule A 1040"] = false;
  forms["Schedule A 1040-NR"] = false;
  forms["Schedule B"] = false;
  forms["Schedule OI"] = false;
  forms["Schedule NEC"] = false;
  forms["1042-S"] = false;

  std::cout << "Hello. Use this program and answer a few questions to determine which tax forms you need to file.\n"
  << "Press ENTER to continue.\n";
  while (std::cin.get() != '\n') {
  continue;
  }

  // Get User Name to Personalize Program
  std::cout << "To begin, what is your name?\n";
  getline(std::cin,user_name);
  
  // Determine VISA Type
  std::cout << "\nThank you " << user_name << "! Now, what type of VISA do you have?\n"
  << "1) F1 \n2) J1 \n3) H1B \n4) Other/No VISA\n"
  << "Please enter the number corresponding to your VISA.\n";
  std::cin >> user_num;
  
  // Based on VISA Type, determine next step
  if (user_num == 3 || user_num == 4) {
    std::cout << "Unfortunately, this is not supported yet.";
    exit(0);
  } else if (user_num == 1 || user_num == 2) {
    int resident_alien = substantialPresenceTest();
    
    if (resident_alien) {
      is_resident_alien(forms);
    } else {
      is_nonresident_alien(forms);
    }
    
  } else { // something went wrong
    abort();
  }
}
