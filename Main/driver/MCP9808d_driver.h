#ifndef MCP9808_DRIVER
#define MCP9808_DRIVER


enum MCP9808_Pointer_bits
{
	Read_Only = 0,   //Read only register
	CONFIG = 1,   //Configuration register
	Tupper = 2,      //Alert Temperature Upper Boundary Tip register
	Tlower = 3,      //Alert Temperature Lower Boundary Tip register
	Tcrit = 4,      //Critical Temperature Trip register
	Ta = 5,       //Temperature register
	Manuf_id = 6,    //Manufacturer ID register 
	Dev_Id = 7,      //Device ID
	Resol_reg = 8   //Resolution register
};

float ReadTemp(void); //Read Temperature function

#endif
