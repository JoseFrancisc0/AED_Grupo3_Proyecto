#ifndef TRANSACTION_H
#define TRANSACTION_H

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
        Transaction(string _client, string _location, double _amount):
            client(_client),
            location(_location),
            amount(_amount)
        {
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

        ~Transaction() = default;
};

#endif //TRANSACTION_H