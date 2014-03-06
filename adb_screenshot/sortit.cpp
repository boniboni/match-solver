#include "sortit.h"
using namespace std::placeholders;

//sorty(short int i, short int j) {
//    return mtxR[i].y < mtxR[j].y;
//}

//sortx(short int i, short int j) {
//    return mtxR[i].x < mtxR[j].x;
//}


bool sortIT::sorty(short int i, short int j) {
    return mtxR[i].y < mtxR[j].y;
}

bool sortIT::sortx(short int i, short int j) {
    return mtxR[i].x < mtxR[j].x;
}


sortIT::sortIT(QObject *parent, mtxPoints *mtxRP) :
    mtxR(mtxRP)
{
}

void sortIT::doX(short int *posMTX)
{
    std::sort(posMTX, posMTX+64, std::bind(&sortIT::sorty, this, _1, _2));
    emit goYa();
}

void sortIT::doYa(short int *posMTX, short int *status)
{
    std::sort(posMTX, posMTX+8, std::bind(&sortIT::sortx, this, _1, _2));
    *status = 1;
}

void sortIT::doYb(short int *posMTX, short int *status)
{
    std::sort(posMTX+8, posMTX+16, std::bind(&sortIT::sortx, this, _1, _2));
    *status = 1;
}

void sortIT::doYc(short int *posMTX, short int *status)
{
    std::sort(posMTX+16, posMTX+24, std::bind(&sortIT::sortx, this, _1, _2));
    *status = 1;
}

void sortIT::doYd(short int *posMTX, short int *status)
{
    std::sort(posMTX+24, posMTX+32, std::bind(&sortIT::sortx, this, _1, _2));
    *status = 1;
}

void sortIT::doYe(short int *posMTX, short int *status)
{
    std::sort(posMTX+32, posMTX+40, std::bind(&sortIT::sortx, this, _1, _2));
    *status = 1;
}

void sortIT::doYf(short int *posMTX, short int *status)
{
    std::sort(posMTX+40, posMTX+48, std::bind(&sortIT::sortx, this, _1, _2));
    *status = 1;
}

void sortIT::doYg(short int *posMTX, short int *status)
{
    std::sort(posMTX+48, posMTX+56, std::bind(&sortIT::sortx, this, _1, _2));
    *status = 1;
}

void sortIT::doYh(short int *posMTX, short int *status)
{
    std::sort(posMTX+56, posMTX+64, std::bind(&sortIT::sortx, this, _1, _2));
    *status = 1;
}

