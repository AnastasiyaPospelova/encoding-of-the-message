#include <iostream>
#include <string>
#include <cctype>
using namespace std;

double check_numbers() {
    string number;
    while (true) {
        cout << "Enter a number: ";
        cin >> number;
        bool flag = true;
        for (size_t i = 0; i < number.length(); i++) {
            if (!isdigit(number[i]) and number[i] != '.') {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "The number is incorrect. Try again." << endl;
                flag = false;
                break;
            }
        }
        if (flag) break;
    }
    return stod(number);
}

int main() {
    double a = check_numbers();
    cout << "Your number: " << a;
    return 0;
}