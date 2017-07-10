#include "nRF24L01.h" 
 	
uchar TX_ADDRESS[TX_ADR_WIDTH]={0xB2,0x52,0xF4,0x09,0x71}; //���͵�ַ
uchar RX_ADDRESS[RX_ADR_WIDTH]={0xB1,0x51,0xF3,0x08,0x70}; //���յ�ַ

uchar    rate = 0x0F;    //2Mbs, 0dB  ���������濪��
uchar    speed = 0x00;

sbit    KEY_up      =P0^0;			
sbit    KEY_down    =P0^2;			

sbit    LKEY_up     =P2^2;			
sbit    LKEY_down   =P2^3;

sbit    action      =P0^1;



sbit    LED1      =P0^7;				//	  ǰ���İ����ӿ�  �����Լ����Ӿ���
sbit    LED2      =P0^6;				//	  ǰ���İ����ӿ�  �����Լ����Ӿ���
sbit    LED3      =P0^5;	
uchar rece_buf[32];							//���ռĴ���

void delay(uint t)
{
	uint a,b;
	for(a=0;a<t;a++)
		for (b=0;b<255;b++);
}
void main()
{	int i;
	P0|=0x0f;	//���߰�������
	P2|=0x0f;

	while(NRF24L01_Check());//�ȴ���⵽NRF24L01������Ż�����ִ��
	NRF24L01_RT_Init(TX_PLOAD_WIDTH,TX_ADDRESS,TX_ADR_WIDTH,RX_ADDRESS,RX_ADR_WIDTH,rate);
	for(i=0;i<12;i++)
	{
			delay(100);	
			LED1=~LED1;
	}
	LED1=1;
  LED2=0;
	LED3=1;
				
	while(1)
	{
		if((KEY_up==0)||(KEY_down==0)||(LKEY_up==0)||(LKEY_down==0)||(action==0))
		{
			delay(10);
			LED1=0;
		  LED2=1;
			LED3=0;
			if(KEY_up==0)						
			{
				rece_buf[0]=1;//һ��Ҫ����2���ֽڣ�rece_buf[0]=1
				while(!KEY_up);	  
				speed +=10;
				if(speed>=80)
					speed=80;
				rece_buf[1]= speed;
				SEND_BUF(rece_buf);
				
			   delay(10);		
			}
			else if(KEY_down==0)			  			
			{
				rece_buf[0]=1;	   				
				while(!KEY_down);  	
				speed -=10;
				if(speed<=0)
					speed = 0;
				rece_buf[1]= speed;
				SEND_BUF(rece_buf);
				delay(10);
			}
			else if(LKEY_up==0)			  				
			{
				rece_buf[0]=1;	  //һ��Ҫ����2���ֽڣ�rece_buf[0]=1
				while(!KEY_up);	 
				speed ++;
				if(speed>=80)
					speed=80;
				rece_buf[1]= speed;
				SEND_BUF(rece_buf);
			  delay(10);				
			}
			else if(LKEY_down==0)			  				
			{
				rece_buf[0]=1;	   				
				while(!KEY_down);  
				speed --;
				if(speed<=0)
					speed = 0;
				rece_buf[1]= speed;
				SEND_BUF(rece_buf);
				delay(10);			
			}
			else if(action==0)			  				
			{
				rece_buf[0]=1;	   //һ��Ҫ����2���ֽڣ�rece_buf[0]=1
				while(!KEY_up);	  
				speed = 0;
				rece_buf[1]= speed;
				SEND_BUF(rece_buf);
			   delay(10);				
			}								
		}
		else			  				
		{
			LED1=1;
		  LED2=0;
			LED3=1;			
		}

	}
}


