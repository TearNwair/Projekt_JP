#include "biblioteki.h"
#include "kolizja.h"

typedef struct _rectangle {
	unsigned short isVisible;
	float x;
	float y;
} Rect;

Rect rects[20];
Rect reect;
int rectMax = 5;
int rectCount = 20;
int keyStates[256];
int isWarning = 0;

//============================================
// Geometria obrazka:
void geom(int w, int h) {
	// Granice przedstawionego fragmentu przestrzeni:
	//   glOrtho(lewa, prawa, dolna, gorna, przednia, tylna);
	glOrtho(-20, 20, -15, 15, -5, 5);
}

//============================================
//Scena:
//Sprawdzenie czy pozycja jest wolna na mapie z założoną tolerancją
int isFreeLocation(float x, float y, float halfSize) {
	int i;
	if (halfSize < 0) {
		halfSize = 2.5f;
	}
	for (i = 0; i < rectCount; i++) {
		if (rects[i].isVisible == 1) {
			if (Intersects(rects[i].x, rects[i].y, x, y, halfSize) == 1) {
				return 0;
			}
		}
	}
	return 1;
}

//Usunięcie ze sceny przeciwników poza mapą
void hideInvisibleRect( ) {
	int i = 0;
	for (i = 0; i < rectCount; i++) {
		if (rects[i].isVisible == 1 && (rects[i].x < -25 || rects[i].y < -20)) {
			rects[i].isVisible = 0;
		}
	}
}

//Stworzenie nowego kwadratu
void createNewRect( ) {
	int i = 0;
	int added = 0;
	int visibleRects = 0;
	while (added == 0 && visibleRects < rectMax && i < rectCount) {
		float x;
		if (rects[i].isVisible == 0) {
			x = rand( ) / (float)RAND_MAX * 20 - 10;
			int j;
			for (j = 0; j < 5 && isFreeLocation(x, 15, 3.0f) == 0; j++) {
				x = rand( ) / (float)RAND_MAX * 20 - 10;
			}
			if (isFreeLocation(x, 15, 3.0f) == 1) {
				rects[i].x = x;
				rects[i].y = 15;
				rects[i].isVisible = 1;
			}
		}
		visibleRects += rects[i].isVisible;
		i++;
	}
}

//Update przeciwników
void updateRects( ) {
	int i;
	for (i = 0; i < rectCount; i++) {
		if (rects[i].isVisible == 1) {
			rects[i].y -= 0.3f;
		}
	}
}

//Update gracza
void updatePlayer( ) {
	if (keyStates[97] == 1) {
		reect.x -= 0.32f;
	}
	if (keyStates[100] == 1) {
		reect.x += 0.32f;
	}
	isWarning = 0;
	if (isFreeLocation(reect.x, reect.y, 2.5f) == 0) {
		isWarning = 1;
	}
	/*int i;
	for (i = 0; i < rectMax; i++) {
	if (rects[i].isVisible == 1) {
	if (Intersects(rects[i].x, rects[i].y, reect.x, reect.y) == 1) {
	isWarning = 1;
	}
	}
	}*/
}

//Update gry
void update(int data) {
	glutTimerFunc(15, update, 0);

	updateRects( );
	updatePlayer( );
	hideInvisibleRect( );
	createNewRect( );

	glutPostRedisplay( );
}

//Draw single rectangle
void rectDraw(float x, float y) {
	glPushMatrix( );
	glTranslated(x, y, 0);

	glBegin(GL_POLYGON);
	glVertex3d(-2.5, 2.5, 0);
	glVertex3d(-2.5, -2.5, 0);
	glVertex3d(2.5, -2.5, 0);
	glVertex3d(2.5, 2.5, 0);
	glEnd( );

	glPopMatrix( );
}

//Draw gracza
void drawPlayer( ) {
	glColor3d(CZERW);
	rectDraw(reect.x, reect.y);
}

//Draw przeciwników
void drawRects( ) {
	glColor3d(NIEBI);
	int i;
	for (i = 0; i < rectCount; i++) {
		if (rects[i].isVisible == 1) {
			rectDraw(rects[i].x, rects[i].y);
		}
	}
}

//Draw gry
void draw(void) {
	if (isWarning == 0) {
		glClearColor(ZIELO, 0.0);
	} else {
		glClearColor(ZOLTY, 0.0);
	}

	glClear(GL_COLOR_BUFFER_BIT);

	drawRects( );
	drawPlayer();

	glFlush( );
}

//Event - zapisanie naciśniętego przycisku
void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

//Event - zapisanie zwolnionego przycisku
void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

//============================================
//Entry point
int main(int ile_arg, char* arg[]) {
	int i;
	reect.x = 2;
	reect.y = -12.5f;
	for (i = 0; i < rectCount; i++) {
		createNewRect( );
	}

	glutInit(&ile_arg, arg);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(arg[0]);
	glClearColor(ZOLTY, 0.0);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutReshapeFunc(geom);
	glutDisplayFunc(draw);
	glutTimerFunc(15, update, 0);
	glutMainLoop( );
	return 0;
}
