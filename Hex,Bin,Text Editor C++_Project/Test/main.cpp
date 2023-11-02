#include <QApplication>
#include <QtTest>
#include "TestMyApp.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TestMyApp testObject;

    int result = QTest::qExec(&testObject);

    return result;
}
