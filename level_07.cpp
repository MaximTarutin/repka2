#include "level_07.h"
#include "qmediaplayer.h"

Level_07::Level_07(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
}

Level_07::~Level_07()
{
    delete output;
    output = nullptr;
    delete sound;
    sound = nullptr;
    delete mysl;
    mysl = nullptr;
    delete myschka;
    myschka = nullptr;
    delete button_back;
    button_back = nullptr;
    delete background;
    background = nullptr;
    for(int i=0; i<17; i++)
    {
        delete puzle[i];
        puzle[i] = nullptr;
    }
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_07::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}

// -------------------- Получаем разрешение экрана --------------------------------

void Level_07::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_07::get_height(int h)
{
    HEIGHT_SCREEN = h;
}


// ----------------------------- Инициализация -------------------------------------

void Level_07::initial()
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
    background->setStyleSheet("border-image: url(:/resource/lev_07/dvor.jpg);"); // Фон экрана
    this->setCentralWidget(background);
    background->show();

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    myschka = new PicObject(":/resource/lev_07/myshka.png", this);
    myschka->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    myschka->move(WIDTH_SCREEN-myschka->width()*2, HEIGHT_SCREEN-myschka->height());
    myschka->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/4, HEIGHT_SCREEN/3+HEIGHT_SCREEN/15);
    mysl->move(myschka->x()+myschka->width()/2, myschka->y()-myschka->height());
    mysl->show();

    create_pazle();             // Создаем набор пазлов

}

// -------------------------------- Создаем набор пазлов -------------------------------------------

void Level_07::create_pazle()
{
    int k = rnd(0,3);       // Выбираем случайный набор
    QString puzle_name = ":/resource/lev_07/00-"+QString::number(k)+".png";
    puzle[0] = new PicObject(puzle_name, mysl);
    puzle[0]->resize_object(WIDTH_SCREEN/12, HEIGHT_SCREEN/8);
    puzle[0]->move(mysl->width()/4, mysl->height()/4);
    puzle[0]->show();

    for(int i=1; i<=16; i++)
    {
        if(i<10) puzle_name = ":/resource/lev_07/0"+QString::number(i)+"-"+QString::number(k)+".png";
        else puzle_name = ":/resource/lev_07/"+QString::number(i)+"-"+QString::number(k)+".png";
        puzle[i] = new PicObject(puzle_name, this);
        puzle[i]->setObjectName(QString::number(i));
        puzle[i]->resize_object(WIDTH_SCREEN/10, HEIGHT_SCREEN/6);
        puzle[i]->raise();
        puzle[i]->hide();
    }
    puzle[1]->move(WIDTH_SCREEN/4, HEIGHT_SCREEN/6);
    for(int i=1; i<=4; i++)
    {
        for(int j=1; j<=4; j++)
        {
            int k=4*(i-1)+j;            // Вычисляем порядковый номер карты
            static int g = 0;           // ряд
            if(k%5 == 0) g++;
            int x = puzle[1]->x()+puzle[1]->width()*(j-1);
            int y = puzle[g+1]->y()+puzle[g+1]->height()*(i-1);
            puzle[k]->move(x,y);
            puzle[k]->show();
        }
    }
}