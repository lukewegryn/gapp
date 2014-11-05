#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include "Advisor.h"

int main(int argc, char ** argv) {
    QApplication app(argc, argv);
    //QWidget window;
    //window.resize(320, 240);
    Advisor myAdvisor;
    myAdvisor.resize(420, 520);
    //window.show();        // returns immediately
    //QPushButton *button = new QPushButton(QApplication::translate("ChildWidget", "Press me"), &window);
    //button->move(100, 100);
    //button->show();
    myAdvisor.show();
    return app.exec();   // enters event loop
  }