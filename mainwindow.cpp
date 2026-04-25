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
    qDebug() << "current level - " << CURRENT_LEVEL;
    switch(CURRENT_LEVEL)
    {
        case 1:
        if(lev_01==(void*)0)
        {
                lev_01 = new Level_01();
                connect(this, &MainWindow::width_scr, lev_01, &Level_01::get_width);        // Получаем разрешение экрана для всех
                connect(this, &MainWindow::height_scr, lev_01, &Level_01::get_height);      // уровней и пишем значение в каждом уровне

                screen_size();
                lev_01->initial();  // Запускаем инициализацию уровня

                connect(lev_01, &Level_01::next_level, this, &MainWindow::get_current_level);  // получаем номер следующего уровня

                connect(lev_01->button_back, &QPushButton::clicked, this, [this]()      // Нажимаем кнопку назад
                        {
                            this->showFullScreen();
                            lev_01->hide();
                        });
                connect(lev_01->button_next, &QPushButton::clicked, this, [this]()
                        {                    
                            lev_01->hide();
                            // ---------------------- Здесь сделать удаление из памяти ненужных объектов из lev_01
                            start_level();
                        });
        }
        lev_01->showFullScreen();   // Показываем уровень во весь экран
        this->hide();               // Скрываем это окно

        break;
        case 2:
            if(lev_02==(void*)0)
            {
                lev_02 = new Level_02();
                connect(this, &MainWindow::width_scr, lev_02, &Level_02::get_width);        // Получаем разрешение экрана для всех
                connect(this, &MainWindow::height_scr, lev_02, &Level_02::get_height);      // уровней и пишем значение в каждом уровне
                screen_size();
                lev_02->initial();

                connect(lev_02, &Level_02::next_level, this, &MainWindow::get_current_level); // получаем номер следующего уровня

                connect(lev_02->button_back, &QPushButton::clicked, this, [this]()          // Нажали кнопку назад в lev_02
                        {
                            lev_01->showFullScreen();
                            lev_02->hide();
                        });
                connect(lev_02, &Level_02::next_level, this, [this]()
                        {
                            lev_02->close();
                            delete lev_02;                      // удаляем второй уровень
                            lev_02 = nullptr;
                            lev_01->showFullScreen();
                            lev_01->view_rdbvgkm(2);            // Показываем дедку на lev_01
                        });
            }
            lev_02->showFullScreen();
            this->hide();
        break;
        case 3:
            if(lev_03==(void*)0)
            {
                lev_03 = new Level_03();
                connect(this, &MainWindow::width_scr, lev_03, &Level_03::get_width);        // Получаем разрешение экрана для всех
                connect(this, &MainWindow::height_scr, lev_03, &Level_03::get_height);      // уровней и пишем значение в каждом уровне
                screen_size();
                lev_03->initial();

                connect(lev_03, &Level_03::next_level, this, &MainWindow::get_current_level);

                connect(lev_03->button_back, &QPushButton::clicked, this, [this]()
                        {
                            lev_01->showFullScreen();
                            lev_03->hide();
                        });
                connect(lev_03, &Level_03::next_level, this, [this]()
                        {
                            lev_03->close();
                            lev_01->showFullScreen();
                            lev_01->view_rdbvgkm(3);            // Показываем бабку на lev_01
                            delete lev_03;                      // удаляем второй уровень
                            lev_03 = nullptr;
                        });
            }
            lev_03->showFullScreen();
            this->hide();
        break;
        case 4:
            if(lev_04==(void*)0)
            {
                lev_04 = new Level_04();
                connect(this, &MainWindow::width_scr, lev_04, &Level_04::get_width);        // Получаем разрешение экрана для всех
                connect(this, &MainWindow::height_scr, lev_04, &Level_04::get_height);      // уровней и пишем значение в каждом уровне
                screen_size();
                lev_04->initial();

                connect(lev_04, &Level_04::next_level, this, &MainWindow::get_current_level);

                connect(lev_04->button_back, &QPushButton::clicked, this, [this]()
                        {
                            lev_01->showFullScreen();
                            lev_04->hide();
                        });
                connect(lev_04, &Level_04::next_level, this, [this]()
                        {
                            lev_04->close();
                            lev_01->showFullScreen();
                            lev_01->view_rdbvgkm(4);            // Показываем внучку на lev_01
                            delete lev_04;                      // удаляем второй уровень
                            lev_04 = nullptr;
                        });
            }
            lev_04->showFullScreen();
            this->hide();
        break;
        case 5:
            if(lev_05==(void*)0)
            {
                lev_05 = new Level_05();
                connect(this, &MainWindow::width_scr, lev_05, &Level_05::get_width);
                connect(this, &MainWindow::height_scr, lev_05, &Level_05::get_height);      // разрешение экрана
                screen_size();
                lev_05->initial();

                connect(lev_05, &Level_05::next_level, this, &MainWindow::get_current_level);   // Получаем номер следующего уровня

                connect(lev_05->button_back, &QPushButton::clicked, this, [this]()      // Нажали кнопку назад
                        {
                            lev_01->showFullScreen();
                            lev_05->hide();
                        });
                connect(lev_05, &Level_05::next_level, this, [this]()
                        {
                            lev_05->close();
                            lev_01->showFullScreen();
                            lev_01->view_rdbvgkm(5);
                            delete lev_05;
                            lev_05 = nullptr;
                        });
            }
            lev_05->showFullScreen();
            this->hide();
        break;
    }
}

// ------------------------- Получаем номер уровня ----------------------------------------

void MainWindow::get_current_level(int lev)
{
    CURRENT_LEVEL = lev;
}

