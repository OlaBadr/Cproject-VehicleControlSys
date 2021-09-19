#include <stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1

char first_menu_fn(void);
char second_menu_fn ( char *light,  float *room, float *eng);


//i,j,k is used to check if light_traffic,room_temp and engine_temp have values from sensors or not
char i=-1,j=-1;

#if WITH_ENGINE_TEMP_CONTROLLER
    char k=-1;
#else
    char k=0;
#endif

int main (void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);


 char first_menu , second_menu , light_traffic =-1 ;
 float room_temp=-1 , engine_temp=-1;

 char *ptr_light = &light_traffic;
 float *ptr_room = &room_temp;
 float *ptr_eng = &engine_temp;

short vehicle_speed ;
char eng_state ,AC, eng_controller;


while (1)
{
	first_menu = first_menu_fn();
	if (first_menu == 0) //quit the program
		break;
	else
		eng_state =1; //Engine is ON

while (i+j+k <0)
    {

	second_menu = second_menu_fn(ptr_light,ptr_room,ptr_eng);

	if (second_menu == 0) //return to first menu
		break;

    //================modify vehicle state=================


	if (light_traffic == 'R')
		vehicle_speed=0;
	else if (light_traffic == 'O')
		vehicle_speed=30;
	else if (light_traffic == 'G')
		vehicle_speed=100;


	if (room_temp < 10 )
	{ AC = 1; //ON
	room_temp = 20;}

	else if (room_temp > 30 )
	{ AC = 1; //ON
	room_temp = 20;}

	else
		AC = 0; //OFF


#if WITH_ENGINE_TEMP_CONTROLLER

	if (engine_temp < 100)
	{eng_controller = 1; //ON
	engine_temp = 125;}

	else if (engine_temp > 150 )
	{ eng_controller = 1; //ON
	engine_temp = 125;}

	else
	    eng_controller = 0; //OFF


	if(vehicle_speed==30)
	{
		eng_controller = 1; //ON
		engine_temp = ((float)engine_temp*(1.25)) + 1.00;
	}
#endif


	if(vehicle_speed==30)
	{
	AC = 1; //ON
	room_temp = ((float)room_temp*(1.25)) + 1.00;}

	//===============Print Current State================

	printf("\n*****Current Vehicle State*****\n");
	if(eng_state == 1)
	     printf("i.Engine State: ON\n");
	else
		printf("i.Engine State: OFF\n");

	if(AC==1)
		printf("ii.AC: ON\n");
	else
		printf("ii.AC: OFF\n");

	printf("iii.Vehicle Speed = %d km/h\n",vehicle_speed);
	printf("iv.Room Temperature =%0.2f C\n",room_temp);

	#if WITH_ENGINE_TEMP_CONTROLLER
	if (eng_controller == 1)
		printf("v.Engine Temperature Controller State: ON\n");
	else
		printf("v.Engine Temperature Controller State: OFF\n");

	printf("vi.Engine Temperature=%0.2f C\n\n",engine_temp);
	#endif


     }



if (i+j+k <0)
	continue;
else
	break;


}

if(first_menu == 0){
	printf("********Program Ended********");
	return 0;}



return 0;
}

char first_menu_fn(void)

{
	unsigned char first_menu;
	while (1)
	{

	//First Menu
	printf("\t Welcome! \n What do you want to do? \n ( please choose from a,b or c)\n");
	printf("a.Turn on the vehicle engine\n");
	printf("b.Turn off the vehicle engine\n");
	printf("c.Quit the system\n");
	scanf(" %c",&first_menu);

	if (first_menu == 'c'){
		printf("Quit the system\n\n");
		return 0;
		}

	else if (first_menu == 'a'){
		break;
	}

	else{
		printf("Turn off the vehicle engine\n\n");
	    continue;}

     }

	return 1;
}

char second_menu_fn ( char *light, float *room, float *eng){

	unsigned char option=0;

	printf("\t Sensors set menu \n\t (choose from a,b,c or d)\n");
	printf("a.Turn off the engine\n");
	printf("b.Set the traffic light color\n");
	printf("c.Set the room temperature (Temperature Sensor)\n");

#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d.Set the engine temperature (Engine Temperature Sensor)\n");
#endif

	scanf(" %c",&option);

	if (option == 'b')
	{ printf("Enter the required color:\n");
		scanf(" %c",&(*light));
	i=0;
		}

	else if(option == 'c')
	{ printf("Enter room temperature:\n");
		scanf(" %f",&(*room));
	j=0;
		}

#if WITH_ENGINE_TEMP_CONTROLLER
	else if (option == 'd')
	{ printf("Enter Engine temperature:\n");
		scanf(" %f",&(*eng));
	k=0;
		}
#endif

	else if (option =='a' )
		{ printf("\nTurn off the engine\n");
		return 0;}



return 1;

}

