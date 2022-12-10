#ifndef PORTFOLIOWINDOW_H
#define PORTFOLIOWINDOW_H

#include <QWidget>

namespace Ui {
class PortfolioWindow;
}

class PortfolioWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PortfolioWindow(QWidget *parent = nullptr);
    ~PortfolioWindow();

private:
    Ui::PortfolioWindow *ui;
};

#endif // PORTFOLIOWINDOW_H
