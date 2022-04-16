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
    chart->setTitle("One port loger");
    axisX->setMin(0);
    axisX->setMax(scrSize*period*1000);
    axisX->setTickCount(scrSize/10+1);
    axisX->setTickInterval(period*10000);
    axisX->setMinorTickCount(9);
    axisX->setLabelFormat("%d");
    axisY->setMin(0);
    axisY->setMax(1);
    axisY->setTickCount(2);
    chart->addSeries(series);
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
    nestedW = new QWidget(this);
    lay = new QBoxLayout(QBoxLayout::TopToBottom,nestedW);
    cmds = new QTextEdit(this);
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
    cmds->setReadOnly(true);
    lay->addWidget(chartView,10);
    lay->addWidget(cmds,2);
    addToolBar(toolBar);
    setCentralWidget(nestedW);
    setStatusBar(stBar);
    resize(1600, 300);


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
    for(int i=0 ; i<rxSize ; ++i) rxBuf[i] = 0;
    received = rxPort->bytesAvailable();
    rxPort->read(rxBuf,rxSize);
    rxPort->clear(QSerialPort::AllDirections);
    for(int i=0 ; (i<received) && (i<scrSize) ; ++i) {
        series->append((float)i*period*1000,rxBuf[i]);
    }
    QString str = QString("%1 : %2").arg(0).arg(scrSize);
    stBar->showMessage(str);
    qDebug() << received;
    necRecognizer();
}

void MainWindow::prevF()
{
    --lr;
    if(lr < 0) lr=0;
    series->clear();
    for(int i=0 ; i<scrSize ; ++i) {
        series->append((float)i*period*1000,rxBuf[i+(lr*scrSize)]);
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
        series->append((float)i*period*1000,rxBuf[i+(lr*scrSize)]);
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

void MainWindow::necRecognizer()
{
    int bitCnt = 0;
    uint8_t prev = 1;
    bool isStart = false;
    int oneCnt = 0;
    int nullCnt = 0;
    uint8_t addr;
    uint8_t command;
    uint32_t word = 0;
    for(int i=0 ; (i<received) && (i<rxSize) ; ++i) {
        // detect start bit
        if((prev == 0) && (rxBuf[i] == 1) && (nullCnt > 20)) {
            isStart = true;
            bitCnt = 0;
            addr = 0;
            command = 0;
        }
        // detect one
        if((prev == 1) && (rxBuf[i] == 0) && (isStart == true) && (oneCnt > 7) && (oneCnt < 11)) {
            word += 1<<bitCnt;
            ++bitCnt;
        }
        // detect null
        if((prev == 1) && (rxBuf[i] == 0) && (isStart == true) && (oneCnt < 7)) {
            ++bitCnt;
        }
        // decode command
        if((bitCnt >= 32) && ((word & 0xff) == (~(word >> 8) & 0xff)) && \
                             ((word >> 16 & 0xff) == (~(word >> 24) & 0xff))) {
            addr = (uint8_t)word;
            command = (uint8_t)(word >> 16);
            QString str = QString("addr %1 cmd %2").arg(addr).arg(command);
            qDebug() << str;
            cmds->append(str);
            isStart = false;
            bitCnt = 0;
        }
        // null counters in case of error
        if(bitCnt >= 32) {
            qDebug() << "comm" << word;
            bitCnt = 0;
            isStart = false;
        }
        // edge detector
        if(rxBuf[i] == 1) ++oneCnt;
        else oneCnt = 0;
        if(rxBuf[i] == 0) ++nullCnt;
        else nullCnt = 0;
        prev = rxBuf[i];
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chart;
}

