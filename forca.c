#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>


/* Posicao do conjunto de caracteres */
#define START_X 15
#define START_Y 9

/* Declaracao de funcoes */
void renderBase();
void renderWord();
void checkWord(char c);
void kill();
void start();

/* Variáveis globais */
int attempts = 0;
int end = 0;
char word[256];
char cWord[256];

void readWord(){
    FILE *f;
    char c;
    int i = 0;
    f = fopen("palavra.txt","rt");
    while((c = fgetc(f)) != EOF){
        word[i] = c;
        i++;
    }
    word[i] = '\0';
    fclose(f);
}


void renderBase(){
    attron(COLOR_PAIR(2));
    mvprintw(2,10, "A forca mais bonita da cidade");
    attron(COLOR_PAIR(3));
    for(int i = 4; i < 10; i++){
        mvprintw(i, 4, "|");
        mvprintw(4,i,"_");
    }
    attroff(COLOR_PAIR(3));
}

void renderWord(){
    int posY = START_Y;
    int posX = START_X;
    int i; 
    for(i = 0; i < strlen(word); i++){
        word[i] = toupper(word[i]);
        if(word[i] != ' ')
            mvprintw(posY,posX,"_");
        posX += 2;
    }

}


void checkWord(char c){
    int correct = 0, i = 0;
    int posY = START_Y;
    int posX = START_X;
    c = toupper(c); 
    for(i = 0; i < strlen(word); i++){
        if(word[i] == ' '){
            mvprintw(posY,posX," ");
            cWord[i] = ' ';
        }
        if(c == word[i]){
            mvprintw(posY,posX,"%c",c);
            cWord[i] = c;
            correct = 1;
        }   
        if(cWord[i] == word[i])
            mvprintw(posY,posX,"%c",cWord[i]);
        posX += 2;
    }
    if(correct != 1)
        kill();
    if(strcmp(cWord,word) == 0){
        end = 1;
    }
    refresh();
}

void kill(){
    attempts++;
    attron(COLOR_PAIR(4));
    switch(attempts){
        case 1:
            mvprintw(5, 10, "O");
            break;
        case 2:
            mvprintw(6, 10, "|");
            break;
        case 3:
            mvprintw(6, 11, "\\");
            break;
        case 4:
            mvprintw(6, 9, "/");
            break;
        case 5:
            mvprintw(7, 11, "\\");
            break;
        case 6:
            mvprintw(7, 9, "/");
            break;
    }
    attroff(COLOR_PAIR(4));
}

void start(){
    /* Zero os valores das strings armazenadas na memória*/
    memset(word,0,256);
    memset(cWord,0, 256);
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(2,23, " A forca mais bonita da cidade ");
    attroff(COLOR_PAIR(2));
    mvprintw(4,5, "Comece digitando uma palavra, quando terminar pressione ENTER");
    mvprintw(5,5, "e depois peça para alguém descobrir");
    mvprintw(7,5, "é só ir digitando, ela não vai aparecer aqui no terminal");
    mvprintw(8,5, "assim seu amigo não vê (;");
    mvprintw(6,5, "Palavra: ");
    scanw(" %[^\n]",word);
    refresh();
    clear();
}


int main(){
    int charVal, quit = 0;
        initscr();
        noecho();
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_BLACK, COLOR_RED);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_RED,COLOR_BLACK);
        init_pair(5, COLOR_GREEN, COLOR_BLACK);
    do{

        attron(COLOR_PAIR(1));
        attempts = 0;
        end = 0;
        start();
        // readWord();
        renderBase();
        renderWord();
        while(attempts <= 6 && end == 0){
            charVal = getch();
            if(isalpha(charVal)){
                checkWord(charVal);
                refresh();
            }
        }

        if(attempts <= 6 && end == 1){
            mvprintw(5,15, "Você salvou a vida do amiguinho ali");
            refresh();
        }else{
            mvprintw(4,13, "Você me matou cara!");
            mvprintw(5,12, "/");
            mvprintw(7,30, "Você perdeu meu bacano :c");
            mvprintw(8,30, "A palavra era -> %s", word);
            refresh();
        }
        attron(COLOR_PAIR(5));
        mvprintw(14,15, "Pressione ENTER para continuar ou Q para sair.");
        attroff(COLOR_PAIR(5));
        charVal = 0;
        while(charVal != 'q' && charVal != 10){
            charVal = getch();
            charVal = tolower(charVal);
            if(charVal == 'q')
                quit = 1;
        }
    }while(quit == 0);
    endwin();
    return 0;
}