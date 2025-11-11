#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    screen_size();          // Присваиваем значения SCREEN_WIDTH и SCREEN_HEIGHT
    initial();

    music = new QMediaPlayer(this);
    audiooutput = new QAudioOutput();
    music->setAudioOutput(audiooutput);
    audiooutput->setVolume(0.3);
    music->setSource(QUrl("qrc:/resource/sound/fon.mp3"));
    music->setLoops(QMediaPlayer::Infinite);
    music->play();
}

MainWindow::~MainWindow()
{
    delete music;
    music = nullptr;
    delete audiooutput;
    audiooutput = nullptr;
    delete button_exit;
    button_exit = nullptr;
    delete button_start;
    button_start = nullptr;
    delete background_logo;
    background_logo = nullptr;
    delete lev_01;
    lev_01 = nullptr;
    delete lev_02;
    lev_02 = nullptr;
}

// ------------------ Вычисляем разрешение экрана ---------------------------

void MainWindow::screen_size()
{
    WIDTH_SCREEN  = QGuiApplication::primaryScreen()->geometry().width();
    HEIGHT_SCREEN = QGuiApplication::primaryScreen()->geometry().height();
    emit width_scr(WIDTH_SCREEN);
    emit height_scr(HEIGHT_SCREEN);
    //qDebug() << WIDTH_SCREEN << HEIGHT_SCREEN;
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

    connect(button_exit, &QPushButton::clicked, this, &MainWindow::exit_of_game);   // Выход из игры
    connect(button_start, &QPushButton::clicked, this, &MainWindow::start_level);   // Запуск текущего уровня
}


// --------------------- Выход из игры ---------------------------------------

void MainWindow::exit_of_game()
{
    music->stop();
    delete music;
    delete audiooutput;
    exit(0);
}

// --------------------- Запуск уровня ---------------------------------------

void MainWindow::start_level()
{
    this->hide();
    switch(CURRENT_LEVEL)
    {
    case 1:
        if(lev_01==(void*)0)   // Если объект не существует, то создаем его
        {
            lev_01 = new Level_01();
            connect(this, &MainWindow::width_scr, lev_01, &Level_01::get_width);        // Получаем разрешение экрана для всех
            connect(this, &MainWindow::height_scr, lev_01, &Level_01::get_height);      // уровней и пишем значение в каждом уровне
            screen_size();
        }
        lev_01->showFullScreen();
        lev_01->initial();
        connect(lev_01->button_back, &QPushButton::clicked, this, [this](){
                lev_01->back_level(); this->showFullScreen();});
        connect(lev_01->button_next, &QPushButton::clicked, this, [this](){
            lev_01->close(); CURRENT_LEVEL=2; start_level();});
        break;
    case 2:
        if(lev_02==(void*)0)
        {
            lev_02 = new Level_02();
            connect(this, &MainWindow::width_scr, lev_02, &Level_02::get_width);
            connect(this, &MainWindow::height_scr, lev_02, &Level_02::get_height);
            connect(lev_02, &Level_02::next_level, this, [this](){
                CURRENT_LEVEL=3; lev_01->show(); lev_01->view_rdbvgkm(2);           // Если ловим сигнал, прибавляем номер уровня
                connect(lev_01->button_next, &QPushButton::clicked, this, [this](){
                    CURRENT_LEVEL=3; delete lev_02; lev_02 = nullptr;               // Объект lev_02 уничтожается
                    start_level();});});                                            // при победе 2 уровня кнопка button_next перейдет
                                                                                    // на 3 уровень

            screen_size();
            lev_02->initial();
        }
        lev_02->showFullScreen();
        connect(lev_02->button_back, &QPushButton::clicked, this, [this](){
                lev_02->back_level(); lev_01->showFullScreen();});

        break;
    case 3:
        if(lev_03==(void*)0)
        {
            lev_03 = new Level_03();
            connect(this, &MainWindow::width_scr, lev_03, &Level_03::get_width);
            connect(this, &MainWindow::height_scr, lev_03, &Level_03::get_height);
            connect(lev_03, &Level_03::next_level, this, [this](){
                CURRENT_LEVEL=4; lev_01->show(); lev_01->view_rdbvgkm(3);           // Если ловим сигнал, прибавляем номер уровня
                connect(lev_01->button_next, &QPushButton::clicked, this, [this](){
                    CURRENT_LEVEL=4; delete lev_03; lev_03 = nullptr;               // Объект lev_03 уничтожается
                    start_level();});});                                            // при победе 3 уровня кнопка button_next перейдет
                                                                                    // на 4 уровень.

            screen_size();
            lev_03->initial();
        }
        lev_03->showFullScreen();
        connect(lev_03->button_back, &QPushButton::clicked, this, [this](){
                lev_03->back_level(); lev_01->showFullScreen();});
        break;
    }
}

