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

    QJsonDocument loadJson(QString fileName = "appdata.json");

    void saveJson(QJsonDocument document, QString fileName = "appdata.json");

    QJsonDocument* noteItems;

    void autoSave();

private slots:
    void on_addButton_clicked();

    void on_listWidget_itemSelectionChanged();

    void on_savButton_clicked();

    void on_delButton_clicked();

    void on_togButton_clicked(bool checked);

    void on_codButton_clicked(bool checked);

private:
    Ui::MainUi *ui;

    int currentRow;

    bool displaySrc;

    bool listUpdated;

    void saveTextTo(int previousRow);

    void loadTextFrom(int currentRow);
};

#endif // MAINUI_H
