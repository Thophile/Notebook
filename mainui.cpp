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

void MainUi::on_translateButton_clicked()
{
    QString noTranslate = " 0123456789";
    QString input = ui->Input->toPlainText();
    QString result = "";
    int offset = ui->spinBox->value();
    int latin1;


    for(int i = 0; i < input.length(); i++){

           if (isupper(input.at(i).toLatin1())){
               latin1 = (input.at(i).toLatin1() - 65 + offset) % 26 + 65;
           }else if(islower(input.at(i).toLatin1())){
                latin1 = (input.at(i).toLatin1() - 97 + offset) % 26 + 97;
           }else{
               continue;
           }
           input.replace(i,1,QChar(latin1));


    }
    ui->Result->setText(input);
}
