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
    for(int i=0; i<=29; i++)
    {
        delete inv_card[i];
        inv_card[i] = nullptr;
        delete card[i];
        card[i] = nullptr;
    }
    for(int i=0; i<2; i++)
    {
        delete hand[i];
        hand[i] = nullptr;
    }
    delete timer_show;
    timer_show = nullptr;
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
    timer_show = new QTimer(this);
    connect(timer_show, &QTimer::timeout, this, &Level_06::checking_for_math);
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

    create_rubaha();                    // Создаем рубашки карт
    create_cards();                     // Загружаем картинки карт
    create_coordinates_list();          // Создаем список координат карт
    mix_coordinates();                  // Перемешиваем пары координат в списке
    arrange_card();                     // Расставляем карточки на поле

    for(int i=0; i<2; i++)      // Показываем подсказку перед первым ходом
    {
        hand[i] = new PicObject(":/resource/lev_01/ruka.png", this);
        hand[i]->resize_object(WIDTH_SCREEN/25, HEIGHT_SCREEN/12);
        hand[i]->show();
        hand[i]->raise();
    }

    connect(hand[1], &PicObject::move_end, this, &Level_06::help);
    HELP_CARD = rnd(0,14);
    help();
}


// ------------------------------ Создаем карты и их рубашки -----------------------------

void Level_06::create_cards()
{
    for(int i=0; i<=29; i++)
    {
        card[i] = new PicObject(this);
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
        card[i]->resize_object(WIDTH_SCREEN/14, HEIGHT_SCREEN/6);
        card[i]->move(WIDTH_SCREEN/6, HEIGHT_SCREEN/20);
        card[i]->hide();
    }
}

void Level_06::create_rubaha()
{
    for(int i=0; i<=29; i++)
    {
        inv_card[i] = new PicObject(this);
        inv_card[i]->load(":/resource/lev_06/plitka.jpg");
        inv_card[i]->resize_object(WIDTH_SCREEN/14, HEIGHT_SCREEN/6);
        inv_card[i]->move(WIDTH_SCREEN/6, HEIGHT_SCREEN/20);
        inv_card[i]->hide();
        inv_card[i]->setObjectName(QString::number(i));
        connect(inv_card[i], &PicObject::clicked, this, &Level_06::mousePressEvent);
    }
}

// ------------------------- Создаем список координат карт -------------------------------

void Level_06::create_coordinates_list()
{

    for(int i=0; i<=4; i++)         // Расставляем карты в ряды
    {
        for(int j=0; j<=5; j++)
        {
            int k = 5*i+j+i;
            static int g = -1;  // ряд
            if(k%5 == 0) g++;
            int x = inv_card[0]->x()+inv_card[0]->width()*j+WIDTH_SCREEN/80*j;
            int y = inv_card[g]->y()+inv_card[g]->height()*i+HEIGHT_SCREEN/60*i;
            inv_card[k]->move(x,y);
            inv_card[k]->show();
        }
    }

    for(int i=0; i<=29; i++)    // Заполняем список координат
    {
        if(i==0)
        {
            int x = WIDTH_SCREEN/6;
            int y = HEIGHT_SCREEN/20;
            inv_card[i]->move(x, y);
            inv_card[i]->show();
            coordinates_card.append(QList<int>() << x << y);
        } else
        if((i>=1)&&(i<=5))
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

// ------------------------------ Расставляем карты на поле -------------------------------

void Level_06::arrange_card()
{
    for(int i=0; i<=29; i++)
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
        card[i]->hide();
        inv_card[i]->move(x, y);
    }
}

// --------------------------------- Подсказка -------------------------------------------

void Level_06::help()
{
    int c = HELP_CARD;
    int x1 = card[c]->x()+card[c]->width()/4;
    int y1 = card[c]->y()+card[c]->height()/2;
    int y11 = y1+HEIGHT_SCREEN/7;
    int x2 = card[c+15]->x()+card[c+15]->width()/4;
    int y2 = card[c+15]->y()+card[c+15]->height()/2;
    int y21 = y2+HEIGHT_SCREEN/7;
    hand[0]->move_to_y(x1, y1, y11, 40);
    hand[1]->move_to_y(x2, y2, y21, 40);
}

// -------------------------------- Кликаем по карте --------------------------------------

void Level_06::mousePressEvent(QMouseEvent *pe)
{
    if(hand[1] != (void*)0)
    {
        delete hand[0];
        hand[0] = nullptr;
        delete hand[1];
        hand[1] = nullptr;
    }

    if(CLICKED_CARD==100)
    {
        if(QObject::sender() && pe->button() == Qt::LeftButton)
        {
            QString nameobj = QObject::sender()->objectName();   // Получаем имя объекта по которому кликнули
            CLICKED_CARD = nameobj.toInt();                      // Получаем номер карты
            if(OPEN_CARD[0] == 100)                              // Если первая карта еще закрыта
            {
                OPEN_CARD[0] = CLICKED_CARD;
                inv_card[CLICKED_CARD]->hide();
                card[CLICKED_CARD]->show();
                CLICKED_CARD = 100;
                return;
            } else
                if(OPEN_CARD[1] == 100)
                {
                    OPEN_CARD[1] = CLICKED_CARD;
                    inv_card[CLICKED_CARD]->hide();
                    card[CLICKED_CARD]->show();
                    //CLICKED_CARD = 100;
                    //checking_for_math();                        // Проверка карт на совпадение
                    timer_show->start(1000);
                    //qDebug() << "Это карта № " << OPEN_CARD[0] << "и карта № " << OPEN_CARD[1];
                    //exit(32);
                }
        }
    } else return;
}

// ---------------------------- Проверяем совпали ли карты ----------------------------------------

void Level_06::checking_for_math()
{
    timer_show->stop();
    if((OPEN_CARD[0]-OPEN_CARD[1]==15)or(OPEN_CARD[1]-OPEN_CARD[0]==15))
    {
        // если карты совпали
        delete card[OPEN_CARD[0]];
        delete card[OPEN_CARD[1]];
        card[OPEN_CARD[0]] = nullptr;
        card[OPEN_CARD[1]] = nullptr;
        OPEN_CARD[0] = 100;
        OPEN_CARD[1] = 100;
        CLICKED_CARD = 100;
        COUNTER++;
        qDebug() << COUNTER;
        if(COUNTER==15) exit(33);
    } else
    {
        card[OPEN_CARD[0]]->hide();
        inv_card[OPEN_CARD[0]]->show();
        card[OPEN_CARD[1]]->hide();
        inv_card[OPEN_CARD[1]]->show();
        OPEN_CARD[0] = 100;
        OPEN_CARD[1] = 100;
        CLICKED_CARD = 100;
    }
}