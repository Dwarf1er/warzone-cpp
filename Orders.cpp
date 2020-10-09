#include "Orders.h"
#include <iostream>
using namespace std;

Orders::Orders() {
};
Deploy::Deploy() {
};
Advance::Advance() {
};
Bomb::Bomb() {
};
Blockade::Blockade() {
};
Airlift::Airlift() {
};
Negotiate::Negotiate() {
};

OrderList::OrderList() {

};
void OrderList::move(int i, int j) {
    //check if i,j falls within the vector size
    if ((i < oList.size() && i >= 0) && (j < oList.size() && j >= 0)) {
        //create a temporary order object and store the vector item at current index
        Orders temp{
            oList.at(i)
        };
        //removes the item
        oList.erase(oList.begin() + i);
        //push back the temporary order at the end of the order list
        if (j == oList.size()) {
            oList.push_back(temp);
        }
        else {
            //insert the temporary object at the current location    
            oList.insert(oList.begin() + j, temp);
        }
    }
};
void OrderList::remove(int i) {
    if (i < oList.size() && i >= 0) {
        //removes the current index item
        oList.erase(oList.begin() + i);
    }
};

//operator overloading
    //assignment operator overloading
void Orders::operator=(const Orders& o) {
    
}

    //stream insertion operator overloading
ostream& operator<<(ostream& out, const Orders& o) {
    out << "Order: " << o << endl;
    return out;
}

istream& operator>>(istream& in, Orders& o) {
    cout << "Enter your order: ";
    in >> o;
    return in;
}