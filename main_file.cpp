/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie o
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <lodepng.h>
#include <time.h>
#include <windows.h>
#include <cmath>
#include "constants.h"
#include "allmodels.h"
#include "myCube.h"

using namespace glm;

float r = 1.0f, dim = 10.0f, duszek = 1.0f;

float x=-5.0f,y=0.0f,z=5.0f;
float dx[4]={0,0,0,0}, dz[4]={0,0,0,0};
float jx = 5.0f, jz = -5.0f;

float aspect=1.0f; //Aktualny stosunek szerokości do wysokości okna
float speed=1;

int punkty = 0;

time_t timer;

bool keys[4], koniec = false, strona = 0, skok = false, l,p;
/////////////////////////

GLuint tex;

GLuint tex2;
/////////////////////////
//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obługi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Obraz ma być generowany w oknie o tej rozdzielczości
    aspect=(float)width/(float)height; //Stosunek szerokości do wysokości okna
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_LEFT) keys[1] = true;
        if (key == GLFW_KEY_RIGHT) keys[3] = true;
        if (key == GLFW_KEY_UP) keys[0] = true;
        if (key == GLFW_KEY_DOWN) keys[2] = true;
        if (key == GLFW_KEY_SPACE) {skok = true; timer=time(NULL);}
        if (key == GLFW_KEY_LEFT) l = true;
        if (key == GLFW_KEY_RIGHT) p = true;
    }

    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_LEFT) keys[1] = false;
        if (key == GLFW_KEY_RIGHT) keys[3] = false;
        if (key == GLFW_KEY_UP) keys[0] = false;
        if (key == GLFW_KEY_DOWN) keys[2] = false;
        if (key == GLFW_KEY_LEFT) l = false;
        if (key == GLFW_KEY_RIGHT) p = false;
    }
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedurę obsługi zmiany rozdzielczości bufora ramki
    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury

	glClearColor(0,0,0,1); //Ustaw kolor czyszczenia ekranu

	glEnable(GL_LIGHTING); //Włącz tryb cieniowania
	glEnable(GL_NORMALIZE); //Włącz tryb cieniowania
	glEnable(GL_LIGHT0); //Włącz zerowe źródło światła
	glEnable(GL_LIGHT1); //Włącz zerowe źródło światła
	glEnable(GL_DEPTH_TEST); //Włącz używanie budora głębokości
	glEnable(GL_COLOR_MATERIAL); //Włącz śledzenie kolorów przez materiał

	float lightPos0[4]={5.0f, 3.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
    float lightPos1[4]={0.0f, 3.0f, -5.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);

	std::vector<unsigned char> image, image2;
    //Alokuj wektor do wczytania obrazka
    unsigned width, height, w2, h2;
    //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
	lodepng::decode(image, width, height, "text2.png");
    glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
     GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    lodepng::decode(image2, w2, h2, "text.png");
    glGenTextures(1,&tex2);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
     GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image2.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	srand(time(NULL));
}

