#include "mainui.h"
#include "ui_mainui.h"
#include <QObject>

MainUi::MainUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainUi)
{
    ui->setupUi(this);

}

MainUi::~MainUi()
{
    delete ui;
}


    }
}
