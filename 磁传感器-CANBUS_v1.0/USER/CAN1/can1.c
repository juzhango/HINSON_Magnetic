#include "can1.h"
#include "AGV_CANBUS_HINSON_MGS160N.h"
#include "usart3.h"
#include "led.h"


/**
  * @brief  Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ42M,
  *         �������CAN_Normal_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);
  *         ������Ϊ:42M/((1+6+7)*6)=500Kbps
  * @param  tsjw: ����ͬ����Ծʱ�䵥Ԫ.
  *         @arg CAN_SJW_1tq ~ CAN_SJW_4tq: 
  * @param  tbs2: ʱ���2��ʱ�䵥Ԫ.
  *         @arg CAN_BS2_1tq ~ CAN_BS2_8tq: 
  * @param  tbs1: ʱ���1��ʱ�䵥Ԫ. 
  *         @arg CAN_BS1_1tq ~ CAN_BS1_16tq: 
  * @param  brp: �����ʷ�Ƶ��.
  *         @arg 1 ~ 1024: 
  * @param  mode: 
  *         @arg CAN_Mode_Normal: 
  *         @arg CAN_Mode_LoopBack: 
  *         @arg CAN_Mode_Silent: 
  *         @arg CAN_Mode_Silent_LoopBack: 
  * @retval 0: init ok; 1: init error
  */
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	
#if CAN1_RX0_INT_ENABLE 
   	NVIC_InitTypeDef  NVIC_InitStructure;
#endif
	
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	
	
    //��ʼ��GPIO
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��PA11,PA12
	
	  //���Ÿ���ӳ������
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11����ΪCAN1
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12����ΪCAN1
	  
  	//CAN��Ԫ����
   	CAN_InitStructure.CAN_TTCM=DISABLE;	//��ʱ�䴥��ͨ��ģʽ   
  	CAN_InitStructure.CAN_ABOM=DISABLE;	//����Զ����߹���	  
  	CAN_InitStructure.CAN_AWUM=DISABLE;//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
  	CAN_InitStructure.CAN_NART=ENABLE;	//��ֹ�����Զ����� 
  	CAN_InitStructure.CAN_RFLM=DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ�  
  	CAN_InitStructure.CAN_TXFP=DISABLE;	//���ȼ��ɱ��ı�ʶ������ 
  	CAN_InitStructure.CAN_Mode= mode;	 //ģʽ���� 
  	CAN_InitStructure.CAN_SJW=tsjw;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=tbs1; //Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2=tbs2;//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=brp;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
  	CAN_Init(CAN1, &CAN_InitStructure);   // ��ʼ��CAN1 
    
		//���ù�����
 	  CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
		
#if CAN1_RX0_INT_ENABLE
	
	  CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����.		    
  
  	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
#endif
	return 0;
}   


/**
  * @brief  
  * @param  stdId: 
  * @param  extId: 
  * @param  ide: 
  * @param  rtr: 
  * @param  *msg: 
  * @param  len: 
  * @retval 0: �ɹ�
  */
u8 CAN1_Send_Msg(uint32_t stdId, uint32_t extId, uint8_t ide, uint8_t rtr,uint8_t* msg, uint8_t len)
{
    u8 mbox;
    u16 i = 0;
    CanTxMsg TxMessage;
    TxMessage.StdId = stdId;
    TxMessage.ExtId = extId;
    TxMessage.IDE = ide;
    TxMessage.RTR = rtr;
    TxMessage.DLC = len;
    for(i = 0; i < len; i++)
        TxMessage.Data[i] = msg[i];
    mbox = CAN_Transmit(CAN1, &TxMessage);
    i = 0;
    while((CAN_TransmitStatus(CAN1, mbox) == CAN_TxStatus_Failed) && (i < 0XFFF))i++;	//�ȴ����ͽ���
    if(i >= 0XFFF)return 1;
    return 0;
}
/**
* @brief  ��������֡
  * @param  stdId: 
  * @param  *msg: 
  * @param  len: 
  * @retval 0: �ɹ�
  */
uint8_t CAN1_Send_Data_Msg(uint32_t stdId,uint8_t* msg, uint8_t len)
{
    u8 mbox;
    u16 i = 0;
    CanTxMsg TxMessage;
    TxMessage.StdId = stdId;
    TxMessage.ExtId = 0;
    TxMessage.IDE = 0;
    TxMessage.RTR = 0;
    TxMessage.DLC = len;
    for(i = 0; i < len; i++)
        TxMessage.Data[i] = msg[i];
    mbox = CAN_Transmit(CAN1, &TxMessage);
    i = 0;
    while((CAN_TransmitStatus(CAN1, mbox) == CAN_TxStatus_Failed) && (i < 0XFFF))i++;	//�ȴ����ͽ���
    if(i >= 0XFFF)return 1;
    return 0;
}

/****************************************************************************
* ��    ��: u8 CAN1_Receive_Msg(u8 *buf)
* ��    �ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;	 			     
* ���ز�����0,�����ݱ��յ�;
    		    ����,���յ����ݳ���;
* ˵    ����       
****************************************************************************/	
u8 CAN1_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
	if( CAN_MessagePending(CAN1,CAN_FIFO0)==0){printf("no msgs!");return 0;}		//û�н��յ�����,ֱ���˳� 
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
	for(i=0;i<RxMessage.DLC;i++)
	buf[i]=RxMessage.Data[i];  
	uart3SendChars(buf,RxMessage.DLC);
	return RxMessage.DLC;	
}



#if CAN1_RX0_INT_ENABLE	//ʹ��RX0��	    
void CAN1_RX0_IRQHandler(void)
{
	
	CanRxMsg RxMessage;
	CAN_Receive(CAN1, 0, &RxMessage);
	DispatchCan1ReceiveMsg(&RxMessage);		//=== USER
}
#endif
