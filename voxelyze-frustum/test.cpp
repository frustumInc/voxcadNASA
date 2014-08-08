#include <stdlib.h>
#include <GL/glut.h>
#include <cv.h>
#include <highgui.h>


void CaptureViewPort(){
	GLubyte * bits;
	GLint viewport[4];
	    
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	int w = viewport[2];
	int h = viewport[3];
	    
	bits = new GLubyte[w*3*h];
	
	glFinish();
	glPixelStorei(GL_PACK_ALIGNMENT,1);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glReadPixels(0, 0, w, h, GL_BGR_EXT, GL_UNSIGNED_BYTE, bits);
	
	IplImage * capImg = cvCreateImage( cvSize(w,h), IPL_DEPTH_8U, 3);
	for(int i=0; i < h; ++i){
    	for(int j=0; j < w; ++j){
        	capImg->imageData[i*capImg->widthStep + j*3+0] = (unsigned char)(bits[(h-i-1)*3*w + j*3+0]);
            capImg->imageData[i*capImg->widthStep + j*3+1] = (unsigned char)(bits[(h-i-1)*3*w + j*3+1]);
            capImg->imageData[i*capImg->widthStep + j*3+2] = (unsigned char)(bits[(h-i-1)*3*w + j*3+2]);
     	}
    }

	cvSaveImage("result.jpg",capImg); 
    cvReleaseImage(&capImg);
    delete[] bits;
}
void draw(void) {

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
	CaptureViewPort();
	exit(1);
}

int main(int argc, char **argv) {
	putenv((char *)"DISPLAY=:1");

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);

	glutInitWindowPosition(50, 25);

    glutInitWindowSize(480,480);

    glutCreateWindow("Hello OpenGL");


    glutDisplayFunc(draw);

    glutMainLoop();
    return 0;
}
