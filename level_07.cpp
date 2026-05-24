#include "level_07.h"
#include "qmediaplayer.h"

Level_07::Level_07(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_07::~Level_07()
{

}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_07::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}

// -------------------- Получаем разрешение экрана --------------------------------

void Level_07::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_07::get_height(int h)
{
    HEIGHT_SCREEN = h;
}


// ----------------------------- Инициализация -------------------------------------

void Level_07::initial()
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
    background->setStyleSheet("border-image: url(:/resource/lev_07/dvor.jpg);"); // Фон экрана
    this->setCentralWidget(background);
    background->show();

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    Myschka = new PicObject(":/resource/lev_07/myshka.png", this);
    Myschka->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    Myschka->move(WIDTH_SCREEN-Myschka->width()*1.5, HEIGHT_SCREEN-Myschka->height());
    Myschka->show();

    Mysl = new PicObject(":/res2/mysl.png", 500, 500, this);
    Mysl->move(Myschka->x()+50, Myschka->y()-Myschka->height());
    Mysl->show();
}