/*
 * CannyEdgeDetecor: Software for edge detection
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
        for (int rawIndex = 0; rawIndex < image.height(); rawIndex++)
        {
            quint32* inputLine = reinterpret_cast<QRgb*>(inputImage.scanLine(rawIndex));
            quint8* outputLine = grayScaledImage.scanLine(rawIndex);

            for (int columnIndex = 0; columnIndex < image.width(); columnIndex++)
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
    unsigned int kernelWidth = kernel->getWidth();
    unsigned int kernelHeight = kernel->getHeight();
    unsigned int offsetx = kernelWidth / 2;
    unsigned int offsety = kernelHeight / 2;

    unsigned int imageWidth = static_cast<unsigned int>(image.width());
    unsigned int imageheight = static_cast<unsigned int>(image.height());

    QImage out(image.size(), inputImage.format());
    float sum;

    quint8 *line;
    const quint8 *lookup_line;

    for (unsigned int y = 0; y < imageheight; y++)
    {
        line = out.scanLine(y);
        for (unsigned  x = 0; x < imageWidth; x++)
        {
            sum = 0;

            for (unsigned int j = 0; j < kernelHeight; j++)
            {
                if (y + j < offsety || y + j >= imageheight)
                {
                    continue;
                }

                lookup_line = image.constScanLine(y + j - offsety);

                for (unsigned  i = 0; i < kernelWidth; i++)
                {
                    if (x + i < offsetx || x + i >= imageWidth)
                    {
                        continue;
                    }

                    sum += kernel->value(j, i) * lookup_line[x + i - offsetx];
                }
            }

            line[x] = qBound(0x00, static_cast<int>(sum), 0xFF);
        }
    }

    return out;
}

void MainWindow::gradientMagnitude(QImage& inputImage, QImage& gradientX, QImage& gradientY)
{
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

    GaussianKernel* kernel = new GaussianKernel(1.0f, 5);
    inputImage = convolution(kernel, inputImage);
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
    quint8 *line;
    const quint8* prev_line;
    const quint8* next_line;
    const quint8* gx_line;
    const quint8* gy_line;

    for (int y = 1; y < inputImage.height() - 1; y++)
    {
        line = inputImage.scanLine(y);
        prev_line = inputImage.scanLine(y - 1);
        next_line = inputImage.scanLine(y + 1);
        gx_line = gradientX.scanLine(y);
        gy_line = gradientY.scanLine(y);

        for (int x = 1; x < inputImage.width() - 1; x++)
        {
            double at = atan2(gy_line[x], gx_line[x]);
            const double dir = fmod(at + M_PI, M_PI) / M_PI * 8;

            if ((1 >= dir || dir > 7) && line[x - 1] < line[x] && line[x + 1] < line[x] ||
                (1 < dir || dir <= 3) && prev_line[x - 1] < line[x] && next_line[x + 1] < line[x] ||
                (3 < dir || dir <= 5) && prev_line[x] < line[x] && next_line[x] < line[x] ||
                (5 < dir || dir <= 7) && prev_line[x + 1] < line[x] && next_line[x - 1] < line[x])
                continue;

            line[x] = 0x00;
        }
    }
}

void MainWindow::doubleThresholdingAndEdgeTracking(QImage& inputImage)
{
    float tmin = 40;
    float tmax = 80;
    QImage outputImage = QImage(inputImage.size(), inputImage.format());
    outputImage.fill(0x00);

    const quint8 *original_line;
    quint8 *result_line;
    int ni, nj;
    std::queue<std::pair<int, int>> edges;

    for (int y = 1; y < outputImage.height() - 1; y++)
    {
        original_line = inputImage.constScanLine(y);
        result_line = outputImage.scanLine(y);

        for (int x = 1; x < outputImage.width() - 1; x++)
        {
            if (original_line[x] >= tmax && result_line[x] == 0x00)
            {
                result_line[x] = 0xFF;
                edges.push(std::make_pair(x, y));

                while (!edges.empty())
                {
                    auto point = edges.front();
                    edges.pop();

                    for (int j = -1; j <= 1; j++)
                    {
                        nj = point.second + j;
                        if (nj < 0 || nj >= image.height())
                        {
                            continue;
                        }

                        original_line = image.constScanLine(nj);
                        result_line = outputImage.scanLine(nj);

                        for (int i = -1; i <= 1; i++)
                        {
                            if (!i && !j)
                            {
                                continue;
                            }

                            ni = point.first + i;
                            if (ni < 0 || ni >= image.width())
                            {
                                continue;
                            }

                            if (original_line[ni] >= tmin && result_line[ni] == 0x00)
                            {
                                result_line[ni] = 0xFF;
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
    image = QImage(fileName);
    displayImage(image);
}

void MainWindow::onCalculateCanny()
{
    qDebug() << "onCannyButtonClicked::Enter";
    QImage gradientX;
    QImage gradientY;

    convertToGrayScale(image);
    smoothing(image);
    findingGradients(image, gradientX, gradientY);
    nonMaximumSuppression(image, gradientX, gradientY);
    doubleThresholdingAndEdgeTracking(image);
    displayImage(image);
}

void MainWindow::onSaveClicked()
{
    qDebug() << "onSaveClicked::Enter";

    QString path = QFileDialog::getExistingDirectory(this, tr("Destination"));
    QString name = "Canny_" + QFileInfo(fileName).fileName();
    image.save(QDir(path).filePath(name));
}
