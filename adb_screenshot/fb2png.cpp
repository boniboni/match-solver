#include "fb2png.h"
#include <remote.h>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtGui>
#include <QThread>
#include <creatematrix.h>

#define FB_FORMAT_UNKNOWN   0
#define FB_FORMAT_RGB565    1
#define FB_FORMAT_ARGB8888  2
#define FB_FORMAT_RGBA8888  3
#define FB_FORMAT_ABGR8888  4
#define FB_FORMAT_BGRA8888  5
#define defaultimg "img.png"

#define LION 1
#define PANDA 2
#define ELEPH 3
#define FROG 4
#define MONKE 5
#define HIPPO 6
#define GIRRA 7
#define BOSS 8
#define BLCKDa 9
#define BLCKDb 10

#define ELEPHIMG "temp0.png"
#define HIPPOIMG "temp1.png"
#define FROGIMG "temp2.png"
#define LIONIMG "temp3.png"
#define MONKEIMG "temp4.png"
#define PANDAIMG "temp5.png"
#define GIRRAIMG "temp6.png"
#define BOSSIMG "temp7.png"
#define BLCKDIMGa "temp8.png"
#define BLCKDIMGb "temp9.png"

fb2png::fb2png(QObject *parent = 0, const char* path = 0) :
    QObject(parent)
{

    mtxRa = new mtxPoints[60];
    mtxRb = new mtxPoints[60];
    mtxRc = new mtxPoints[60];
    mtxRd = new mtxPoints[60];
    mtxRe = new mtxPoints[60];
    mtxRf = new mtxPoints[60];
    mtxRg = new mtxPoints[60];
    mtxRh = new mtxPoints[60];
    mtxRi = new mtxPoints[60];
    mtxRj = new mtxPoints[60];

    mtxR = new mtxPoints[64];


    if (get_fb_from_adb() == 0) {

        //   c->deleteLater();
        return;

    }

}

int fb2png::get_fb_from_adb() {

    // if need_fb = 1

    qRegisterMetaType<CustomInt>("CustomInt");

    threadR = new QThread;

    c = new Remote(this, &framebuffer);
    c->moveToThread(threadR);

    connect(this, SIGNAL(threadSR()),
            threadR, SLOT(quit()));
    connect(threadR, SIGNAL(finished()),
            c, SLOT(deleteLater()));
    //    connect(this, SIGNAL(threadDR()),
    //            threadR, SLOT(quit()));

    connect(this, SIGNAL(connectR(CustomInt)),
            c, SLOT(connectToServer(CustomInt)));

    threadR->start();
    printf("Remote Thread criado\n");

    emit connectR(1);

    /* Parse FB header. */
    // adb_read(buf, sizeof(struct fbinfo));
    // fbinfo = (struct fbinfo*) buf;

    //   if (fbinfo->version != DDMS_RAWIMAGE_VERSION) {
    //       E("unspport adb version");
    //   }

    /* Assemble struct fb */
    //   memcpy(fb, &fbinfo->bpp, sizeof(struct fbinfo) - 4);
    //   fb_dump(fb);

    //   fb->data = malloc(fb->size);
    //   if (!fb->data) return -1;

    /* Read out the whole framebuffer */
    //   int bytes_read = 0;
    //   while (bytes_read < fb->size) {
    //       bytes_read += adb_read(fb->data + bytes_read, fb->size - bytes_read);
    return 0;
}

