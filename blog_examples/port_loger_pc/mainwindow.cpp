#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rxPort = new QSerialPort(this);
    series = new QLineSeries(this);
    chart = new QChart();
    chartView = new QChartView(chart);
    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);
    // qraphics settings
    series->setName("spline");
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("One port loger");
    axisX->setMin(0);
    axisX->setMax((float)scrSize*period);
    axisX->setTickCount(scrSize/10+1);
    axisX->setTickInterval(period*10);
    axisX->setMinorTickCount(9);
    axisY->setMin(0);
    axisY->setMax(1);
    axisY->setTickCount(2);
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisX,Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chartView->setRenderHint(QPainter::Antialiasing);


    // interface
    toolBar = new QToolBar(this);
    prev = new QPushButton(this);
    next = new QPushButton(this);
    pause = new QPushButton(this);
    connect(next, SIGNAL(released()), this, SLOT(nextF()));
    connect(prev, SIGNAL(released()), this, SLOT(prevF()));
    connect(pause, SIGNAL(released()), this, SLOT(pauseF()));
    prev->setText("prev");
    next->setText("next");
    pause->setText("pause");
    toolBar->addWidget(prev);
    toolBar->addWidget(next);
    toolBar->addWidget(pause);
    stBar = new QStatusBar(this);
    stBar->showMessage("0:1000");
    setCentralWidget(chartView);
    addToolBar(toolBar);
    setStatusBar(stBar);
    resize(1600, 200);

    // port settings
    QList<QSerialPortInfo> list;
    list = QSerialPortInfo::availablePorts();
    for( int i=0 ; i<list.length() ; ++i) {
        qDebug() << list[i].portName();
        if( list[i].portName().contains("ACM") ) {
            rxPort->setPortName(list[i].portName());
        }
    }
    rxPort->setBaudRate(9600,QSerialPort::Input);
    rxPort->open(QIODevice::ReadOnly);

    // update graphics
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(upgrade()));
    timer->start(1000);


}

void MainWindow::upgrade()
{
    if(isPause) return;
    series->clear();
    int obtained = rxPort->bytesAvailable();
    qDebug() << obtained;
    for(int i=0 ; i<rxSize ; ++i) rxBuf[i] = 0;
    received = rxPort->bytesAvailable();
    rxPort->read(rxBuf,rxSize);
    rxPort->clear(QSerialPort::AllDirections);
    for(int i=0 ; (i<obtained) && (i<scrSize) ; ++i) {
        series->append((float)i*period,rxBuf[i]);
    }
    QString str = QString("%1 : %2").arg(0).arg(scrSize);
    stBar->showMessage(str);
}

void MainWindow::prevF()
{
    --lr;
    if(lr < 0) lr=0;
    series->clear();
    for(int i=0 ; i<scrSize ; ++i) {
        series->append((float)i*period,rxBuf[i+(lr*scrSize)]);
    }
    QString str = QString("paused %1 : %2").arg(lr*scrSize).arg((lr+1)*scrSize);
    stBar->showMessage(str);
}

void MainWindow::nextF()
{

    ++lr;
    if(lr >= received/scrSize) lr=received/scrSize -1;
    series->clear();
    for(int i=0 ; i<scrSize ; ++i) {
        series->append((float)i*period,rxBuf[i+(lr*scrSize)]);
    }
    QString str = QString("paused %1 : %2").arg(lr*scrSize).arg((lr+1)*scrSize);
    stBar->showMessage(str);
}

void MainWindow::pauseF()
{
    isPause = !isPause;
    if(isPause) {
        QString str = QString("paused %1 : %2").arg(0).arg(scrSize);
        stBar->showMessage(str);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chart;
}

