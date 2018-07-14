Data was collected using commit `cbe28079ba94519dbe33b98c67d5848d1041f939` version of the code.
In this version of the code, sending a 'd' across the USART causes the program to dump its 1000 samples of ADC data in hex.

So I ran this in one terminal:
```
cat /dev/ttyUSB0 > data0
```
and opened up picocom in another and pressed 'd'

There's probably a better way to do it but this works well enough
