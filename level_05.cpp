#include "level_05.h"
#include "qmediaplayer.h"
#include "qpushbutton.h"

Level_05::Level_05(QWidget *parent)
    : QMainWindow{parent}
{

}
Level_05::~Level_05()
{
    delete output;
    output = nullptr;
    delete sound;
    sound = nullptr;
    delete background;
    background = nullptr;
    delete button_back;
    button_back = nullptr;
    delete mysl;
    mysl = nullptr;
    delete dog;
    dog = nullptr;
}

// -------------------- Получаем разрешение экрана --------------------------------

void Level_05::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_05::get_height(int h)
{
    HEIGHT_SCREEN = h;
}

// --------------------------- Инициализация --------------------------------------

void Level_05::initial()
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
    background->setStyleSheet("border-image: url(:/resource/lev_05/dvor.jpeg);"); // Фон экрана
    this->setCentralWidget(background);
    background->show();

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    dog = new PicObject(":/resource/lev_05/zuchka.png", this);
    dog->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
    dog->move(WIDTH_SCREEN/2+WIDTH_SCREEN/12, HEIGHT_SCREEN/2-HEIGHT_SCREEN/10);    // Собака на фоне
    dog->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/3+HEIGHT_SCREEN/15);
    mysl->move(dog->x()+dog->width()/2, dog->y()-dog->height()/2-dog->height()/6);  // Мысль собаки
    mysl->show();

    panel[0] = new PicObject(":/resource/lev_05/cyan.png", this);
    panel[0]->resize_object(WIDTH_SCREEN/9, HEIGHT_SCREEN/5);

    coordinates.append(QList<int>() << WIDTH_SCREEN/40 << HEIGHT_SCREEN/6);
    panel[0]->move(coordinates.at(0).at(0), coordinates.at(0).at(1));
    coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width() << panel[0]->y());
    coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()*2 << panel[0]->y());
    coordinates.append(QList<int>() << panel[0]->x() << panel[0]->y()+panel[0]->height());
    coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width() << panel[0]->y()+panel[0]->height());
    coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()*2 << panel[0]->y()+panel[0]->height());
    coordinates.append(QList<int>() << panel[0]->x() << panel[0]->y()+panel[0]->height()*2);
    coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width() << panel[0]->y()+panel[0]->height()*2);
    coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()*2 << panel[0]->y()+panel[0]->height()*2);


    for(int i=1; i<=8; i++)
    {
        panel[i] = new PicObject(":/resource/lev_05/cyan.png", this); // Рисуем панель
        panel[i]->resize_object(WIDTH_SCREEN/9, HEIGHT_SCREEN/5);
        panel[i]->move(coordinates.at(i).at(0), coordinates.at(i).at(1));
        panel[i]->show();
    }

    //coordinates.append(QList<int>() << WIDTH_SCREEN/40 << HEIGHT_SCREEN/6);
    //panel[0]->move(coordinates.at(0).at(0), coordinates.at(0).at(1));
    // coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()+1 << panel[0]->y());
    // coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()*2+1 << panel[0]->y());
    // coordinates.append(QList<int>() << panel[0]->x() << panel[0]->y()+panel[0]->height()+1);
    // coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()+1 << panel[0]->y()+panel[0]->height()+1);
    // coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()*2+1 << panel[0]->y()+panel[0]->height()+1);
    // coordinates.append(QList<int>() << panel[0]->x() << panel[0]->y()+panel[0]->height()*2+1);
    // coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()+1 << panel[0]->y()+panel[0]->height()*2+1);
    // coordinates.append(QList<int>() << panel[0]->x()+panel[0]->width()*2+1 << panel[0]->y()+panel[0]->height()*2+1);

    //panel->move(WIDTH_SCREEN/40, HEIGHT_SCREEN/6);
}