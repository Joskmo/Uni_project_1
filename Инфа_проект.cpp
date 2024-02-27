#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

const int NUM_OF_MONTHS = 12, BASE_YEAR = 1919;
const vector <vector <int>> test_leap_year = { {1920, 1}, {1921, 0}, {2000, 1}, {2100, 0} };
const vector <vector <int>> test_month_days = { {1, 2000, 31}, {2, 2000, 29}, {2, 2001, 28}, {7, 2000, 31}, {8, 2000, 31}, {4, 2000, 30}, {12, 2000, 31} };
const vector <vector <int>> test_first_day_detecting = { {1, 2023, 6}, {2, 2023, 2}, {4, 2023, 5}, {5, 2023, 0}, {8, 2023, 1}, {9, 2023, 4}, {2, 2024, 3} };
int month = 0, year = 0;

int input_int(int low_lim, int high_lim) {
    string input;
    int test = 0, output = 0;
    try {
        cin >> input;
        for (int i = 0; i < input.size(); i++) {
            test = ((int)input[i] > 47 && (int)input[i] < 58);
            if (test == 0) {
                cout << "Проверьте введённые данные" << endl;
                output = 0;
                break;
            }
            else {
                output = stoi(input);
                if (output < low_lim || output > high_lim) {
                    cout << "Проверьте введённые данные" << endl;
                    output = 0;
                    break;
                }
            }
        }
    }
    catch (exception& ex) {
        output = 0;
        cout << "Проверьте введённые данные" << endl;
    }
    return output;
} 

int leap_year(int year) {
    return (!(year % 400)) || (year % 100 != 0 && year % 4 == 0);
}

int month_days(int month, int year) {
    int month_days[NUM_OF_MONTHS] = { 31, 28 + leap_year(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return month_days[month - 1];
}

int first_day_detecting(int month, int year) {
    int amount_of_days = 0;
    for (int i = BASE_YEAR; i <= (year - 1); i++)
        amount_of_days += (365 + leap_year(i));
    for (int i = 1; i < month; i++)
        amount_of_days += month_days(i, year);
    return (amount_of_days + 2) % 7;
}

void print_month(int month, int year) {
    string name_of_months[NUM_OF_MONTHS] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
    cout << name_of_months[month - 1] << " " << year << endl;
    cout << " ПН" << " ВТ" << " СР" << " ЧТ" << " ПТ" << " СБ" << " ВС" << endl << " ";
    for (int i = 0; i < first_day_detecting(month, year); i++)
        cout << "   ";
    for (int i = 1; i <= month_days(month, year); i++) {
        if (i < 10)
            cout << " ";
        cout << i << " ";
        if ((i + first_day_detecting (month, year)) % 7 == 0)
            cout << endl << " ";
    }
    cout << endl;
}

void test_func() {
    for (auto test : test_leap_year)
        assert(leap_year(test[0] == test[1]));
    for (auto test : test_month_days)
        assert(month_days(test[0], test[1]) == test[2]);
    for (auto test : test_first_day_detecting)
        assert(first_day_detecting(test[0], test[1]) == test[2]);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    test_func();
    cout << "Предварительный тест пройден успешно!" << endl;
    cout << "Введите месяц и год: ";
    while (month == 0 || year == 0) {
        month = input_int(1, NUM_OF_MONTHS);
        if (!month) year = 0;
        else year = input_int(BASE_YEAR, 2029);
    }
    print_month(month, year);
    system("pause");
    return 0;  
}