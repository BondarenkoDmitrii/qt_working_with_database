#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QtSql/QSqlDatabase"
#include "QSqlQuery"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Подключаем базу данных
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\worklists.db");
    db.open();

    //Осуществляем запрос проб
    QSqlQuery query;
    query.exec("SELECT id, barcode FROM samples");

    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString barcode = query.value(1).toString();

    //Создаем строки в дереве
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,barcode);

    //Осуществляем запрос тестов для проб
    QSqlQuery query_id;
    query_id.exec("SELECT id_samples, id_test FROM samples_has_tests");

    while (query_id.next())
{
    QString id_samples = query_id.value(0).toString();
    QString id_test = query_id.value(1).toString();

    //Осуществляем запрос тестов
    QSqlQuery query_test;
    query_test.exec("SELECT id, name FROM tests");


    if(id == id_samples)
    {
    QTreeWidgetItem *child = new QTreeWidgetItem();

    while (query_test.next())
    {
        QString idt = query_test.value(0).toString();
        QString name = query_test.value(1).toString();
    if(id_test == idt)
    {
    child->setText(1,name);
    itm->addChild(child);
    }
    }
    ui->treeWidget->addTopLevelItem(itm);
    }
}
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
