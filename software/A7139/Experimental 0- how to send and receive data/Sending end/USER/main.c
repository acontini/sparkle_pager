#include "AT89X52.h"
#include "A7139.h"
#include "INTDEF.h"
#include "PLATFORM.h"

#define LED (P3_6) //LED��P3.6�������͵�ƽ��Ч��������
#define KEY (P3_7) //KEY��P3.7�������͵�ƽ��Ч�����£�
Uint8 idata tmpbuf[64]; //�������ڴ�Ž��յ�������

/*XTAL @11.0592 Baud @9600*/
static void UART_Init(void)
{
	SM0 =  0x00;          
	SM1 =  0x01;
	REN =  0x01;
	TMOD = 0x20;     
	TH1 =  0xfD;
	TL1 =  0xfD;
	TR1 =  0x01;
	ES =   0x01;                                       
}
/*XTAL @11.0592 */
static void LED_Flash_Twice(void)
{
	LED=0;
	Delay10ms(2);
	LED=1;
	Delay10ms(2);
	LED=0;
	Delay10ms(2);
	LED=1;
}

void A7139_WriteFIFO(void)
{
	Uint8 i;
	StrobeCmd(CMD_TFR);	//����Tx����ָ��λ��	
    SCS=0;
	SPIx_WriteByte(CMD_FIFO_W);	//�ͳ���дFIFO��������������
	for(i=0; i <64; i++)
		SPIx_WriteByte(i); //��0-63֮���������Ϊ���������ݶ�д��A7139�ڲ���FIFO�������У����͸����ն�
	SCS=1;				   //����ֻΪ��ʾ�򵥣��ʲ�ȡ��0-7֮������֣��û��������޸���Ҫ���͵���������
}

void A7139_ReadFIFO(void)
{
    Uint8 i;
	StrobeCmd(CMD_RFR);	//����Rx����ָ��λ��	
    SCS=0;
	SPIx_WriteByte(CMD_FIFO_R);	 //�ͳ�����FIFO��������������
	for(i=0; i <64; i++)
		tmpbuf[i] = SPIx_ReadByte(); //��A7139�ڲ���FIFO�������ж�ȡ���ݣ��������յ������ݴ�������tmpbuf���Ա�����
	SCS=1;							 
}
void C51_SendData(void)
{
	A7139_WriteFIFO();
	StrobeCmd(CMD_TX);
	while(GIO2); //ѭ���ȴ�ֱ�����ݷ�����ϣ�GIO2���Ž����һ���������ź�
}
void C51_RecvData(void)
{
	StrobeCmd(CMD_RX);
	while(GIO2); //ѭ���ȴ�ֱ�����ݽ�����ϣ�GIO2���Ž����һ���������ź�
	A7139_ReadFIFO();
}

void main(void)
{
	Uint8 i;
	UART_Init(); //���ڳ�ʼ��
	A7139_Init(433.921f); //A7139��ʼ��
	LED_Flash_Twice();	 //�ϵ�LED��˸2�Σ���Ϊָʾ��
	while(1)
	{
		if(!KEY)
		{
			Delay10ms(1);
			if(!KEY)
			{
				LED = 0;
				C51_SendData();	   //��������
				LED = 1;
				C51_RecvData();	   //ѭ���������ݣ�ֱ���������
				LED_Flash_Twice(); 
				for(i=0;i<64;i++)   //�����յ��ķ�������ͨ�����ڴ�ӡ�������û���ͨ��PC�˵Ĵ������ֲ鿴
				{
					SBUF = tmpbuf[i]; //���ӽ��ն˴��õ���������ͨ�����ڴ�ӡ����
					while(!TI);		  
					TI=0;			  //����ӦΪ0x40-0x7F������64�ֽ�
				}
			}
		}
	}
}


