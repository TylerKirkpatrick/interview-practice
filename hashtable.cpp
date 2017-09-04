#include <iostream>
#include <stdlib.h>     /* srand, rand */

using namespace std;

const int TABLE_SIZE = 512;

class HashEntry {
private:
      int key;
      int value;
public:
      HashEntry(int key, int value) {
            this->key = key;
            this->value = value;
      }

      int getKey() {
            return key;
      }

      int getValue() {
            return value;
      }
};

class HashMap {
private:
      HashEntry **table;
public:
      HashMap() {
            table = new HashEntry*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;
      }

      int get(int key) {
            int hash = (key % TABLE_SIZE);
            while (table[hash] != NULL && table[hash]->getKey() != key)
                  hash = (hash + 1) % TABLE_SIZE;
            if (table[hash] == NULL)
                  return -1;
            else
                  return table[hash]->getValue();
      }

      void put(int key, int value) {
            int hash = (key % TABLE_SIZE);
            while (table[hash] != NULL && table[hash]->getKey() != key)
                  hash = (hash + 1) % TABLE_SIZE;
            if (table[hash] != NULL)
                  delete table[hash];
            table[hash] = new HashEntry(key, value);
      }

      void printMap() {

          for(int i = 0; i < TABLE_SIZE; i++) {
              int printThis = table[i]->getValue();
              cout<< i <<" -> "<< printThis <<endl;
          }

      }

      ~HashMap() {
            cout<<"DELETING HASH MAP"<<endl;
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }
};

int main() {
    HashMap myMap;

    for(int i = 0; i < TABLE_SIZE; i++) {
        int toPut = rand() % 500 + 1;

        myMap.put(i, toPut);
    }

    myMap.printMap();

    return 0;
}
