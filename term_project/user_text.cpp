#include "user_text.h"

GLuint base;
HDC hDC;

GLvoid BuildFont(GLvoid)
{
    HFONT font; // <1>
    base = glGenLists(96); // <2>
    font = CreateFont(-24, // <3-1>
        0,
        0,
        0,
        FW_BOLD, // <3-2>
        FALSE, // <3-3>
        FALSE, // <3-4>
        FALSE, // <3-5>
        ANSI_CHARSET, // <3-6>
        OUT_TT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY,
        FF_DONTCARE | DEFAULT_PITCH,
        "Courier New"); // <3-6>

    SelectObject(hDC, font); // <4>
    wglUseFontBitmaps(hDC, 32, 96, base); // <5>
}

GLvoid KillFont(GLvoid)
{
    glDeleteLists(base, 96);
}

GLvoid glPrint(const char* text)
{
    glPushAttrib(GL_LIST_BIT); //<1>
    glListBase(base - 32); //<2>
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); //<3>
    glPopAttrib(); //<4>
}


int InitGL(GLvoid)
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    ///////////////////////// NEW //////////////////////////
    BuildFont();
    ///////////////////////// NEW //////////////////////////

    return TRUE;
}



int DrawGLScene(GLvoid)
{
 
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -4.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glColor3f(0.5f, 0.5f, 1.0f);      //<1>
    //glRasterPos2f(-1.4f, 0.0f);       //<2>
    glPrint("Dip2K's OpenGL Forum");  //<3>

    return TRUE;
}

void output(int x, int y, float r, float g, float b, int* font, const char* string)
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter( font, string[i]);
    }
}