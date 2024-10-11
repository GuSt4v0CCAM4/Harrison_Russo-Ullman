#include <iostream>
#include <vector>
#include <string>
using namespace std;


enum Rights { NONE, VIEW, ADD, EDIT, DELETE };

struct Product {
    string name;
    int quantity;
    float price;
};

struct User {
    string name;
    string password;  
    string role;  
};

class AccessControl {
private:
    vector<User> users;
    vector<Product> products;
    vector<vector<Rights>> accessMatrix;

public:
    void addUser(string userName, string password, string role) {
        users.push_back({ userName, password, role });
        accessMatrix.push_back(vector<Rights>(products.size(), NONE));
    }

    void addProduct(string productName, int quantity, float price) {
        products.push_back({ productName, quantity, price });
        for (auto& row : accessMatrix) {
            row.push_back(NONE);
        }
    }

    void assignRights(int userId, int productId, Rights right) {
        if (userId < users.size() && productId < products.size()) {
            accessMatrix[userId][productId] = right;
        }
    }

    void revokeRights(int userId, int productId) {
        if (userId < users.size() && productId < products.size()) {
            accessMatrix[userId][productId] = NONE;
        }
    }

    void showProducts(int userId) {
        if (userId < users.size()) {
            cout << "Productos accesibles para el usuario " << users[userId].name << ":\n";
            for (int i = 0; i < products.size(); ++i) {
                if (accessMatrix[userId][i] != NONE) {
                    cout << "- " << products[i].name << " (Cantidad: " << products[i].quantity << ", Precio: " << products[i].price << ")\n";
                }
            }
        }
    }

    void interactWithProduct(int userId) {
        int choice;
        do {
            cout << "\nMenú de productos para " << users[userId].name << ":\n";
            cout << "1. Ver productos\n";
            cout << "2. Salir\n";
            cout << "Seleccione una opción: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    showProducts(userId);
                    break;
                case 2:
                    cout << "Saliendo...\n";
                    break;
                default:
                    cout << "Opción inválida. Intente de nuevo.\n";
                    break;
            }
        } while (choice != 2);
    }

    int login(string userName, string password) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].name == userName && users[i].password == password) {
                return i; 
            }
        }
        return -1; 
    }
};

int main() {
    AccessControl system;
    
    system.addUser("Admin", "admin123", "admin");
    system.addUser("Empleado", "empleado123", "empleado");

    system.addProduct("Laptop", 10, 1500.00);
    system.addProduct("Mouse", 50, 25.99);

    system.assignRights(0, 0, VIEW); 
    system.assignRights(0, 1, ADD);  
    system.assignRights(1, 0, VIEW); 
    system.assignRights(1, 1, NONE); 

    string userName, password;
    cout << "Ingrese su nombre de usuario: ";
    cin >> userName;
    cout << "Ingrese su contraseña: ";
    cin >> password;

    int userId = system.login(userName, password);
    if (userId != -1) {
        cout << "Bienvenido, " << userName << ".\n";
        system.interactWithProduct(userId);  
    } else {
        cout << "Usuario o contraseña incorrectos.\n";
    }

    return 0;
}
