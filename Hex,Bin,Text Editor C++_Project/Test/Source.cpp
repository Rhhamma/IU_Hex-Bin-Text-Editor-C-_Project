#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QFile>
#include <QIODevice>
#include <QRegularExpression>
#include <QTextStream>
enum ContentType {
    Text,
    Hex,
    Binary
};

// Read the content of a file
QString readFileContent(const QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll();
        file.close();
        return content;
    }
    return QString();
}

// Save content to a file
void saveFileContent(const QString& filePath, const QString& content) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << content;
        file.close();
    }
}

// Detect the content type (Text, Hex, Binary)
ContentType detectContentType(const QString& content) {
    QRegularExpression hexRegex("^[A-Fa-f0-9\\s]+$");
    QRegularExpression binaryRegex("^[01\\s]*$");


    if (binaryRegex.match(content).hasMatch()) {
        return Binary;
    }
    else if (hexRegex.match(content).hasMatch()) {
        return Hex;
    }
    else {
        return Text;
    }
}

// Convert text to hexadecimal representation
QString convertTextToHex(const QString& text) {
    QByteArray byteArray = text.toUtf8();
    return byteArray.toHex().toUpper();
}

// Convert hexadecimal to text representation
QString convertHexToText(const QString& hex) {
    QByteArray byteArray = QByteArray::fromHex(hex.toUtf8());
    return QString::fromUtf8(byteArray);
}

// Convert text to binary representation
QString convertTextToBinary(const QString& text) {
    QByteArray byteArray = text.toUtf8();
    QString binaryContent;
    for (char c : byteArray) {
        QString binaryStr = QString::number(static_cast<unsigned char>(c), 2).rightJustified(8, '0');
        binaryContent += binaryStr + ' ';
    }
    return binaryContent.trimmed();
}

// Convert binary to text representation
QString convertBinaryToText(const QString& binary) {
    QStringList binaryList = binary.split(' ', QString::SkipEmptyParts);
    QByteArray byteArray;
    for (const QString& binaryStr : binaryList) {
        bool ok;
        int value = binaryStr.toInt(&ok, 2);
        if (ok) {
            byteArray.append(static_cast<char>(value));
        }
        else {
            QMessageBox::warning(nullptr, "Error", "Invalid binary value.");
            return QString();
        }
    }
    return QString::fromUtf8(byteArray);
}

// Convert hexadecimal to binary representation
QString convertHexToBinary(const QString& hex) {
    QStringList hexList = hex.split(' ', QString::SkipEmptyParts);
    QString binaryContent;
    for (const QString& hexStr : hexList) {
        bool ok;
        int value = hexStr.toInt(&ok, 16);
        if (ok) {
            QString binaryStr = QString::number(value, 2).rightJustified(8, '0');
            binaryContent += binaryStr + ' ';
        }
        else {
            QMessageBox::warning(nullptr, "Error", "Invalid hex value.");
            return QString();
        }
    }
    return binaryContent.trimmed();
}

// Convert binary to hexadecimal representation
QString convertBinaryToHex(const QString& binary) {
    QStringList binaryList = binary.split(' ', QString::SkipEmptyParts); // Remove 'Qt::'
    QString hexContent;
    for (const QString& binaryStr : binaryList) {
        bool ok;
        int value = binaryStr.toInt(&ok, 2);
        if (ok) {
            QString hexStr = QString::number(value, 16).toUpper();
            hexContent += hexStr + ' ';
        }
        else {
            QMessageBox::warning(nullptr, "Error", "Invalid binary value.");
            return QString();
        }
    }
    return hexContent.trimmed();
}
/*
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    QWidget* centralWidget = new QWidget(&window);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    QLabel* filePathLabel = new QLabel("<b>File Path:</b>");
    layout->addWidget(filePathLabel);

    QLabel* label = new QLabel("No file selected");
    layout->addWidget(label);

    QPushButton* browseButton = new QPushButton("Browse");
    layout->addWidget(browseButton);

    QLabel* fileDataLabel = new QLabel("<b>File Data:</b>");
    layout->addWidget(fileDataLabel);

    QComboBox* formatComboBox = new QComboBox;
    formatComboBox->addItems({ "Text", "Hex", "Binary" });
    formatComboBox->setEnabled(false); // Disabled until file is selected
    layout->addWidget(formatComboBox);

    QTextEdit* contentTextEdit = new QTextEdit;
    layout->addWidget(contentTextEdit);

    QPushButton* saveButton = new QPushButton("Save");
    saveButton->setEnabled(false); // Disabled until content is converted
    layout->addWidget(saveButton);

    QObject::connect(browseButton, &QPushButton::clicked, [&]() {
        QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File");
        if (!filePath.isEmpty()) {
            label->setText(filePath);

            QString content = readFileContent(filePath);
            contentTextEdit->setPlainText(content);

            ContentType contentType = detectContentType(content);
            formatComboBox->setCurrentIndex(contentType);

            formatComboBox->setEnabled(true);
            saveButton->setEnabled(true);
        }
        });

    QObject::connect(formatComboBox, &QComboBox::currentTextChanged, [&](const QString& format) {
        QString content = contentTextEdit->toPlainText();
        ContentType contentType = detectContentType(content);

        QString convertedContent;
        if (contentType == Text) {
            if (format == "Hex") {
                convertedContent = convertTextToHex(content);
            }
            else if (format == "Binary") {
                convertedContent = convertTextToBinary(content);
            }
            else {
                convertedContent = content;
            }
        }
        else if (contentType == Hex) {
            if (format == "Text") {
                convertedContent = convertHexToText(content);
            }
            else if (format == "Binary") {
                convertedContent = convertHexToBinary(content);
            }
            else {
                convertedContent = content;
            }
        }
        else { // Binary
            if (format == "Text") {
                convertedContent = convertBinaryToText(content);
            }
            else if (format == "Hex") {
                convertedContent = convertBinaryToHex(content);
            }
            else {
                convertedContent = content;
            }
        }

        contentTextEdit->setPlainText(convertedContent);
        });

    QObject::connect(saveButton, &QPushButton::clicked, [&]() {
        QString filePath = label->text();
        QString content = contentTextEdit->toPlainText();

        ContentType originalFormat = detectContentType(readFileContent(filePath));

        QString convertedContent;
        if (originalFormat == Text) {
            if (formatComboBox->currentText() == "Hex") {
                convertedContent = convertHexToText(content);
            }
            else if (formatComboBox->currentText() == "Binary") {
                convertedContent = convertBinaryToText(content);
            }
            else {
                convertedContent = content;
            }
        }
        else if (originalFormat == Hex) {
            if (formatComboBox->currentText() == "Text") {
                convertedContent = convertTextToHex(content);
            }
            else if (formatComboBox->currentText() == "Binary") {
                convertedContent = convertBinaryToHex(content);
            }
            else {
                convertedContent = content;
            }
        }
        else { // Binary
            if (formatComboBox->currentText() == "Text") {
                convertedContent = convertTextToBinary(content);
            }
            else if (formatComboBox->currentText() == "Hex") {
                convertedContent = convertHexToBinary(content);
            }
            else {
                convertedContent = content;
            }
        }

        saveFileContent(filePath, convertedContent);
        QMessageBox::information(nullptr, "Save", "File saved successfully.");
        });

    window.setCentralWidget(centralWidget);
    window.show();

    return app.exec();
}
*/
