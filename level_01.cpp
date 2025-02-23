#include "level_01.h"


Level_01::Level_01(QWidget *parent)
    : QMainWindow(parent)
{

}

Level_01::~Level_01()
{
    delete background_lev01;
}

// ------------------- Инициализация --------------------------

void Level_01::initial()
{
    background_lev01 = new QLabel(this);
    background_lev01->setStyleSheet("border-image: url(:/resource/lev_01/dom-fon.jpg);");
    this->setCentralWidget(background_lev01);

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    button_next = new QPushButton(this);
    button_next->setStyleSheet("border-image: url(:/resource/lev_01/next.png);");
    button_next->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_next->move(WIDTH_SCREEN-WIDTH_SCREEN/12, HEIGHT_SCREEN/20);
    button_next->hide();
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

// ---------------- Возврат на главный экран --------------------

void Level_01::back_level()
{
    this->close();
}
