#ifndef LEVEL__3_H
#define LEVEL__3_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include "picobject.h"

class Level_03 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_03(QWidget *parent = nullptr);
    ~Level_03();

public slots:
    void initial();                             // Инициализация уровня
    void get_width(int w);                      // Получаем WIDTH_SCREEN
    void get_height(int h);                     // Получаем HEIGHT_SCREEN

private:
    int     WIDTH_SCREEN = 0;                   // Ширина экрана
    int     HEIGHT_SCREEN = 0;                  // Высота экрана

    QLabel          *background = nullptr;      // Фон уровня
    QMediaPlayer    *sound = nullptr;           // Проигрыватель
    QAudioOutput    *output = nullptr;          // Аудиовыход
    QPushButton     *button_back = nullptr;     // Кнопка назад
    PicObject       *table = nullptr;           // Стол
    PicObject       *babka = nullptr;           // Бабка
    PicObject       *mysl = nullptr;            // Мысль бабки
    PicObject       *tazik[5] = {};             // Состояния тазика по мере наполняемости продуктами
    PicObject       *produkt[5] = {};           // Продукты
    PicObject       *produkt_mysl[5] = {};      // Продукты в мысли

    QList<QList<int>>  coordinates = {};        // Координаты инструмента (список в списке - [[a,b],[a,b],...,[a,b]])
    QList<int>  produkt_value = {};             // Список нумерации продукты
    QList<int>  produkt_mysl_value = {};        // Список нумерации продукты в мысли

signals:
};

#endif // LEVEL__3_H
