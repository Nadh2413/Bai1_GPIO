#include <stdint.h>

//Define  Logic GPIO PIN ---------------------
#define GPIO_PIN_SET 	1
#define GPIO_PIN_RESET 	0
#define GPIO_PIN_LOW	0
#define GPIO_PIN_HIGH	1

//define GPIO PIN ------
#define LED_GPIO_PORT	GPIOA
#define LED_GPIO_PIN	GPIP_Pin_5
#define LED_PIN5	5
#define LEDControl_SetClock		RCC_AHB1Periph_GPIOA

#define BUTTON_GPIO_PORT	GPIOC
#define BUTTON_GPIO_PIN		GPIO_Pin_13
#define BUTTON_PIN13		13
#define BUTTONControl_SetClock 	RCC_AHB1Periph_GPIOC

static
void Led_Init(void)
{

	//0eclare type variable GPIO Struct-
	GPIO_InitTypeDef GPIO_InitStructure;

	//Enable Clock GPTOA--
	RCC_AHB1PeriphClockCmd(LEDControl_SetClock, ENABLE);


	//Choose Pin Led-' -
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;

	//Choose Pin Led as Out-
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

	//Choose Speed Pin-
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//Select type-' -
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	//Select status
	GPIO_InitStructure.GPIO_PuPd = GPTO PuPd_DOWN ;

	//The function initializes all of the above values--
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

}

//Chan PC13 dieu khien button *****

static
void Button_Init(void)
{
	//0eclare type variable GPIO Struc-
	GPIO_InitTypeDef GPIO_InitStructure ;

	//Enable Clock GPI0C--
	RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock, ENABLE);

	//Choose Pin BUTTON--
	GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;

	//Choose Pin Led as Input--
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;

	//Choose Speed Pin-
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//Select status -
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	//The function initializes a11 of the above values
	GPIO_Init(BUTTON_GPIO_PORT, &GP10_InitStructure);
}

//Dieu  khien LED  thanh ghi
static
void LedControl_SetStatus(GPIO_TypeDef * GPIOx, uint8_t GPIO_PIN, uint8_t Status)
{
//	Set bit in BSRR Register
	if(Status == GPIO_PIN_SET){
		GPIOx->BSRRL |= 1 << GPIO_PIN;
	}
//	Reset bit in BSRR Register
	if(Status == GPIO_PIN_RESET){
		GPIOx->BSRRH |= 1 << GPIO_PIN;
	}
}

//Read Button Value
static
uint8_t ButtonRead_Status(GPIO_TypeDef * GPIOx, uint32_t GPIO_PIN)
{
	uint32_t Read_Pin;
//	Read bit in IDR register
	Read_Pin = (GPIOx->IDR) >> GPIO_PIN;
	Read_Pin = Read_Pin & 0x01;

	return Read_Pin;
}

int main(void)
{
    // Initialize the LED and button pins
    Led_Init();
    Button_Init();

    // Loop forever
    while(1)
    {
        // Read the button state
        uint8_t buttonState = ButtonRead_Status(BUTTON_GPIO_PORT, BUTTON_PIN13);

        // Toggle the LED state if the button is pressed
        if(buttonState == GPIO_PIN_RESET)
        {
            static uint8_t ledState = GPIO_PIN_RESET; // Static variable to keep track of the LED state
            ledState = (ledState == GPIO_PIN_RESET) ? GPIO_PIN_SET : GPIO_PIN_RESET; // Toggle the LED state
            LedControl_SetStatus(LED_GPIO_PORT, LED_PIN5, ledState);
        }
    }
}
