#ifndef CREATEMATRIX_H
#define CREATEMATRIX_H

#include <QObject>
#include <iostream>
#include <cstdint>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <fb.h>
#include <time.h>
#include <QFile>
#include <fb.h>
#include <QThread>
#include <QDebug>

#include <algorithm>


class createMatrix : public QObject
{
    Q_OBJECT
public:
    explicit createMatrix(QObject *parent, cv::Mat *refP, short int tipo);
    ~createMatrix();
    typedef short int CustomInt;
    cv::Mat *ref;
    cv::Mat *tpl0;
    cv::Mat *ref_gray0;
    cv::Mat *tpl0_gray;
    cv::Mat *dst;
    void fastMatchTemplate(cv::Mat *srca, cv::Mat *srcb, cv::Mat *dst, int maxlevel);
    QFile *file;


signals:

public slots:
    void Work(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);

};

#endif // CREATEMATRIX_H
