#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction{
    private:
        string sender;
        string recipient;
        double amount;
    public:
        Transaction(string _sender, string _recipient, double _amount):
            sender(_sender),
            recipient(_recipient),
            amount(_amount)
        {}

        string getSender() const{
            return sender;
        }

        string getRecipient() const{
            return recipient;
        }

        double getAmount() const{
            return amount;
        }

        ~Transaction() = default;
};

#endif //TRANSACTION_H