#include "level_02.h"
#include <ctime>

Level_02::Level_02(QWidget *parent)
    : QMainWindow{parent}
{
    srand(time(NULL));
    for(int i=0; i<8; i++)
    {
        x[i]=0;
        y[i]=0;
    }
}

Level_02::~Level_02()
{
    delete button_back;
    button_back = nullptr;
    delete background_lev02;
    background_lev02 = nullptr;
    for(int i=0; i==7; i++)
    {
        delete instruments[i];
        instruments[i] = nullptr;
        delete instruments_mysl[i];
        instruments_mysl[i] = nullptr;
    }
    delete mysl;
    mysl = nullptr;
    delete dedka;
    dedka = nullptr;
    delete cell;
    cell = nullptr;
    delete sound;
    sound = nullptr;
    delete output;
    output = nullptr;
}

//------------------ генератор случайных чисел в диапазоне от a до b -----------------------

int Level_02::rnd(int a, int b)
{
    int k;
    b=b-a+1;
    k   =   rand()%b+a;
    return k;
}


// ------------------ Получаем ширину и высоту экрана ----------------------

void Level_02::get_width(int w)
{
    WIDTH_SCREEN = w;
}

void Level_02::get_height(int h)
{
    HEIGHT_SCREEN = h;
}

// ------------------- Инициализация ------------------------------------

void Level_02::initial()
{
    background_lev02 = new QLabel(this);
    background_lev02->setStyleSheet("border-image: url(:/resource/lev_02/saray.jpg);");
    this->setCentralWidget(background_lev02);
    background_lev02->show();

    QCursor cursorTarget = QCursor(QPixmap(":/resource/logo/cursor1.png"),0,0);
    this->setCursor(cursorTarget);

    sound = new QMediaPlayer(this);
    output = new QAudioOutput();
    sound->setAudioOutput(output);
    output->setVolume(1);

    button_back = new QPushButton(this);
    button_back->setStyleSheet("border-image: url(:/resource/lev_01/return.png);");
    button_back->resize(WIDTH_SCREEN/20, HEIGHT_SCREEN/10);
    button_back->move(WIDTH_SCREEN/30, HEIGHT_SCREEN/20);
    button_back->show();

    dedka = new PicObject(":/resource/lev_02/dedka.png", this);
    dedka->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    dedka->move(0,HEIGHT_SCREEN-dedka->height());
    dedka->show();

    mysl = new PicObject(":/resource/lev_02/mysl.png", this);
    mysl->resize_object(WIDTH_SCREEN/6, HEIGHT_SCREEN/3);
    mysl->move(dedka->width()/2, dedka->height());
    mysl->show();

    cell = new PicObject(":/resource/lev_02/fon.png", this);
    cell->resize_object(WIDTH_SCREEN/2, HEIGHT_SCREEN/10);
    cell->move(WIDTH_SCREEN/2-WIDTH_SCREEN/4,HEIGHT_SCREEN/30);
    cell->show();

    instruments[0] = new PicObject(":/resource/lev_02/fomka.png", this);
    instruments[0]->resize_object(WIDTH_SCREEN/14, HEIGHT_SCREEN/10);
    instruments[1] = new PicObject(":/resource/lev_02/leyka.png", this);
    instruments[1]->resize_object(WIDTH_SCREEN/13, HEIGHT_SCREEN/10);
    instruments[2] = new PicObject(":/resource/lev_02/lopata.png", this);
    instruments[2]->resize_object(WIDTH_SCREEN/10, HEIGHT_SCREEN/6);
    instruments[3] = new PicObject(":/resource/lev_02/molotok.png", this);
    instruments[3]->resize_object(WIDTH_SCREEN/21, HEIGHT_SCREEN/12);
    instruments[4] = new PicObject(":/resource/lev_02/serp.png", this);
    instruments[4]->resize_object(WIDTH_SCREEN/21, HEIGHT_SCREEN/12);
    instruments[5] = new PicObject(":/resource/lev_02/topor.png", this);
    instruments[5]->resize_object(WIDTH_SCREEN/26, HEIGHT_SCREEN/12);
    instruments[6] = new PicObject(":/resource/lev_02/vedro.png", this);
    instruments[6]->resize_object(WIDTH_SCREEN/26, HEIGHT_SCREEN/12);
    instruments[7] = new PicObject(":/resource/lev_02/vily.png", this);
    instruments[7]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/8);

    instruments_mysl[0] = new PicObject(":/resource/lev_02/fomka.png", this);
    instruments_mysl[0]->resize_object(WIDTH_SCREEN/18, HEIGHT_SCREEN/14);
    instruments_mysl[1] = new PicObject(":/resource/lev_02/leyka.png", this);
    instruments_mysl[1]->resize_object(WIDTH_SCREEN/17, HEIGHT_SCREEN/14);
    instruments_mysl[2] = new PicObject(":/resource/lev_02/lopata.png", this);
    instruments_mysl[2]->resize_object(WIDTH_SCREEN/14, HEIGHT_SCREEN/12);
    instruments_mysl[3] = new PicObject(":/resource/lev_02/molotok.png", this);
    instruments_mysl[3]->resize_object(WIDTH_SCREEN/25, HEIGHT_SCREEN/16);
    instruments_mysl[4] = new PicObject(":/resource/lev_02/serp.png", this);
    instruments_mysl[4]->resize_object(WIDTH_SCREEN/25, HEIGHT_SCREEN/16);
    instruments_mysl[5] = new PicObject(":/resource/lev_02/topor.png", this);
    instruments_mysl[5]->resize_object(WIDTH_SCREEN/30, HEIGHT_SCREEN/16);
    instruments_mysl[6] = new PicObject(":/resource/lev_02/vedro.png", this);
    instruments_mysl[6]->resize_object(WIDTH_SCREEN/26, HEIGHT_SCREEN/12);
    instruments_mysl[7] = new PicObject(":/resource/lev_02/vily.png", this);
    instruments_mysl[7]->resize_object(WIDTH_SCREEN/20, HEIGHT_SCREEN/12);

    for(int i=0; i<8; i++)
    {
        instruments[i]->hide();
        instruments_mysl[i]->hide();
    }

    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/8 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/5);
    coordinates.append(QList<int>() << WIDTH_SCREEN/3 << HEIGHT_SCREEN-HEIGHT_SCREEN/6);
    coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/5 << HEIGHT_SCREEN-HEIGHT_SCREEN/6);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/17);
    coordinates.append(QList<int>() << WIDTH_SCREEN-WIDTH_SCREEN/4 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/17);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2-WIDTH_SCREEN/5 << HEIGHT_SCREEN/2+HEIGHT_SCREEN/12);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/12 << HEIGHT_SCREEN-HEIGHT_SCREEN/5);
    coordinates.append(QList<int>() << WIDTH_SCREEN/2+WIDTH_SCREEN/5 << HEIGHT_SCREEN/2-HEIGHT_SCREEN/5);

    for(int i=0; i<8; i++)
    {
        instruments[i]->show();
        instruments_mysl[i]->setParent(mysl);
    }

    mix_instruments();

    for(int i=0; i<8; i++)
    {
        x[i] = coordinates.at(value_i[i]).at(0);   // Расставляем инструмент
        y[i] = coordinates.at(value_i[i]).at(1);
        instruments[i]->move(x[i],y[i]);
    }

    mysl_deda(STEP_NUMBER);
}

