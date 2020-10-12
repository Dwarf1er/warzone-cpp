#include "OrdersDriver.h"

OrdersDriver::OrdersDriver()
{
    Bomb* bB = new Bomb();
    Airlift* aL = new Airlift();
    Negotiate* nT = new Negotiate();
    Blockade* bD = new Blockade();
    Advance* aV = new Advance();
    Deploy* dP = new Deploy();

    OrderList oL;
    oL.addOrders(bB);
    oL.addOrders(aL);
    oL.addOrders(nT);
    oL.addOrders(bD);
    oL.addOrders(aV);
    oL.addOrders(dP);

    for (int i = 0; i < 6; i++) {
        printf("%d \t", i);
        oL.getOList()[i]->execute();
    }

    printf("\n");

    oL.move(0, 3);
    for (int i = 0; i < 6; i++) {
        printf("%d \t", i);
        oL.getOList()[i]->execute();
    }

    printf("\n");

    oL.remove(0);
    for (int i = 0; i < 5; i++) {
        printf("%d \t", i);
        oL.getOList()[i]->execute();
    }

    printf("\ncout:\n");
    std::cout << *bB << std::endl;
    std::cout << *aL << std::endl;
    std::cout << *nT << std::endl;
    std::cout << *bD << std::endl;
    std::cout << *aV << std::endl;
    std::cout << *dP << std::endl;
}

OrdersDriver::~OrdersDriver()
{
}
