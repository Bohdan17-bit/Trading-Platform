#ifndef TABLEMODELTRADEHISTORY_H
#define TABLEMODELTRADEHISTORY_H

#include <QSqlTableModel>

class TableModelTradeHistory : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TableModelTradeHistory(QObject *parent = nullptr);
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // TABLEMODELTRADEHISTORY_H
