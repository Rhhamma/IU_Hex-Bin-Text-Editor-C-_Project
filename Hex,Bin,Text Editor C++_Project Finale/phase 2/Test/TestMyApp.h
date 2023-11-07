#ifndef TESTMYAPP_H
#define TESTMYAPP_H

#include <QObject>

class TestMyApp : public QObject {
    Q_OBJECT

private slots:
    void testReadFileContent();
    void testDetectContentType();
    void testConvertTextToHex();
    void testConvertHexToText();
    void testConvertTextToBinary();
    void testConvertBinaryToText();
    void testConvertHexToBinary();
    void testConvertBinaryToHex();
};

#endif // TESTMYAPP_H
