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
    background->setStyleSheet("border-image: url(:/resource/lev_05/dvor.jpeg);");
    this->setCentralWidget(background);
    background->show();

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    dog = new PicObject(":/resource/lev_05/zuchka.png", this);
    dog->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/2+HEIGHT_SCREEN/8);
    dog->move(WIDTH_SCREEN/2+WIDTH_SCREEN/6, HEIGHT_SCREEN/2-HEIGHT_SCREEN/6);
    dog->show();


}