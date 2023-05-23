#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include <vector>
#include <string>
using namespace std;

class Block{
    private:
        Transaction transaction;
        string blockhash;
        string prevHash;
    public:
        Block(Transaction _transaction, string _prevHash): transaction(_transaction), prevHash(_prevHash){
            blockhash = calculateHash();
        }

        string calculateHash(){

        }

        ~Block() = default;
};

#endif //BLOCK_H