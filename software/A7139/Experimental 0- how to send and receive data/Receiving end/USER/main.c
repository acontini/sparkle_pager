#include "AT89X52.h"
#include "INTDEF.h"
#include "A7139.h"
#include "PLATFORM.h"

#define LED (P3_6) //LED��P3.6�������͵�ƽ��Ч��������
#define KEY (P3_7) //KEY��P3.7�������͵�ƽ��Ч�����£�
Uint8 idata tmpbuf[64]; //�������ڴ�Ž��յ�������
/*XTAL @11.0592*/
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
	SPIx_WriteByte(CMD_FIFO_W);//�ͳ���дFIFO��������������
	for(i=0; i <64; i++)
		SPIx_WriteByte(i+64);//�ͳ������͵�����
	SCS=1;					 //��64-127֮���������Ϊ���ն˷������ݶ�д��A7139�ڲ���FIFO�������У����������Ͷ�				      
							 //����ֻΪ��ʾ�򵥣��ʲ�ȡ��64-127֮������֣��û��������޸���Ҫ���͵ķ�������
}

void A7139_ReadFIFO(void)
{
    Uint8 i;
	StrobeCmd(CMD_RFR); //����Rx����ָ��λ��
    SCS=0;
	SPIx_WriteByte(CMD_FIFO_R);//�ͳ�����FIFO��������������
	for(i=0; i <64; i++)
		tmpbuf[i] = SPIx_ReadByte(); //��A7139�ڲ���FIFO�������ж�ȡ���ݣ��������յ������ݴ�������tmpbuf���Ա�����
	SCS=1;
}
void C51_SendData(void)
{	
	A7139_WriteFIFO();
	StrobeCmd(CMD_TX);
	while(GIO2); //ѭ���ȴ������ݷ�����Ϻ�GIO2���Ž����һ���������ź�
}
void C51_RecvData(void)
{
	StrobeCmd(CMD_RX);
	while(GIO2); //ѭ���ȴ������ݽ�����Ϻ�GIO2���Ž����һ���������ź�
	A7139_ReadFIFO();
}
void main(void)
{
	A7139_Init(433.921f); //A7139��ʼ��
	LED_Flash_Twice();//�ϵ�LED��˸2�Σ���Ϊָʾ��
	while(1)
	{
	    C51_RecvData(); 
		LED_Flash_Twice();
		C51_SendData();
	}
}


