#include "level_04.h"
#include <ctime>

Level_04::Level_04(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_04::~Level_04()
{
    delete background;
    background = nullptr;
    delete button_back;
    button_back = nullptr;    
    delete vnuchka;
    vnuchka = nullptr;
    delete holst;
    holst = nullptr;

    for(int i=0; i<=7; i++)
    {
        delete vnuchka_holst[i];
        vnuchka_holst[i] = nullptr;
    }

    for(int i=0; i<7; i++)
    {
        delete pens[i];
        pens[i] = nullptr;
        delete mysl_obj[i];
        mysl_obj[i] = nullptr;
    }

    delete mysl;
    mysl = nullptr;
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_04::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k = rand()%b+a;
    return k;
}

// ------------------- Получаем ширину и высоту экрана --------------------

void Level_04::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_04::get_height(int h)
{
    HEIGHT_SCREEN = h;
}

// ------------------------- Инициализация --------------------------------

void Level_04::initial()
{
    sound = new QMediaPlayer(this);
    output = new QAudioOutput();
    sound->setAudioOutput(output);
    output->setVolume(1);

    value_p = {0,1,2,3,4,5,6};  // нумерация карандашей в списке
    value_m = {0,1,2,3,4,5,6};  // нумерация предметов в списке

    // ------ курсор -------

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    // ---------------------

    background = new QLabel(this);
    background->setStyleSheet("border-image: url(:/resource/lev_04/fon.jpg);");
    this->setCentralWidget(background);
    background->show();

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    vnuchka = new PicObject(":/resource/lev_04/vnuchka-111.png", this);
    vnuchka->resize_object(WIDTH_SCREEN/8, HEIGHT_SCREEN/3);
    vnuchka->move(WIDTH_SCREEN/10, HEIGHT_SCREEN/2+HEIGHT_SCREEN/8);
    vnuchka->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    mysl->move(vnuchka->x()+vnuchka->width()/2, vnuchka->y()-vnuchka->height());
    mysl->show();

    holst = new PicObject(":/resource/lev_04/holst.png", this);
    holst->resize_object(WIDTH_SCREEN/5, HEIGHT_SCREEN/2+HEIGHT_SCREEN/3);
    holst->move(WIDTH_SCREEN/2, HEIGHT_SCREEN/2-HEIGHT_SCREEN/4);
    holst->show();

    vnuchka_holst[0] = new PicObject(":/resource/lev_04/vn-01.png", holst);
    vnuchka_holst[1] = new PicObject(":/resource/lev_04/vn-00.png", holst);
    vnuchka_holst[2] = new PicObject(":/resource/lev_04/vn-03.png", holst);
    vnuchka_holst[3] = new PicObject(":/resource/lev_04/vn-05.png", holst);
    vnuchka_holst[4] = new PicObject(":/resource/lev_04/vn-04.png", holst);
    vnuchka_holst[5] = new PicObject(":/resource/lev_04/vn-06.png", holst);
    vnuchka_holst[6] = new PicObject(":/resource/lev_04/vn-07.png", holst);
    vnuchka_holst[7] = new PicObject(":/resource/lev_04/vnuchka.png", holst);

    for(int i=0; i<=7; i++)
    {
        vnuchka_holst[i]->resize_object(WIDTH_SCREEN/7, HEIGHT_SCREEN/3);
        vnuchka_holst[i]->move(holst->width()/6, holst->height()/7);
        vnuchka_holst[i]->hide();
    }
    vnuchka_holst[7]->show();

    container = new PicObject(":/resource/lev_02/fon.png", this);
    container->resize_object(WIDTH_SCREEN/3, HEIGHT_SCREEN/13);
    container->move(WIDTH_SCREEN/5, HEIGHT_SCREEN/20);
    container->show();

    // Инициализируем карандаши

    pens[0] = new PicObject(":/resource/lev_04/karandash-2.png", this);
    pens[0]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[1] = new PicObject(":/resource/lev_04/karandash-1.png", this);
    pens[1]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[2] = new PicObject(":/resource/lev_04/karandash-3.png", this);
    pens[2]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[3] = new PicObject(":/resource/lev_04/karandash-5.png", this);
    pens[3]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[4] = new PicObject(":/resource/lev_04/karandash-4.png", this);
    pens[4]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[5] = new PicObject(":/resource/lev_04/karandash-6.png", this);
    pens[5]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);
    pens[6] = new PicObject(":/resource/lev_04/karandash-7.png", this);
    pens[6]->resize_object(WIDTH_SCREEN/100, HEIGHT_SCREEN/15);

    // Инициализируем объекты в мыслях внучки

    mysl_obj[0] = new PicObject(":/resource/lev_04/platok.png", mysl);
    mysl_obj[0]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/8);
    mysl_obj[0]->move(mysl->width()/2-mysl_obj[0]->width()/2,
                      mysl->height()/2-mysl_obj[0]->height());
    mysl_obj[0]->hide();
    mysl_obj[1] = new PicObject(":/resource/lev_04/lico.png", mysl);
    mysl_obj[1]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    mysl_obj[1]->move(mysl->width()/2-mysl_obj[1]->width()/2,
                      mysl->height()/2-mysl_obj[1]->height());
    mysl_obj[1]->hide();
    mysl_obj[2] = new PicObject(":/resource/lev_04/volosy.png", mysl);
    mysl_obj[2]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/15);
    mysl_obj[2]->move(mysl->width()/2-mysl_obj[2]->width()/2,
                      mysl->height()/2-mysl_obj[2]->height());
    mysl_obj[2]->hide();
    mysl_obj[3] = new PicObject(":/resource/lev_04/korzina.png", mysl);
    mysl_obj[3]->resize_object(WIDTH_SCREEN/25, HEIGHT_SCREEN/12);
    mysl_obj[3]->move(mysl->width()/2-mysl_obj[3]->width()/2,
                      mysl->height()/2-mysl_obj[3]->height());
    mysl_obj[3]->hide();
    mysl_obj[4] = new PicObject(":/resource/lev_04/grib.png", mysl);
    mysl_obj[4]->resize_object(WIDTH_SCREEN/25, HEIGHT_SCREEN/12);
    mysl_obj[4]->move(mysl->width()/2-mysl_obj[4]->width()/2,
                      mysl->height()/2-mysl_obj[4]->height());
    mysl_obj[4]->hide();
    mysl_obj[5] = new PicObject(":/resource/lev_04/platie.png", mysl);
    mysl_obj[5]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/8);
    mysl_obj[5]->move(mysl->width()/2-mysl_obj[5]->width()/2,
                      mysl->height()/2-mysl_obj[5]->height());
    mysl_obj[5]->hide();
    mysl_obj[6] = new PicObject(":/resource/lev_04/sapogi.png", mysl);
    mysl_obj[6]->resize_object(WIDTH_SCREEN/15, HEIGHT_SCREEN/20);
    mysl_obj[6]->move(mysl->width()/2-mysl_obj[6]->width()/2,
                      mysl->height()/2-mysl_obj[6]->height());
    mysl_obj[6]->hide();

    // Список координат карандашей в карандашнице

    coordinates.append(QList<int>() << container->x()+container->width()/15
                                    << container->y()+container->height()/8);
    coordinates.append(QList<int>() << container->x()+container->width()/15+container->width()/7
                                    << container->y()+container->height()/8);
    coordinates.append(QList<int>() << container->x()+container->width()/15+(container->width()/7)*2
                                    << container->y()+container->height()/8);
    coordinates.append(QList<int>() << container->x()+container->width()/15+(container->width()/7)*3
                                    << container->y()+container->height()/8);
    coordinates.append(QList<int>() << container->x()+container->width()/15+(container->width()/7)*4
                                    << container->y()+container->height()/8);
    coordinates.append(QList<int>() << container->x()+container->width()/15+(container->width()/7)*5
                                    << container->y()+container->height()/8);
    coordinates.append(QList<int>() << container->x()+container->width()/15+(container->width()/7)*6
                                    << container->y()+container->height()/8);

    mix_pens();     // Перемешиваем список карандашей
    mix_mysl();     // Перемешиваем список объектов в мысли внучки

    for(int i=0; i<=6; i++)     // Расставляем карандаши
    {
        pens[value_p[i]]->move(coordinates[i].at(0), coordinates[i].at(1));
        pens[i]->show();
    }

    mysl_obj[value_m[STEP]]->show();

    connect(pens[0], &PicObject::clicked, this, [this](){ACTIVE_PEN=0;});
    connect(pens[1], &PicObject::clicked, this, [this](){ACTIVE_PEN=1;});
    connect(pens[2], &PicObject::clicked, this, [this](){ACTIVE_PEN=2;});
    connect(pens[3], &PicObject::clicked, this, [this](){ACTIVE_PEN=3;});   // Определяем активный карандаш
    connect(pens[4], &PicObject::clicked, this, [this](){ACTIVE_PEN=4;});   // по клику по нему
    connect(pens[5], &PicObject::clicked, this, [this](){ACTIVE_PEN=5;});
    connect(pens[6], &PicObject::clicked, this, [this](){ACTIVE_PEN=6;});
    for(int i=0; i<=6; i++)
    {
        connect(pens[i], &PicObject::clicked, this, &Level_04::mousePressEvent);
    }
}

