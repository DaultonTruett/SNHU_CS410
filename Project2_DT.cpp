#include <iostream>
#include <string>

//include limits to handle 'std::cin' input stream failues - DT
#include <limits>

// VULNERABILITY: Global variables - moved to class as private - DT
/* Global variables <nums, names>
int num1 = 1;
int num2 = 2;
int num3 = 1;
int num4 = 1;
int num5 = 2;

std::string name1 = "Bob Jones";
std::string name2 = "Sarah Davis";
std::string name3 = "Amy Friendly";
std::string name4 = "Johnny Smith";
std::string name5 = "Carol Spears";
*/

// Encapsulate the code within a class to prevent the code from being visible - DT
class User {
    // User data is private and only accessable via an instance of the class obj with public class functions - DT
private:
    int num1 = 1;
    int num2 = 2;
    int num3 = 1;
    int num4 = 1;
    int num5 = 2;

    std::string name1 = "Bob Jones";
    std::string name2 = "Sarah Davis";
    std::string name3 = "Amy Friendly";
    std::string name4 = "Johnny Smith";
    std::string name5 = "Carol Spears";

public:
    int CheckUserPermissionAccess() {
        // NOTE: if fix were to include an API call to a DB to access/compare encrypted sensitive data for
        // authentication purposes, 'std::string' input would need to be checked for potential SQL injection - DT

        // VULNERABILITY: sensitive data(password) must not be hardcoded, retieve encrypted data from DB via API call - DT
        std::string password = "123";

        // VULNERABILITY: sensitive data(user password from input) must be 
        // encrypted after recieved from user, implement trusted encryption algorithm - DT
        std::string userPassword;

        std::string userName;

        std::cout << "Enter your username: " << std::endl;
        std::cin >> userName;

        std::cout << "Enter your password: " << std::endl;
        std::cin >> userPassword;

        // VULNERABILITY: hardcoded sensitive data(password) and sensitive data(user password from input)
        // must not be stored in local variables as plaintext and compared for authentication
        // utilize API call to compare encrypted input with stored encrypted data for associated user - DT
        if (userPassword == password) {
            return 1;
        };
        return 0;
    };

    void ChangeCustomerChoice() {
        int changeChoice, newService;

        // VULNERABILITY: Possibility of buffer overflow/underflow OR type mismatch (char input for int)
        // with 'std::cin' causing unexpected program crash or behavior(infinite loop) - DT
        try { // FIX: Input validation and exception handling - DT
            std::cout << "Enter the number of the client that you wish to change" << std::endl;
            std::cin >> changeChoice;

            if (changeChoice < 1 || changeChoice > 5) {
                // FIX: added input validation when input is type 'int' but not a valid option - DT
                std::cout << "Please input a valid menu option (1, 2, 3, 4, 5)" << std::endl;
                return;
            };

        }
        catch (std::istream::failure& E) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Only 'integer' inputs allowed, please input a valid number." << std::endl;
            return;
        };

        // VULNERABILITY: Possibility of buffer overflow/underflow OR type mismatch (char input for int)
        // with 'std::cin' causing unexpected program crash or behavior(infinite loop) - DT
        try { // FIX: Input validation and exception handling - DT
            std::cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)" << std::endl;
            std::cin >> newService;

            if (newService < 1 || newService > 2) {
                // FIX: added input validation when input is type 'int' but not a valid option - DT
                std::cout << "Please select a valid menu option (1 or 2)" << std::endl;
                return;
            }

            if (changeChoice == 1) {
                num1 = newService;

            }
            else if (changeChoice == 2) {
                num2 = newService;

            }
            else if (changeChoice == 3) {
                num3 = newService;

            }
            else if (changeChoice == 4) {
                num4 = newService;

            }
            else if (changeChoice == 5) {
                num5 = newService;
            };

        }
        catch (std::istream::failure& E) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Only 'integer' inputs allowed, please input a valid number." << std::endl;
            return;
        };
    };

    void DisplayInfo() {
        std::cout << "  Client's name    Service Selected (1 = Brokerage, 2 = Retirement)" << std::endl;
        std::cout << "1. " << name1 << " selected option " << num1 << std::endl;
        std::cout << "2. " << name2 << " selected option " << num2 << std::endl;
        std::cout << "3. " << name3 << " selected option " << num3 << std::endl;
        std::cout << "4. " << name4 << " selected option " << num4 << std::endl;
        std::cout << "5. " << name5 << " selected option " << num5 << std::endl;
    };
};



int main() {
    // Call for 'catch' block to handle 'std::cin' exceptions - DT
    std::cin.exceptions(std::istream::failbit | std::istream::badbit);

    int answer, choice;

    // Create instance obj of User class - DT
    User user;

    std::cout << "Created by: Daulton Truett" << std::endl;
    std::cout << std::endl;

    std::cout << "Hello! Welcome to our Investment Company" << std::endl;

    while (answer != 1) {
        answer = user.CheckUserPermissionAccess();

        if (answer != 1) {
            std::cout << "Invalid Password. Please try again." << std::endl;
        };
    };

    while (choice != 3) {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "DISPLAY the client list (enter 1)" << std::endl;
        std::cout << "CHANGE a client's choice (enter 2)" << std::endl;
        std::cout << "Exit the program.. (enter 3)" << std::endl;

        // VULNERABILITY: Possibility of buffer overflow/underflow OR type mismatch (char input for int)
        // with 'std::cin' causing unexpected program crash or behavior(infinite loop) - DTS
        try { // FIX: Input validation and exception handling - DT
            std::cin >> choice;
            std::cout << "You chose " << choice << std::endl;

            if (choice == 1) {
                // FIX: Only display user information via class obj method so the data is not easily visible - DT
                user.DisplayInfo();

            }
            else if (choice == 2) {
                // FIX: Access private class members via class method to bypass global variables - DT
                user.ChangeCustomerChoice();

            }
            else if (choice == 3) { // NOT A VULNERABILITY: Added response for exiting - DT
                std::cout << "Goodbye" << std::endl;

            }
            else { // FIX: added input validation when input is type 'int' but not a valid option - DT
                std::cout << "Please input a valid menu option (1, 2 or 3)" << std::endl;
            };

        }
        catch (std::istream::failure& E) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Only 'integer' inputs allowed, please input a valid number." << std::endl;
        };
    };

    return 0;
};

