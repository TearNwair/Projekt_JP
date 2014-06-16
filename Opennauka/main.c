#include "biblioteki.h"
#include "kolizja.h"


typedef struct _rectangle{
    int isVisible;
    float x;
    float y;
} Rect;

int rectMax = 8;
int rectCount = 20;
Rect rects[20];
Rect reect;
int keyStates[256];
//============================================
// Geometria obrazka:

void geom(int w, int h) {
  // Granice przedstawionego fragmentu przestrzeni:
  //   glOrtho(lewa, prawa, dolna, gorna, przednia, tylna);
  glOrtho(-20, 20, -15, 15, -5, 5);
}

//============================================
// Scena:

int isFreeLocation(float x, float y){
    int i;
    for(i = 0; i < rectMax; i++){
        if(rects[i].isVisible == 1){
            if(Intersects(rects[i].x,rects[i].y,x,y) == 1){
                return 0;
            }
        }
    }
    return 1;
}

//Rysowanie kwadratu
void rectDraw(float x, float y){
glPushMatrix();
    glTranslated(x, y, 0);

    glBegin(GL_POLYGON);
    glVertex3d(-5, 5, 0);
    glVertex3d(-5, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 5, 0);
    glEnd();
glPopMatrix();
}
// Kwadrat, ktorym staeruje
void reectDraw()
{
 glColor3d(CZERW);
 rectDraw(reect.x, reect.y);
}
//Kwadrat spadajacy
void wyswietl(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3d(NIEBI);            // kolor
//Licznik ile widocznych kwadratow ma sie pojawic
int i;
for(i = 0; i < rectCount; i++){
    if(rects[i].isVisible==1)
        rectDraw(rects[i].x, rects[i].y);
}

reectDraw();

  glFlush();
}

//Update pozycji niebieskich kwadratow
void updateRect(){
    int i;
    for(i = 0; i < rectCount; i++){
        if(rects[i].isVisible==1){
            rects[i].x += 0.0012f;
            rects[i].y -= 0.3f;
        }
    }
}
//Update ruchu sterowanego kwadratu
void updateReect()
{
    if(keyStates[97] == 1){
        reect.x -= 0.32f;
    }
     if(keyStates[100] == 1)
     {
        reect.x += 0.32f;
     }
}
//Zeruje licznik MAX gdy kwadraty nie sa juz widoczne
void hideInvisibleRect(){
    int i = 0;
    for(i = 0; i < rectCount; i++){
        if(rects[i].isVisible == 1 && (rects[i].x < -25 || rects[i].y < -20)){
            rects[i].isVisible = 0;
        }
    }
}


void newRect(){
    int i = 0;
    int added = 0;
    int visibleRects = 0;
    while(added == 0 && visibleRects < rectMax && i < rectCount){
        if(rects[i].isVisible == 0){
            float x = rand() / (float)RAND_MAX * 20 - 10;
            //float y = rand() / (float)RAND_MAX * 7;
            rects[i].isVisible = 0;
            rects[i].x = x;
            rects[i].y = 15;
            int j;
            for(j = 0; j < 50 && isFreeLocation(x,15)==0 ; j++)
            {
            x = rand() / (float)RAND_MAX * 20 - 10;
            }
            if(isFreeLocation(x,15)==1){
                rects[i].isVisible = 1;
            }
        }
        visibleRects += rects[i].isVisible;
        i++;
    }
}

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
    keyStates[key] = 0;
}

void czasowa(int data) {
    glutTimerFunc(15,czasowa,0);

    int i, j;
    for(i = 0; i < rectMax; i++){
        for(j = i+1; j < rectMax; j++){
            if(rects[i].isVisible == 1){
                if(Intersects(rects[i].x,rects[i].y,rects[j].x,rects[j].y) == 1){

                }
            }
        }
    }

    updateRect();
    updateReect();
    hideInvisibleRect();

    newRect();

    glutPostRedisplay();
}

//============================================

int main(int ile_arg, char* arg[]) {
    //utworz_baze();
    //wczyt_spis();
    //menu_podstawa();
    //menu_glowne();

  glutInit(&ile_arg, arg);
  glutInitWindowSize(500, 400);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(arg[0]);
  glClearColor(ZOLTY, 0.0);
int i;
    reect.x = 2;
    reect.y = -15;
for(i = 0; i < rectCount; i++){
    float x = rand() / (float)RAND_MAX * 20;
    float y = rand() / (float)RAND_MAX * 1 +30;
    rects[i].isVisible = (i < rectMax);
    rects[i].x = x - 10;
    rects[i].y = 15 + y;
}
  glutKeyboardFunc(keyPressed);
  glutKeyboardUpFunc(keyUp);
  glutReshapeFunc(geom);
  glutDisplayFunc(wyswietl);
  glutTimerFunc(15,czasowa,0);
  glutMainLoop();
  return 0;
}