// ---------------------------  Перемешиваем список карандашей ----------------------

void Level_04::mix_pens()
{
    int k = 0;
    int temp = 0;
    for(int i=0; i<=6; i++)
    {
        k = rnd(0,6);
        temp = value_p[k];
        value_p[k] = value_p[i];
        value_p[i] = temp;
    }
}

// ---------------------------  Перемешиваем список предметов в мысли ----------------------

void Level_04::mix_mysl()
{
    int k = 0;
    int temp = 0;
    for(int i=0; i<=6; i++)
    {
        k = rnd(0,6);
        temp = value_m[k];
        value_m[k] = value_m[i];
        value_m[i] = temp;
    }
}

// --------------------- Нажатие кнопки мышки -------------------------------------

void Level_04::mousePressEvent(QMouseEvent *pe)
{


    if(QObject::sender() && pe->button() == Qt::LeftButton)         // Если нажали по какому-либо объекту
    {
        old_x = pens[ACTIVE_PEN]->x();  // запоминаем координаты выбранного карандаша
        old_y = pens[ACTIVE_PEN]->y();
    }
    else
    {
        ACTIVE_PEN = 10;

    }
}

// ----------------------- Перемещение мышки ---------------------------------------

void Level_04::mouseMoveEvent(QMouseEvent *pe)
{
    int x=0;
    int y=0;
    int y1=0;
    if(ACTIVE_PEN <= 6)
    {
        x = pe->pos().x();
            y = pe->pos().y()-pens[ACTIVE_PEN]->height()/2;
        y1 = pe->pos().y();
        pens[ACTIVE_PEN]->move(x,y);
        if(ACTIVE_PEN==5)
        {
            if((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/17)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/6-WIDTH_SCREEN/80)&&
               (y1>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/50)&&(y1<=HEIGHT_SCREEN/2+HEIGHT_SCREEN/8))
            {
                //exit(54);
            }
        }
    }

}

