#pragma once
#include <iostream>
#include<vector>
using namespace std;

class Orders {
    /*
    ->The Order class implements a stream insertion operator(<<) that outputs a string describing the
    order.If the order has been executed, it should also output the effect of the order. (print out the strings)
    ->Every order subclass must implement the validate() method that is used to validate if the
    order is valid.
    ->Every order subclass must implement the execute() method that first validates the order,
    and executes its action if it is valid, according to the order’s meaning and the player’s state.
    */
public:
    Orders();
    //operator overloading
    //assignment operator overloading
    void operator = (const Orders& o);
    //stream insertion operator overloading
    friend ostream& operator<<(ostream& out, const Orders& o);
    friend istream& operator>>(istream& in, Orders& o);
};
//Derived classes for orders
class Deploy : public Orders {
public:
    Deploy();
    bool validate();
    bool execute();
};
class Advance : public Orders {
public:
    Advance();
    void validate();
    void execute();
};
class Bomb : public Orders {
public:
    Bomb();
    void validate();
    void execute();
};
class Blockade : public Orders {
public:
    Blockade();
    void validate();
    void execute();
};
class Airlift : public Orders {
public:
    Airlift();
    void validate();
    void execute();
};
class Negotiate : public Orders {
public:
    Negotiate();
    void validate();
    void execute();
};

class OrderList {
    /*
    * The OrdersList class contains a list of Order objects.
    * The OrdersList class implements a remove() method that deletes an order from the list.
    * The OrdersList class implements a move() method to move an order in the list of orders.
    */
private:
    vector<Orders*> oList;
public:
    OrderList();
    void move(int i, int j);
    void remove(int i);
    vector<Orders*> get_orders();
};