void fb2png::on_finishedFB() {
    //  int i;
    // int *point;
    printf("FinishedFB chamado\n");
    printf("bpp framebuffer: %u\n", framebuffer.bpp);
    printf("size framebuffer: %u\n", framebuffer.size);
    printf("width framebuffer: %u\n", framebuffer.width);
    printf("height framebuffer: %u\n", framebuffer.height);
    printf("red offset framebuffer: %u\n", framebuffer.red_offset);
    printf("red length framebuffer: %u\n", framebuffer.red_length);
    printf("blue offset framebuffer: %u\n", framebuffer.blue_offset);
    printf("blue length framebuffer: %u\n", framebuffer.blue_length);
    printf("green offset framebuffer: %u\n", framebuffer.green_offset);
    printf("green length framebuffer: %u\n", framebuffer.green_length);
    printf("alpha offset framebuffer: %u\n", framebuffer.alpha_offset);
    printf("alpha length framebuffer: %u\n", framebuffer.alpha_length);
    printf("bytes fb: %d\n", (int)sizeof(framebuffer));
    printf("bytes fbinfo: %d\n", (int)sizeof(infor));
    printf("bytes fb: %d\n", (int)sizeof(framebuffer));
    printf("tamanho esperado de data: %u\n", framebuffer.size);

    //point = (int *)framebuffer.data;
    //   point = static_cast<int*>(framebuffer.data);
    //  for (i = 0; i <= 1000;i++) {
    //      printf("%d", point++);
    //  }

    savePNG();

}

