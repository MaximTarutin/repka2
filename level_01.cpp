#include "level_01.h"
#include <ctime>


Level_01::Level_01(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(NULL));
}

Level_01::~Level_01()
{
    for(int i=0; i==8; i++)
    {
        delete ovoshi_gray[i];
    }
    delete button_next;
    delete button_back;
    delete background_lev01;
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_01::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}


// ------------------- Инициализация --------------------------

void Level_01::initial()
{
    background_lev01 = new QLabel(this);
    background_lev01->setStyleSheet("border-image: url(:/resource/lev_01/fon.jpg);");
    this->setCentralWidget(background_lev01);
    background_lev01->show();

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    // Координаты объектов хранятся в списке

    QList<QList<int>>  coordinates;
    coordinates.append(QList<int>() << WIDTH_SCREEN/25 << HEIGHT_SCREEN-HEIGHT_SCREEN/4);
    coordinates.append(QList<int>() << WIDTH_SCREEN/60 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/10 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/3 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/4 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/20 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/5 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    coordinates.append(QList<int>() << WIDTH_SCREEN/6 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/15);
    coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/9 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/8);

    qDebug() << coordinates;

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

    ovoshi_gray[0] = new PicObject(":/resource/lev_01/repka-gray.png", this);
    ovoshi_gray[0]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    //ovoshi_gray[0]->move(coordinates.at(0).at(0), coordinates.at(0).at(1));
    ovoshi_gray[0]->show();

    ovoshi_gray[1] = new PicObject(":/resource/lev_01/baklagan-gray.png", this);
    ovoshi_gray[1]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    //ovoshi_gray[1]->move(WIDTH_SCREEN/60, HEIGHT_SCREEN/2+HEIGHT_SCREEN/20);
    ovoshi_gray[1]->show();

    ovoshi_gray[2] = new PicObject(":/resource/lev_01/chesnok-gray.png", this);
    ovoshi_gray[2]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    //ovoshi_gray[2]->move(WIDTH_SCREEN/2+WIDTH_SCREEN/10, HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    ovoshi_gray[2]->show();

    ovoshi_gray[3]= new PicObject(":/resource/lev_01/grusha-gray.png", this);
    ovoshi_gray[3]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    //ovoshi_gray[3]->move(WIDTH_SCREEN/2+WIDTH_SCREEN/3, HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    ovoshi_gray[3]->show();

    ovoshi_gray[4] = new PicObject(":/resource/lev_01/morkovka-gray.png", this);
    ovoshi_gray[4]->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/4);
    //ovoshi_gray[4]->move(WIDTH_SCREEN/2-WIDTH_SCREEN/4, HEIGHT_SCREEN/2+HEIGHT_SCREEN/4);
    ovoshi_gray[4]->show();

    ovoshi_gray[5] = new PicObject(":/resource/lev_01/ogurec-gray.png", this);
    ovoshi_gray[5]->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/5);
    //ovoshi_gray[5]->move(WIDTH_SCREEN/2-WIDTH_SCREEN/20, HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    ovoshi_gray[5]->show();

    ovoshi_gray[6] = new PicObject(":/resource/lev_01/tomat-gray.png", this);
    ovoshi_gray[6]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/7);
    //ovoshi_gray[6]->move(WIDTH_SCREEN/2+WIDTH_SCREEN/5, HEIGHT_SCREEN/2+HEIGHT_SCREEN/5);
    ovoshi_gray[6]->show();

    ovoshi_gray[7] = new PicObject(":/resource/lev_01/tykva-gray.png", this);
    ovoshi_gray[7]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    //ovoshi_gray[7]->move(WIDTH_SCREEN/6, HEIGHT_SCREEN/2+HEIGHT_SCREEN/15);
    ovoshi_gray[7]->show();

    ovoshi_gray[8] = new PicObject(":/resource/lev_01/rediska-gray.png", this);
    ovoshi_gray[8]->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/6);
    //ovoshi_gray[8]->move(WIDTH_SCREEN-WIDTH_SCREEN/9, HEIGHT_SCREEN/2+HEIGHT_SCREEN/8);
    ovoshi_gray[8]->show();

    int temp = 0;
    int x = 0;
    int y = 0;
    int k = 0;
    QList<int> value_i = {0,1,2,3,4,5,6,7,8};

    for(int i=0; i<9; i++)
    {
        k = rnd(0,8);
        temp = value_i[k];
        value_i[k] = value_i[i];
        value_i[i] = temp;
    }

    qDebug() << value_i;

    for(int i=0; i<9; i++)
    {
        x = coordinates.at(value_i[i]).at(0);
        y = coordinates.at(value_i[i]).at(1);
        ovoshi_gray[i]->move(x,y);
    }

//     int k = 8;
//     int i = 0;
//     QList<int> value_i;
//     bool value = false;
//     while(k>=0)
//     {
//         i = rnd(0,8);
//         if(value_i.isEmpty()==true)
//         {
//             value_i.append(i);
//             k--;
//             ovoshi_gray[i]->move(coordinates.at(i).at(0), coordinates.at(i).at(1));
//             value = true;
//         }
//     }
// qDebug() << value_i;
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
