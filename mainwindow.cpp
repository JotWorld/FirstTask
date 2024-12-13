#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include "Qtransformfile.h"
#include "drawer.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Qtransformfile qtf;
    Drawer dr;
    QGraphicsScene *scene = new QGraphicsScene(this);
    QString filePath = "C:/Users/acer/Documents/qgraph/qtgraph.txt";
    QList<QString> strArray = qtf.read("C:/Users/acer/Documents/qgraph/qtgraph.txt");
    QVector<QVector<int>> adjancyMatrix = qtf.buildmatrix(strArray);
    int matrixLength = qtf.pointsCount(strArray);
    dr.drawEdges(scene,filePath,dr.drawPoints(scene,filePath));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(400, 400);
    ui->graphicsView->setSceneRect(0, 0, 400, 400);
}

MainWindow::~MainWindow()
{
    delete ui;
}
