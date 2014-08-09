#include <iostream>
#include "VX_Object.h"
#include "VX_Environment.h"
#include "VX_Sim.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <cv.h>
#include <highgui.h>
using namespace cv;

CVX_Object Object;
CVX_Environment Environment;
CVX_Sim Simulator;

void camera (void) {
	double scale = 1.0;
	gluLookAt ( -472.236*scale, -459.546*scale, 271.046*scale,      127.082*scale, 50.498*scale, 33.481*scale,   0, 0, 1 );
}

void enable (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
    //glEnable (GL_LIGHTING); //PROBLEMS!!!
	//glEnable(GL_COLOR_MATERIAL);
    //glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader

}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewportto the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (10, (GLfloat)w / (GLfloat)h, .1, 100000); //set the perspective (angle of sight, width, height, nearClip, farClip)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

void endSimulation(){
	std::ofstream myfile;
    myfile.open ("data.txt");
    //myfile << "Max Strain :" << "\t" << Simulator.SS.MaxBondStrain << "\n";
	//myfile << "Max Stress :" << "\t" << Simulator.SS.MaxBondStress << "\n"; 
    myfile << "Max Displacement :" << "\t" << Simulator.SS.MaxVoxDisp << "\n";
	//myfile << "Max Displacement X :" << "\t" << Simulator.SS.TotalObjDisp.x  << "\n";
	//myfile << "Max Displacement Y :" << "\t" << Simulator.SS.TotalObjDisp.y  << "\n";
	//myfile << "Max Displacement Z :" << "\t" << Simulator.SS.TotalObjDisp.z  << "\n";

    myfile.close();
    
	Object.SaveVXCFile("individual.vxc");
	Simulator.SaveVXAFile("individual.vxa");
	std::cout << "\n\n";
	
	//Simulator.VoxMesh.ToStl(dir + ":/WORKFLOW_trabecularOptimization/trabecularOptimization/mesh.stl", Simulator.pEnv->pObj, true);

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
	cvSaveImage("result.jpg",capImg);
	cvReleaseImage(&capImg);
	delete[] bits;
}

void display (void) {  
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Clear the background of our window to red  
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer  
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
	camera();
    enable();
	glutSwapBuffers(); //swap the buffers
	CaptureViewPort();
	endSimulation();
} 


