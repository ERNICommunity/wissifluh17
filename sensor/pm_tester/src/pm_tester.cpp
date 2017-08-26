//============================================================================
// Name        : pm_tester.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : This programm is a test to read a "nova PM sensor". The sensor
//      measures particle mater in the air.
//============================================================================

#include <iostream>
#include <fstream>

#include <unistd.h>

#include <libserialport.h>

using namespace std;

const char* desired_port = "/dev/ttyUSB0";
struct sp_port *port;

ofstream myfile;

void list_ports() {
  int i;
  struct sp_port **ports;

  sp_return error = sp_list_ports(&ports);
  if (error == SP_OK) {
    for (i = 0; ports[i]; i++) {
      printf("Found port: '%s'\n", sp_get_port_name(ports[i]));
    }
    sp_free_port_list(ports);
  } else {
    printf("No serial devices detected\n");
  }
  printf("\n");
}

void parse_serial(unsigned char *byte_buff, int byte_num) {
  //printf("%x,%x,%x,%x\n",byte_buff[3], byte_buff[2], byte_buff[5], byte_buff[4]);
  double pm25 = (double)(((int)byte_buff[3])*256 +((int)byte_buff[2]))/10;
  double pm10 = (double)(((int)byte_buff[5])*256 +((int)byte_buff[4]))/10;

  //printf("pm25:%f, pm10:%f\n", pm25, pm10);

  myfile << pm25 << "\t" << pm10 << "\n";
  myfile.flush();
}

int main() {
	cout << "!!!Hello World!!!" << endl;// prints !!!Hello World!!!

	list_ports();

	printf("Opening port '%s' \n", desired_port);
	  sp_return error = sp_get_port_by_name(desired_port,&port);
	  if (error == SP_OK) {
	    error = sp_open(port,SP_MODE_READ);
	    if (error == SP_OK) {
	      sp_set_baudrate(port,9600);
	      sp_set_stopbits (port, 1);
	      sp_set_parity (port, SP_PARITY_NONE );

	      myfile.open ("pm-data.log");
	      myfile << "pm25\tpm10\n";

	      while(true) {

	        sleep(0.5); // can do something else in mean time
	        int bytes_waiting = sp_input_waiting(port);
	        if (bytes_waiting > 0) {
//	          printf("Bytes waiting %i\n", bytes_waiting);
	          unsigned char byte_buff[512];
	          int byte_num = 0;
	          byte_num = sp_nonblocking_read(port,byte_buff,512);
	          parse_serial(byte_buff,byte_num);
	        }
	        fflush(stdout);
	      }

	      sp_close(port);

	      myfile.close();

	    } else {
	      printf("Error opening serial device\n");
	    }
	  } else {
	    printf("Error finding serial device\n");
	}

	return 0;
}
