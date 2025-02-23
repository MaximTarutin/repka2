#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    lev_01 = new Level_01(this);

    connect(this, &MainWindow::width_scr, lev_01, &Level_01::get_width);
    connect(this, &MainWindow::height_scr, lev_01, &Level_01::get_height);

    screen_size();          // Присваиваем значения SCREEN_WIDTH и SCREEN_HEIGHT
    initial();

    connect(button_exit, &QPushButton::clicked, this, &MainWindow::exit_of_game);
    connect(button_start, &QPushButton::clicked, this, &MainWindow::start_level);
}

MainWindow::~MainWindow()
{
    delete button_exit;
    delete button_start;
    delete background_logo;
    delete lev_01;
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
    emit width_scr(WIDTH_SCREEN);
    emit height_scr(HEIGHT_SCREEN);

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

// --------------------- Запуск уровня ---------------------------------------

void MainWindow::start_level()
{
    lev_01->show();
}

