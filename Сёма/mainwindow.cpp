#include "mainwindow.h"
#include "ui_mainwindow.h"

int k = 0;
int beespeed = 10;
int dt = 40;
int bearspeed = 2;
int count = 0;
int forestspeed = 4;
int dy = 3;
int rabbitspeed = 4;
int f = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    count = 0;
    // Создаем объект QMovie и загружаем в него анимированный GIF-файл
    QMovie *movie = new QMovie("E:/Ris/seman/bear4.gif");

    // Загружаем первый кадр GIF-изображения в объект QPixmap
    QPixmap pixmap = movie->currentPixmap();

    // Устанавливаем этот pixmap в QLabel
    ui->bear->setPixmap(pixmap);

    // Устанавливаем объект QMovie в QLabel и запускаем анимацию
    ui->bear->setMovie(movie);
    movie->start();

    // Создаем объект QMovie и загружаем в него анимированный GIF-файл
    QMovie *movie2 = new QMovie("E:/Ris/seman/bee1.gif");

    // Загружаем первый кадр GIF-изображения в объект QPixmap
    QPixmap pixmap2 = movie2->currentPixmap();

    // Устанавливаем этот pixmap в QLabel
    ui->bee->setPixmap(pixmap2);

    // Устанавливаем объект QMovie в QLabel и запускаем анимацию
    ui->bee->setMovie(movie2);
    movie2->start();

    // Создаем объект QMovie и загружаем в него анимированный GIF-файл
    QMovie *movie3 = new QMovie("E:/Ris/seman/rabbit.gif");

    // Загружаем первый кадр GIF-изображения в объект QPixmap
    QPixmap pixmap3 = movie3->currentPixmap();

    // Устанавливаем этот pixmap в QLabel
    ui->rabbit->setPixmap(pixmap3);

    // Устанавливаем объект QMovie в QLabel и запускаем анимацию
    ui->rabbit->setMovie(movie3);
    movie3->start();
}

void MainWindow::onTimeout()
{
    if(ui->forest->geometry().x() >-731 && f == 0){ //Движение леса, растений + улея вправо
        ui->forest->setPixmap(QPixmap("E:/Ris/seman/back.png"));
        ui->forest->setGeometry(ui->forest->geometry().x()-forestspeed,10,1461,440);
        ui->plant->setPixmap(QPixmap("E:/Ris/seman/plants.png"));
        ui->plant->setGeometry(ui->plant->geometry().x()-forestspeed,20,1461,431);
        ui->hive->setPixmap(QPixmap("E:/Ris/seman/da3.png"));
        ui->hive->setGeometry(ui->hive->geometry().x()-forestspeed,50,171,141);
    }

    if(ui->bee->geometry().x() < 1700){
        ui->bee->setGeometry(ui->bee->geometry().x() + beespeed, 30, 71, 71);
    }
    else if (ui->bee->geometry().x() == 1700){
        QMovie *movie2 = ui->bee->movie();
        movie2->stop();
    }
    if (ui->bear->geometry().x() < 500) { // движение медведя вправо
        ui->bear->setGeometry(ui->bear->geometry().x() + bearspeed, 210, 341, 281);
    }
    else if (k == 0) {
        // остановить анимацию гифки
        QMovie *movie = ui->bear->movie();
        movie->stop();

        // загрузить новую гифку и начать её анимацию, если это первый раз
        QMovie *newMovie = new QMovie("E:/Ris/seman/bear2.gif");
        ui->bear->setMovie(newMovie);
        newMovie->start();
        k = 1;
        f = 1;
    }
    else if(k == 1 && ui->rabbit->geometry().x() > 750)
    {
        QMovie *movie3 = new QMovie("E:/Ris/seman/bear3.gif");
        ui->bear->setMovie(movie3);
        movie3->start();
        k = 2;
    }
    else {
        // если проигрывание гифки "bear2.gif" завершено, увеличить счетчик
        QMovie *newMovie = ui->bear->movie();
        int frameCount = newMovie->frameCount();
        int currentFrameNumber = newMovie->currentFrameNumber();
        if (currentFrameNumber == frameCount - 1) {
            ++count;

            // если проигрывание гифки "bear2.gif" завершено 3 раза, остановитьВот код с учетом ваших требований:
            if (count == 10) {
                newMovie->stop();
                ui->forest->setPixmap(QPixmap("E:/Ris/seman/back1.png"));
                ui->hive->setPixmap(QPixmap("E:/Ris/seman/da2.png"));
                while (ui->hive->geometry().y() < 325){
                    ui->hive->setGeometry(ui->hive->geometry().x(),ui->hive->geometry().y() + dy,171,141);
                }
            }
        }
    }
    if(ui->rabbit->geometry().x() < 800 && ui->bear->geometry().x() > 450)
    {
        ui->rabbit->setGeometry(ui->rabbit->geometry().x() + rabbitspeed,324,171,141);
    }
    if(ui->rabbit->geometry().x() >= ui->hive->geometry().x() && ui->rabbit->geometry().x() < 800)
    { //Если корды кролика >= кордам улея, то улей двигается вместе с зайцем
        ui->hive->setGeometry(ui->hive->geometry().x() + rabbitspeed,330,171,141);
    }
    if(f == 1 && k == 2)
    {
        if(ui->forest->geometry().x() < 0){ // движение леса + природы + медведя влево
            ui->forest->setGeometry(ui->forest->geometry().x()+forestspeed,10,1461,440);
            ui->plant->setGeometry(ui->plant->geometry().x()+forestspeed,20,1461,431);
            ui->bear->setGeometry(ui->bear->geometry().x() - 5, 210, 341, 281);
        }
        else
        {
            QApplication::exit(); // закрытие приложения
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer->start(25);
}

