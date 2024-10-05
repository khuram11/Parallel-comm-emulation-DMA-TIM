# Parallel-comm-emulation-DMA-TIM
This function emulate a parallel synchronous communication through the GPIO interface on STM32F407, using the embedded DMA IP and TIM.
properties : 
  8 bit data read from memory , 8 bit or half word write to GPIO-ODR 
  Data length upto 65536 bytes
  CLK generation using TIM_CH1 configured in PWM mode,
  DMA request on OCxREF signal
  
  
