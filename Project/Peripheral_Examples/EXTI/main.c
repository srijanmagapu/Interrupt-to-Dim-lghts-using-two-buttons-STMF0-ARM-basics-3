
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

void EXTI0_Config(void);

volatile unsigned short Var;

volatile int c;

 volatile int dim = 10;
GPIO_InitTypeDef GPIO_InitStructure;
static __IO uint32_t TimingDelay;


/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);


int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
      
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);     
  
  //BUTTON_USER = GPIO_Pin_0
  GPIO_InitStructure.GPIO_Pin = BUTTON_USER;                     //GPIO intitialized and Pin 0 is set
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                  // Pin 0 is set as input
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;                // Pull Down
  GPIO_Init(GPIOA, &GPIO_InitStructure);

//  while(1) { Var = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);}
  /* Initialize LEDs mounted on STM32F0-Discovery kit */
  STM_EVAL_LEDInit(LED3);                               //light initiateLEd3
  STM_EVAL_LEDInit(LED4);                               //light inititateLED4

 if (SysTick_Config(SystemCoreClock / 200))            //interrupt routing 5ms
  { 
    /* Capture error */ 
    while (1);
  }
  /* Infinite loop */
  while (1){
        // while(Var != 0xFFFF)
     // ;
 
    while(Var != 0xFFFF)                        //when var is not equal to 1
      ;
    
    if(++dim >= 10){                            //increment the existing value of dim and check if >=10 then dim = 0
    dim = 0;
    }
    
    while(Var != 0x0000)                        //until Var is not equal to 0
      ;
  }
    }

/**
  * @brief  Configure PA0 in interrupt mode
  * @param  None
  * @retval None
  */
void EXTI0_Config(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  
  /* Enable GPIOA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   

  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Connect EXTI0 Line to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI0 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
