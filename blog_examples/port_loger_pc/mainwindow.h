#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QPushButton>
#include <QToolBar>
#include <QStatusBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void upgrade(void);
    void prevF(void);
    void nextF(void);
    void pauseF(void);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // buttons
    QToolBar *toolBar;
    QPushButton *prev;
    QPushButton *next;
    QPushButton *pause;
    QStatusBar *stBar;
    // port
    QSerialPort *rxPort;
    // chart
    QLineSeries* series;
    QChart *chart;
    QChartView *chartView;
    // костыль
    QTimer *timer;
    // buffer
    static constexpr int rxSize = 300000;
    static constexpr int scrSize = 100;
    char rxBuf[rxSize];
    int lr = 0;
    bool isPause = false;
};
#endif // MAINWINDOW_H
