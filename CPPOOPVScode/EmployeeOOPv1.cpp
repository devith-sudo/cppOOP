#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

const int MAX_EMPLOYEES = 1000; // Increased maximum capacity

class Employee {
private:
    int id;
    string name;
    string gender;
    int age;
    string position;
    double salary;

public:
    void input() {
        cout << "Enter Employee ID: ";
        while (!(cin >> id) || id <= 0) {
            handleInvalidInput();
            cout << "Invalid input. Please enter a positive integer for ID: ";
        }
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Gender: ";
        getline(cin, gender);

        cout << "Enter Age: ";
        while (!(cin >> age) || age <= 0) {
            handleInvalidInput();
            cout << "Invalid input. Please enter a positive integer for age: ";
        }
        cin.ignore();

        cout << "Enter Position: ";
        getline(cin, position);

        cout << "Enter Salary: ";
        while (!(cin >> salary) || salary < 0) {
            handleInvalidInput();
            cout << "Invalid input. Please enter a non-negative number for salary: ";
        }
    }

    void show() const {
        cout << "ID: " << id
             << ", Name: " << name
             << ", Gender: " << gender
             << ", Age: " << age
             << ", Position: " << position
             << ", Salary: $" << fixed << setprecision(2) << salary << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getSalary() const { return salary; }
    void updateName(const string& newName) { name = newName; }

    static void handleInvalidInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again.\n";
    }
};

class EmployeeList {
private:
    Employee employees[MAX_EMPLOYEES];
    int count = 0;

public:
    void addEmployees() {
        int n;
        cout << "How many employees do you want to add? (0-" << (MAX_EMPLOYEES - count) << "): ";
        while (!(cin >> n) || n < 0 || n > (MAX_EMPLOYEES - count)) {
            Employee::handleInvalidInput();
            cout << "Please enter a number between 0 and " << (MAX_EMPLOYEES - count) << ": ";
        }

        if (n == 0) {
            cout << "No employees added.\n";
            return;
        }

        for (int i = 0; i < n; i++) {
            cout << "\nEntering details for employee " << (count + 1) << " of " << (count + n) << ":\n";
            Employee emp;
            emp.input();

            if (findEmployeeById(emp.getId()) != -1) {
                cout << "Employee with ID " << emp.getId() << " already exists. Skipping this employee.\n";
                i--; // Decrement counter to retry this position
                continue;
            }

            if (count >= MAX_EMPLOYEES) {
                cout << "Maximum capacity reached. Cannot add more employees.\n";
                break;
            }

            employees[count++] = emp;
            cout << "Employee added successfully (" << count << "/" << MAX_EMPLOYEES << " slots used).\n";
        }
    }

    void showAll() const {
        if (count == 0) {
            cout << "No employees available.\n";
            return;
        }

        cout << "\nAll Employees (" << count << "):\n";
        for (int i = 0; i < count; i++) {
            employees[i].show();
        }
    }

    int findEmployeeById(int id) const {
        for (int i = 0; i < count; i++) {
            if (employees[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    void findAndShowEmployee() const {
        if (count == 0) {
            cout << "No employees available to search.\n";
            return;
        }

        int searchId;
        cout << "Enter ID to find: ";
        while (!(cin >> searchId)) {
            Employee::handleInvalidInput();
            cout << "Enter ID to find: ";
        }

        int index = findEmployeeById(searchId);
        if (index != -1) {
            cout << "Employee found:\n";
            employees[index].show();
        } else {
            cout << "Employee with ID " << searchId << " not found.\n";
        }
    }

    void updateEmployeeName() {
        if (count == 0) {
            cout << "No employees available to update.\n";
            return;
        }

        int id;
        cout << "Enter ID to update name: ";
        while (!(cin >> id)) {
            Employee::handleInvalidInput();
            cout << "Enter ID to update name: ";
        }

        int index = findEmployeeById(id);
        if (index != -1) {
            cin.ignore();
            string newName;
            cout << "Enter new name: ";
            getline(cin, newName);
            employees[index].updateName(newName);
            cout << "Name updated successfully.\n";
        } else {
            cout << "Employee with ID " << id << " not found.\n";
        }
    }

    void deleteEmployee() {
        if (count == 0) {
            cout << "No employees available to delete.\n";
            return;
        }

        int delId;
        cout << "Enter ID to delete: ";
        while (!(cin >> delId)) {
            Employee::handleInvalidInput();
            cout << "Enter ID to delete: ";
        }

        int index = findEmployeeById(delId);
        if (index != -1) {
            // Shift all elements after the deleted one to the left
            for (int i = index; i < count - 1; i++) {
                employees[i] = employees[i + 1];
            }
            count--;
            cout << "Employee deleted successfully.\n";
        } else {
            cout << "Employee with ID " << delId << " not found.\n";
        }
    }

    void sortBySalary() {
        if (count == 0) {
            cout << "No employees available to sort.\n";
            return;
        }

        // Using selection sort for simplicity
        for (int i = 0; i < count - 1; i++) {
            int maxIndex = i;
            for (int j = i + 1; j < count; j++) {
                if (employees[j].getSalary() > employees[maxIndex].getSalary()) {
                    maxIndex = j;
                }
            }
            if (maxIndex != i) {
                swap(employees[i], employees[maxIndex]);
            }
        }

        cout << "Employees sorted by salary (descending order):\n";
        showAll();
    }
};

void showMenu() {
    cout << "\n--- Employee Management System ---\n";
    cout << "1. Add Employees\n";
    cout << "2. Show All Employees\n";
    cout << "3. Find Employee by ID\n";
    cout << "4. Update Employee Name by ID\n";
    cout << "5. Delete Employee by ID\n";
    cout << "6. Sort Employees by Salary (Descending)\n";
    cout << "7. Exit\n";
    cout << "Enter your choice (1-7): ";
}

int main() {
    EmployeeList employeeList;
    int choice;

    do {
        showMenu();
        
        while (!(cin >> choice)) {
            Employee::handleInvalidInput();
            showMenu();
        }

        switch (choice) {
            case 1:
                employeeList.addEmployees();
                break;
            case 2:
                employeeList.showAll();
                break;
            case 3:
                employeeList.findAndShowEmployee();
                break;
            case 4:
                employeeList.updateEmployeeName();
                break;
            case 5:
                employeeList.deleteEmployee();
                break;
            case 6:
                employeeList.sortBySalary();
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 7.\n";
                break;
        }

    } while (choice != 7);

    return 0;
}