void fb2png::savePNG() {

    qDebug()<<"Thread fb2png: "<<this->QObject::thread()->currentThreadId();


    int fmt = getFMT();
    printf("getFMT: %d\n", fmt);
    switch(fmt) {
    case FB_FORMAT_RGB565:
        /* emulator use rgb565 */

        printf("Formato: FB_FORMAT_RGB565\n");
        break;
    case FB_FORMAT_ARGB8888:
        /* most devices use argb8888 */

        printf("Formato: FB_FORMAT_ARGB8888\n");
        break;
    case FB_FORMAT_ABGR8888:

        printf("Formato: FB_FORMAT_ABGR8888\n");
        break;
    case FB_FORMAT_BGRA8888:

        printf("Formato: FB_FORMAT_BGRA8888\n");
        break;
    case FB_FORMAT_RGBA8888:

        printf("Formato: FB_FORMAT_RGBA8888\n");
        break;
    default:
        printf("Formato: Desconhecido\n");
    }
    //const unsigned char *point = static_cast<unsigned char*>(framebuffer.data);

    // printf("Tamanho Data: %d\n", c->Data.size());

    //const char *buffer = c->Data.constData();
    //printf("porra: %s\n", buffer);
    const unsigned char *buffer = (unsigned char*)c->Data.constData();

    img = new QImage(buffer, 1080, 1920, QImage::Format_RGBA8888);
    printf("img vazio: %d height: %d width: %d formato: %d\n", img->isNull(), img->width(), img->height(), img->format());
    //  img->invertPixels(QImage::InvertRgb);
    // bool lol = img->loadFromData(c->Data.constData());
    // printf("loadfromdata: %d\n", lol);
    //   img->invertPixels(QImage::InvertRgb);
    bool sav = img->save("imagem.png", "PNG", 100);
    printf("salvou: %d\n", sav);
    emit threadSR();
    threadR->wait();
    //    emit threadDR();

    ref = new cv::Mat();
    *ref = cv::imread(defaultimg);
    //    cvNamedWindow("Image Window", CV_WINDOW_NORMAL);
    //    cv::imshow("Image Window", ref);

    //    cv::waitKey();


    // allocate opencv threads 1
    threadMa = new QThread;
    threadMb = new QThread;
    threadMc = new QThread;
    threadMd = new QThread;

    // allocate object workers 1
    mA = new createMatrix(this, ref, ELEPH);
    mB = new createMatrix(this, ref, HIPPO);
    mC = new createMatrix(this, ref, FROG);
    mD = new createMatrix(this, ref, LION);

    // move threads 1
    mA->moveToThread(threadMa);
    mB->moveToThread(threadMb);
    mC->moveToThread(threadMc);
    mD->moveToThread(threadMd);

    // slots and signals A
    connect(this, SIGNAL(threadSMa()),
            threadMa, SLOT(quit()));
    connect(threadMa, SIGNAL(finished()),
            mA, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkA(short int*, short int*, struct mtxPoints*, CustomInt)),
            mA, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));

    // slots and signals B
    connect(this, SIGNAL(threadSMb()),
            threadMb, SLOT(quit()));
    connect(threadMb, SIGNAL(finished()),
            mB, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkB(short int*, short int*, struct mtxPoints*, CustomInt)),
            mB, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));

    // slots and signals C
    connect(this, SIGNAL(threadSMc()),
            threadMc, SLOT(quit()));
    connect(threadMc, SIGNAL(finished()),
            mC, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkC(short int*, short int*, struct mtxPoints*, CustomInt)),
            mC, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));

    // slots and signals D
    connect(this, SIGNAL(threadSMd()),
            threadMd, SLOT(quit()));
    connect(threadMd, SIGNAL(finished()),
            mD, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkD(short int*, short int*, struct mtxPoints*, CustomInt)),
            mD, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));


    // start 1
    threadMa->start();
    printf("mA Thread criado\n");
    threadMb->start();
    printf("mB Thread criado\n");
    threadMc->start();
    printf("mC Thread criado\n");
    threadMd->start();
    printf("mD Thread criado\n");

    // emit 1
    emit startWorkA(&mStatusA, &mCountA, mtxRa, ELEPH);
    emit startWorkB(&mStatusB, &mCountB, mtxRb, HIPPO);
    emit startWorkC(&mStatusC, &mCountC, mtxRc, FROG);
    emit startWorkD(&mStatusD, &mCountD, mtxRd, LION);





    // allocate opencv threads 2
    threadMe = new QThread;
    threadMf = new QThread;
    threadMg = new QThread;
    threadMh = new QThread;

    // allocate object workers 2
    mE = new createMatrix(this, ref, PANDA);
    mF = new createMatrix(this, ref, MONKE);
    mG = new createMatrix(this, ref, GIRRA);
    mH = new createMatrix(this, ref, BOSS);

    // move threads 2
    mE->moveToThread(threadMe);
    mF->moveToThread(threadMf);
    mG->moveToThread(threadMg);
    mH->moveToThread(threadMh);

    // slots and signals E
    connect(this, SIGNAL(threadSMe()),
            threadMe, SLOT(quit()));
    connect(threadMe, SIGNAL(finished()),
            mE, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkE(short int*, short int*, struct mtxPoints*, CustomInt)),
            mE, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));

    // slots and signals F
    connect(this, SIGNAL(threadSMf()),
            threadMf, SLOT(quit()));
    connect(threadMf, SIGNAL(finished()),
            mF, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkF(short int*, short int*, struct mtxPoints*, CustomInt)),
            mF, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));

    // slots and signals G
    connect(this, SIGNAL(threadSMg()),
            threadMg, SLOT(quit()));
    connect(threadMg, SIGNAL(finished()),
            mG, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkG(short int*, short int*, struct mtxPoints*, CustomInt)),
            mG, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));

    // slots and signals H
    connect(this, SIGNAL(threadSMh()),
            threadMh, SLOT(quit()));
    connect(threadMh, SIGNAL(finished()),
            mH, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkH(short int*, short int*, struct mtxPoints*, CustomInt)),
            mH, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));

    // start 2
    threadMe->start();
    printf("mE Thread criado\n");
    threadMf->start();
    printf("mF Thread criado\n");
    threadMg->start();
    printf("mG Thread criado\n");
    threadMh->start();
    printf("mH Thread criado\n");

    // emit 2
    emit startWorkE(&mStatusE, &mCountE, mtxRe, PANDA);
    emit startWorkF(&mStatusF, &mCountF, mtxRf, MONKE);
    emit startWorkG(&mStatusG, &mCountG, mtxRg, GIRRA);
    emit startWorkH(&mStatusH, &mCountH, mtxRh, BOSS);





    // allocate opencv threads 3
    threadMi = new QThread;
    threadMj = new QThread;

    // allocate object workers 3
    mI = new createMatrix(this, ref, BLCKDa);
    mJ = new createMatrix(this, ref, BLCKDb);

    // move threads 3
    mI->moveToThread(threadMi);
    mJ->moveToThread(threadMj);

    // slots and signals I
    connect(this, SIGNAL(threadSMi()),
            threadMi, SLOT(quit()));
    connect(threadMi, SIGNAL(finished()),
            mI, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkI(short int*, short int*, struct mtxPoints*, CustomInt)),
            mI, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));


    // slots and signals J
    connect(this, SIGNAL(threadSMj()),
            threadMj, SLOT(quit()));
    connect(threadMj, SIGNAL(finished()),
            mJ, SLOT(deleteLater()));

    connect(this, SIGNAL(startWorkJ(short int*, short int*, struct mtxPoints*, CustomInt)),
            mJ, SLOT(Work(short int*, short int*, struct mtxPoints*, CustomInt)));

    // start 3
    threadMi->start();
    printf("mI Thread criado\n");
    threadMj->start();
    printf("mJ Thread criado\n");

    // emit 3
    emit startWorkI(&mStatusI, &mCountI, mtxRi, BLCKDa);
    emit startWorkJ(&mStatusJ, &mCountJ, mtxRj, BLCKDb);


    for (int i = 0; i < 64; i++) {
        posMTX[i] = i;
    }

    short int scan = 0;

    while (scan <10)
    {
        if (mStatusA ^ mStatusB ^ mStatusC ^ mStatusD ^ mStatusE ^ mStatusF ^ mStatusG ^ mStatusH ^ mStatusI ^ mStatusJ) {
            if (mStatusA) {
                mStatusA = 0;
                scan++;
                emit threadSMa();
                threadMa->wait();
                printf("parou A\n");
            }

            if (mStatusB) {
                mStatusB = 0;
                scan++;
                emit threadSMb();
                threadMb->wait();
                printf("parou B\n");

            }

            if (mStatusC) {
                mStatusC = 0;
                emit threadSMc();
                threadMc->wait();
                printf("parou C\n");
                scan++;
            }

            if (mStatusD) {
                mStatusD = 0;
                scan++;
                emit threadSMd();
                threadMd->wait();
                printf("parou D\n");
            }

            if (mStatusE) {
                mStatusE = 0;
                scan++;
                emit threadSMe();
                threadMe->wait();
                printf("parou E\n");
            }

            if (mStatusF) {
                mStatusF = 0;
                scan++;
                emit threadSMf();
                threadMf->wait();
                printf("parou F\n");
            }
            if (mStatusG) {
                mStatusG = 0;
                scan++;
                emit threadSMg();
                threadMg->wait();
                printf("parou G\n");
            }
            if (mStatusH) {
                mStatusH = 0;
                scan++;
                emit threadSMh();
                threadMh->wait();
                printf("parou H\n");
            }
            if (mStatusI) {
                mStatusI = 0;
                scan++;
                emit threadSMi();
                threadMi->wait();
                printf("parou I\n");
            }
            if (mStatusJ) {
                mStatusJ = 0;
                scan++;
                emit threadSMj();
                threadMj->wait();
                printf("parou J\n");
            }
        }
    }
    scan = 0;
    gomerge();

    delete ref;
    delete img;




    // allocate sortX thread
    sortingX = new QThread;


    // allocate sortX worker
    sX = new sortIT(this, mtxR);

    // move sX thread
    sX->moveToThread(sortingX);

    // slots and signals sortX
    connect(this, SIGNAL(threadSx()),
            sortingX, SLOT(quit()));
    connect(sortingX, SIGNAL(finished()),
            sX, SLOT(deleteLater()));

    connect(sX, SIGNAL(goYa()), this, SLOT(goY()));

    connect(this, SIGNAL(startDoX(short int*)),
            sX, SLOT(doX(short int*)));

    sortingX->start();
    printf("sortingX Thread criado\n");

    // emit sort x
    emit startDoX(posMTX);




    //

    // QImage::QImage(const uchar * data, int width, int height, Format format, QImageCleanupFunction cleanupFunction = 0, void * cleanupInfo = 0)


    //  img->invertPixels(QImage::InvertRgb);




    // bool QPixmap::loadFromData ( const uchar * data, uint len, const char * format = 0, Qt::ImageConversionFlags flags = Qt::AutoColor )

}

