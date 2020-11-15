/*
 * CannyEdgeDetecor: Software for edge detection
 *
 * BLG 513E Image Processing HW#1
 *
 * Copyright (C)  Mehmet AKTAS 0504181576
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "basekernel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayImage(const QImage& inputImage);

    QImage convolution(const BaseKernel* kernel, const QImage& inputImage);
    void gradientMagnitude(QImage& inputImage, QImage& gradientX, QImage& gradientY);


    void convertToGrayScale(QImage& inputImage);
    void smoothing(QImage& inputImage);
    void findingGradients(QImage& inputImage, QImage& gradientX, QImage& gradientY);
    void nonMaximumSuppression(QImage& inputImage, QImage& gradientX, QImage& gradientY);
    void doubleThresholdingAndEdgeTracking(QImage& inputImage);

public slots:
    void onSelectImageClicked();
    void onCalculateCanny();
    void onSaveClicked();

private:
    Ui::MainWindow *ui;

    QString fileName;
    QImage image;
    QGraphicsScene graphicScene;
};
#endif // MAINWINDOW_H
