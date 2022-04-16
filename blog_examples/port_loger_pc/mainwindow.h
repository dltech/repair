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
#include <QValueAxis>
#include <QBoxLayout>
#include <QTextEdit>
#include <QWidget>

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
    QBoxLayout *lay;
    QTextEdit *cmds;
    QStatusBar *stBar;
    QWidget *nestedW;
    // port
    QSerialPort *rxPort;
    // chart
    QLineSeries* series;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisX;
    QValueAxis *axisY;
    // костыль
    QTimer *timer;
    // buffer
    static constexpr int rxSize = 20000;
    static constexpr int scrSize = 200;
    static constexpr float period = 0.0002;
    int received;
    char rxBuf[rxSize];
    int lr = 0;
    bool isPause = false;
    void samsungRecognizer(void);
    void necRecognizer(void);
};
#endif // MAINWINDOW_H
