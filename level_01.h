#ifndef LEVEL_01_H
#define LEVEL_01_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "picobject.h"


class Level_01 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_01(QWidget *parent = nullptr);
    ~Level_01();
    QPushButton     *button_next = nullptr;                 // Кнопка следующий уровень
    QPushButton     *button_back = nullptr;                 // Кнопка назад

private:
    int WIDTH_SCREEN = 0;                                   // Разрешение экрана
    int HEIGHT_SCREEN = 0;

    QLabel          *background_lev01 = nullptr;            // Фон уровня 1
    PicObject       *repka = nullptr;                       // Овощи
    PicObject       *repka_gray = nullptr;
    PicObject       *baklagan = nullptr;
    PicObject       *baklagan_gray = nullptr;
    PicObject       *chesnok = nullptr;
    PicObject       *chesnok_gray = nullptr;
    PicObject       *grusha = nullptr;
    PicObject       *grusha_gray = nullptr;
    PicObject       *kartoshka = nullptr;
    PicObject       *kartoshka_gray = nullptr;
    PicObject       *morkovka = nullptr;
    PicObject       *morkovka_gray = nullptr;
    PicObject       *ogurec = nullptr;
    PicObject       *ogurec_gray = nullptr;
    PicObject       *rediska = nullptr;
    PicObject       *rediska_gray = nullptr;
    PicObject       *tomat = nullptr;
    PicObject       *tomat_gray = nullptr;
    PicObject       *tykva = nullptr;
    PicObject       *tykva_gray = nullptr;


public slots:
    void initial();                                         // инициализация
    void get_width(int w);                                  // Получаем WIDTH_SCREEN
    void get_height(int h);                                 // Получаем HEIGHT_SCREEN
    void back_level();                                      // Возврат на главный экран

signals:
};

#endif // LEVEL_01_H
