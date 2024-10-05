void Parallel_Transmit_DMA_TIM(uint8_t *SrcBuff, volatile uint32_t *GPIO_ODR,
		uint16_t length) {
	assert(length < 65536);

	// set direction of GPIO[7:0} as output.
	GPIOB->MODER = 0b0101010101010101;

	//disable the stream by clearing EN in SCR registers

	uint32_t RegData = DMA2_Stream1->CR;
	if ((RegData & 0b1)) {
		DMA2_Stream1->CR = RegData & ~0b1;
		while (DMA2_Stream1->CR & 0b1)
			;
	}

	//Set the peripheral port register address in the DMA_SxPAR register
	DMA2_Stream1->M0AR = (uint32_t) SrcBuff;
	DMA2_Stream1->PAR = (uint32_t) GPIO_ODR;
	DMA2_Stream1->NDTR = 18;
	//select DMA request Channel
	DMA2_Stream1->CR |= 11 << 25;
	DMA2_Stream1->CR &= ~(1 << 25);
	// set the priority of the stream
	DMA2_Stream1->CR &= ~(0b11 << 15); // check this
	//Set the direction mem to pheripheral
	DMA2_Stream1->CR |= 1 << 6;
	DMA2_Stream1->CR &= ~(1 << 7);
	//set the size
	DMA2_Stream1->CR &= ~(0b1111 << 11);
	//set the increment
	DMA2_Stream1->CR |= 1 << 10; // increment the memory address
	DMA2_Stream1->CR &= ~(1 << 9); // keep the mem address fixed

	// Enable the DMA stream
	DMA2_Stream1->CR |= 1;
	TIM1->DIER |= 0b1 << 9;

}
