#include "objectinfo.h"

objectInfo::objectInfo(QString passedType, QString passedBand, QString passedAlbum,
                       double passedPrice, QString passedLocation, qint32 passedXS,
                       qint32 passedS, qint32 passedM, qint32 passedL, qint32 passedXL,
                       qint32 passedXXL, QString passedcatNum, qint32 passedTQ)
{
    type = passedType;
    band = passedBand;
    album = passedAlbum;
    price = passedPrice;
    location = passedLocation;
    XS = passedXS;
    S = passedS;
    M = passedM;
    L = passedL;
    XL = passedXL;
    XXL = passedXXL;
    catNum = passedcatNum;
    TQ = passedTQ;
}
