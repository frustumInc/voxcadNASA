#define USE_OPEN_GL
#include <iostream>
#include <fstream>
#include "VX_Object.h"
#include "VX_Environment.h"
//#include "VX_Sim.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <cv.h>
#include <highgui.h>
#include "VX_FEA.h"
#include "Utils/Vec3D.h"
#include <exception>

using namespace cv;

CVX_Object Object;
CVX_Environment Environment;
//CVX_Sim Simulator;
CVX_FEA Simulator;

void camera (void) {
	double scale = 1.0;
	gluLookAt (
			-0.250,
			-0.250,
			0.125,
			0.054,
			0.025,
			0.0,
			0,
			0,
			1
			);
}

void endSimulation(){
	std::ofstream myfile;
    myfile.open("data.txt");
    //myfile << "Max Strain :" << "\t" << Simulator.SS.MaxBondStrain << "\n";
	//myfile << "Max Stress :" << "\t" << Simulator.SS.MaxBondStress << "\n"; 
    
	myfile << "Max Displacement:" << Simulator.GetMaxDisp()*1000 << "\n";	
    myfile << "Total Weight:" << Simulator.pEnv->pObj->GetWeight() << "\n";
	
	//myfile << "Max Displacement X :" << "\t" << Simulator.SS.TotalObjDisp.x  << "\n";
	//myfile << "Max Displacement Y :" << "\t" << Simulator.SS.TotalObjDisp.y  << "\n";
	//myfile << "Max Displacement Z :" << "\t" << Simulator.SS.TotalObjDisp.z  << "\n";

    myfile.close();
    
	//Object.SaveVXCFile("individual.vxc");
	//Simulator.SaveVXAFile("individual.vxa");
	std::cout << "\n\n";
	
	//Environment.VoxMesh.ToStl("individual.stl", Simulator.pEnv->pObj, true);

	exit(1);
}

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
	cvSaveImage("image.jpg",capImg);
	cvReleaseImage(&capImg);
	delete[] bits;
}

void enable (void) {
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
}

void reshape (int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10, (GLfloat)800 / (GLfloat)800, .1, 100000);
	glMatrixMode(GL_MODELVIEW);
}

void display (void) {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glLoadIdentity(); 
	camera();
	enable();

	//Simulator.DrawView = true;
	//Simulator.ViewGeo = true; //look at geometry?
	//Simulator.ViewGeoMesh = true; //if looking at geometry, do we want the mesh?

	//Simulator.CurViewCol = RVC_MATERIAL;
	//Simulator.CurViewCol = RVC_STRAIN;
	//Simulator.CurViewCol = RVC_STRAIN;
	//Simulator.CurViewCol = RVC_DISP;
	//Simulator.DrawFloor();
	//Simulator.DrawVoxMesh();
	//Simulator.defMesh.Draw();
	Simulator.DrawFEA();
	

	//glLineWidth(2.5); 
	//glColor3f(1.0, 0.0, 0.0);
	//glBegin(GL_LINES);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(15, 0.0, 0.0);
	//glEnd();

	//glColor3f(0.0, 5.0, 0.0);
	//glBegin(GL_LINES);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(0.0, 15.0, 0.0);
	//glEnd();

	//glColor3f(0.0, 0.0, 5.0);
	//glBegin(GL_LINES);
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(0.0, 0.0, 15.0);
	//glEnd();

	CaptureViewPort();
	endSimulation();
} 


