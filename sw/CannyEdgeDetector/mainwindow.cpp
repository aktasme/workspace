/*
 * CannyEdgeDetecor: Software foredge detection
 *
 * BLG 513E Image Processing HW#1
 *
 * Copyright (C)  Mehmet AKTAS 0504181576
 *
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gaussiankernel.h"
#include "sobelxkernel.h"
#include "sobelykernel.h"
#include <cmath>
#include <queue>
#include <utility>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonSelect, &QPushButton::clicked, this, &MainWindow::onSelectImageClicked);
    connect(ui->pushButtonCanny, &QPushButton::clicked, this, &MainWindow::onCalculateCanny);
    connect(ui->pushButtonSave, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
    connect(ui->spinBoxSigma, SIGNAL(valueChanged(int)), this, SLOT(onSigmaChanged(int)));
    connect(ui->spinBoxKernelSize, SIGNAL(valueChanged(int)), this, SLOT(onKernelSizeChanged(int)));
    connect(ui->spinBoxThresholdLow, SIGNAL(editingFinished()), this, SLOT(onThresholdLowChanged()));
    connect(ui->spinBoxThresholdHigh, SIGNAL(editingFinished()), this, SLOT(onThresholdHighChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayImage(const QImage& inputImage)
{
    qDebug() << "displayImage::Enter";

    graphicScene.clear();
    graphicScene.addPixmap(QPixmap::fromImage(inputImage));
    graphicScene.setSceneRect(inputImage.rect());
    ui->graphicsView->setScene(&graphicScene);
    ui->graphicsView->fitInView(graphicScene.sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::convertToGrayScale(QImage& inputImage)
{
    qDebug() << "convertToGrayScale::Enter";

    if(inputImage.isGrayscale())
    {
        qDebug() << "onSelectImage::Already grayscale!";
    }
    else
    {
        QImage grayScaledImage(inputImage.size(), QImage::Format_Grayscale8);
        for(int rawIndex = 0; rawIndex < inputImage.height(); rawIndex++)
        {
            quint32* inputLine = reinterpret_cast<QRgb*>(inputImage.scanLine(rawIndex));
            quint8* outputLine = grayScaledImage.scanLine(rawIndex);

            for(int columnIndex = 0; columnIndex < inputImage.width(); columnIndex++)
            {
                QRgb* inputPixel = inputLine + columnIndex;
                quint8 grayPixel = qGray(*inputPixel);
                outputLine[columnIndex] = grayPixel;
            }
        }

        inputImage = grayScaledImage;
    }
}

QImage MainWindow::convolution(const BaseKernel* kernel, const QImage& inputImage)
{
    qDebug() << "convolution::Enter";

    unsigned int kernelWidth = kernel->getWidth();
    unsigned int kernelHeight = kernel->getHeight();
    unsigned int offsetx = kernelWidth / 2;
    unsigned int offsety = kernelHeight / 2;

    unsigned int imageWidth = static_cast<unsigned int>(inputImage.width());
    unsigned int imageheight = static_cast<unsigned int>(inputImage.height());

    QImage out(inputImage.size(), inputImage.format());
    float sum;

    quint8 *line;
    const quint8 *lookupLine;

    for(unsigned int y = 0; y < imageheight; y++)
    {
        line = out.scanLine(y);
        for(unsigned  x = 0; x < imageWidth; x++)
        {
            sum = 0;

            for(unsigned int j = 0; j < kernelHeight; j++)
            {
                if (y + j < offsety || y + j >= imageheight)
                {
                    continue;
                }

                lookupLine = inputImage.constScanLine(y + j - offsety);

                for(unsigned  i = 0; i < kernelWidth; i++)
                {
                    if (x + i < offsetx || x + i >= imageWidth)
                    {
                        continue;
                    }

                    sum += kernel->value(j, i) * lookupLine[x + i - offsetx];
                }
            }

            sum = abs(sum);
            line[x] = qBound(0x00, static_cast<int>(sum), 0xFF);
        }
    }

    return out;
}

void MainWindow::gradientMagnitude(QImage& inputImage, QImage& gradientX, QImage& gradientY)
{
    qDebug() << "gradientMagnitude::Enter";

    quint8 *line;
    const quint8 *gradientXline;
    const quint8 *gradientYline;

    for(int y = 0; y < inputImage.height(); y++)
    {
        line = inputImage.scanLine(y);
        gradientXline = gradientX.scanLine(y);
        gradientYline = gradientY.scanLine(y);

        for(int x = 0; x < inputImage.width(); x++)
        {
            line[x] = qBound(0x00, static_cast<int>(hypot(gradientXline[x], gradientYline[x])), 0xFF);
        }
    }
}

void MainWindow::smoothing(QImage& inputImage)
{
    qDebug() << "smoothing::Enter";

    if(sigma < 1.0)
    {
        inputImage = baseImage;
    }
    else
    {
        GaussianKernel* kernel = new GaussianKernel(sigma, kernelSize);
        inputImage = convolution(kernel, inputImage);
    }
}

void MainWindow::findingGradients(QImage& inputImage, QImage& gradientX, QImage& gradientY)
{
    SobelXKernel sobelX;
    SobelYKernel sobelY;
    gradientX = convolution(&sobelX, inputImage);
    gradientY = convolution(&sobelY, inputImage);

    gradientMagnitude(inputImage, gradientX, gradientY);
}

void MainWindow::nonMaximumSuppression(QImage& inputImage, QImage& gradientX, QImage& gradientY)
{
    qDebug() << "nonMaximumSuppression::Enter";

    quint8 *line;
    const quint8* previousLine;
    const quint8* nextLine;
    const quint8* gradientXLine;
    const quint8* gradientYLine;

    for(int y = 1; y < inputImage.height() - 1; y++)
    {
        line = inputImage.scanLine(y);
        previousLine = inputImage.scanLine(y - 1);
        nextLine = inputImage.scanLine(y + 1);

        gradientXLine = gradientX.scanLine(y);
        gradientYLine = gradientY.scanLine(y);

        for(int x = 1; x < inputImage.width() - 1; x++)
        {
            double at = atan2(gradientYLine[x], gradientXLine[x]);
            const double dir = fmod(at + M_PI, M_PI) / M_PI * 8;

            if (((1 >= dir || dir > 7) && line[x - 1] < line[x] && line[x + 1] < line[x]) ||
                ((1 < dir || dir <= 3) && previousLine[x - 1] < line[x] && nextLine[x + 1] < line[x]) ||
                ((3 < dir || dir <= 5) && previousLine[x] < line[x] && nextLine[x] < line[x]) ||
                ((5 < dir || dir <= 7) && previousLine[x + 1] < line[x] && nextLine[x - 1] < line[x]))
                continue;

            line[x] = 0x00;
        }
    }
}

void MainWindow::doubleThresholdingAndEdgeTracking(QImage& inputImage)
{
    qDebug() << "nonMaximumSuppression::Enter";

    QImage outputImage = QImage(inputImage.size(), inputImage.format());
    outputImage.fill(0x00);

    const quint8 *inputLine;
    quint8 *outputLine;
    int ni, nj;
    std::queue<std::pair<int, int>> edges;

    for(int y = 1; y < outputImage.height() - 1; y++)
    {
        inputLine = inputImage.constScanLine(y);
        outputLine = outputImage.scanLine(y);

        for(int x = 1; x < outputImage.width() - 1; x++)
        {
            if (inputLine[x] >= thresholdMax && outputLine[x] == 0x00)
            {
                outputLine[x] = 0xFF;
                edges.push(std::make_pair(x, y));

                while (!edges.empty())
                {
                    auto point = edges.front();
                    edges.pop();

                    for(int j = -1; j <= 1; j++)
                    {
                        nj = point.second + j;
                        if (nj < 0 || nj >= inputImage.height())
                        {
                            continue;
                        }

                        inputLine = inputImage.constScanLine(nj);
                        outputLine = outputImage.scanLine(nj);

                        for(int i = -1; i <= 1; i++)
                        {
                            if (!i && !j)
                            {
                                continue;
                            }

                            ni = point.first + i;
                            if (ni < 0 || ni >= inputImage.width())
                            {
                                continue;
                            }

                            if (inputLine[ni] >= thresholdMin && outputLine[ni] == 0x00)
                            {
                                outputLine[ni] = 0xFF;
                                edges.push(std::make_pair(ni, nj));
                            }
                        }
                    }
                }
            }
        }
    }

    inputImage = outputImage;
}

void MainWindow::onSelectImageClicked()
{
    qDebug() << "onSelectImage::Enter";

    fileName = QFileDialog::getOpenFileName(this, tr("Select Image"));
    baseImage = QImage(fileName);
    resultImage = baseImage;
    displayImage(resultImage);
    ui->pushButtonCanny->setEnabled(true);
}

void MainWindow::onCalculateCanny()
{
    qDebug() << "onCannyButtonClicked::Enter";

    resultImage = baseImage;

    QImage gradientX;
    QImage gradientY;

    convertToGrayScale(resultImage);
    smoothing(resultImage);
    findingGradients(resultImage, gradientX, gradientY);
    nonMaximumSuppression(resultImage, gradientX, gradientY);
    doubleThresholdingAndEdgeTracking(resultImage);

    displayImage(resultImage);

    ui->spinBoxSigma->setEnabled(true);
    ui->spinBoxKernelSize->setEnabled(true);
    ui->spinBoxThresholdLow->setEnabled(true);
    ui->spinBoxThresholdHigh->setEnabled(true);
    ui->pushButtonSave->setEnabled(true);
}

void MainWindow::onSaveClicked()
{
    qDebug() << "onSaveClicked::Enter";

    QString path = QFileDialog::getExistingDirectory(this, tr("Destination"));
    QString name = "Canny_" + QFileInfo(fileName).fileName();
    resultImage.save(QDir(path).filePath(name));
}

void MainWindow::onSigmaChanged(int value)
{
    ui->spinBoxSigma->setEnabled(false);

    sigma = static_cast<float>(value);

    qDebug() << "onSaveClicked::Enter sigma:" << sigma;

    emit onCalculateCanny();
}

void MainWindow::onKernelSizeChanged(int value)
{
    ui->spinBoxKernelSize->setEnabled(false);

    kernelSize = static_cast<unsigned int>(value);

    qDebug() << "onSaveClicked::Enter kernelSize:" << kernelSize;

    emit onCalculateCanny();
}

void MainWindow::onThresholdLowChanged()
{
    ui->spinBoxThresholdLow->setEnabled(true);

    thresholdMin = static_cast<float>(ui->spinBoxThresholdLow->value());

    qDebug() << "onSaveClicked::Enter thresholdMin:" << thresholdMin;

    emit onCalculateCanny();
}

void MainWindow::onThresholdHighChanged()
{
    ui->spinBoxThresholdHigh->setEnabled(true);

    thresholdMax = static_cast<float>(ui->spinBoxThresholdHigh->value());

    qDebug() << "onSaveClicked::Enter thresholdMax:" << thresholdMax;

    emit onCalculateCanny();
}
