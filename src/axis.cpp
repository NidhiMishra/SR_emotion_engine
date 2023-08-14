#include "axis.h"

float GREEN[3]={0,1,0};
float RED[3]={1,0,0};
float MEGENTA[3]={1,0,1};

void coordinate(void){
	
	 glEnable(GL_BLEND);//启用融合效果
     glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//设置融合方式
	 glEnable(GL_POINT_SMOOTH);//对点进行平滑处理 
	 glEnable(GL_LINE_SMOOTH);//对线进行平滑处理

	 GLUquadric *myQuad;
	 GLfloat h=3;
     GLfloat h1=0.2;
	 GLfloat r=0.03;
	 GLint s=20;

	 //Z axis
	 glPushMatrix();
	 glTranslatef(0,0,-0.5*h);
	 glShadeModel(GL_SMOOTH);
     glColor4ub(107,142,35,255);
	 myQuad=gluNewQuadric();	
	 gluCylinder(myQuad,r,r,h,s,s);
	 glPopMatrix();

	 glPushMatrix();
	 glTranslatef(0,0,0.5*h);
	 glShadeModel(GL_SMOOTH);
     glColor4ub(107,142,35,255);
	 myQuad=gluNewQuadric();	
	 gluCylinder(myQuad,r,0,h1,2*s,2*s);
	 glPopMatrix();

	 glRasterPos3f(0,0,0.5*h+h1); 
	 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'D');

	 // X axis
	 glPushMatrix();
	  glTranslatef(-0.5*h,0,0);
	 glRotatef(90,0,1,0);
	
	 glShadeModel(GL_SMOOTH);
     glColor4ub(255,128,0,255);
	 myQuad=gluNewQuadric();	
	 gluCylinder(myQuad,r,r,h,s,s);
	 glPopMatrix();

	  glPushMatrix();
	  glTranslatef(0.5*h,0,0);
	 glRotatef(90,0,1,0);
	
	 glShadeModel(GL_SMOOTH);
     glColor4ub(255,128,0,255);
	 myQuad=gluNewQuadric();	
	 gluCylinder(myQuad,r,0,h1,2*s,2*s);
	 glPopMatrix();

	 glRasterPos3f(0.5*h+h1,0,0); 
	 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');

	 //Y axis
	 glPushMatrix();
	 glTranslatef(0,-0.5*h,0);
	 glRotatef(-90,1,0,0);

	 glShadeModel(GL_SMOOTH);
     glColor4ub(94,38,18,255);
	 myQuad=gluNewQuadric();	
	 gluCylinder(myQuad,r,r,h,s,s);
	 glPopMatrix();

	 glPushMatrix();
	 glTranslatef(0,0.5*h,0);
	 glRotatef(-90,1,0,0);

	 glShadeModel(GL_SMOOTH);
     glColor4ub(94,38,18,255);
	 myQuad=gluNewQuadric();	
	 gluCylinder(myQuad,r,0,h1,2*s,2*s);
	 glPopMatrix();

	 glRasterPos3f(0,0.5*h+h1,0); 
	 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');


	 glDepthMask(GL_FALSE);

	 	double width;
	glGetDoublev(GL_LINE_WIDTH, &width);

	glLineWidth(6); 

	 glColor4f(0,0,1,0.4);
	 glutWireCube(2);
	 glLineWidth(width);

	 glBegin(GL_QUADS);

	 glColor4f(1.0f,1.0f,1.0f,0.05f);
	 glVertex3f(1,1,1);
	 glVertex3f(1,-1,1);
	 glVertex3f(1,-1,-1);
	 glVertex3f(1,1,-1);

	 glColor4f(1.0f,1.0f,1.0f,0.05f);
	 glVertex3f(-1,1,1);
	 glVertex3f(-1,-1,1);
	 glVertex3f(-1,-1,-1);
	 glVertex3f(-1,1,-1);

	 glColor4f(1.0f,1.0f,1.0f,0.05f);
	 glVertex3f(1,1,1);
	 glVertex3f(-1,1,1);
	 glVertex3f(-1,1,-1);
	 glVertex3f(1,1,-1);

	 glColor4f(1.0f,1.0f,1.0f,0.05f);
	 glVertex3f(1,-1,1);
	 glVertex3f(-1,-1,1);
	 glVertex3f(-1,-1,-1);
	 glVertex3f(1,-1,-1);

	 glColor4f(1.0f,1.0f,1.0f,0.05f);
	 glVertex3f(1,1,1);
	 glVertex3f(-1,1,1);
	 glVertex3f(-1,-1,1);
	 glVertex3f(1,-1,1);

	 glColor4f(1.0f,1.0f,1.0f,0.05f);
	 glVertex3f(1,1,-1);
	 glVertex3f(-1,1,-1);
	 glVertex3f(-1,-1,-1);
	 glVertex3f(1,-1,-1);

	 glEnd();
	 glLineWidth(width); 

	
	 glDepthMask(GL_TRUE);

	// glDisable(GL_BLEND); //关闭融合效果

	
}

