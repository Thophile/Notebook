#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>
#include <QMainWindow>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QJsonDocument>
#include <QBoxLayout>
#include <QJsonObject>
#include <QJsonArray>
#include <QLayout>
#include <QLabel>
#include <QScrollArea>
#include <QListWidget>
#include <QStandardPaths>
#include <QObject>
#include <QShortcut>

namespace Ui {
class MainUi;
}

class MainUi : public QWidget
{
    Q_OBJECT

public:
    explicit MainUi(QWidget *parent = nullptr);

    ~MainUi();

private slots:

    void on_translateButton_clicked();

private:
    Ui::MainUi *ui;

};

#endif // MAINUI_H
