#include "mainui.h"
#include "ui_mainui.h"
#include <QObject>

MainUi::MainUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainUi)
{
    ui->setupUi(this);

    //Initialise list
    QJsonDocument noteItems = this->loadJson();
    for (int i = 0; i < noteItems.array().size(); i++) {
        QJsonObject row = noteItems.array().at(i).toObject();
        ui->listWidget->addItem(row.value("title").toString());

    }

    //Open first file
    currentRow = 0;
    ui->listWidget->setCurrentRow( 0 );

    //Link shortcut to save button action
    QShortcut *shortcut = new QShortcut(QKeySequence("CTRL+S"), this);

    QObject::connect(shortcut, &QShortcut::activated, this, &MainUi::on_savButton_clicked);

}

MainUi::~MainUi()
{
    delete ui;
}

/* === Methods === */

//Load the json data
QJsonDocument MainUi::loadJson(QString fileName) {

    QFile jsonFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +"/"+ fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

//Save data as json
void MainUi::saveJson(QJsonDocument document, QString fileName) {

    QFile jsonFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +"/"+ fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
    jsonFile.close();
}

//Save the text to the file
void MainUi::saveTextTo(int currentRow){

    //Read textEdit content
    QString content = ui ->textEdit->toMarkdown();
    QString title = ui->listWidget->item(currentRow)->text();


    //Load json object
    QJsonDocument data = this->loadJson();
    QJsonArray arr = data.array();
    QJsonObject file = arr.at(currentRow).toObject();

    //Update json value
    file.insert("note", QJsonValue::fromVariant(content));
    file.insert("title", QJsonValue::fromVariant(title));
    arr.removeAt(currentRow);
    arr.insert(currentRow, file);
    data.setArray(arr);
    this->saveJson(data);

}

//Load the text from a file
void MainUi::loadTextFrom(int currentRow){
    QString content = this->loadJson().array()[currentRow].toObject()["note"].toString();
    if(displaySrc)
        ui->textEdit->setPlainText(content);
    else
        ui->textEdit->setMarkdown(content);
}

//Autosave current file on app closing
void MainUi::autoSave(){
    this->saveTextTo(this->currentRow);
}

/* === Slots === */

//Save current and load next file
void MainUi::on_listWidget_itemSelectionChanged()
{
    //Dont save if it's a new or deleted item
    if(this->listUpdated){
        if(this->currentRow != -1) saveTextTo(this->currentRow);
    }
    loadTextFrom(ui->listWidget->currentRow());
    this->currentRow = ui->listWidget->currentRow();

    //Reseting flag
    this->listUpdated = true;

}

//Create a new file
void MainUi::on_addButton_clicked()
{
    //getting promptfrom view
    QString title = ui->searchBar->text();
    if(title == "") return;
    //creating entry
    QJsonObject noteItem;
    noteItem.insert("title",QJsonValue::fromVariant(title));
    noteItem.insert("note",QJsonValue::fromVariant(""));

    //Updating json
    QJsonDocument data = this->loadJson();
    QJsonArray arr = data.array();
    arr.append(noteItem);
    data.setArray(arr);
    this->saveJson(data);

    //updating view
    ui->listWidget->addItem(title);
    ui->searchBar->clear();

}

//Save document
void MainUi::on_savButton_clicked()
{
    if(this->listUpdated){
        saveTextTo(this->currentRow);
    }
    loadTextFrom(ui->listWidget->currentRow());
    this->currentRow = ui->listWidget->currentRow();

    //Reseting flag
    this->listUpdated = true;


}

//Delete currently selected item
void MainUi::on_delButton_clicked()
{
    //Updating json
    QJsonDocument data = this->loadJson();
    QJsonArray arr = data.array();

    arr.removeAt(ui->listWidget->currentRow());
    data.setArray(arr);
    this->saveJson(data);

    //Rising flag
    this->listUpdated = false;

    //Updating view
    this->currentRow = ui->listWidget->currentRow();
    ui->listWidget->takeItem(ui->listWidget->currentRow()); //--> trigger event and come back

    //Set flag again for next event trigger
    loadTextFrom(ui->listWidget->currentRow());
    this->listUpdated = false;





}

void MainUi::on_togButton_clicked(bool checked)
{
    ui->LeftFrame->setVisible(checked);
    QIcon* ico = new QIcon(checked ? ":/icons/chev_left.ico" : ":/icons/chev_right.ico");
    ui->togButton->setIcon(*ico);
}

void MainUi::on_codButton_clicked(bool checked)
{
    this->displaySrc = checked;
    if(checked){

        QString tmp = ui->textEdit->toMarkdown();
        ui->textEdit->clear();
        ui->textEdit->setPlainText(tmp);
        ui->textEdit->setStyleSheet("");
    }
    else {
        QString tmp = ui->textEdit->toPlainText();
        ui->textEdit->clear();
        ui->textEdit->setMarkdown(tmp);
    }

}
