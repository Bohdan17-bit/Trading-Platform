#include "utils/txtreader.h"
#include <QFile>
#include <QTextStream>

QStringList TXTReader::getListCryptocoins()
{
    QStringList listCoins;
    QFile file("./db/cryptocoins.txt");
    if(!QFile::exists(file.fileName()))
    {
       return listCoins;
    }
    QTextStream textStream(&file);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!textStream.atEnd())
        {
            listCoins.append(textStream.readLine());
        }
    }
    return listCoins;
}
