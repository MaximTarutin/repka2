#include "level_06.h"

Level_06::Level_06(QWidget *parent)
    : QMainWindow{parent}
{

}

Level_06::~Level_06()
{

}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_06::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}

// -------------------- Получаем разрешение экрана --------------------------------

void Level_06::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_06::get_height(int h)
{
    HEIGHT_SCREEN = h;
}

// ----------------------------- Инициализация -------------------------------

void Level_06::initial()
{
    sound = new QMediaPlayer(this);
    output = new QAudioOutput();
    sound->setAudioOutput(output);
    output->setVolume(1);

    // ------ курсор -------

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    // ---------------------

    background = new QLabel(this);
    background->setStyleSheet("border-image: url(:/resource/lev_06/fon.jpg);"); // Фон экрана
    this->setCentralWidget(background);
    background->show();

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();
}

