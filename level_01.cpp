#include "level_01.h"


Level_01::Level_01(QWidget *parent)
    : QWidget{parent}
{
    initial();
}

Level_01::~Level_01()
{

}

// ------------------- Инициализация --------------------------

void Level_01::initial()
{
    background_lev01 = new QLabel(this);
    background_lev01->setStyleSheet("border-image: url(:/resource/lev_01/dom-fon.jpg);");
}

// ---------------- Получаем SCREEN_WIDTH ----------------------

void Level_01::get_width(int w)
{
    WIDTH_SCREEN = w;
}

// ---------------- Получаем SCREEN_HEIGHT ----------------------

void Level_01::get_height(int h)
{
    HEIGHT_SCREEN = h;
}