int main(int argc, char *argv[]){
	char* InputFile;
	//create the three main objects
	CVXC_Structure structure;
	// CVX_Object Object;
	// CVX_Environment Environment;
	// CVX_Sim Simulator;
	// CVX_SimGA Simulator;
	// CVX_SimGA SimulatorGA;
	long int Step = 0;
	vfloat Time = 0.0; //in seconds
	Vec3D<> Vox0Pos;	//for reporting the position of the first voxel
	bool print_scrn = false;

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
	if (!Simulator.LoadVXAFile(InputFile)){
		if (/*Simulator.*/print_scrn) std::cout << "\nProblem importing VXA file. Quitting\n";
		return(0);	//return, indicating via code (0) that we did not complete the simulation
		}
	std::string ReturnMessage;
	if (/*Simulator.*/print_scrn) std::cout << "\nImporting Environment into simulator...\n";

	Simulator.Import(&Environment, 0, &ReturnMessage);
	if (/*Simulator.*/print_scrn) std::cout << "Simulation import return message:\n" << ReturnMessage << "\n";
	// Simulator.pEnv->UpdateCurTemp(Time, &Simulator.LocalVXC);	//set the starting temperature 
	// Simulator.pEnv->UpdateCurTemp(Time);	//set the starting temperature (nac: pointer removed for debugging)
	// Simulator.IniCM=Simulator.GetCM();	//set the starting CM position
	// std::cout<<"NumVox:"<<Simulator.pEnv->pObj->GetNumVox()<<std::endl;
	// std::cout<<"sensorTypes:"<<std::endl;
	// for(int i=0; i<10; i++)
	// {
	// 	std::cout<<int(Simulator.VoxArray[i].GetSensorType())<<std::endl;
	// }

	// std::cout<<"muscleTypes:"<<std::endl;
	// for(int i=0; i<10; i++)
	// {
	// 	std::cout<<int(Simulator.VoxArray[i].GetMuscleType())<<std::endl;
	// }

	// std::cout<<"materialTypes:"<<std::endl;
	// for(int i=0; i<10; i++)
	// {
	// 	std::cout<<int(Simulator.VoxArray[i].GetMaterial())<<std::endl;
	// }
	// while (Step<100000 && Time<1) //nac: removed for DEBUGGING!!!: while (Step<Simulator.SimStopStep && Time<Simulator.SimStopTime)
	// if (Simulator.sensorTrace)
	// {
	//	Simulator.traceFileName = Simulator.FitnessFileName.substr(0,Simulator.FitnessFileName.length()-11).append("trace.txt");
		// std::cout << Simulator.traceFileName << std::endl;
	// 	Simulator.sensorTraceFile.open(Simulator.traceFileName.c_str());
	// }


	// while (not Simulator.StopConditionMet()){
	for(int i=0; i<5000; i++){
		//do some reporting via the stdoutput if required
		if (Step%1000 == 0.0 && /*Simulator.*/print_scrn) //Only output every n time steps
		// if (fmod(Time,0.001) < 0.00000001  && /*Simulator.*/print_scrn) //Only output every n time steps
		// if (print_scrn)
		{
			//std::cout << "Step: " << i << " \tCoM X: " << Simulator.GetCM().x*1000 << "mm" << "\tCoM Y: " << Simulator.GetCM().y*1000 << "mm" << "\tCoM Z: " << Simulator.GetCM().z*1000 << "mm\n"; //note that computing the COM requires looping through the entire voxel array, and is therefore not very efficient
			// Vox0Pos=Simulator.VoxArray[0].GetCurPos()*1000; //*1000 //position in mm
			// std::cout << "Time: " << Time << " \tVox 0 X: " << Vox0Pos.x << "mm" << "\tVox 0 Y: " << Vox0Pos.y << "mm" << "\tVox 0 Z: " << Vox0Pos.z << "mm\n";	//just display the position of the first voxel in the voxelarray
			// std::cout << std::endl;
			// std::cout << "Step: " << Step << std::endl;
			std::cout << "Time: " << Time << std::endl;
			// std::cout << "here" << std::endl;
			//std::cout << Simulator.pEnv->pObj->GetBaseMat(Simulator.VoxArray[45].GetMaterial())->GetName() << std::endl;
			// std::cout << Simulator.pEnv->pObj->GetBaseMat(Simulator.VoxArray[250].GetMaterial())->GetCurMatTemp() << std::endl;
			// std::cout << Simulator.VoxArray[250].GetCurScale().x << std::endl;
			// std::cout << Simulator.VoxArray[250].GetElectricallyActiveOld() << std::endl;
			//std::cout << "Scale: " << Simulator.VoxArray[45].GetCurScale().x << std::endl;

			// for (int thisRow=0; thisRow<10; thisRow++)
			// {
			// 	for (int thisCol=0; thisCol<10; thisCol++)
			// 	{
			// 		std::cout << Simulator.VoxArray[thisRow*10+thisCol].GetElectricallyActiveOld();
			// 	}
			// 	std::cout << std::endl;
			// }
		}

		//do the actual simulation step
		Simulator.TimeStep(&ReturnMessage);
		// std::cout << "here1" << std::endl;
		//TODO: add in error reporting if there is some problem with the timestep
		Step += 1;	//increment the step counter
		Time += Simulator.dt;	//update the sim tim after the step
		// std::cout << "here2" << std::endl;
		// Simulator.pEnv->UpdateCurTemp(Time, &Simulator.LocalVXC);	//pass in the global time, and a pointer to the local object so its material temps can be modified
		// Simulator.pEnv->UpdateCurTemp(Time);	//pass in the global time, and a pointer to the local object so its material temps can be modified (nac: pointer removed for debugging)
		// nac: not needed for non-cyclic actuations:  Simulator.pEnv->UpdateCurTime(Time);	//just pass in the Simulation time to the Environment (currently used only for calculating phase of actuations)
		// std::cout << "here3" << std::endl;
		i = i+1;
	}

	if (print_scrn) std::cout<<"Ending at: "<<Time<<std::endl;
	//generate results file, if required
	// if (SimulatorGA.WriteFitnessFile) SimulatorGA.SaveResultFile(SimulatorGA.FitnessFileName);
	// Simulator.SaveResultFile("resultsFile.xml",Simulator);
	// if (Simulator.sensorTrace)
	// {
		// std::cout << Simulator.traceFileName << std::endl;
	// 	Simulator.sensorTraceFile.close();
	// }

	// Simulator.SaveResultFile(Simulator.FitnessFileName);
	putenv((char *)"DISPLAY=:1");

    //OPEN GL WINDOW
	glutInit(&argc, argv); // Initialize GLUT  
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth 
	glutInitWindowSize (800, 800); // Set the width and height of the window  
	glutInitWindowPosition (100, 100); // Set the position of the window  
	glutCreateWindow ("Voxelyze"); // Set the title for the window  
  
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering  
	glutIdleFunc(display);
	glutReshapeFunc (reshape); //reshape the window accordingly
	glutMainLoop(); // Enter GLUT's main loop
	return 1;	//code for successful completion
}