void fb2png::goY() {

    emit threadSx();
    sortingX->wait();
    printf("parou sortingX\n");






    // allocate sortY thread 1
    sortingYa = new QThread;
    sortingYb = new QThread;
    sortingYc = new QThread;
    sortingYd = new QThread;


    // allocate sortY worker 1
    sYa = new sortIT(this, mtxR);
    sYb = new sortIT(this, mtxR);
    sYc = new sortIT(this, mtxR);
    sYd = new sortIT(this, mtxR);

    // move sY thread 1
    sYa->moveToThread(sortingYa);
    sYb->moveToThread(sortingYb);
    sYc->moveToThread(sortingYc);
    sYd->moveToThread(sortingYd);


    // slots and signals sortYa
    connect(this, SIGNAL(threadSyA()),
            sortingYa, SLOT(quit()));
    connect(sortingYa, SIGNAL(finished()),
            sYa, SLOT(deleteLater()));

    connect(this, SIGNAL(startDoYa(short int*, short int*)),
            sYa, SLOT(doYa(short int*, short int*)));

    // slots and signals sortYb
    connect(this, SIGNAL(threadSyB()),
            sortingYb, SLOT(quit()));
    connect(sortingYb, SIGNAL(finished()),
            sYb, SLOT(deleteLater()));

    connect(this, SIGNAL(startDoYb(short int*, short int*)),
            sYb, SLOT(doYb(short int*, short int*)));

    // slots and signals sortYc
    connect(this, SIGNAL(threadSyC()),
            sortingYc, SLOT(quit()));
    connect(sortingYc, SIGNAL(finished()),
            sYc, SLOT(deleteLater()));

    connect(this, SIGNAL(startDoYc(short int*, short int*)),
            sYc, SLOT(doYc(short int*, short int*)));

    // slots and signals sortYd
    connect(this, SIGNAL(threadSyD()),
            sortingYd, SLOT(quit()));
    connect(sortingYd, SIGNAL(finished()),
            sYd, SLOT(deleteLater()));

    connect(this, SIGNAL(startDoYd(short int*, short int*)),
            sYd, SLOT(doYd(short int*, short int*)));

    sortingYa->start();
    printf("sortingYa Thread criado\n");

    sortingYb->start();
    printf("sortingYb Thread criado\n");

    sortingYc->start();
    printf("sortingYc Thread criado\n");

    sortingYd->start();
    printf("sortingYd Thread criado\n");

    // emit sort Sy 1
    emit startDoYa(posMTX, &sortStatusA);
    emit startDoYb(posMTX, &sortStatusB);
    emit startDoYc(posMTX, &sortStatusC);
    emit startDoYd(posMTX, &sortStatusD);










    // allocate sortY thread 2
    sortingYe = new QThread;
    sortingYf = new QThread;
    sortingYg = new QThread;
    sortingYh = new QThread;


    // allocate sortY worker 2
    sYe = new sortIT(this, mtxR);
    sYf = new sortIT(this, mtxR);
    sYg = new sortIT(this, mtxR);
    sYh = new sortIT(this, mtxR);

    // move sY thread 2
    sYe->moveToThread(sortingYe);
    sYf->moveToThread(sortingYf);
    sYg->moveToThread(sortingYg);
    sYh->moveToThread(sortingYh);


    // slots and signals sortYe
    connect(this, SIGNAL(threadSyE()),
            sortingYe, SLOT(quit()));
    connect(sortingYe, SIGNAL(finished()),
            sYe, SLOT(deleteLater()));

    connect(this, SIGNAL(startDoYe(short int*, short int*)),
            sYe, SLOT(doYe(short int*, short int*)));

    // slots and signals sortYf
    connect(this, SIGNAL(threadSyF()),
            sortingYf, SLOT(quit()));
    connect(sortingYf, SIGNAL(finished()),
            sYf, SLOT(deleteLater()));

    connect(this, SIGNAL(startDoYf(short int*, short int*)),
            sYf, SLOT(doYf(short int*, short int*)));

    // slots and signals sortYg
    connect(this, SIGNAL(threadSyG()),
            sortingYg, SLOT(quit()));
    connect(sortingYg, SIGNAL(finished()),
            sYg, SLOT(deleteLater()));

    connect(this, SIGNAL(startDoYg(short int*, short int*)),
            sYg, SLOT(doYg(short int*, short int*)));

    // slots and signals sortYh
    connect(this, SIGNAL(threadSyH()),
            sortingYh, SLOT(quit()));
    connect(sortingYh, SIGNAL(finished()),
            sYh, SLOT(deleteLater()));

    connect(this, SIGNAL(startDoYh(short int*, short int*)),
            sYh, SLOT(doYh(short int*, short int*)));

    sortingYe->start();
    printf("sortingYe Thread criado\n");

    sortingYf->start();
    printf("sortingYf Thread criado\n");

    sortingYg->start();
    printf("sortingYg Thread criado\n");

    sortingYh->start();
    printf("sortingYh Thread criado\n");

    // emit sort Sy 2
    emit startDoYe(posMTX, &sortStatusE);
    emit startDoYf(posMTX, &sortStatusF);
    emit startDoYg(posMTX, &sortStatusG);
    emit startDoYh(posMTX, &sortStatusH);



    printf("check 1\n");

    short int scanS = 0;

    while (scanS <8)
    {
//        printf("scanS: %d\n", scanS);
//        printf("sortStatusA: %d sortStatusB: %d sortStatusC: %d sortStatusD: %d sortStatusE: %d sortStatusF: %d sortStatusG: %d sortStatusH: %d\n", sortStatusA, sortStatusB, sortStatusC, sortStatusD, sortStatusE, sortStatusF, sortStatusG, sortStatusH);
        if (sortStatusA ^ sortStatusB ^ sortStatusC ^ sortStatusD ^ sortStatusD ^ sortStatusE ^ sortStatusF ^ sortStatusG ^ sortStatusH) {
            if (sortStatusA) {
                sortStatusA = 0;
                scanS++;
                emit threadSyA();
                sortingYa->wait();
                printf("parou sYa\n");
            }
            if (sortStatusB) {
                sortStatusB = 0;
                scanS++;
                emit threadSyB();
                sortingYb->wait();
                printf("parou sYb\n");
            }
            if (sortStatusC) {
                sortStatusC = 0;
                scanS++;
                emit threadSyC();
                sortingYc->wait();
                printf("parou sYc\n");
            }
            if (sortStatusD) {
                sortStatusD = 0;
                scanS++;
                emit threadSyD();
                sortingYd->wait();
                printf("parou sYd\n");
            }
            if (sortStatusE) {
                sortStatusE = 0;
                scanS++;
                emit threadSyE();
                sortingYe->wait();
                printf("parou sYe\n");
            }
            if (sortStatusF) {
                sortStatusF = 0;
                scanS++;
                emit threadSyF();
                sortingYf->wait();
                printf("parou sYf\n");
            }
            if (sortStatusG) {
                sortStatusG = 0;
                scanS++;
                emit threadSyG();
                sortingYg->wait();
                printf("parou sYg\n");
            }
            if (sortStatusH) {
                sortStatusH = 0;
                scanS++;
                emit threadSyH();
                sortingYh->wait();
                printf("parou sYh\n");
            }

        }
    }



    int mCount = 0;

    while(mCount<64) {
        switch (mtxR[posMTX[mCount]].p) {
        case LION:
            printf("registrados: %d - X:%d - Y: %d - LION \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case PANDA:
            printf("registrados: %d - X:%d - Y: %d - PANDA \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case ELEPH:
            printf("registrados: %d - X:%d - Y: %d - ELEPH \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case FROG:
            printf("registrados: %d - X:%d - Y: %d - FROG \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case MONKE:
            printf("registrados: %d - X:%d - Y: %d - MONKE \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case HIPPO:
            printf("registrados: %d - X:%d - Y: %d - HIPPO \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case GIRRA:
            printf("registrados: %d - X:%d - Y: %d - GIRRA \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case BOSS:
            printf("registrados: %d - X:%d - Y: %d - BOSS \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case BLCKDa:
            printf("registrados: %d - X:%d - Y: %d - BLCKDa \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        case BLCKDb:
            printf("registrados: %d - X:%d - Y: %d - BLCKDb \n", mCount, mtxR[posMTX[mCount]].x, mtxR[posMTX[mCount]].y);
            mCount++;
            break;
        }
    }

}


void fb2png::gomerge() {
    short int j = 0;
    while (j < 64) {

        for (short int i = 0; i< mCountA; i++)
        {
            mtxR[j] = mtxRa[i];
            j++;
        }

        for (short int i = 0; i< mCountB; i++)
        {
            mtxR[j] = mtxRb[i];
            j++;
        }

        for (short int i = 0; i< mCountC; i++)
        {
            mtxR[j] = mtxRc[i];
            j++;
        }

        for (short int i = 0; i< mCountD; i++)
        {
            mtxR[j] = mtxRd[i];
            j++;
        }

        for (short int i = 0; i< mCountE; i++)
        {
            mtxR[j] = mtxRe[i];
            j++;
        }

        for (short int i = 0; i< mCountF; i++)
        {
            mtxR[j] = mtxRf[i];
            j++;
        }

        for (short int i = 0; i< mCountG; i++)
        {
            mtxR[j] = mtxRg[i];
            j++;
        }

        for (short int i = 0; i< mCountH; i++)
        {
            mtxR[j] = mtxRh[i];
            j++;
        }

        for (short int i = 0; i< mCountI; i++)
        {
            mtxR[j] = mtxRi[i];
            j++;
        }

        for (short int i = 0; i< mCountJ; i++)
        {
            mtxR[j] = mtxRj[i];
            j++;
        }

    }



    for (short int i = 0; i < 64;i++)
    {
        printf("mtxR[%d]->x: %d\n", i, mtxR[i].x);
        printf("mtxR[%d]->y: %d\n", i, mtxR[i].y);
        printf("mtxR[%d]->p %d\n", i, mtxR[i].p);

    }

}

int fb2png::getFMT() {
    int ao = framebuffer.alpha_offset;
    int ro = framebuffer.red_offset;
    int go = framebuffer.green_offset;
    int bo = framebuffer.blue_offset;

    /* TODO: use offset */
    if (framebuffer.bpp == 16) {
        return FB_FORMAT_RGB565; }

    /* TODO: validate */
    if (ao == 0 && ro == 8) {
        return FB_FORMAT_ARGB8888; }

    if (ao == 0 && bo == 8) {
        return FB_FORMAT_ABGR8888; }

    if (ro == 0) {
        return FB_FORMAT_RGBA8888; }

    if (bo == 0) {
        return FB_FORMAT_BGRA8888; }

    /* fallback */
    return FB_FORMAT_UNKNOWN;

}


