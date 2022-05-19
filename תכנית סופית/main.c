//25/04/2021
#include "initsys.h"

#include "Isd4004Spi.h"
#include "fingerprint.h"
extern  PageID;

sbit sensorDOOR =P2^1;

void Init_Device(void);
void MenuScreen();

void servo(unsigned int Width)  //P1.0
{
	if(Width>2300) Width=2300;
	if(Width<700) Width=700;
	Width=-4*Width;

	PCA0CPL0= Width;
	PCA0CPH0= Width>>8;	
}


void main(void)
{
	S16 x=0, y=0,  ButtonNum;
	Init_Device();
	initSYS();

	MenuScreen();
	PCA0CN    = 0x40;
	servo(2300);
  delay_ms(2000);
	PCA0CN    = 0x00;
	while(1) {
		if(!T_IRQ) {
			delay_ms(10);
			x = ReadTouchX();
			y = ReadTouchY();
			ButtonNum= ButtonTouch(x, y);
			if(ButtonNum==1){ 
				LCD_fillScreen(BLACK);		
				LCD_print2C(20,150,"Record1 ",3,WHITE,BLACK);				
				Record(0);
				LCD_print2C(20,150,"Play1 ",3,WHITE,BLACK);			
				PlayI(0);
				MenuScreen();
			}
			else if(ButtonNum==2){ 
				LCD_fillScreen(BLACK);		
				LCD_print2C(20,150,"Record2 ",3,WHITE,BLACK);				
				Record(100);
				LCD_print2C(20,150,"Play2 ",3,WHITE,BLACK);			
				PlayI(100);
				MenuScreen();
			}
			else if(ButtonNum==3){
				LCD_fillScreen(BLACK);		
				LCD_print2C( 20,150,"Record3 ",3,WHITE,BLACK);				
				Record(200);
				LCD_print2C(20,150,"Play3  ",3,WHITE,BLACK);			
				PlayI(200);
				MenuScreen();		
			}
			else if(ButtonNum==4) {
				LCD_fillScreen(BLACK);		
				LCD_print2C(20,150,"Record4 ",3,WHITE,BLACK);				
				Record(300);
				LCD_print2C(20,150,"Play4 ",3,WHITE,BLACK);			
				PlayI(300);
				MenuScreen();
			}

			else if(ButtonNum==5) {
				LCD_fillScreen(BLACK);		
				LCD_print2C(20,150,"Record5 ",3,WHITE,BLACK);				
				Record(400);
				LCD_print2C(20,150,"Play5 ",3,WHITE,BLACK);			
				PlayI(400);
				MenuScreen();
			}
			else if(ButtonNum==6) {
				LCD_fillScreen(BLACK);		
				LCD_print2C(20,150,"SERVO ",3,WHITE,BLACK);
				PCA0CN    = 0x40;
				servo(700);
				delay_ms(2000);
				LCD_print2C(20,150,"SERVO ",3,WHITE,BLACK);		
				servo(2300);
				delay_ms(2000);
				PCA0CN    = 0x00;
				MenuScreen();
			}
			else if(ButtonNum==7) {
				LCD_fillScreen(BLACK);	
				LCD_print2C(20,150,"Blu  ",3,WHITE,BLACK);
				LCD_print2C(20,150,"Send SMS  ",3,WHITE,BLACK);	
				PlayI(0);
				SetTarget(1); // uart
				printf("**0532255630");
				delay_ms(1000);
				printf("##Attempted hacking");
				delay_ms(1000);
				printf("$$");
				delay_ms(1000);
				printf("**0544784787");
				delay_ms(1000);
				printf("##Attempeted vault hacking");
				delay_ms(1000);
				printf("$$");

				MenuScreen();
			}

			else if(ButtonNum==8){
				LCD_fillScreen(BLACK);	
				LCD_print2C(20,150,"Finger  ",3,WHITE,BLACK);
				if(FindFinger())
				{
					LCD_setCursor (25, 50);
					printf("id=%d      ",(int)PageID);
					//PlayI(100);
				}
				else{
					printf("error not find  "); 
				}
				while(T_IRQ);	
				MenuScreen();
			}

			else if(ButtonNum==9){
				LCD_fillScreen(BLACK);	
				LCD_print2C(20,150,"Finger  ",3,WHITE,BLACK);
				if(FindFinger())
				{
					LCD_setCursor (25, 50);
					printf("id=%d      ",(int)PageID);
					if(PageID==0) 
						PlayI(200);
					else if(PageID==2) 
						PlayI(300);
					else
						PlayI(100); 

					PCA0CN    = 0x40;
					servo(700);
					LCD_print2C(20,150,"open ",3,WHITE,BLACK);	
					delay_ms(2000);
					while(sensorDOOR==0);//no hand
					delay_ms(1);
					//printf("sensorDOOR =%d ",sensorDOOR);
					while(sensorDOOR==1);// hand
					//printf("sensorDOOR =%d ",sensorDOOR);
					delay_ms(2000);
					servo(2300);
					LCD_print2C(20,150,"close ",3,WHITE,BLACK);
					delay_ms(2000);
					PCA0CN    = 0x00;
					

				}
				else{
					printf("error not find  "); 
					PlayI(0);
					SetTarget(1); // uart
					printf("**0544784787");
					delay_ms(1000);
					printf("##Attempted vault hacking");
					delay_ms(1000);
					printf("$$");
					SetTarget(0); // uart
				}
				while(T_IRQ);	
				MenuScreen();
			}
		}	
	}
}

void MenuScreen() {
	LCD_fillScreen(BLACK);
	LCD_print2C(20,30,"project steve&elior",3,WHITE,BLACK);
	LCD_clearButton();	
	LCD_drawButton(1,10,  80,60,60, 10, RED,WHITE,"Rec1",2);
	LCD_drawButton(2,80, 80,60,60, 10, BLUE,YELLOW,"Rec2",2);
	LCD_drawButton(3,150, 80,60,60, 10, GREEN,BLACK,"Rec3",2);
	LCD_drawButton(4,220, 80,60,60, 10, YELLOW,BLACK,"Rec4",2);
	LCD_drawButton(5,290, 80,60,60, 10, GRAY,BLACK,"Rec5",2);
	LCD_drawButton(6,10, 200,60,60, 10, YELLOW,BLACK,"SERVO",2);
	LCD_drawButton(7,80, 200,60,60, 10, BLUE,WHITE,"blu ",2);
	LCD_drawButton(8,150, 200,60,60, 10, RED,BLACK,"finger ",2);
	LCD_drawButton(9,220, 200,60,60, 10, YELLOW,BLACK,"run ",2);
	LCD_setText2Color(WHITE,BLACK);
}




