#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "json.hpp"

namespace Ui {
class MainWindow;
}
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plainTextEdit_textChanged();

public:
    Ui::MainWindow *ui;
    void travelJson(const std::string& keyName, const nlohmann::json& j, QTreeWidgetItem* qtree);
    std::string getTypeString(const nlohmann::json& j) {
        std::string ret;
        if(j.is_array()) {
            ret =  "[]";
        }
        else if(j.is_object()) {
            ret =  "{}";
        }
        else {
            ret =  "nnn";
        }
        std::cout << j.dump() << "=>" << ret << std::endl;
        return ret;
    }
    void showEvent( QShowEvent* event ) {
        std::string jsonText = R"(
{"a":1, "b":2, "c":{"d1":1, "d2":2}, "darr":[100,200,300,{"d1":1, "d2":2}]}
)";
        ui->plainTextEdit->setPlainText(jsonText.c_str());
        on_plainTextEdit_textChanged();
    }


};

#endif // MAINWINDOW_H
