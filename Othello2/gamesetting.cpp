#include "gamesetting.h"

GameSetting::GameSetting()
{

}
int GameSetting::getGameMode()
{
    return this->gameMode;
}

void GameSetting::setGameMode(int gameMode)
{
    this->gameMode = gameMode;
}

bool GameSetting::isStoneFreezing()
{
    return this->stoneFreezing;
}

void GameSetting::setStoneFreezing(bool stoneFreezing)
{
    this->stoneFreezing = stoneFreezing;
}

int GameSetting::getI_var()
{
    return i_var;
}

void GameSetting::setI_var(int i_var)
{
    this->i_var = i_var;
}

int GameSetting::getMaxFreezed()
{
    return this->maxFreezed;
}

void GameSetting::setMaxFreezed(int i_var)
{
    this->maxFreezed = i_var;
}

int GameSetting::getB_var()
{
    return b_var;
}

void GameSetting::setB_var(int b_var)
{
    this->b_var = b_var;
}

void GameSetting::setAiMode(int mode)
{
    this->aiMode=mode;
}

void GameSetting::setInstancies(int instancies)
{
    this->instancies = instancies;
}

int GameSetting::getInstancies()
{
    return this->instancies;
}

int GameSetting::getSize()
{
    return this->size;
}
int GameSetting::getAiMode()
{
    return this->aiMode;
}
void GameSetting::setSize(int size)
{
    this->size = size;
}