int main(int argc, char *argv[]){
	char* InputFile;
	long int Step = 0;
	vfloat Time = 0.0; //in seconds
	Vec3D<> Vox0Pos;	//for reporting the position of the first voxel
	bool print_scrn = false;

	
	putenv((char *)"DISPLAY=:1");
	
	//first, parse inputs. Use as: -f followed by the filename of the .vxa file that describes the simulation. Can also follow this with -p to cause console output to occur
	if (argc < 2) 
	{ // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "\nInput file required. Quitting.\n";
		return(0);	//return, indicating via code (0) that we did not complete the simulation
	} 
	else 
	{ // if we got enough parameters...
		for (int i = 1; i < argc; i++) 
		{ 
			if (strcmp(argv[i],"-f") == 0) 
			{
				InputFile = argv[i + 1];	// We know the next argument *should* be the filename:
			} 
			else if (strcmp(argv[i],"-p") == 0) 
			{
				// Simulator.print_scrn=true;	//decide if output to the console is desired
				/*Simulator.*/print_scrn=true;	//decide if output to the console is desired
			}
		}
	} 

	//setup main object
	Simulator.pEnv = &Environment;	//connect Simulation to environment
	Environment.pObj = &Object;		//connect environment to object

	//import the configuration file
//	if (!Simulator.LoadVXAFile(InputFile)){
//		if (/*Simulator.*/print_scrn) std::cout << "\nProblem importing VXA file. Quitting\n";
//		return(0);	//return, indicating via code (0) that we did not complete the simulation
//		}
//	std::string ReturnMessage;
//	if (/*Simulator.*/print_scrn) std::cout << "\nImporting Environment into simulator...\n";
//
//	Simulator.Import(&Environment, 0, &ReturnMessage);
//	if (/*Simulator.*/print_scrn) std::cout << "Simulation import return message:\n" << ReturnMessage << "\n";
	
	//bool converged = false;
	//double history = 10000000000.0;
	//while (not converged){
	//for(int i=0; i<5000; i++){
		//if (Step%1000 == 0.0 && /*Simulator.*/print_scrn) //Only output every n time steps
		// if (fmod(Time,0.001) < 0.00000001  && /*Simulator.*/print_scrn) //Only output every n time steps
		// if (print_scrn)
		//{
		//	std::cout << "Displacement : " << Simulator.SS.MaxVoxDisp << std::endl;
		//}
		
		//if (Step == 5000){
		//	converged = true;
		//}
		
		// if (Simulator.SS.MaxVoxDisp == history){
		// 	converged = true;
		// }
		// if (Simulator.SS.MaxVoxDisp != history){
		// 	history = Simulator.SS.MaxVoxDisp;
		// }

		//do the actual simulation step
		//Simulator.TimeStep(&ReturnMessage);
		//Step += 1;	//increment the step counter
		//Time += Simulator.dt;	//update the sim tim after the step
		//i = i+1;
	//}
	//Environment.SaveBCXFile("case_study_3.bcx");	
	//Object.InitializeMatter(0.001f, 10, 20, 10);

	Object.LoadVXCFile(InputFile);	
	Environment.AddObject(&Object);

	//Environment.AddFixedBc(Vec3D<>(0, 0, 0), Vec3D<>(1.0f, 0.01f, 1.0f));
	//Environment.AddForcedBc(Vec3D<>(0, 0.99, 0), Vec3D<>(1.0f, 0.01f, 1.0f), Vec3D<>(0, 0, -1.0f));
	//Simulator.ImportObj(&Environment);


	if (!Environment.LoadBCXFile("case_study_3.bcx")){
		if (/*Environment.*/print_scrn) std::cout << "\nProblem importing BCX file. Quitting\n";
		return(0);	//return, indicating via code (0) that we did not complete the simulation
		}
	std::string ReturnMessage;
	if (/*Environment.*/print_scrn) std::cout << "\nImporting Bounderies into Environment...\n";

	Simulator.ImportObj(&Environment, &ReturnMessage);
	if (/*Simulator.*/print_scrn) std::cout << "Simulation import return message:\n" << ReturnMessage << "\n";
	
	Simulator.Solve(&ReturnMessage);
	if (/*Simulator.*/print_scrn) std::cout << "Solve return message:\n" << ReturnMessage << "\n";

	//OPEN GL WINDOW
	glutInit(&argc, argv); // Initialize GLUT  
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth 
	glutInitWindowSize (800, 800); // Set the width and height of the window  
	glutCreateWindow ("Voxelyze"); // Set the title for the window  
		
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering  
	//glutIdleFunc(display);
	
	glutReshapeFunc (reshape); //reshape the window accordingly
	glutMainLoop(); // Enter GLUT's main loop
	return 1;	//code for successful completion
}
