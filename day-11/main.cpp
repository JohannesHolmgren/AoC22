/* Day 11 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <stdlib.h>

using namespace std;


class Monkey {
    private:
        deque<int> items;
        int (*operation)(int);
        bool (*test)(int);
        int trueIndex;  // where to go depending on test
        int falseIndex; // where to go depending on test
    
    public:

    Monkey(deque<int> items, int(*operation)(int), bool (*test)(int), int trueIndex, int falseIndex){
        this->items = items;
        this->operation = operation;
        this->test = test;
        this->trueIndex = trueIndex;
        this->falseIndex = falseIndex;
    }

    void takeTurn(vector<Monkey> monkeys) {
        // for each item held
        while(items.size() > 0) {
            // Get item
            int item = items.front();
            items.pop_front();
            // Execute operation
            item = operation(item);
            // divide by three acc. to text
            item /= 3;
            // do test
            if(test(item)) {
                // give to monkey at trueIndex
                monkeys[trueIndex].recieveItem(item);
            }
            else {
                // give to monkey at falseIndex
                monkeys[falseIndex].recieveItem(item);
            }
        }
    }

    void recieveItem(int item) {
        items.push_back(item);
    }



int main() {

    vector<int> startM0 = {98, 89, 52};
    int startM1[] = {57, 95, 80, 92, 57, 78};
    int startM2[] = {82, 74, 97, 75, 51, 92, 83};
    int startM3[] = {97, 88, 51, 68, 76};
    int startM4[] = {63};
    int startM5[] = {94, 91, 51, 63};
    int startM6[] = {61, 54, 94, 71, 74, 68, 98, 83};
    int startM7[] = {90, 56};

    Monkey monkeys[] = {
        Monkey(startM0, [](int item) {return item*5;}, [](int item) {return item % 6 == 0;}, 6, 1),
        Monkey(startM1, [](int item) {return item*13;}, [](int item) {return item % 2 == 0;}, 2, 6),
        Monkey(startM2, [](int item) {return item+5;}, [](int item) {return item % 19 == 0;}, 7, 5),
        Monkey(startM3, [](int item) {return item+6;}, [](int item) {return item % 7 == 0;}, 0, 4),
        Monkey(startM4, [](int item) {return item+1;}, [](int item) {return item % 17 == 0;}, 0, 1),
        Monkey(startM5, [](int item) {return item+4;}, [](int item) {return item % 13 == 0;}, 4, 3),
        Monkey(startM6, [](int item) {return item+2;}, [](int item) {return item % 3 == 0;}, 2, 7),
        Monkey(startM7, [](int item) {return item*item;}, [](int item) {return item % 11 == 0;}, 3, 5)
    };

    return 0;
}

};