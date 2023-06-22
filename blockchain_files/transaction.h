#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Transaction{
    private:
        string client;
        string location;
        double amount;
        time_t date;
    public:
        Transaction() = default;
        Transaction(string _client, string _location, double _amount): client(_client), location(_location), amount(_amount){
            date = time(nullptr);
        }

        string getClient() const{
            return client;
        }

        string getLocation() const{
            return location;
        }

        double getAmount() const{
            return amount;
        }

        time_t getDate() const{
            return date;
        }

        void printTransaction(){
            cout << "Cliente: " << client << endl;
            cout << "Lugar: " << location << endl;
            cout << "Monto: " << amount << endl;

            char buffer[80];
            struct tm* timeinfo;
            timeinfo = localtime(&date);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            cout << "Fecha: " << buffer << endl;
        }

        ~Transaction() = default;
};

#endif //TRANSACTION_H