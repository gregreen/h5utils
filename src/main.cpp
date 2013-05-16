#include <iostream>
#include <stdio.h>

#include "h5utils.h"

int main(int argc, char **argv) {
	H5::Exception::dontPrint();
	
	remove("test.h5");
	
	H5::H5File *file = H5Utils::openFile("test.h5", H5Utils::READ | H5Utils::WRITE);
	if(file == NULL) {
		std::cout << "Failed to open file." << std::endl;
		return 0;
	}
	std::cout << "Opened file!" << std::endl;
	
	H5::Group *group = H5Utils::openGroup(file, "/parent/subgroup/group");
	if(group == NULL) {
		std::cout << "Failed to open group." << std::endl;
		return 0;
	}
	std::cout << "Opened group!" << std::endl;
	
	// Write large attribute
	
	hsize_t length_ = 16300;
	float *att_data = new float[length_];
	for(unsigned int i=0; i<length_; i++) {
		att_data[i] = (float)i;
	}
	
	// Allow large attributes to be stored in dense storage, versus compact (which has 64 kB limit)
	//if(length_ > 5) {
	//	hid_t dID = dataset->getCreatePlist().getId();
	//	herr_t res = H5Pset_attr_phase_change(dID, 0, 0);
	//	std::cerr << res << std::endl;
	//	if(res < 0) {
	//		std::cerr << "Failed to specify dense storage." << std::endl;
	//	}
	//}
	
	for(int i=0; i<5; i++) {
		std::cerr << "Writing attribute ..." << std::endl;
		
		std::stringstream att_name;
		att_name << "test-att-" << i;
		
		H5::DataSpace dspace(1, &length_);
		H5::Attribute att = group->createAttribute(att_name.str().c_str(), H5::PredType::NATIVE_FLOAT, dspace);
		att.write(H5::PredType::NATIVE_FLOAT, att_data);
		
		std::cerr << "Attribute written." << std::endl;
	}
	
	delete[] att_data;
	
	delete file;
	delete group;
	
	std::cout << "Program completed." << std::endl;
	return 0;
}
