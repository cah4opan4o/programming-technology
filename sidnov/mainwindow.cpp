#include "mainwindow.h"
#include "ui_mainwindow.h"
int k = 0; // переменная ключ, для переключения действий                                                  НЕ ЗАБУДЬ ПОМЕНЯТЬ АДРЕСС ФАЙЛОВ ПОДКАЧКИ
int groundspeed = 4;
int witchspeed = 3;
int count;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    count = 0;
    // Создаем объект QMovie и загружаем в него анимированный GIF-файл
    QMovie *movie = new QMovie("E:/Ris/sidnov/run.gif");

    // Загружаем первый кадр GIF-изображения в объект QPixmap
    QPixmap pixmap = movie->currentPixmap();

    // Устанавливаем этот pixmap в QLabel
    ui->witch->setPixmap(pixmap);

    // Устанавливаем объект QMovie в QLabel и запускаем анимацию
    ui->witch->setMovie(movie);
    movie->start();

    QMovie *movie2 = new QMovie("E:/Ris/sidnov/flymouse.gif");
    QPixmap pixmap2 = movie2->currentPixmap();
    ui->flymouse->setPixmap(pixmap2);
    ui->flymouse->setMovie(movie2);
    movie2->start();

    QMovie *movie3 = new QMovie("E:/Ris/sidnov/redis.gif");
    QPixmap pixmap3 = movie3->currentPixmap();
    ui->redis->setPixmap(pixmap3);
    ui->redis->setMovie(movie3);
    movie3->start();

    QMovie *movie4 = new QMovie("E:/Ris/sidnov/slime.gif");
    QPixmap pixmap4 = movie4->currentPixmap();
    ui->slime->setPixmap(pixmap4);
    ui->slime->setMovie(movie4);
    movie4->start();

    QMovie *movie5 = new QMovie("E:/Ris/sidnov/sky.gif");
    QPixmap pixmap5 = movie5->currentPixmap();
    ui->sky->setPixmap(pixmap5);
    ui->sky->setMovie(movie5);
    movie5->start();
}

void MainWindow::onTimeout(){
    if(k == 1 && ui->witch->geometry().x() < 0){ // начальное передвижение летучей мыши и ведьмы
        ui->witch->setGeometry(ui->witch->geometry().x() + witchspeed,380,247,207);
        ui->flymouse->setGeometry(ui->witch->geometry().x(),260,184,99);
    }
    if(k == 1 && ui->background->geometry().x() <=-1650){
        k = 2;
        // остановить анимацию гифки
        QMovie *movie = ui->witch->movie();
        movie->stop();

        // загрузить новую гифку и начать её анимацию, если это первый раз
        QMovie *newMovie = new QMovie("E:/Ris/sidnov/water.gif");
        ui->witch->setMovie(newMovie);
        newMovie->start();
    }
    if(k == 2){
        // если проигрывание гифки "water.gif" завершено, увеличить счетчик
        QMovie *newMovie = ui->witch->movie();
        int frameCount = newMovie->frameCount();
        int currentFrameNumber = newMovie->currentFrameNumber();
        if (currentFrameNumber == frameCount - 1) {
            ++count;

            // если проигрывание гифки "water.gif" завершено 4 раза, остановить код:
            if (count == 10) {
                newMovie->stop();
                k = 3;
            }
        }
    }

    if (k == 1 && ui->background->geometry().x() >-1650 && ui->witch->geometry().x() >= 0){ // движение заднего плана, переднего, редиски и слайма
        ui->background->setGeometry(ui->background->geometry().x()-groundspeed,0,3000,600);
        ui->foreground->setGeometry(ui->foreground->geometry().x()-groundspeed,0,3000,600);
        ui->redis->setGeometry(ui->redis->geometry().x()-groundspeed,90,177,152);
        ui->slime->setGeometry(ui->slime->geometry().x()-groundspeed,110,89,72);
    }
    if(k == 3){
        QMovie *movie = ui->witch->movie();
        movie->stop();

        // загрузить новую гифку и начать её анимацию, если это первый раз
        QMovie *newMovie = new QMovie("E:/Ris/sidnov/run.gif");
        ui->witch->setMovie(newMovie);
        newMovie->start();
        k = 4;
    }

    if(k == 4 && ui->background->geometry().x() >-2100){ // движение заднего и переднего плана
        ui->background->setGeometry(ui->background->geometry().x()-groundspeed,0,3000,600);
        ui->foreground->setGeometry(ui->foreground->geometry().x()-groundspeed,0,3000,600);
    }

    if(ui->background->geometry().x() == -2100){
        k = 5;
    }

    if(k == 5){
        QMovie *movie = ui->witch->movie();
        movie->stop();

        // загрузить новую гифку и начать её анимацию, если это первый раз
        QMovie *newMovie = new QMovie("E:/Ris/sidnov/fly.gif");
        ui->witch->setMovie(newMovie);
        newMovie->start();
        k = 6;
    }

    if(k == 6 && ui->background->geometry().x() >-2400){ // движение заднего и переднего плана
        ui->background->setGeometry(ui->background->geometry().x()-groundspeed,0,3000,600);
        ui->foreground->setGeometry(ui->foreground->geometry().x()-groundspeed,0,3000,600);
    }
    if(k == 6 && ui->witch->geometry().x() < 600){ // полёт ведьмы вверх вместе с летучей мышью
        ui->witch->setGeometry(ui->witch->geometry().x() + witchspeed,ui->witch->geometry().y() - witchspeed,247,207);
        ui->flymouse->setGeometry(ui->witch->geometry().x(),ui->witch->geometry().y(),184,99);
    }
    if(ui->witch->geometry().x() > 600){ // закрыть приложение, когда ведьма за экраном
        QApplication::exit();
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
    k = 1;
    ui->background->setPixmap(QPixmap("E:/Ris/sidnov/zadnik.png"));
    ui->foreground->setPixmap(QPixmap("E:/Ris/sidnov/pered.png"));
}
