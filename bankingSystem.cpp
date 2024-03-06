#include <iostream>
#include <fstream> //creating file and storing data


bool isAccountNumber1Empty(const std::string& accountNumber) {
    return accountNumber.empty();
}

int main(){

    int option; //menu picks
    std::string name, dob, address, numberID; //switch statement case 1 strings

    double balance = 0; // account balance amount
    int deposit; 
    int withdraw;

    std::string accountNumber = "LT1234567890"; //IBAN number
    std::string accountnumber1;
    char subOption;

    char consent; //consent of account closure

    std::ofstream file; //mentioned here, so it could be used in case 6
    
    while (true) {
        std::cout << "MAIN MENU \n";
        std::cout << "01. NEW ACCOUNT \n"
                  << "02. DEPOSIT AMOUNT \n"
                  << "03. WITHDRAW AMOUNT \n"
                  << "04. ACCOUNT BALANCE \n"
                  << "05. ACCOUNT NUMBER \n"
                  << "06. CLOSE MY ACCOUNT \n"
                  << "07. MODIFY AN ACCOUNT \n"
                  << "08. EXIT \n";
        std::cout << "Select your option (1-8): ";
        std::cin >> option;

        if(option < 1 || option > 8){
        std::cout << "There is no such option! \n";
        std::cout << "PLEASE TAKE YOUR CARD!";
        return 0;
        }

        switch (option){
        case 1: {
            std::ofstream file("newAccount.txt");
            if(file.is_open()) {
                std::cout << "Enter your name and surname: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                std::cout << "Enter your date of birth (YYYY-MM-DD): ";
                std::getline(std::cin, dob);

                std::cout << "Enter your address (street, house/apartment number, city, postal code): ";
                std::getline(std::cin, address);

                std::cout << "Enter your personal identification number: ";
                std::getline(std::cin, numberID);

                file << "Name: " << name << "\n";
                file << "Date of birth: " << dob << "\n";
                file << "Address: " << address << "\n";
                file << "Personal identification number: " << numberID << "\n";

                std::cout << "Account created successfully. \n";
                file.close();
            }else {
                std::cout << "Unable to create account file. \n";
            }
            break;
        }
        case 2: {
            std::cout << "How much you would like to deposit?: ";
            std::cin >> deposit;
            balance += deposit;

            std::cout << "You have successfully deposited: " << deposit << " $ \n";
            break;
        }
        case 3: {
            std::cout << "How much you would like to withdraw?: ";
            std::cin >> withdraw;

            if(withdraw <= 0){
                std::cout << "Invalid withdrawal amount. Please enter a positive value. \n";
            }else if(balance < withdraw){
                std::cout << "You don't have enough funds to withdraw this amount. \n";
            }else{
                balance -= withdraw;
                std::cout << "You have successfully withdrawed: " << withdraw << " $ \n";
            }
            break;
        }
        case 4: {
            std::cout << "Your current account balance is: " << balance << " $ \n";
            break;
        }
        case 5: {
            std::cout << "Your account numbers are: \n" << accountNumber << "\n" << accountnumber1 << "\n";
            std::cout << "---------------------------- \n";
            std::cout << "A. CREATE ADDITIONAL IBAN \n"
                      << "B. DELETE ADDITIONAL IBAN \n"
                      << "C. EXIT TO MAIN MENU \n"
                      << "Select your option (A-C): ";
            std::cin >> subOption;

            switch(subOption){
                case 'A':
                case 'a':
                    if(accountnumber1.empty()){
                        accountnumber1 = "LT0987654321";
                        std::cout << "You have successfully created additional IBAN! \n";
                    }else{
                        std::cout << "You can only create one additional IBAN! \n";
                }
                    break;
            
                case 'B':
                case 'b':
                    if(isAccountNumber1Empty(accountnumber1)){
                        std::cout << "You don't have an additional IBAN! \n";
                    }else{
                        std::cout << "Are you sure you want to delete your IBAN?(Y/N): ";
                        std::cin >> consent;

                        if(consent == 'Y' || consent == 'y'){
                            accountnumber1.clear();
                            std::cout << "Your additional IBAN has been deleted successfully! \n";
                        }else{
                            std::cout << "Invalid input! Please input only Y/N \n";
                        }
                }
                    break;

                case 'C':
                case 'c':
                    std::cout << "Returning to main menu \n";
                    break;
            }
            break;
        
        case 6: {
            std::cout << "Are you sure you want to close your account?(Y/N): ";
            std::cin >> consent;

            if(consent == 'Y' || consent == 'y'){
                file.close();
                if(std::remove("newAccount.txt") != 0) {
                    std::cout << "Error closing account \n";
                }
                std::cout << "Closing your account... \n";

                balance = 0;
                accountNumber.clear();
                accountnumber1.clear();
                
                std::cout << "Your account has been closed successfully! \n";
            }
            break;
        }
        case 7: {
            std::ofstream outputFile("newAccount.txt");

            if(outputFile.is_open()){
                std::string name, dob, address, numberID;

                std::cout << "Enter your name and surname: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                std::cout << "Enter your date of birth (YYYY-MM-DD): ";
                std::getline(std::cin, dob);

                std::cout << "Enter your address (street, house/apartment number, city, postal code): ";
                std::getline(std::cin, address);

                std::cout << "Enter your personal identification number: ";
                std::getline(std::cin, numberID);

                outputFile << "Name: " << name << "\n";
                outputFile << "Date of birth: " << dob << "\n";
                outputFile << "Address: " << address << "\n";
                outputFile << "Personal identification number: " << numberID << "\n";

                std::cout << "Your account information was successfully updated!";

                outputFile.close();
            }else{
                std::cout << "Your account can not be modified.";
            }
            break;
        }
        case 8:
            std::cout << "Shutting down. Have a nice day!";
            return 0;
    
        }
        }
    }
    
    return 0;
}