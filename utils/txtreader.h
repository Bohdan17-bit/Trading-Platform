#ifndef TXTREADER_H
#define TXTREADER_H
#include <QStringList>

class TXTReader
{
private:
    TXTReader(){};
public:
    static QStringList getListCryptocoins();
};

#endif // TXTREADER_H
