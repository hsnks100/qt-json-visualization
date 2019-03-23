#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "json.hpp"
#include <iostream>
using nlohmann::json;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // QTreeWidgetItem* subItem1 = new QTreeWidgetItem;
    // subItem1->setText(0, "? - 1");
    // row1->addChild(subItem1);

    // QTreeWidgetItem* subItem2 = new QTreeWidgetItem;
    // subItem2->setText(0, "? - 1");
    // row1->addChild(subItem2);

    // QTreeWidgetItem* subsubItem1 = new QTreeWidgetItem;
    // subsubItem1->setText(0, "k - 1");
    // subItem2->addChild(subsubItem1);

    QTreeWidget* treewidget = ui->treeWidget;
    treewidget->resize(500, 500);
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
        QTreeWidget* treewidget = ui->treeWidget;
        treewidget->clear();
        QTreeWidgetItem* header = new QTreeWidgetItem;
        header->setText(0, "name");
        treewidget->setHeaderItem(header);

        QTreeWidgetItem* row1 = new QTreeWidgetItem(treewidget);
        row1->setText(0, "JSON");


        travelJson("JSON", j3, row1);
        treewidget->expandAll();
        // travelJson(j3);
    } catch(json::parse_error) {
        printf("failed\n");
    }
}

/*
{"a":1, "b":2, "c":{"d1":1, "d2":2}, "darr":[100,200,300,{"d1":1, "d2":2}]}
*/

void MainWindow::travelJson(const std::string& keyName, const nlohmann::json& j, QTreeWidgetItem* qtree) {
    // somethings.
    if(j.is_object()) {
        // std::string t = i.key();
        QTreeWidgetItem* row1 = new QTreeWidgetItem;
        std::string key = getTypeString(j) + keyName;
        row1->setText(0, QString(key.c_str()));
        qtree->addChild(row1);

        for (auto i = j.begin(); i != j.end(); ++i) {
            // std::cout << *it << '\n';
            travelJson(i.key(), *i, row1);
        }
    }
    else if(j.is_array()) {
        QTreeWidgetItem* row1 = new QTreeWidgetItem;
        std::string key = getTypeString(j) + keyName;
        row1->setText(0, QString(key.c_str()));
        qtree->addChild(row1);
        for(auto& i: j.items()) {
            // std::string t = i.key();
            // std::cout << t << ":";
            travelJson(i.key(), i.value(), row1);
        }

    }
    else if(j.is_primitive()) {
        std::string v;
        v = keyName + ":" + j.dump();
        QTreeWidgetItem* row1 = new QTreeWidgetItem;
        row1->setText(0, QString(v.c_str()));
        qtree->addChild(row1);
        std::cout << v << std::endl;
    }
    // printf("%d\n", __LINE__);
    // if(j.is_object()) {
    //     for(auto& i: j.items()) {
    //         printf("%s\n", i.key().c_str());
    //         if(i.value().is_object()) {
    //             QTreeWidgetItem* row1 = new QTreeWidgetItem;
    //             std::string key = i.key();
    //             row1->setText(0, QString(key.c_str()));
    //             printf("qtree->%s\n", key.c_str());
    //             qtree->addChild(row1);

    //             travelJson(i.value(), row1);
    //         }
    //         else if(i.value().is_primitive()) {
    //             printf("%d\n", __LINE__);
    //             QTreeWidgetItem* row1 = new QTreeWidgetItem;
    //             printf("%d\n", __LINE__);
    //             std::string value = "";
    //             if(i.value().is_string()) {
    //                 value = i.value().get<std::string>();
    //             }
    //             else if(i.value().is_number()) {
    //                 value = i.value().get<double>();
    //             }
    //             printf("%d\n", __LINE__);
    //             row1->setText(0, QString(value.c_str()));
    //             printf("%d\n", __LINE__);
    //             qtree->addChild(row1);
    //             printf("qtree->%s\n", value.c_str());

    //         }
    //     }
    // }
}
