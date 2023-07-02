#include "mainwindow.h"
#include "ui_mainwindow.h"
int k = 0; // k = 0 idle/ k = 2 run / k = 3 attack
int knightSpeed = 1;
int backgroundspeed = 4;
int st = 0; //st = 0 idle / st = 1 run / st = 2 attack/
int count = 0;
int dy = 5;
int driverspeed = 3;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Создаем объект QMovie и загружаем в него анимированный GIF-файл
    QMovie *movie = new QMovie("E:/Ris/ivan/sky.gif");
    // Загружаем первый кадр GIF-изображения в объект QPixmap
    QPixmap pixmap = movie->currentPixmap();
    // Устанавливаем этот pixmap в QLabel
    ui->Sky->setPixmap(pixmap);
    // Устанавливаем объект QMovie в QLabel и запускаем анимацию
    ui->Sky->setMovie(movie);
    movie->start();

    QMovie *movie2 = new QMovie("E:/Ris/ivan/idle.gif");
    QPixmap pixmap2 = movie2->currentPixmap();
    ui->knight->setPixmap(pixmap2);
    ui->knight->setMovie(movie2);
    movie2->start();

    QMovie *movie3 = new QMovie("E:/Ris/ivan/driver.gif");
    QPixmap pixmap3 = movie3->currentPixmap();
    ui->driver->setPixmap(pixmap3);
    ui->driver->setMovie(movie3);
    movie3->start();

    QMovie *movie4 = new QMovie("E:/Ris/ivan/batman.gif");
    QPixmap pixmap4 = movie4->currentPixmap();
    ui->batman->setPixmap(pixmap4);
    ui->batman->setMovie(movie4);
    movie4->start();

    QMovie *movie5 = new QMovie("E:/Ris/ivan/monster1.gif");
    QPixmap pixmap5 = movie5->currentPixmap();
    ui->monster->setPixmap(pixmap5);
    ui->monster->setMovie(movie5);
    movie5->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeout()
{
    if(k == 1 && ui->knight->geometry().x() == 0)//run
    {
        // остановить анимацию гифки
        QMovie *movie2 = ui->knight->movie();
        movie2->stop();

        //загрузить новую гифку и начать её анимацию, если это первый раз
        QMovie *newMovie = new QMovie("E:/Ris/ivan/run.gif");
        ui->knight->setMovie(newMovie);
        newMovie->start();
        k = 2;
    }
    if(k==2 && ui->batman->geometry().x() > -1000)
    {
        ui->batman->setGeometry(ui->batman->geometry().x() - 10,50,235,240);
    }
    if(k==2 && ui->monster->geometry().x() > -1000){
        ui->monster->setGeometry(ui->monster->geometry().x() - 8,300,200,256);
    }
    if(ui->knight->geometry().x() + 150 >= ui->monster->geometry().x() && k==2){
        // остановить анимацию рыцаря
        QMovie *movie2 = ui->knight->movie();
        movie2->stop();

        // загрузить новую гифку атаки и начать её анимацию
        QMovie *newMovie = new QMovie("E:/Ris/ivan/attack.gif");
        ui->knight->setMovie(newMovie);
        newMovie->start();
        k = 3;        // опустить монстра на Y = 600
        ui->monster->setGeometry(ui->monster->geometry().x(), 600, 200, 256);

        // задержка перед сменой гифки на бег
        QTimer::singleShot(1000, this, [=](){
            // загрузить новую гифку бега и начать её анимацию
            QMovie *newMovie2 = new QMovie("E:/Ris/ivan/run.gif");
            ui->knight->setMovie(newMovie2);
            newMovie2->start();
            k = 2;
        });
    }
    if(k == 2 && ui->knight->geometry().x() < 350 && st == 1)
    {
        ui->knight->setGeometry(ui->knight->geometry().x() + knightSpeed,280,600,279);
        if(ui->knight->geometry().x() + 150 >= ui->box->geometry().x()){
            if(ui->knight->geometry().y() < 300){
                ui->knight->setGeometry(ui->knight->geometry().x(),300,600,279);
            }
            if(ui->knight->geometry().x() > ui->box->geometry().x() && ui->knight->geometry().y() == 300)
            {
               ui->knight->setGeometry(ui->knight->geometry().x(),280,600,279);
            }
        }
    }
    if(ui->knight->geometry().x() >= ui->hay2->geometry().x() + 400)
    {
        QMovie *movieX = ui->knight->movie();
        movieX->stop();
        QMovie *newMovie3 = new QMovie("E:/Ris/ivan/idle.gif");
        ui->knight->setMovie(newMovie3);
        newMovie3->start();
    }
    if(ui->background->geometry().x() > -2400 && st == 1)
    {
        ui->hay2->setGeometry(ui->hay2->geometry().x() - 8,400,825,196);
        ui->background->setGeometry(ui->background->geometry().x() - backgroundspeed,0,3600,600);
        ui->box->setGeometry(ui->box->geometry().x() - backgroundspeed,450,141,114);
        ui->driver->setGeometry(ui->driver->geometry().x() - backgroundspeed,350,250,250);
    }
    if(ui->background->geometry().x() <= -2399 && ui->knight->geometry().x() >= 349 && ui->driver->geometry().x() <= 1200)
    {
        ui->driver->setGeometry(ui->driver->geometry().x() + driverspeed,350,250,250);
    }
    if(ui->driver->geometry().x() >= 1200 && ui->background->geometry().x() <= -2399 && ui->knight->geometry().x() >= 349 && ui->meteor->geometry().y() < 80)
    {
        ui->meteor->setGeometry(ui->meteor->geometry().x() -3 ,ui->meteor->geometry().y() +10,564,564);
    }
    if(ui->meteor->geometry().y() >= 80){
        QApplication::exit(); // закрытие приложения
    }
}

void MainWindow::on_pushButton_clicked()
{
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer->start(25);
    k = 1;
    st = 1;
}