float odl(float a, float b, float c, float d) {
    return sqrt(pow(a-c,2) + pow(b-d,2));
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle) {
	//************Tutaj umieszczaj kod rysujący obraz******************l

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyść bufor kolorów (czyli przygotuj "płótno" do rysowania)
    mat4 P=perspective(50.0f*PI/180.0f,aspect,1.0f,50.0f); //Wylicz macierz rzutowania P
    mat4 V=lookAt( //Wylicz macierz widoku
                  vec3(20.0f,15.0f,-20.0f),
                  vec3(0.0f,0.0f,0.0f),
                  vec3(0.0f,1.0f,0.0f));
    glMatrixMode(GL_PROJECTION); //Włącz tryb modyfikacji macierzy rzutowania
    glLoadMatrixf(value_ptr(P)); //Załaduj macierz rzutowania
    glMatrixMode(GL_MODELVIEW);  //Włącz tryb modyfikacji macierzy model-widok

    if (punkty != 0 && punkty%6 == 0) {
        float lightPos0[4]={0.0f, 1.0f, 0.2f, 0.0f};
        glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
        float lightPos1[4]={-0.2f, 1.0f, 0.0f, 0.0f};
        glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);

    } else {
        float lightPos0[4]={0.1f, 1.0f, 0.0f, 0.0f};
        glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
        float lightPos1[4]={0.0f, 1.0f, -0.1f, 0.0f};
        glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);
    }

    x+=0.5f * (keys[1] + ((-1)*keys[3]));
    z+=0.5f * (keys[0] + ((-1)*keys[2]));
    if (x>dim-r) x=dim-r;
    else if (x<-dim+r) x=-dim+r;
    if (z>dim-r) z=dim-r;
    else if (z<-dim+r) z=-dim+r;
    if (difftime(time(NULL), timer) > 0.6)
        skok = false;

    mat4 Mp=mat4(1.0f);
    mat4 W, S, R;
    W=translate(Mp, vec3(x,2.0f+skok*3,z));
    glLoadMatrixf(value_ptr(V*Mp*W));



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex2);
    glEnableClientState(GL_VERTEX_ARRAY );
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glShadeModel(GL_SMOOTH);
    glColor3d(2.0f,2.0f,0.0f);
    Models::sphere.drawSolid();

    glBindTexture(GL_TEXTURE_2D,tex);

    ////////////////////////DUSZKI

    //mat4 M=mat4(1.0f);
    //glLoadMatrixf(value_ptr(V*M));
    //glScalef(duszek,duszek,duszek);
    //glTranslatef(0.0f,2.0f,0.0f);

    dx[0]+=(strona*2-1)*0.1f;
    dz[0]+=(strona*2-1)*0.1f;
    if (dx[0]>dim/duszek-1) {dx[0]=dim/duszek-1; (strona == 0) ? strona=1 : strona=0;}
    else if (dx[0]<-dim/duszek+1) {dx[0]=-dim/duszek+1; (strona == 0) ? strona=1 : strona=0;}
    if (dz[0]>dim/duszek-1) {dz[0]=dim/duszek-1;}
    else if (dz[0]<-dim/duszek+1) {dz[0]=-dim/duszek+1;}


    mat4 M=mat4(1.0f);
    W=translate(M, vec3(dx[0],2.0f,dz[0]));
    S=scale(M,vec3(duszek,duszek,duszek));
    glLoadMatrixf(value_ptr(V*M*W*S));
    glShadeModel(GL_SMOOTH);
    glColor3d(2.0f,1.5f,0.0f);
    Models::cube.drawSolid();
/////////////////////////////DUSZEK2
    //M=mat4(1.0f);
    //glLoadMatrixf(value_ptr(V*M));

    //glScalef(duszek,duszek,duszek);
    //glTranslatef(0.0f,2.0f,0.0f);


    dx[1]-=(strona*2-1)*0.1f;
    dz[1]+=(strona*2-1)*0.1f;
    if (dx[1]>dim/duszek-1) {dx[1]=dim/duszek-1; (strona == 0) ? strona=1 : strona=0;}
    else if (dx[1]<-dim/duszek+1) {dx[1]=-dim/duszek+1; (strona == 0) ? strona=1 : strona=0;}
    if (dz[1]>dim/duszek-1) {dz[1]=dim/duszek-1;}
    else if (dz[1]<-dim/duszek+1) {dz[1]=-dim/duszek+1;}

    M=mat4(1.0f);
    W=translate(M, vec3(dx[1],2.0f,dz[1]));
    S=scale(M,vec3(duszek,duszek,duszek));
    glLoadMatrixf(value_ptr(V*M*W*S));
    glShadeModel(GL_SMOOTH);
    glColor3d(0.0f,2.0f,1.5f);

    Models::cube.drawSolid();
    //glVertexPointer( 3, GL_FLOAT, 0, geomVertices);
    //glTexCoordPointer( 2, GL_FLOAT, 0, geomTexCoords);
    //glDrawArrays( GL_QUADS, 0, geomVertexCount);

