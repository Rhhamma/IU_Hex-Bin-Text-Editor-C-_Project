#include "TestMyApp.h"
#include <QtTest>

#include "Source.cpp" // Include your original code here

void TestMyApp::testReadFileContent() {
    // Create a temporary test file
    QString testFilePath = "test.txt";
    QString testContent = "This is a test content.";
    saveFileContent(testFilePath, testContent);

    // Test reading the content
    QString result = readFileContent(testFilePath);

    QCOMPARE(result, testContent);

    // Clean up the test file
    QFile(testFilePath).remove();
}

void TestMyApp::testDetectContentType() {
    QString textContent = "This is regular text content.";
    QString hexContent = "1A 2B 3C";
    QString binaryContent = "01010100 01100101 01110011 01110100";

    ContentType textType = detectContentType(textContent);
    ContentType hexType = detectContentType(hexContent);
    ContentType binaryType = detectContentType(binaryContent);

    qDebug() << "Text type: " << textType;
    qDebug() << "Hex type: " << hexType;
    qDebug() << "Binary type: " << binaryType;

    QCOMPARE(textType, Text);
    QCOMPARE(hexType, Hex);
    QCOMPARE(binaryType, Binary);
}


void TestMyApp::testConvertTextToHex() {
    QString textContent = "Hello, World!";
    QString expectedHex = "48656C6C6F2C20576F726C6421";

    QString resultHex = convertTextToHex(textContent);
    QCOMPARE(resultHex, expectedHex);
}

void TestMyApp::testConvertHexToText() {
    QString hexContent = "48656C6C6F2C20576F726C6421";
    QString expectedText = "Hello, World!";

    QString resultText = convertHexToText(hexContent);
    QCOMPARE(resultText, expectedText);
}

void TestMyApp::testConvertTextToBinary() {
    QString textContent = "Test";
    QString expectedBinary = "01010100 01100101 01110011 01110100";

    QString resultBinary = convertTextToBinary(textContent);
    QCOMPARE(resultBinary, expectedBinary);
}

void TestMyApp::testConvertBinaryToText() {
    QString binaryContent = "01010100 01100101 01110011 01110100";
    QString expectedText = "Test";

    QString resultText = convertBinaryToText(binaryContent);
    QCOMPARE(resultText, expectedText);
}

void TestMyApp::testConvertHexToBinary() {
    QString hexContent = "1A 2B 3C";
    QString expectedBinary = "00011010 00101011 00111100";

    QString resultBinary = convertHexToBinary(hexContent);
    QCOMPARE(resultBinary, expectedBinary);
}

void TestMyApp::testConvertBinaryToHex() {
    QString binaryContent = "00011010 00101011 00111100";
    QString expectedHex = "1A 2B 3C";

    QString resultHex = convertBinaryToHex(binaryContent);
    QCOMPARE(resultHex, expectedHex);
}
