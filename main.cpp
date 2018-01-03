#include <ncurses.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "bar.h"
#include "status.h"
#include "changeling.h"
#include "game.h"
#include "square.h"
#include "areaOfEffect.h"
#include "board.h"
#include "plant.h"
#include "win.h"

/*
 * GNUminki - gra sapero-podobna na GPLv3
 * Damian Fajfer, Miłosz Szczepański
 * Wydział Elektroniki i Telekomunikacji
 * Politechnika Poznańska, 2017
 */

/*
 *  TODO: Interaction with the board (will be done after merge)
 */

void debug(const char *input, WINDOW *changelingWindow, int &chanCurY, int chanMaxY) {
    mvwprintw(changelingWindow, chanCurY, 2, input);
    wrefresh(changelingWindow);
    ++chanCurY;
    if (chanCurY == chanMaxY) chanCurY = 1;
}

int main() {
    bool gameStarted = false;
    bool isRunning = true;
    int flagCount = 0;
    int bombCount = 0;
    int ch, maxY, maxX;
    int curX, curY;
    int gameBegY, gameBegX, gameMaxY;
    int chanMaxY, chanCurY = 1;
    WINDOW *barWindow, *statusWindow, *gameWindow;
    WINDOW *changelingWindow;

    initscr();
    raw();
    noecho();
    keypad(stdscr, true);
    start_color();
    short COLOR_BG = 1;
    short COLOR_TEXT = 3;
    init_color(COLOR_BG, 80, 11, 110);
    init_color(COLOR_TEXT, 504, 504, 0);
    init_pair(1, COLOR_TEXT, COLOR_BG);
    attron(COLOR_PAIR(1) | A_BLINK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);          //popup & bar default
    init_pair(3, COLOR_WHITE, COLOR_MAGENTA);   //debug default
    wbkgd(stdscr, COLOR_PAIR(1));
    getmaxyx(stdscr, maxY, maxX);
    refresh();
    barWindow = bar(maxY);
    statusWindow = status(maxY / 5,
                          (int) (maxX / 4.8));
    changelingWindow = changeling(maxY - getmaxy(statusWindow) - getmaxy(barWindow),
                                  (int) (maxX / 4.8),
                                  getmaxy(statusWindow));
    gameWindow = game(maxY,
                      getmaxx(changelingWindow));

    gameMaxY = getmaxy(gameWindow) - 1;
    chanMaxY = getmaxy(changelingWindow) - 1;
    getbegyx(gameWindow, gameBegY, gameBegX);
    gameBegY += 1;
    gameBegX += 1;

    move(gameBegY, gameBegX);
    curY = gameBegY;
    curX = gameBegX;
    move(0, 0);

    ////////////////////////////////////////////////////////////////////////////////////////

    square **tab;
    //TODO  Zrobić klasę, w której będą 3 powyższe pola. Dalej w klasie tej dodać konstruktor, który wykona poniższy kod.
    tab = new square *[maxX - 1];
    for (int i = 0; i < maxX - 1; i++)
        tab[i] = new square[gameMaxY];

    //////////////////////////////////////////////////// ustawianie min, generowanie planszy
    board *tablica = new board();
    tablica->create_board(maxX - 1, gameMaxY, tab);

    plant *ustaw;
    ustaw->mine_plant(maxX - 1, gameMaxY, tab);

    ////////////////////////////////////////////////////

    areaOfEffect *pokaz;
    //pokaz->show_area(x, y, tab);  //TODO do wywołania funkcji potrzbuje koorydynatów wybranego pola

    win *wygrana;
    wygrana->if_win(maxX - 1, gameMaxY, tab); //do sprawdzania wygranej


    //TODO to umieścić w destruktorze nowej klasy
    for (int i = 0; i < maxX - 1; i++)
        delete[]tab[i];
    delete[]tab;

    /////////////////////////////////////////////////////////////////////////////////////////


    while (isRunning) {
        ch = getch();
        switch (ch) {
            case KEY_LEFT: {
                if (gameStarted) {
                    debug("KEY_LEFT pressed\t\t", changelingWindow, chanCurY, chanMaxY);
                    if (curX == gameBegX) curX = maxX - 1;
                    move(curY, --curX);
                    wrefresh(gameWindow);
                }
                break;
            }
            case KEY_RIGHT: {
                if (gameStarted) {
                    debug("KEY_RIGHT pressed\t\t", changelingWindow, chanCurY, chanMaxY);
                    if (curX == maxX - 2) curX = gameBegX - 1;
                    move(curY, ++curX);
                    wrefresh(gameWindow);
                }
                break;
            }
            case KEY_UP: {
                if (gameStarted) {
                    debug("KEY_UP pressed\t\t", changelingWindow, chanCurY, chanMaxY);
                    if (curY == gameBegY) curY = gameMaxY;
                    move(--curY, curX);
                    wrefresh(gameWindow);
                }
                break;
            }
            case KEY_DOWN: {
                if (gameStarted) {
                    debug("KEY_DOWN pressed\t\t", changelingWindow, chanCurY, chanMaxY);
                    if (curY == gameMaxY - 1) curY = gameBegY - 1;
                    move(++curY, curX);
                    wrefresh(gameWindow);
                }
                break;
            }

            case 102: {
                if (gameStarted) {
                    char square = inch();
                    mvwprintw(statusWindow, 3, 2, "Last char\t: %c\t", square);
                    debug("F pressed\t\t", changelingWindow, chanCurY, chanMaxY);
                    wrefresh(changelingWindow);

                    switch (square) {
                        case '.': {
                            addch('F');
                            mvwprintw(statusWindow, 1, 2, "Mines\t: %d\t", --bombCount);
                            mvwprintw(statusWindow, 2, 2, "Flags\t: %d\t", ++flagCount);
                            break;
                        }
                        case 'F': {
                            addch('.');
                            mvwprintw(statusWindow, 1, 2, "Mines\t: %d\t", ++bombCount);
                            mvwprintw(statusWindow, 2, 2, "Flags\t: %d\t", --flagCount);
                            break;
                        }
                        default:  //do nothing
                            break;
                    }
                    move(curY, curX);
                    wrefresh(statusWindow);
                }
                break;
            }
            case 10: {
                if (gameStarted) {
                    debug("KEY_ENTER pressed\t\t", changelingWindow, chanCurY, chanMaxY);
                    mvwprintw(changelingWindow, chanCurY, 2, "X: %d\t\t", curX);
                    mvwprintw(changelingWindow, ++chanCurY, 2, "Y: %d\t\t", curY);
                    ++chanCurY;
                    wrefresh(changelingWindow);
                    move(curY, curX);
                    //curX & curY here should do all the charm related to the matrix

                    areaOfEffect *pokaz;
                    //pokaz->show_area(x, y, tab);  //TODO do wywołania funkcji potrzbuje koorydynatów wybranego pola

                }
                break;
            }

            case KEY_F(2): {
                debug("New game started\t\t", changelingWindow, chanCurY, chanMaxY);
                system("./highscore.sh > /dev/null 2>&1");
                gameStarted = true;
                flagCount = bombCount = 0;
                barWindow = bar(maxY);
                gameWindow = game(maxY,
                                  getmaxx(changelingWindow));
                changelingWindow = changeling(maxY - getmaxy(statusWindow) - getmaxy(barWindow),
                                              (int) (maxX / 4.8),
                                              getmaxy(statusWindow));
                statusWindow = status(maxY / 5,
                                      (int) (maxX / 4.8));

                getbegyx(gameWindow, gameBegY, gameBegX);
                gameBegY += 1;
                gameBegX += 1;

                move(gameBegY, gameBegX);
                curY = gameBegY;
                curX = gameBegX;

                mvwprintw(statusWindow, 4, 2, "A[X]\t: %d\t", maxX - getmaxx(changelingWindow) - 2);
                mvwprintw(statusWindow, 5, 2, "A[Y]\t: %d\t", gameMaxY - 1);
                wrefresh(statusWindow);
                // Array size is [gameMaxX-1][gameMaxY-1];
                break;
            }
            case KEY_F(12): {
                for (int i = 0; i < 40; ++i) {
                    std::stringstream result_stream;
                    std::streambuf *backup = std::cout.rdbuf(result_stream.rdbuf());
                    int res = system("cat $HOME/.local/share/gnuminki/playerList");
                    std::cout.rdbuf(backup);
                    std::string output = result_stream.str();
                    const char *outputFinal = output.c_str();
                    mvwprintw(statusWindow, 6, 2, outputFinal);
                    usleep(90000);
                }
                WINDOW *thanksWindow = newwin((int) (maxY / 12), (int) (maxX / 6), (int) (maxY * 0.2),
                                              (int) (maxX * 0.2));
                box(thanksWindow, 0, 0);
                wbkgd(thanksWindow, COLOR_PAIR(2));

                mvwprintw(thanksWindow, 1, 1, "Thanks for playing!");
                wrefresh(thanksWindow);
                getch();
                isRunning = false;
                break;
            }
            default: //do nothing
                break;
        }
        refresh();
    }
    endwin();
    return 0;
}