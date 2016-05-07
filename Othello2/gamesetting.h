#ifndef GAMESETTING_H
#define GAMESETTING_H
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
//description in cpp file
class GameSetting
{
private:
    int gameMode = 0; //0 - AI, 1-Human
    bool stoneFreezing = false;
    int i_var = 0;
    int b_var = 0;
    int maxFreezed = 0;
    int size;
    int instancies = 1;
public:
      int aiMode = 1; //1-1st ai script, 2- 2nd ai script
    GameSetting();
    int getGameMode();
    void setGameMode(int);
    bool isStoneFreezing();
    void setStoneFreezing(bool);
    int getI_var();
    void setI_var(int);
    int getMaxFreezed();
    void setMaxFreezed(int);
    int getB_var();
    void setAiMode(int);
    void setB_var(int);
    void setInstancies(int instancies);
    int getInstancies();
    int getSize();
    int getAiMode();
    void setSize(int);
};

#endif // GAMESETTING_H
