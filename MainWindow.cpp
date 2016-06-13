#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include "graph.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonVisualize_clicked()
{
    QFile file(ui->editFilename->text());
    if(!file.open(QIODevice::ReadOnly))
        return;

    QByteArray fileData = file.readAll();
    file.close();

    Binviz binviz((unsigned char*)fileData.constData(), fileData.size());
    int size = 256;
    PointMatrix m(size);
    int maxDups;
    binviz.ProducePoints(m, maxDups);

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    qreal viewWidth = ui->graphicsView->width() - 5;
    qreal viewHeight = ui->graphicsView->height() - 5;

    qreal rectWidth = viewWidth / size;
    qreal rectHeight = viewHeight / size;

    qDebug() << viewWidth;
    qDebug() << viewHeight;
    qDebug() << rectWidth;
    qDebug() << rectHeight;

    QPen pen(Qt::transparent, 0);

    /*scene->addRect(10, 10, rectWidth, rectHeight, pen, QBrush(Qt::blue));
    scene->addRect(10, 20, rectWidth, rectHeight, pen, QBrush(Qt::red));
    scene->addRect(20, 10, rectWidth, rectHeight, pen, QBrush(Qt::green));*/

    /*
4D4D4D (gray)
5DA5DA (blue)
FAA43A (orange)
60BD68 (green)
F17CB0 (pink)
B2912F (brown)
B276B2 (purple)
DECF3F (yellow)
F15854 (red)
     */

    QList<QColor> colors;
    colors.append(QColor("#4D4D4D"));
    colors.append(QColor("#5DA5DA"));
    colors.append(QColor("#FAA43A"));
    colors.append(QColor("#60BD68"));
    colors.append(QColor("#F17CB0"));
    colors.append(QColor("#B2912F"));
    colors.append(QColor("#B276B2"));
    colors.append(QColor("#DECF3F"));
    colors.append(QColor("#F15854"));

    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            int count = m.at(x, y);
            QColor color = colors[!count ? 0 : count % colors.size()];
            scene->addRect(y * rectWidth, x * rectHeight, rectWidth, rectHeight, pen, QBrush(color));
        }
    }
}