void draw_aff_context(const point& emo_context){
	 glPushMatrix();
	 glTranslatef(emo_context[0],emo_context[1],emo_context[2]);
	 glShadeModel(GL_SMOOTH);
	 glColor3f(1.f,0.f,1.f);
	 glutSolidSphere(0.1,20,20);
	 glPopMatrix();
}
void draw_relationship(const point& relationship){
	 glPushMatrix();
	 glTranslatef(relationship[0],relationship[1],relationship[2]);
	 glShadeModel(GL_SMOOTH);
	 glColor3f(0.f,1.f,1.f);
	 glutSolidSphere(0.1,20,20);
	 glPopMatrix();
}

void mydraw(const Mood &mood,const zjz::Emotion *EmotionPool)
 {
	 glPushMatrix();
	 glTranslatef(mood.Position[0],mood.Position[1],mood.Position[2]);
	 glShadeModel(GL_SMOOTH);
	 glColor3f(1.f,1.f,1.f);
	 glutSolidSphere(0.1,20,20);
	 glPopMatrix();


	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity>1e-2)
		{
			glPushMatrix();
			glTranslatef(EmotionPool[i].Position[0],EmotionPool[i].Position[1],EmotionPool[i].Position[2]);
			glShadeModel(GL_SMOOTH);
			glColor3f(1.f,0.f,0.f);
			glutSolidSphere(0.2*EmotionPool[i].Intensity,20,20);
			glPopMatrix();
			draw_vector(EmotionPool[i].Position, RED,2);
	     }
	}
 }

void alma_draw(const Mood &mood,const zjz::Emotion &emotion,const zjz::Emotion *EmotionPool)
 {
	 glPushMatrix();
	 glTranslatef(mood.Position[0],mood.Position[1],mood.Position[2]);
	 glShadeModel(GL_SMOOTH);
	 glColor3f(1.f,1.f,1.f);
	 glutSolidSphere(0.1,20,20);
	 glPopMatrix();


	if(emotion.Intensity>1e-2)
	{
	    glPushMatrix();
		glTranslatef(emotion.Position[0],emotion.Position[1],emotion.Position[2]);
		glShadeModel(GL_SMOOTH);
		glColor3f(1.f,0.f,1.f);
		glutSolidSphere(0.2*emotion.Intensity,20,20);
		glPopMatrix();
		draw_vector(emotion.Position, MEGENTA,2);
	}
	for(int i=0;i!=22;++i){
		if(EmotionPool[i].Intensity>1e-2)
		{
			glPushMatrix();
			glTranslatef(EmotionPool[i].Position[0],EmotionPool[i].Position[1],EmotionPool[i].Position[2]);
			glShadeModel(GL_SMOOTH);
			glColor3f(1.f,0.f,0.f);
			glutSolidSphere(0.2*EmotionPool[i].Intensity,20,20);
			glPopMatrix();
			draw_vector(EmotionPool[i].Position, RED,2);
	     }
	}

 }

void draw_vector(const point& temp, const float* color, const float& width){
	 double wid;
	glGetDoublev(GL_LINE_WIDTH, &wid);
	glLineWidth(width); 

	 glColor3f(color[0],color[1],color[2]);
	 glBegin(GL_LINES);

	
	 glVertex3f(0,0,0);
	 glVertex3f(temp[0],temp[1],temp[2]);
	

	 glEnd();
	 glLineWidth(wid); 
}