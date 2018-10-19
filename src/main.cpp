#include <iostream>
#include <GL/freeglut.h>

#include "IParticleSystem.h"

using namespace std;
using namespace IMath;


#define GLUT_WHEEL_UP   3
#define GLUT_WHEEL_DOWN 4



//=================================  Unit Test ==================================//

float Width = 600;
float Height = 400;

void print_text(int x, int y, string String)
{
   //(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, Width , 0, Height, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for(unsigned int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


/// Camera value
struct ICamera
{

        Vector3 mEye;
        Vector3 mCenter;
        Vector3 mUp;

} camera;


IMatrix4x4r mOrientCamera;




std::vector<IParticle*> Particles;
IParticleSystem         ParticleSystem;



float TimeStep = 1.0 / 60.0;
bool Pause = true;

// Initialization
void initilization()
{

    camera.mEye    =  Vector3(0,0,0);
    camera.mCenter =  Vector3(0,0,0);
    camera.mUp     =  Vector3(0,1,0);


    float aspect = Width / Height;
    float zNear  = 1.0;
    float zFar   = 1024;
    float fov    = 45.0;

    IMatrix4x4r  Prespective = IMatrix4x4r::CreatePerspective(fov, aspect , zNear , zFar );

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(Prespective);

    //srand(time(0));
    int size = 15;
    for(int i = 0; i < size; i++ )
    {
        float ang = ((2.0) * M_PI / float(size)) * (i);

        for (int j = 0; j < 100; ++j)
        {
            Real      random_radius = j/float(10);//((size * 0.5) - rand()%size) * 2.f;
            Vector3 random_vertex( cos(ang) * random_radius , 0 , sin(ang) * random_radius);
            random_vertex /= rand()%3;

            Real massa = 2;
            auto particle = ParticleSystem.CreateParticle( random_vertex , massa , ParticleType::DYNAMIC );
            Particles.push_back(particle);
        }


    }

}




// Display the scene
void display()
{

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glViewport(0, 0, Width , Height );

    float aspect = Width / Height;
    float zNear  = 1.0;
    float zFar   = 1024;
    float fov    = 45.0;

    IMatrix4x4r  Prespective = IMatrix4x4r::CreatePerspective(fov, aspect , zNear , zFar );
    IMatrix4x4r  ViewModel   = IMatrix4x4r::CreateLookAt( -camera.mEye , camera.mCenter , camera.mUp );


    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(Prespective);


    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(ViewModel);



    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glPushMatrix();
    for (std::size_t i = 0; i < Particles.size(); ++i)
    {
        glColor3f(1,0,0);
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex3fv(Particles[i]->GetPosition());
        glEnd();
         glColor3f(0,1,0);
        glBegin(GL_LINES);
          glVertex3fv(Particles[i]->GetPosition());
          glVertex3fv(Particles[i]->GetPosition() + Particles[i]->GetVelocity() );
        glEnd();
    }
    glPopMatrix();


    print_text( 20 , Height - 20 , " KEY   : (W,S,A,D)  : Move-Camera");
    print_text( 20 , Height - 40 , " MOUSE : (LEFT_KEY) : Rotate-Camera");

    print_text( 20 , Height - 60 , " KEY   : (Down)     : ApplyImpulseMoment");

    char buff[256];
    sprintf( buff , " Particles-Size     : %zu " , Particles.size());
    print_text( 20 , Height - 80 , buff);

    glutSwapBuffers();

}






float zoom_distance = 25;

float oldX = 0;
float oldY = 0;

float angle_X = 0;
float angle_Y = 0;

int   mouse_button = -1;



void UpdateTime(void)
{
    camera.mEye = zoom_distance * Vector3::Z * mOrientCamera.GetInverse();
    display();

    float timeStep = 1.0 / 60.f;
    ParticleSystem.Update(timeStep);


    ParticleSystem.AdvancedAngularMoment(Vector3::Y);

};


// Reshape function
void reshape(int width, int height)
{
    Width  = width;
    Height = height;

    float aspect = Width / Height;
    float zNear  = 1.0;
    float zFar   = 1024;
    float fov    = 45.0;

    IMatrix4x4r  Prespective = IMatrix4x4r::CreatePerspective(fov, aspect , zNear , zFar );

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(Prespective);
}


// Called when a mouse button event occurs
void mouseButton(int button, int state, int x, int y)
{
    mouse_button = button;

    float aspect = Width / Height;
    float m_x = ((x / Width ) - 0.5f) * aspect * 0.834;
    float m_y = ((y / Height) - 0.5f) * 0.834;

    oldX = m_x;
    oldY = m_y;

    if (state == GLUT_UP )
    {
        if ( button == GLUT_WHEEL_UP )
        {
            zoom_distance -= 0.5;
        }
        else if( button == GLUT_WHEEL_DOWN )
        {
            zoom_distance += 0.5;
        }
    }


    if (button == GLUT_RIGHT_BUTTON )
    {
        ;
    }

}

// Called when a mouse motion event occurs
void mouseMotion(int x, int y)
{
   float aspect = Width / Height;
   float m_x = ((x / Width ) - 0.5f) * aspect * 0.834;
   float m_y = ((y / Height) - 0.5f) * 0.834;

   float speedX = (m_x - oldX);
   float speedY = (m_y - oldY);

   if( mouse_button == GLUT_LEFT_BUTTON )
   {
       float coff = 1.5f;

       angle_X += speedX * coff;
       angle_Y -= speedY * coff;
   }

   oldX = m_x;
   oldY = m_y;


   mOrientCamera = IMatrix4x4r::CreateRotationAxis( Vector3::Y , angle_X );
   mOrientCamera = IMatrix4x4r::CreateRotationAxis( Vector3::X , angle_Y ) * mOrientCamera;

}


void processNormalKeys(unsigned char key, int x, int y)
{

    switch(key)
    {
      case 27 : exit(0); break;
      case ' ' : Pause = !Pause; break;
    }

}


void processSpecialKeys(int key, int x, int y) {

    switch(key)
    {
        case GLUT_KEY_UP:

               ParticleSystem.AdvancedAngularMoment(Vector3::Y);

            break;
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
    }
}




// Main function
int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Initialize the size of the GLUT windows
    glutInitWindowSize( Width ,  Height );
    // Initialize the position of the GLUT windows
    glutInitWindowPosition( 0 , 0 );
    // Initialize the create window
    glutCreateWindow("Demo: RelativityPhysics-Particles");

    initilization();

    glutDisplayFunc(display);

    // Glut Idle function that is continuously called
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);


    glutIdleFunc(UpdateTime);

    // here are the new entries
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);




    // Glut main looop
    glutMainLoop();


    /**/
    return 0;
}
