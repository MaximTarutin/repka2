#include "level_06.h"

Level_06::Level_06(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
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
        card[i] = new PicObject(this);
        card[i]->resize_object(WIDTH_SCREEN/14, HEIGHT_SCREEN/6);
        card[i]->hide();
    }

    // -------------------- Заполняем список координат карт -----------------------------

    inv_card[0]->move(WIDTH_SCREEN/6, HEIGHT_SCREEN/20);
    inv_card[0]->show();

    for(int i=0; i<=29; i++)
    {
        if((i>=0)&&(i<=5))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*i+WIDTH_SCREEN/80*i;
            int y = inv_card[0]->y();
            inv_card[i]->move(x, y);
            //inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=6)&&(i<=11))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*(i-6)+WIDTH_SCREEN/80*(i-6);
            int y = inv_card[0]->y()+inv_card[0]->height()+HEIGHT_SCREEN/60;
            inv_card[i]->move(x, y);
            //inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=12)&&(i<=17))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*(i-12)+WIDTH_SCREEN/80*(i-12);
            int y = inv_card[0]->y()+inv_card[0]->height()*2+HEIGHT_SCREEN/60*2;
            inv_card[i]->move(x, y);
            //inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=18)&&(i<=23))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*(i-18)+WIDTH_SCREEN/80*(i-18);
            int y = inv_card[0]->y()+inv_card[0]->height()*3+HEIGHT_SCREEN/60*3;
            inv_card[i]->move(x, y);
            //inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=24)&&(i<=29))
        {
            int x = inv_card[0]->x()+inv_card[0]->width()*(i-24)+WIDTH_SCREEN/80*(i-24);
            int y = inv_card[0]->y()+inv_card[0]->height()*4+HEIGHT_SCREEN/60*4;
            inv_card[i]->move(x, y);
            //inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        }
    };

    // ------------------------------------------------------------------------------------

    mix_coordinates();  // Перемешиваем пары координат в списке

    for(int i=0; i<=29; i++)    // Расставляем карточки на поле
    {
        if((i==0)or(i==15)) card[i]->load(":/resource/lev_06/babka.png");
        if((i==1)or(i==16)) card[i]->load(":/resource/lev_06/dedka.png");
        if((i==2)or(i==17)) card[i]->load(":/resource/lev_06/chesnok1.png");
        if((i==3)or(i==18)) card[i]->load(":/resource/lev_06/grusha1.png");
        if((i==4)or(i==19)) card[i]->load(":/resource/lev_06/kartoshka1.png");
        if((i==5)or(i==20)) card[i]->load(":/resource/lev_06/koshka.png");
        if((i==6)or(i==21)) card[i]->load(":/resource/lev_06/morkovka1.png");
        if((i==7)or(i==22)) card[i]->load(":/resource/lev_06/myshka.png");
        if((i==8)or(i==23)) card[i]->load(":/resource/lev_06/ogurec1.png");
        if((i==9)or(i==24)) card[i]->load(":/resource/lev_06/rediska1.png");
        if((i==10)or(i==25)) card[i]->load(":/resource/lev_06/repka.png");
        if((i==11)or(i==26)) card[i]->load(":/resource/lev_06/tomat.png");
        if((i==12)or(i==27)) card[i]->load(":/resource/lev_06/tykva1.png");
        if((i==13)or(i==28)) card[i]->load(":/resource/lev_06/vnuchka.png");
        if((i==14)or(i==29)) card[i]->load(":/resource/lev_06/zuchka.png");
        int x = coordinates_card.at(i).at(0);
        int y = coordinates_card.at(i).at(1);
        card[i]->move(x, y);
        card[i]->show();
    }
}

// ------------------------------- Перемешиваем список координат --------------------------

void Level_06::mix_coordinates()
{
    int k = 0;
    for(int i=0; i<=29; i++)
    {
        k = rnd(0,29);
        coordinates_card[i].swap(coordinates_card[k]);  // Меняем местами элементы списка
    }
}

