#include "level_03.h"
#include "qmediaplayer.h"
#include "qpushbutton.h"
#include <ctime>

Level_03::Level_03(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_03::~Level_03()
{
    delete background;
    background = nullptr;
    delete output;
    output = nullptr;
    delete sound;
    sound = nullptr;
    delete button_back;
    button_back = nullptr;
    delete table;
    table = nullptr;
    delete mysl;
    mysl = nullptr;
    delete babka;
    babka = nullptr;
    for(int i=0; i<5; i++)
    {
        delete tazik[i];
        tazik[i] = nullptr;
    }
}

// ------------------ Получаем ширину и высоту экрана ----------------------

void Level_03::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_03::get_height(int h)
{
    HEIGHT_SCREEN = h;
}


// ------------------------- Инициализация уровня --------------------------------------

void Level_03::initial()
{
    background = new QLabel(this);
    background->setStyleSheet("border-image: url(:/resource/lev_03/level_3.jpg);");
    this->setCentralWidget(background);
    background->show();

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    sound = new QMediaPlayer(this);
    output = new QAudioOutput();
    sound->setAudioOutput(output);
    output->setVolume(1);

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    table = new PicObject(":/resource/lev_03/stol.png", this);
    table->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    table->move(WIDTH_SCREEN/2-WIDTH_SCREEN/20, HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    table->show();

    babka = new PicObject(":/resource/lev_03/babka.png", this);
    babka->resize_object(WIDTH_SCREEN/8, HEIGHT_SCREEN/3);
    babka->move(WIDTH_SCREEN/2+WIDTH_SCREEN/4, HEIGHT_SCREEN/2+HEIGHT_SCREEN/10);
    babka->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/5);
    mysl->move(babka->x()+babka->width()/2, babka->y()-mysl->height());
    mysl->show();

    tazik[0] = new PicObject(":/resource/lev_03/tazik-01.png", this);       // Пустой тазик
    tazik[1] = new PicObject(":/resource/lev_03/tazik-02.png", this);       // Тазик с молоком
    tazik[2] = new PicObject(":/resource/lev_03/tazik-03.png", this);       // Тазик добавили масло
    tazik[3] = new PicObject(":/resource/lev_03/tazik-04.png", this);       // Тазик добавили яйца
    tazik[4] = new PicObject(":/resource/lev_03/tazik-05.png", this);       // Тазик добавили муку и соль
    tazik[5] = new PicObject(":/resource/lev_03/tazik-06.png", this);       // тазик со взбитым тестом

    tazik[0]->resize_object(WIDTH_SCREEN/16, HEIGHT_SCREEN/12);
    tazik[0]->move(WIDTH_SCREEN/30, HEIGHT_SCREEN-HEIGHT_SCREEN/3+HEIGHT_SCREEN/10);
    tazik[0]->show();

    for(int i=1; i<=5; i++)
    {
        tazik[i]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/8);
        tazik[i]->move(table->x()+table->width()/4,
                       table->y()-tazik[i]->height()/2-tazik[i]->height()/6);
        tazik[i]->hide();
    }

    produkt[0] = new PicObject(":/resource/lev_03/milk.png", this);
    produkt[0]->resize_object(WIDTH_SCREEN/14, HEIGHT_SCREEN/10);


}
