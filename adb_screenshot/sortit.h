#ifndef SORTIT_H
#define SORTIT_H

#include <QObject>
#include <algorithm>
#include <fb.h>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <functional>



class sortIT : public QObject
{
    Q_OBJECT
public:
    explicit sortIT(QObject *parent = 0, mtxPoints *mtxRP = 0);
    struct mtxPoints *mtxR;
    bool sorty(short int i, short int j);
    bool sortx(short int i, short int j);

signals:
    void goYa();

public slots:

    void doX(short int *posMTX = 0);
    void doYa(short int *posMTX = 0, short int *status = 0);
    void doYb(short int *posMTX = 0, short int *status = 0);
    void doYc(short int *posMTX = 0, short int *status = 0);
    void doYd(short int *posMTX = 0, short int *status = 0);
    void doYe(short int *posMTX = 0, short int *status = 0);
    void doYf(short int *posMTX = 0, short int *status = 0);
    void doYg(short int *posMTX = 0, short int *status = 0);
    void doYh(short int *posMTX = 0, short int *status = 0);
};

#endif // SORTIT_H
