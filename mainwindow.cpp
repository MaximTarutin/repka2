#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    screen_size();          // Присваиваем значения SCREEN_WIDTH и SCREEN_HEIGHT
    initial();

    connect(button_exit, &QPushButton::clicked, this, &MainWindow::exit_of_game);
}

MainWindow::~MainWindow()
{
    delete button_exit;
    delete button_start;
    delete background_logo;
}

// ------------------ Вычисляем разрешение экрана ---------------------------

void MainWindow::screen_size()
{
    WIDTH_SCREEN  = QGuiApplication::primaryScreen()->geometry().width();
    HEIGHT_SCREEN = QGuiApplication::primaryScreen()->geometry().height();
}

// ---------------------- Инициализация --------------------------------------

void MainWindow::initial()
{
    background_logo = new QLabel(this);
    background_logo->setStyleSheet("border-image: url(:/resource/logo/repka-fon.jpg);");
    this->setCentralWidget(background_logo);

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    button_start = new QPushButton(this);
    button_start->setStyleSheet("border-image: url(:/resource/logo/prosrach.png);");
    button_start->setStyleSheet("border-image: url(:/resource/logo/start.png);");
    button_start->move(WIDTH_SCREEN/30,HEIGHT_SCREEN/20);
    button_start->resize(WIDTH_SCREEN/7,HEIGHT_SCREEN/7);

    button_exit = new QPushButton(this);
    button_exit->setStyleSheet("border-image: url(:/resource/logo/prosrach.png);");
    button_exit->setStyleSheet("border-image: url(:/resource/logo/exit2.png);");
    button_exit->move(WIDTH_SCREEN-WIDTH_SCREEN/8, HEIGHT_SCREEN-HEIGHT_SCREEN/5);
    button_exit->resize(WIDTH_SCREEN/10,HEIGHT_SCREEN/7);
}


// --------------------- Выход из игры ---------------------------------------

void MainWindow::exit_of_game()
{
    exit(0);
}



