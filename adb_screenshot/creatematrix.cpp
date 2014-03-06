#include "creatematrix.h"

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

#define WIDTH 8
#define HEIGHT 8
#define SIZE 63

createMatrix::createMatrix(QObject *parent = 0, cv::Mat *refP = 0, CustomInt tipo = 0) :
    ref(refP)
{

    tpl0 = new cv::Mat();

    switch (tipo) {
    case ELEPH:
        *tpl0 = cv::imread(ELEPHIMG);
        break;
    case HIPPO:
        *tpl0 = cv::imread(HIPPOIMG);
        break;
    case LION:
        *tpl0 = cv::imread(LIONIMG);
        break;
    case PANDA:
        *tpl0 = cv::imread(PANDAIMG);
        break;
    case GIRRA:
        *tpl0 = cv::imread(GIRRAIMG);
        break;
    case BOSS:
        *tpl0 = cv::imread(BOSSIMG);
        break;
    case FROG:
        *tpl0 = cv::imread(FROGIMG);
        break;
    case MONKE:
        *tpl0 = cv::imread(MONKEIMG);
        break;
    case BLCKDa:
        *tpl0 = cv::imread(BLCKDIMGa);
        break;
    case BLCKDb:
        *tpl0 = cv::imread(BLCKDIMGb);
        break;
    }



    ref_gray0 = new cv::Mat();
    tpl0_gray = new cv::Mat();
    dst = new cv::Mat();

    cv::cvtColor(*ref, *ref_gray0, CV_BGR2GRAY);
    cv::cvtColor(*tpl0, *tpl0_gray, CV_BGR2GRAY);



}

void createMatrix::Work(short int *status, short int *counter = 0, struct mtxPoints *mtxRX = 0, CustomInt tipo = 0) {
    char bufe[1024];

    switch (tipo) {
    case ELEPH:
        file = new QFile("eleph.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case HIPPO:
        file = new QFile("hippo.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case LION:
        file = new QFile("lion.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case PANDA:
        file = new QFile("panda.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case GIRRA:
        file = new QFile("girra.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case BOSS:
        file = new QFile("boss.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case FROG:
        file = new QFile("frog.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case MONKE:
        file = new QFile("monke.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case BLCKDa:
        file = new QFile("BLCKDa.txt");
        file->open(QIODevice::WriteOnly);
        break;
    case BLCKDb:
        file = new QFile("BLCKDb.txt");
        file->open(QIODevice::WriteOnly);
        break;
    }





    fastMatchTemplate(ref_gray0, tpl0_gray, dst, 2);
    while (true)
    {
        double minval, maxval;
        cv::Point minloc, maxloc;
        cv::minMaxLoc(*dst, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= 0.9)
        {
            cv::rectangle(
                        *ref, maxloc,
                        cv::Point(maxloc.x + tpl0->cols, maxloc.y + tpl0->rows), CV_RGB(0,255,0), 2);
            cv::floodFill(
                        *dst, maxloc,
                        cv::Scalar(0), 0,
                        cv::Scalar(.1),
                        cv::Scalar(1.)
                        );
            short int num = *counter;
            mtxRX[num].x = (maxloc.x) + (tpl0->cols)/2;
            mtxRX[num].y = (maxloc.y) + (tpl0->rows)/2;
            mtxRX[num].p = tipo;
            sprintf(bufe, "registrados: %d - X:%d - Y: %d - TIPO: %d - thread: %#07x\n", num, mtxRX[num].x, mtxRX[num].y, mtxRX[num].p, this->QObject::thread()->currentThreadId());
            file->write(bufe);
            (*counter)++;
        }
        else
            break;

    }
    file->close();



    *status = 1;
}

void createMatrix::fastMatchTemplate(cv::Mat *srca,  // The reference image
                                     cv::Mat *srcb,  // The template image
                                     cv::Mat *dst,   // Template matching result
                                     int maxlevel)   // Number of levels
{
    std::vector<cv::Mat> refs, tpls, results;

    // Build Gaussian pyramid
    cv::buildPyramid(*srca, refs, maxlevel);
    cv::buildPyramid(*srcb, tpls, maxlevel);

    cv::Mat ref, tpl, res;

    // Process each level
    for (int level = maxlevel; level >= 0; level--)
    {
        ref = refs[level];
        tpl = tpls[level];
        res = cv::Mat::zeros(ref.size() + cv::Size(1,1) - tpl.size(), CV_32FC1);

        if (level == maxlevel)
        {
            // On the smallest level, just perform regular template matching
            cv::matchTemplate(ref, tpl, res, CV_TM_CCORR_NORMED);
        }
        else
        {
            // On the next layers, template matching is performed on pre-defined
            // ROI areas.  We define the ROI using the template matching result
            // from the previous layer.

            cv::Mat mask;
            cv::pyrUp(results.back(), mask);

            cv::Mat mask8u;
            mask.convertTo(mask8u, CV_8U);

            // Find matches from previous layer
            std::vector<std::vector<cv::Point> > contours;
            cv::findContours(mask8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

            // Use the contours to define region of interest and
            // perform template matching on the areas
            for (unsigned int i = 0; i < contours.size(); i++)
            {
                cv::Rect r = cv::boundingRect(contours[i]);
                cv::matchTemplate(
                            ref(r + (tpl.size() - cv::Size(1,1))),
                            tpl,
                            res(r),
                            CV_TM_CCORR_NORMED
                            );
            }
        }

        // Only keep good matches
        cv::threshold(res, res, 0.94, 1., CV_THRESH_TOZERO);
        results.push_back(res);
    }

    res.copyTo(*dst);
}

createMatrix::~createMatrix() {
        delete tpl0, ref_gray0, tpl0_gray, dst, file;

}
