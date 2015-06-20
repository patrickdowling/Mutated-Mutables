// Copyright 2012 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Driver for DAC.

#include "braids/drivers/dac.h"

#include <string.h>

namespace braids {
  
void Dac::Init() {
  // Initialize SS pin.
  GPIO_InitTypeDef gpio_init;
  gpio_init.GPIO_Pin = GPIO_Pin_12;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
#ifndef STM32F4XX
  gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
#else
  gpio_init.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init.GPIO_OType = GPIO_OType_PP;
  gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
#endif
  GPIO_Init(GPIOB, &gpio_init);
  
  // Initialize MOSI and SCK pins.
  gpio_init.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
#ifndef STM32F4XX
  gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
#else
  gpio_init.GPIO_Mode = GPIO_Mode_AF;
  gpio_init.GPIO_OType = GPIO_OType_PP;
  gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
#endif
  GPIO_Init(GPIOB, &gpio_init);

#ifdef STM32F4XX
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2); // SPI2_SCK
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2); // SPI2_MOSI
#endif

  // Initialize SPI
  SPI_InitTypeDef spi_init;
#ifdef STM32F4XX
  spi_init.SPI_Direction = SPI_Direction_1Line_Tx;
#else
  spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
#endif
  spi_init.SPI_Mode = SPI_Mode_Master;
  spi_init.SPI_DataSize = SPI_DataSize_16b;
  spi_init.SPI_CPOL = SPI_CPOL_High;
  spi_init.SPI_CPHA = SPI_CPHA_1Edge;
  spi_init.SPI_NSS = SPI_NSS_Soft;
  spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
  spi_init.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &spi_init);
  SPI_Cmd(SPI2, ENABLE);

#ifdef STM32F4XX
#ifdef DAC_USE_DMA
  dma_buffer_[0] = dma_buffer_[1] = 32768;

  RCC_AHB1PeriphClockCmd(DAC_DMA_CLOCK, ENABLE);

  DMA_Cmd(DAC_DMA_STREAM, DISABLE);
  DMA_DeInit(DAC_DMA_STREAM);

  dma_init_tx_.DMA_Channel = DAC_DMA_CHANNEL;
  dma_init_tx_.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR;
  dma_init_tx_.DMA_Memory0BaseAddr = (uint32_t)dma_buffer_;
  dma_init_tx_.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  dma_init_tx_.DMA_BufferSize = 2;
  dma_init_tx_.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  dma_init_tx_.DMA_MemoryInc = DMA_MemoryInc_Enable;
  dma_init_tx_.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  dma_init_tx_.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  dma_init_tx_.DMA_Mode = DMA_Mode_Normal;
  dma_init_tx_.DMA_Priority = DMA_Priority_VeryHigh;
  dma_init_tx_.DMA_FIFOMode = DMA_FIFOMode_Disable;
  dma_init_tx_.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
  dma_init_tx_.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  dma_init_tx_.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DAC_DMA_STREAM, &dma_init_tx_);

  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
  DMA_Cmd(DAC_DMA_STREAM, ENABLE);

#endif
#endif
}

}  // namespace braids
