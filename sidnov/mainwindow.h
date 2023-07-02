#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTimer"
#include "QLabel"
#include "QMovie"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimeout();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
};
#endif // MAINWINDOW_H

// ТЗ: Ведьма выходит из дома вместе со своим питомцем - летучей мышью, и направляется к небольшому деревцу, которое растет у дома. Она поливает его и после этого улетает на работу.
