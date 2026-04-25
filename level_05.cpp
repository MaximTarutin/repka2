#include "level_05.h"
#include "qmediaplayer.h"
#include "qpushbutton.h"

Level_05::Level_05(QWidget *parent)
    : QMainWindow{parent}
{

}
Level_05::~Level_05()
{

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

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();
}