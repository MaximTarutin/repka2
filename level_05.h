#ifndef LEVEL__5_H
#define LEVEL__5_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QList>
#include "picobject.h"

class Level_05 : public QMainWindow
{
    Q_OBJECT
public:
    explicit Level_05(QWidget *parent = nullptr);
    ~Level_05();

    void initial();                                 // Инициализация
    QPushButton *button_back = nullptr;             // Кнопка назад

public slots:
    void get_width(int w);                          // Получаем ширину экрана
    void get_height(int h);                         // Получаем высоту экрана

private:
    int WIDTH_SCREEN = 0;                           // Ширина экрана
    int HEIGHT_SCREEN = 0;                          // Высота экрана

    QLabel      *background = nullptr;              // Фон
    QMediaPlayer    *sound = nullptr;               // Проигрыватель
    QAudioOutput    *output = nullptr;              // Аудиовыход
    PicObject       *dog = nullptr;                 // Собака на фоне
    PicObject       *mysl = nullptr;                // Мысль собаки
    PicObject       *panel[8] = {};                 // Панель куда складываем пазл
    PicObject       *pazl[8] = {};                  // Набор пазлов
    QList<QList<int>> coordinates_panel = {};       // Координаты частей панели
    QList<QList<int>> coordinates_pazl = {};        // Координаты пазлов вокруг панели


signals:
    void next_level(int lev);                       // Сигнал переход на следующий уровень
};

#endif // LEVEL__5_H
