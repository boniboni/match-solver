#ifndef FB2PNG_H
#define FB2PNG_H

#include <QObject>
#include <fb.h>
#include <remote.h>
#include <creatematrix.h>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtGui>
#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <sortit.h>

class fb2png : public QObject
{
    Q_OBJECT
public:
    explicit fb2png(QObject *parent, const char* path);
    typedef short int CustomInt;

    struct mtxPoints *mtxR;
    struct mtxPoints *mtxRa;
    struct mtxPoints *mtxRb;
    struct mtxPoints *mtxRc;
    struct mtxPoints *mtxRd;
    struct mtxPoints *mtxRe;
    struct mtxPoints *mtxRf;
    struct mtxPoints *mtxRg;
    struct mtxPoints *mtxRh;
    struct mtxPoints *mtxRi;
    struct mtxPoints *mtxRj;
    //    struct mtxPoints *mtxRl;

    short int posMTX[64];

    struct fb framebuffer;
    struct fbinfo infor;

    // thread Remote
    QThread *threadR;

    // thread opencv
    QThread *threadMa;
    QThread *threadMb;
    QThread *threadMc;
    QThread *threadMd;
    QThread *threadMe;
    QThread *threadMf;
    QThread *threadMg;
    QThread *threadMh;
    QThread *threadMi;
    QThread *threadMj;


    // thread sort
    QThread *sortingX;
    QThread *sortingYa;
    QThread *sortingYb;
    QThread *sortingYc;
    QThread *sortingYd;
    QThread *sortingYe;
    QThread *sortingYf;
    QThread *sortingYg;
    QThread *sortingYh;

    // worker sorts

    sortIT *sX;
    sortIT *sYa;
    sortIT *sYb;
    sortIT *sYc;
    sortIT *sYd;
    sortIT *sYe;
    sortIT *sYf;
    sortIT *sYg;
    sortIT *sYh;

    // worker objects
    createMatrix *mA;
    createMatrix *mB;
    createMatrix *mC;
    createMatrix *mD;
    createMatrix *mE;
    createMatrix *mF;
    createMatrix *mG;
    createMatrix *mH;
    createMatrix *mI;
    createMatrix *mJ;

    cv::Mat *ref;
    QImage *img;
    Remote *c;

    int get_fb_from_adb();
    void savePNG();
    int getFMT();
    void gomerge();

    // matrix counter
    short int mCountA = 0;
    short int mCountB = 0;
    short int mCountC = 0;
    short int mCountD = 0;
    short int mCountE = 0;
    short int mCountF = 0;
    short int mCountG = 0;
    short int mCountH = 0;
    short int mCountI = 0;
    short int mCountJ = 0;

    // matrix status
    short int mStatusA = 0;
    short int mStatusB = 0;
    short int mStatusC = 0;
    short int mStatusD = 0;
    short int mStatusE = 0;
    short int mStatusF = 0;
    short int mStatusG = 0;
    short int mStatusH = 0;
    short int mStatusI = 0;
    short int mStatusJ = 0;

    // sortY status
    short int sortStatusA = 0;
    short int sortStatusB = 0;
    short int sortStatusC = 0;
    short int sortStatusD = 0;
    short int sortStatusE = 0;
    short int sortStatusF = 0;
    short int sortStatusG = 0;
    short int sortStatusH = 0;

signals:
    void connectR(CustomInt mode);
    void threadSR();
    void threadSMa();
    void threadSMb();
    void threadSMc();
    void threadSMd();
    void threadSMe();
    void threadSMf();
    void threadSMg();
    void threadSMh();
    void threadSMi();
    void threadSMj();
    //    void threadSMl();

    void threadSx();
    void threadSyA();
    void threadSyB();
    void threadSyC();
    void threadSyD();
    void threadSyE();
    void threadSyF();
    void threadSyG();
    void threadSyH();


    void startWorkA(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkB(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkC(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkD(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkE(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkF(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkG(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkH(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkI(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);
    void startWorkJ(short int *status, short int *counter, struct mtxPoints *mtxRX, CustomInt tipo);

    void startDoX(short int *posMTX);

    void startDoYa(short int *posMTX, short int *status);
    void startDoYb(short int *posMTX, short int *status);
    void startDoYc(short int *posMTX, short int *status);
    void startDoYd(short int *posMTX, short int *status);
    void startDoYe(short int *posMTX, short int *status);
    void startDoYf(short int *posMTX, short int *status);
    void startDoYg(short int *posMTX, short int *status);
    void startDoYh(short int *posMTX, short int *status);



public slots:
    void on_finishedFB();
    void goY();
};

#endif // FB2PNG_H
