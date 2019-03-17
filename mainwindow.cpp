#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.hpp"
using nlohmann::json;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QTreeWidget* treewidget = ui->treeWidget;
    QTreeWidgetItem* header = new QTreeWidgetItem;
    header->setText(0, "name");
    header->setText(1, "age");
    header->setText(2, "etc");
    treewidget->setHeaderItem(header);

    QTreeWidgetItem* row1 = new QTreeWidgetItem(treewidget);
    row1->setText(0, "col 1");
    row1->setText(1, "col 2");
    row1->setText(2, "col 3");

    QTreeWidgetItem* row2 = new QTreeWidgetItem(treewidget);
    // treewidget->addTopLevelItem(row2);
    row2->setText(0, "?");
    row2->setText(1, "??");
    row2->setText(2, "???");

    QTreeWidgetItem* subItem1 = new QTreeWidgetItem;
    subItem1->setText(0, "? - 1");
    subItem1->setText(1, "? - 2");
    subItem1->setText(2, "? - 3");
    row2->addChild(subItem1);

    QTreeWidgetItem* subItem2 = new QTreeWidgetItem;
    subItem2->setText(0, "? - 1");
    subItem2->setText(1, "? - 2");
    row2->addChild(subItem2);

    QTreeWidgetItem* subsubItem1 = new QTreeWidgetItem;
    subsubItem1->setText(0, "k - 1");
    subsubItem1->setText(1, "k - 2");
    subItem2->addChild(subsubItem1);

    // treewidget->resize(500, 500);
    // treewidget->setSortingEnabled(true);
    // treewidget->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plainTextEdit_textChanged()
{
    auto t = ui->plainTextEdit->toPlainText();
    json j;

    try {
        json j3 = json::parse(t.toStdString());
        travelJson(j3);
    } catch(json::parse_error) {
        printf("failed\n");
    }
}

void MainWindow::travelJson(const nlohmann::json& j) {
    // somethings.
}
