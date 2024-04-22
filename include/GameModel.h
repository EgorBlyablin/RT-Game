//
// Created by Иван on 22.04.2024.
//

#ifndef RTETRIS_GAMEMODEL_H
#define RTETRIS_GAMEMODEL_H

#include "Assets.h"


enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

class GameModel
{
public:
    static const int SIZE = 4;			// Размер игрового поля в плашках
    static const int ARRAY_SIZE = SIZE * SIZE;	// Размер массива
    static const int FIELD_SIZE = 500;		// Размер игрового поля в пикселях
    static const int CELL_SIZE = 120;		// Размер плашки в пикселях
protected:
    int elements[ARRAY_SIZE];
public:
    GameModel();
    void Init();
    int* Elements() { return elements; }
};


#endif //RTETRIS_GAMEMODEL_H