/////////////////////////////DUSZEK3
    //M=mat4(1.0f);
    //glLoadMatrixf(value_ptr(V*M));

    //glScalef(duszek,duszek,duszek);
    //glTranslatef(0.0f,2.0f,0.0f);

    dx[2]-=(strona*2-1)*0.1f;
    dz[2]-=(strona*2-1)*0.1f;
    if (dx[2]>dim/duszek-1) {dx[2]=dim/duszek-1; (strona == 0) ? strona=1 : strona=0;}
    else if (dx[2]<-dim/duszek+1) {dx[2]=-dim/duszek+1; (strona == 0) ? strona=1 : strona=0;}
    if (dz[2]>dim/duszek-1) {dz[2]=dim/duszek-1;}
    else if (dz[2]<-dim/duszek+1) {dz[2]=-dim/duszek+1;}


    M=mat4(1.0f);
    W=translate(M, vec3(dx[2],2.0f,dz[2]));
    S=scale(M,vec3(duszek,duszek,duszek));
    glLoadMatrixf(value_ptr(V*M*W*S));

    glShadeModel(GL_SMOOTH);
    glColor3d(1.5f,1.5f,1.5f);

    Models::cube.drawSolid();


    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);

    ////////////////////////////////JEDZONKO
    if (punkty != 0 && punkty%6 == 0) {
        M=mat4(1.0f);
        W=translate(M, vec3(jx,2.0f,jz));
        R=rotate(M,angle*PI,vec3(0.0f,1.0f,0.0f));
        glLoadMatrixf(value_ptr(V*M*W*R));


        if (odl(x,z,jx,jz) <= r+1 && !skok) {
            jx = rand()%20-10;
            jz = rand()%20-10;
            printf("Zdobyłeś punkt, brawo! Twoja obecna liczba punktów to: %d\n", ++punkty);
        }

        glShadeModel(GL_SMOOTH);
        glColor3d(2.0f,2.0f,0.6f);
        Models::torus.drawSolid();
    } else {
        M=mat4(1.0f);
        W=translate(M, vec3(jx,3.0f,jz));
        S=scale(M, vec3(0.75f,0.75f,0.75f));
        R=rotate(M,angle*PI,vec3(0.0f,1.0f,0.0f));
        glLoadMatrixf(value_ptr(V*M*W*S*R));


        if (odl(x,z,jx,jz) <= r+1 && !skok) {
            jx = rand()%20-10;
            jz = rand()%20-10;
            printf("Zdobyłeś punkt, brawo! Twoja obecna liczba punktów to: %d\n", ++punkty);
        }

        glShadeModel(GL_SMOOTH);
        glColor3d(0.0f,1.0f,0.0f);
        Models::moje.drawSolid();

    }
////////////////////////////////////PLANSZA
    if (odl(x,z,dx[0],dz[0]) <= r+duszek && !skok) {
        koniec = true;
    }
    if (odl(x,z,dx[1],dz[1]) <= r+duszek && !skok) {
        koniec = true;
    }
    if (odl(x,z,dx[2],dz[2]) <= r+duszek && !skok) {
        koniec = true;
    }

    if (koniec) {
        printf("Przegrałeś frajerze!\n");
    }

    M=mat4(1.0f);
    S=scale(M,vec3(dim,1,dim));
    glLoadMatrixf(value_ptr(V*M*S));


    glShadeModel(GL_SMOOTH);
    glColor3d(0.0f + koniec,0.0f,0.5f*(1-koniec));
    Models::cube.drawSolid();

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}

int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	GLenum err;
	if ((err=glewInit()) != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

    float angle=0.0f; //Aktualny kąt obrotu obiektu
	glfwSetTime(0); //Wyzeruj timer


	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
	    angle+=speed*glfwGetTime(); //Oblicz przyrost kąta obrotu i zwiększ aktualny kąt
	    glfwSetTime(0); //Wyzeruj timer
		drawScene(window, angle); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
        if (koniec) break;
	}
    Sleep(1000);
    glDeleteTextures(1,&tex);
	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
