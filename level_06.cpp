#include "level_06.h"

Level_06::Level_06(QWidget *parent)
    : QMainWindow{parent}
{

}

Level_06::~Level_06()
{
    delete output;
    output = nullptr;
    delete sound;
    sound = nullptr;
    delete button_back;
    button_back = nullptr;
    delete cat;
    cat = nullptr;
    delete background;
    background = nullptr;
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

    cat = new PicObject(":/resource/lev_06/cat.png", this);
    cat->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/2);
    cat->move(WIDTH_SCREEN-cat->width(), HEIGHT_SCREEN-cat->height());
    cat->show();

    for(int i=0; i<=29; i++)
    {
        inv_card[i] = new PicObject(":/resource/lev_06/plitka.jpg", this);
        inv_card[i]->resize_object(WIDTH_SCREEN/14, HEIGHT_SCREEN/6);
        inv_card[i]->hide();
    }

    // -------------------- Заполняем список координат карт -----------------------------

    inv_card[0]->move(WIDTH_SCREEN/6, HEIGHT_SCREEN/20);
    inv_card[0]->show();

    for(int i=0; i<30; i++)
    {
        if((i>=0)&&(i<=5))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*i+WIDTH_SCREEN/80*i;
            int y = inv_card[0]->y();
            inv_card[i]->move(x, y);
            inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=6)&&(i<=11))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*(i-6)+WIDTH_SCREEN/80*(i-6);
            int y = inv_card[0]->y()+inv_card[0]->height()+HEIGHT_SCREEN/60;
            inv_card[i]->move(x, y);
            inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=12)&&(i<=17))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*(i-12)+WIDTH_SCREEN/80*(i-12);
            int y = inv_card[0]->y()+inv_card[0]->height()*2+HEIGHT_SCREEN/60*2;
            inv_card[i]->move(x, y);
            inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=18)&&(i<=23))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*(i-18)+WIDTH_SCREEN/80*(i-18);
            int y = inv_card[0]->y()+inv_card[0]->height()*3+HEIGHT_SCREEN/60*3;
            inv_card[i]->move(x, y);
            inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=24)&&(i<=29))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*(i-24)+WIDTH_SCREEN/80*(i-24);
            int y = inv_card[0]->y()+inv_card[0]->height()*4+HEIGHT_SCREEN/60*4;
            inv_card[i]->move(x, y);
            inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        }
    };

    // ------------------------------------------------------------------------------------

    qDebug() << coordinates_card;
}

