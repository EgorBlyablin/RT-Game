//
// Created by Иван on 22.04.2024.
//
#include "GameModel.h"


GameModel::GameModel() {
    Init();
}

void GameModel::Init() {
    // Заполняем массив плашек
    for (int i = 0; i < ARRAY_SIZE - 1; i++) elements[i] = i + 1;
}
