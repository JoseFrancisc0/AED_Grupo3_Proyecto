#include <iostream>
#include <string>
#include "blockchain.h"

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    BlockChain blockchain;
    int choice;
    while (true) {
        cout << "----------------------------------" << endl;
        cout << "       Blockchain App" << endl;
        cout << "----------------------------------" << endl;
        cout << '\n';
        cout << "1. Colocar Transaccion" << endl;
        cout << "2. Mostrar Blockchain" << endl;
        cout << "3. Busqueda singular" << endl;
        cout << "4. Busqueda por rango" << endl;
        cout << "5. Maximo valor" << endl;
        cout << "6. Minimo valor" << endl;
        cout << "7. Eliminar transaccion" << endl;
        cout << "8. Recalculo en cascada" << endl;
        cout << "9. Cargar datos" << endl;
        cout << '\n';
        cout << "0. Salir" << endl;
        cout << '\n';
        cout << "Ingrese opcion (0-9): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string client, location;
                double amount;

                cout << "Ingrese el cliente: ";
                cin.ignore();
                getline(cin, client);

                cout << "Ingrese el lugar: ";
                getline(cin, location);

                cout << "Ingrese la cantidad: ";
                cin >> amount;

                Transaction transaction(client, location, amount);
                blockchain.addTransaction(transaction);

                cout << "La transaction ha sido colocada exitosamente." << endl;
                break;
            }
            case 2: {
                blockchain.printBlockchain();
                break;
            }
            case 3: {
                string searchHash;
                cout << "Ingrese Hash: ";
                cin.ignore();
                getline(cin, searchHash);

                Transaction result = blockchain.search(searchHash);
                cout << "Transaccion encontrada: " << endl;
                result.printTransaction();
                break;
            }
            case 4: {
                string beginHash, endHash;
                cout << "Ingrese Hash inicial: ";
                cin.ignore();
                getline(cin, beginHash);

                cout << "Ingrese Hash final: ";
                getline(cin, endHash);

                vector<Transaction> result = blockchain.range_search(beginHash, endHash);
                cout << "Transacciones encontradas" << endl;
                for (auto item : result) {
                    item.printTransaction();
                    cout << endl;
                }
                break;
            }
            case 5: {
                Transaction result = blockchain.max_value();
                cout << "Transaccion encontrada: " << endl;
                result.printTransaction();
                break;
            }
            case 6: {
                Transaction result = blockchain.min_value();
                cout << "Transaccion encontrada: " << endl;
                result.printTransaction();
                break;
            }
            case 7: {
                int index;
                cout << "Ingrese index: ";
                cin >> index;

                blockchain.deleteRecordatIndex(index - 1);
                cout << "La transaccion ha sido eliminada exitosamente." << endl;
                break;
            }
            case 8: {
                blockchain.cascadeRecalculation();
                cout << "Recalculo en cascada completado." << endl;
                cout << "Blockchain recalculada:" << endl;
                blockchain.printBlockchain();
                break;
            }
            case 9: {
                string filePath;
                cout << "Ingrese path del archivo: ";
                cin.ignore();
                getline(cin, filePath);

                try {
                    blockchain.loadFromCSV(filePath);
                    cout << "La data ha sido cargada exitosamente." << endl;
                } catch (const std::exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 0: {
                cout << "Saliendo..." << endl;
                return 0;
            }
            default: {
                cout << "Opcion invalida." << endl;
                break;
            }
        }

        cout << "Presione cualquier tecla para regresar al menu...";
        cin.ignore();
        cin.get();

        clearScreen();
    }
}