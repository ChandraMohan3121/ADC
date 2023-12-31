#include <lpc214x.h>
void adc_init(void) {
    PINSEL1 |= 0x01000000;
    AD0CR = 0x00200402;
}
void uart_init(void) {
    PINSEL0 |= 0x00000005;
    U1LCR = 0x83;
    U1DLL = 97;
    U1DLM = 0;
    U1LCR = 0x03;
}
int main() {
    int data, val;
    float voltage; 
    adc_init();
    uart_init();
    while (1) {
        while (!(U1LSR & 0x01));
        data = U1RBR;
        if (data == 'A') {
            AD0CR |= 0x01000000; 
            while (!(AD0GDR & 0x80000000)); 
            val = (AD0GDR >> 6) & 0x3FF;    
            voltage = ((float)val / 1023.0) * 100.0;
            U1THR = (int)voltage;
            while (!(U1LSR & 0x20)); 
        }
    }
}
