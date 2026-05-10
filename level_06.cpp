#include "level_06.h"

Level_06::Level_06(QWidget *parent)
    : QMainWindow{parent}
{

}

Level_06::~Level_06()
{

}

// ----------------------------- Инициализация -------------------------------

void Level_06::initial()
{

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