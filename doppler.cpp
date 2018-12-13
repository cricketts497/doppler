#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>
#include <math.h>

void check_wavenumber(int argc, char **argv){
	if (argc == 1){
		throw "Need a wavenumber value!";
	}
	else{
		try{
			atof(argv[argc-1]);
		} catch(...) {
			throw "Need a wavenumber value!";
		}
	}
}

void check_value(int index, int argc, double value){
	if (index+2 >= argc || value < 1){
		throw "Invalid option input";
	}
}

double to_power(double power, double value){
	double result = 1;
	for(int i=1; i<=power; i++){
		result *= value;
	}
	return result;
}


int main(int argc, char **argv)
{	
	//hard coded default values
	double energy = 20;
	double mass = 120;
	double wavenumber = 0;
	bool lab_frame = false;
	std::string frame = "rest";
	
	double c = 2.99792458e4;
	double amu = 9.314940954e8;
	
	std::cout << std::setprecision(10);
	
	//check for at least one input
	try{
		check_wavenumber(argc, argv);
	}catch(const char* msg){
		std::cerr << msg << std::endl;
		return 1;
	}
	
	//check for keywords
	for (int i=0; i<argc; i++){
		//energy
		if (strcmp(argv[i], "-E") == 0){
			try{
				check_value(i, argc, atof(argv[i+1]));
			} catch(const char* msg){
				std::cerr << msg << std::endl;
				return 1;
			}
			energy = atof(argv[i+1]);
		}
		//mass
		else if (strcmp(argv[i], "-m") == 0){
			try{
				check_value(i, argc, atof(argv[i+1]));
			} catch(const char* msg){
				std::cerr << msg << std::endl;
				return 1;
			}
			mass = atof(argv[i+1]);
		}
		//rest frame vs lab frame wavenumber
		else if(strcmp(argv[i], "-l") == 0){
			lab_frame = true;
		}
		//wavenumber
		else if(i==argc-1){
			wavenumber = atof(argv[i]);
		}
	}
	
	//check frame
	if (lab_frame){
		frame = "lab";
	}
	
	//show values being used in console
	std::cout << "Mass: " << mass << " amu, energy: " << energy << " keV, " << frame << " frame wavenumber: " << wavenumber << " cm^-1" << std::endl;
	
	//doppler shift parameters
	double beta = sqrt(1-to_power(2.0, (amu*mass)/(energy+amu*mass)));
	//double beta = (amu*mass)/(energy+amu*mass);

	double doppler = sqrt((1+beta)/(1-beta));
	
	std::cout << beta << ", " << doppler << std::endl;
	
	//convert lab to rest frame or rest to lab frame
	if (lab_frame){
		wavenumber /= doppler;
		frame = "rest";
	}else{
		wavenumber *= doppler;
		frame = "lab";
	}
	
	std::cout << "----------------------------\n" << frame << " frame wavenumber: " << wavenumber << "\n----------------------------" << std::endl;
	
	return 0;
}
