#include "SmartCar_Isr.h"





            /*spi�й�dma�ж�*/
IFX_INTERRUPT(qspi0DmaTxISR, 0, IFX_INTPRIO_DMA_CH1 )
{
    //IfxCpu_enableInterrupts();//�����ж�Ƕ��
    IfxQspi_SpiMaster_isrDmaTransmit(&oled_spi);
}

IFX_INTERRUPT(qspi0DmaRxISR, 0, IFX_INTPRIO_DMA_CH2)
{
    //IfxCpu_enableInterrupts();//�����ж�Ƕ��
    IfxQspi_SpiMaster_isrDmaReceive(&oled_spi);
}

IFX_INTERRUPT(qspi0ErISR, 0, IFX_INTPRIO_QSPI0_ER)
{
    IfxCpu_enableInterrupts();//�����ж�Ƕ��
    IfxQspi_SpiMaster_isrError(&oled_spi);

    // Process errors. Eg: parity Error is checked below
    //IfxQspi_SpiMaster_Channel *chHandle   = IfxQspi_SpiMaster_activeChannel(&my_spi);
//    if( chHandle->errorFlags.parityError == 1)
//    {
//        // Parity Error
//    }
}

