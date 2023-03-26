#include "tablemodel/tablemodeltradehistory.h"
#include <QBrush>

TableModelTradeHistory::TableModelTradeHistory(QObject *parent)
    : QSqlTableModel{parent}
{

}

QVariant TableModelTradeHistory::data(const QModelIndex &idx, int role) const
{
    if(role == Qt::BackgroundRole)
    {
        if(QSqlTableModel::data(this->index(idx.row(), 1)).toString() == "sell")
        {
            return QColor(255, 142, 136);
        }
        else if(QSqlTableModel::data(this->index(idx.row(), 1)).toString() == "buy")
        {
            return QColor(173, 253, 135);
        }
    }
    else if(role == Qt::DisplayRole)
    {
        return QSqlTableModel::data(idx);
    }
    return QVariant();
}
