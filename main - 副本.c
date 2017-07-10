#include "nRF24L01.h" 
 	
uchar TX_ADDRESS[TX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //���͵�ַ
uchar RX_ADDRESS[RX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //���յ�ַ

uchar   rate = 0x0F;    //2Mbs, 0dB  ���������濪��


sbit    KEY_up      =P2^1;			
sbit    KEY_down    =P2^2;			
sbit    KEY_left    =P2^3;				
sbit    KEY_right   =P2^0;

sbit    lKEY_up     =P2^4;			
sbit    lKEY_down   =P2^5;



sbit    LED1      =P3^7;				//	  ǰ���İ����ӿ�  �����Լ����Ӿ���
sbit    LED2      =P3^3;				//	  ǰ���İ����ӿ�  �����Լ����Ӿ���
	
uchar rece_buf[32];							//���ռĴ���

void Forward()
{
	P1=0xaa;	//10101010
}

void Back()
{
	P1=0x55;	//01010101
}

void Turn_left()
{
	P1=0xa5;	//10100101
}

void Turn_right()
{
	P1=0x5a;	//01011010
}

void Stop()
{
	P1=0x00;
}

void delay(uint t)
{
	uint a,b;
	for(a=0;a<t;a++)
		for (b=0;b<255;b++);
}
void main()
{
	LED1=0;
	LED2=0;
	while(NRF24L01_Check());                    //�ȴ���⵽NRF24L01������Ż�����ִ��
	NRF24L01_RT_Init(TX_PLOAD_WIDTH,TX_ADDRESS,TX_ADR_WIDTH,RX_ADDRESS,RX_ADR_WIDTH,rate);			
	while(1)
	{
 //	**************************************
//		if(KEY_up==0||KEY_down==0||KEY_left==0||KEY_right==0||lKEY_up==0||lKEY_down==0)
//		{
//			LED1=1;
//			if(KEY_up==0)						
//			{
//				rece_buf[1]='1';
//				rece_buf[0]=1;	   					//һ��Ҫ����1���ֽڣ�rece_buf[0]=1
//				while(!KEY_up)
//					SEND_BUF(rece_buf);	
//			}
//			if(KEY_down==0)			  			
//			{
//				rece_buf[1]='2';
//				rece_buf[0]=1;	   				
//				while(!KEY_down)
//					SEND_BUF(rece_buf);	
//			}
//			if(KEY_left==0)			  				
//			{
//				rece_buf[1]='3';
//				rece_buf[0]=1;	   				
//				while(!KEY_left)
//					SEND_BUF(rece_buf);		
//			}
//			if(KEY_right==0)			  				
//			{
//				rece_buf[1]='4';
//				rece_buf[0]=1;	   				
//				while(!KEY_right)
//					SEND_BUF(rece_buf);		
//			}
//			if(lKEY_up==0)						
//			{
//				rece_buf[1]='5';
//				rece_buf[0]=1;	   					//һ��Ҫ����1���ֽڣ�rece_buf[0]=1
//				while(!lKEY_up)
//					SEND_BUF(rece_buf);	
//			}
//			if(lKEY_down==0)			  			
//			{
//				rece_buf[1]='6';
//				rece_buf[0]=1;	   				
//				while(!lKEY_down)
//					SEND_BUF(rece_buf);	
//			}
//
//
//			LED1=0;
//		}
////		else			  				
////		{
////			LED1=0;
////			rece_buf[1]='5';
////			rece_buf[0]=1;	   				
////			SEND_BUF(rece_buf);				
////		}

//**************************************************
		if(NRF_IRQ==0)	 	// �������ģ����յ�����
		{		
			
			if(NRF24L01_RxPacket(rece_buf)==0)
			{	
				if(rece_buf[1]=='1')		   	//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
				{
					LED2=1;
					Forward(); 
				}
				else if(rece_buf[1]=='2')	 		//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
				{
					LED2=1;
					Back();
				}
				else if(rece_buf[1]=='3')	 		//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
				{
					LED2=1;
					Turn_left();
				}	
				else if(rece_buf[1]=='4')	 		//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
				{
					LED2=1;
					Turn_right();
				}
				
				else if(rece_buf[1]=='5')		   	//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
				{
					LED2=1;
					Forward();
					delay(100);
					P1=0x00;
				   	delay(20);
				}
				else if(rece_buf[1]=='6')	 		//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
				{
					LED2=1;
					Back();
					delay(100);
					P1=0x00;
				   	delay(20);
				}
				else//if(	rece_buf[1]=='5')	 		//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
				{
					Stop();
				}
				
				delay(10);
			}
		}
		else 	
		{
			LED2=0;
			Stop();
		}

//**************************************		
	}
}



