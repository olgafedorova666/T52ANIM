#include <stdlib.h>
#include <cmath>
#include <glut.h>
#include <cstdio> 
#include <time.h> 
#ifndef _ANIM_H_
#define _ANIM_H_

namespace fegl
{
  class anim;
  class object
  {
    public:
      virtual void Response(anim &Ani)
      {
       ;
      }
      virtual void Render(anim &Ani)
      {
        glPushMatrix();
        glColor3d(0, 0.6, 0.7);
        glBegin(GL_QUADS);
        glVertex3d(-1, 0, -1);
        glVertex3d(-1, 0, 1);
        glVertex3d(1, 0, 1);
        glVertex3d(1, 0, -1);
        glEnd();
        glPopMatrix();
      }
  };
  class anim
  {
  private:
    static const int MAX = 100;
    object *Stock[MAX];
    int StockSize;

    static anim Instance;

    static void Keyboard(unsigned char key, int x, int y)
    {
      if (key == 27)
        exit(0);
    }
   
  public:
    int IsPause;
    double FullTime;

    static void Display(void)
    {
      glClearColor(0.3, 0.5, 0.7, 1);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_COLOR_MATERIAL);
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      glEnable(GL_NORMALIZE);
      Instance.Timer();
      Instance.Render();
      glutSwapBuffers();
      glutPostRedisplay();    
    }

    static void Reshape(int W, int H)
  {
    double x = 1, y = 1;
    glViewport(0, 0, W, H);
    if(W > H)
      x *= (double)W/H;
    else
      y *= (double)H/W;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-x, x, -y, y, -100, 100);
    glFrustum(-x, x, -y, y, -100, 100);

    gluPerspective(30, 0.9, -100, 100);
    gluLookAt(3, 3, 3, 0, 0 , 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
  }

    anim() : StockSize(0)
    {
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

      glutInitWindowPosition(0, 0);
      glutInitWindowSize(500, 500);
      glutCreateWindow("10-4 forever!!!");

      glutDisplayFunc(Display);
      glutReshapeFunc(Reshape);
      glutKeyboardFunc(Keyboard);
    }  
    //~anim(void);
    void Run(void)
    {
      glutMainLoop();
    }

    static anim &Get(void)
    {
      return Instance;
    }
    anim & operator<<(object *Obj)
    {
      if(StockSize < MAX)
        Stock[StockSize++] = Obj;
      else
        delete Obj;
      return *this;
    }
    void Render(void)
    {
      for(int i = 0; i < StockSize; i++)
        Stock[i]->Render(*this);
    }
    double Time, DeltaTime;

    void Timer(void)
    {
      static long StartTime = -1;
      long CurTime = clock(); 
      if(StartTime == - 1)
        StartTime = CurTime;
      else
        FullTime = (double)(CurTime - StartTime) / CLOCKS_PER_SEC;
    } 
  };


class SnowMan: public object
{
   void Response(anim &Ani)
      {
       ;
      }

   void DrawCylinder(double R, double r, double h, int n)
{

  double x, y, t;
  double sA = R / sqrt((R - r) * (R - r) + h * h);
  double cA = h / sqrt((R - r) * (R - r) + h * h);
  int i;
  glBegin(GL_QUAD_STRIP);
  for(i = 0; i <= n; i++)
  {
    t = i * 2 * 3.1415 / n;
    glNormal3d(cos(t) * cA, sA, sin(t) * sA);
    y = R * sin(t);
    x = R * cos(t);
    glTexCoord2d((double) i / n, 0);
    glVertex3d(x, 0, y);
    y = r * sin(t);
    x = r * cos(t);
    glTexCoord2d((double) (i + 1) / n, 1);
    glVertex3d(x, h, y);
  
  }
   glEnd();
}

   void Render(anim &Ani)
      {
        glPushMatrix();
        glTranslated(0, abs(sin(Ani.FullTime * 5))/2, 0);
        glRotated(sin(Ani.FullTime * 5) * 90, 0, 1, 0);
        glColor3d(1, 1, 1);
        glutSolidSphere(0.2, 50, 20);
        glTranslated(0, 0.25, 0);
        glutSolidSphere(0.15, 50, 20);
        glTranslated(0, 0.2, 0);
        glutSolidSphere(0.1, 50, 20);
        glColor3d(1, 0.6, 0);
        glutSolidCone(0.05, 0.2, 50, 20);
        glColor3d(1, 0, 1);
        DrawCylinder(0.09, 0.06, 0.2, 50);
        glPopMatrix();
      }
};

class XmasTree: public object
{
  void Response(anim &Ani)
      {
       ;
      }
  void DrawCylinder(double R, double r, double h, int n)
  {

     double x, y, t;
   double sA = R / sqrt((R - r) * (R - r) + h * h);
    double cA = h / sqrt((R - r) * (R - r) + h * h);
    int i;
  glBegin(GL_QUAD_STRIP);
  for(i = 0; i <= n; i++)
  {
    t = i * 2 * 3.1415 / n;
    glNormal3d(cos(t) * cA, sA, sin(t) * sA);
    y = R * sin(t);
    x = R * cos(t);
    glTexCoord2d((double) i / n, 0);
    glVertex3d(x, 0, y);
    y = r * sin(t);
    x = r * cos(t);
    glTexCoord2d((double) (i + 1) / n, 1);
    glVertex3d(x, h, y);
  
  }
   glEnd();
}
    void Render(anim &Ani)
      {
        glPushMatrix();
        glTranslated(-0.7, -0.3, 0);
        glColor3d(1, 0, 0.3);
        glRotated(sin(Ani.FullTime * 2) * 20, 1, 0, 1);
        glColor3d(0, 1, 0);
        glRotated(-90, 1, 0, 0);
        glutSolidCone(0.3, 0.5, 50, 50);
        glTranslated(0, 0, 0.3);
        glRotated(sin(Ani.FullTime * 2) * 20, 1, 0, 0);
        glutSolidCone(0.2, 0.4, 50, 50);
        glPopMatrix();
      }
};
}
    /*
class object
    {
    public:
      void object::Response(fegl::anim &Ani)
      {
       ;
      }
      void object::Render(fegl::anim &Ani)
      {
        glutSolidSphere(1, 1, 1);
      }
    };              */
#endif
/*class Reshape
{
  public:
    float Size;
    virtual void Draw(void)
    {
       cout<<"Shape";
    }
};

class sphere: public Reshape
{
  public:
    vec Center;
    double R;
    void Draw(void)
    {
       cout<<"Shape";
    }
};
class box: public Reshape
{
  public:
    vec Center, Side;
    double R;
    void Draw(void)
    {
       cout<<"Box";
    }
};
*/