// ---------------------- Отпускание кнопки мышки ----------------------------------

void Level_04::mouseReleaseEvent(QMouseEvent *pe)
{
    int x;
    int y;
    x = pe->pos().x();
    //y = pe->pos().y()-pens[ACTIVE_PEN]->height()/2;
    y = pe->pos().y();
    value_m[STEP]=5; // <------------------------------------------------------------------------------------------------
     if(value_m[STEP]==ACTIVE_PEN)
     {
        if(ACTIVE_PEN==0)
        {
            if(((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/16)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/13)&&
                 (y>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/9)&&(y<=HEIGHT_SCREEN/2-HEIGHT_SCREEN/15))||
                ((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/8)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/7)&&
                 (y>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/9)&&(y<=HEIGHT_SCREEN/2-HEIGHT_SCREEN/15))||
                ((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/14)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/8)&&
                 (y>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/7-HEIGHT_SCREEN/80)&&
                 (y<=HEIGHT_SCREEN/2-HEIGHT_SCREEN/8)))
            {
                vnuchka_holst[0]->show();
                STEP++;
                //delete pens[ACTIVE_PEN];
                //pens[ACTIVE_PEN] = nullptr;
            }
        }
        if(ACTIVE_PEN==1)
        {
            if((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/13)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/8)&&
                  (y>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/11)&&(y<=HEIGHT_SCREEN/2-HEIGHT_SCREEN/30))
            {
                vnuchka_holst[1]->show();
                STEP++;
            }
        }        
        if(ACTIVE_PEN==2)
        {
            if((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/13)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/8)&&
                (y>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/8)&&(y<=HEIGHT_SCREEN/2-HEIGHT_SCREEN/10))
            {
                vnuchka_holst[2]->show();
                STEP++;
            }
        }
        if(ACTIVE_PEN==3)
        {
            if((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/24)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/12)&&
                (y>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/28)&&(y<=HEIGHT_SCREEN/2+HEIGHT_SCREEN/45))
            {
                vnuchka_holst[3]->show();
                STEP++;
            }
        }
        if(ACTIVE_PEN==4)
        {
            if((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/8)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/6-WIDTH_SCREEN/80)&&
                (y>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/20)&&(y<=HEIGHT_SCREEN/2-HEIGHT_SCREEN/30))
            {
                vnuchka_holst[4]->show();
                STEP++;
            }
        }
        if(ACTIVE_PEN==5)
        {
            if((x>=WIDTH_SCREEN/2+WIDTH_SCREEN/17)&&(x<=WIDTH_SCREEN/2+WIDTH_SCREEN/6-WIDTH_SCREEN/80)&&
                (y>=HEIGHT_SCREEN/2-HEIGHT_SCREEN/50)&&(y<=HEIGHT_SCREEN/2+HEIGHT_SCREEN/8))
            {
                vnuchka_holst[5]->show();
                STEP++;
            }
        }
        pens[ACTIVE_PEN]->move_to_xy(x, old_x, y, old_y, 1);
    } 
    ACTIVE_PEN = 10;
}

// -------------------------- Закрываем текущее окно --------------------------------

void Level_04::back_level()
{
    this->close();
}


