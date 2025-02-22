#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    background_logo = new QLabel(this);
    background_logo->setStyleSheet("border-image: url(:/resource/logo/repka-fon.jpg);");
    this->setCentralWidget(background_logo);

    button_start = new QPushButton(this);
    button_start->setStyleSheet("border-image: url(:/resource/logo/prosrach.png);");
    button_start->setStyleSheet("border-image: url(:/resource/logo/start.png);");
    button_start->move(100,100);
    button_start->resize(100,100);

    button_exit = new QPushButton(this);
    button_exit->setStyleSheet("border-image: url(:/resource/logo/prosrach.png);");
    button_exit->setStyleSheet("border-image: url(:/resource/logo/exit2.png);");
    button_exit->move(400,400);
    button_exit->resize(100,100);

    screen_size();

    qDebug() << WIDTH_SCREEN << HEIGHT_SCREEN;

    connect(button_exit, &QPushButton::clicked, this, &MainWindow::exit_of_game);
}

MainWindow::~MainWindow()
{
    delete button_exit;
    delete button_start;
    delete background_logo;
}

void MainWindow::exit_of_game()
{
    exit(0);
}

void MainWindow::screen_size()
{
    WIDTH_SCREEN  = QGuiApplication::primaryScreen()->geometry().width();
    HEIGHT_SCREEN = QGuiApplication::primaryScreen()->geometry().height();
}