// ---------------- Перемешаем список нумерации инструмента --------------------------

void Level_02::mix_instruments()
{
    int temp = 0;
    int k = 0;
    value_i = {0,1,2,3,4,5,6,7};        // порядок инструмента
    value_m = {0,1,2,3,4,5,6,7};        // порядок очередности инструмента в мысли

    for(int i=0; i<8; i++)
    {
        k = rnd(0,7);
        temp = value_i[k];
        value_i[k] = value_i[i];        // Перемешиваем список инструмента
        value_i[i] = temp;
    }

    for(int i=0; i<8; i++)              // Определяем порядок появления инструмента в мысли
    {
        k = rnd(0,7);
        temp = value_m[k];
        value_m[k] = value_m[i];
        value_m[i] = temp;
    }
}

// --------------------- Отображаем о чем думает дед ----------------------

void Level_02::mysl_deda(int step)
{
    instruments_mysl[value_m[step]]->move(mysl->width()/4, mysl->height()/4);
    instruments_mysl[value_m[step]]->show();
}

// --------------------- Кликаем по предмету --------------------------------

void Level_02::mousePressEvent(QMouseEvent *pe)
{
    static int step = cell->width()/50;  // расстояние между инструментами расставленных в ячейке

    if((pe->x() >= instruments[value_m[STEP_NUMBER]]->x())&&
        (pe->x() <= instruments[value_m[STEP_NUMBER]]->x()+instruments[value_m[STEP_NUMBER]]->width())&&
        (pe->y() >= instruments[value_m[STEP_NUMBER]]->y())&&
        (pe->y() <= instruments[value_m[STEP_NUMBER]]->y()+instruments[value_m[STEP_NUMBER]]->height()))
    {
        if(STEP_NUMBER == 7)
        {
            instruments[value_m[7]]->move(cell->x()+step, cell->y()+cell->height()/20);     // Победа
            instruments_mysl[value_m[7]]->hide();
            instruments[value_m[STEP_NUMBER]]->resize_object(instruments_mysl[value_m[7]]->width(),
                                                             instruments_mysl[value_m[7]]->height());
            victory();
        }
        else
        {
            instruments_mysl[value_m[STEP_NUMBER]]->hide();
            instruments[value_m[STEP_NUMBER]]->resize_object(instruments_mysl[value_m[STEP_NUMBER]]->width(),
                                                             instruments_mysl[value_m[STEP_NUMBER]]->height());
            instruments[value_m[STEP_NUMBER]]->move_to_xy(instruments[value_m[STEP_NUMBER]]->x(), cell->x()+step,
                                                          instruments[value_m[STEP_NUMBER]]->y(), cell->y()+cell->height()/10, 1);
            step+=instruments_mysl[value_m[STEP_NUMBER]]->width()+cell->width()/50;
            sound->setSource(QUrl("qrc:/resource/sound/yes.mp3"));
            sound->play();
            STEP_NUMBER++;
            mysl_deda(STEP_NUMBER);
        }
    } else
    {
        sound->setSource(QUrl("qrc:/resource/sound/nea.wav"));
        sound->play();
    }
}

// ---------------------- Победа -----------------------------------

void Level_02::victory()
{
    sound->setSource(QUrl("qrc:/resource/sound/salut.mp3"));
    sound->play();
    timer_firework = new QTimer(this);
    timer_firework->start(11000);
    connect(timer_firework, &QTimer::timeout, this, [this](){this->close();emit next_level();});
    firework = new PicObject(":/resource/lev_02/salut.gif", this);
    firework->show();
    firework->animation_start(WIDTH_SCREEN/2, HEIGHT_SCREEN/2);
}

// -------------------- Возврат на 1 уровень -------------------------------

void Level_02::back_level()
{
    this->close();
}




