![image-20250220215818640](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250220215818640.png)

3PWM控制6MOS管，一路PWM通过控制EG2133的H1和L1来控制连接MOS的GH1和GL1 ，进而控制电机的OUT1，由于H1和L1的共轭作用，让OUT1只有开和关两个状态，直接接电或者直接接地，芯片内部自带死区控制

![image-20250220220041120](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250220220041120.png)

![image-20250220221109078](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250220221109078.png)

由于付秒平衡，开关的频率决定了该相的对地电压

![image-20250220220515584](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250220220515584.png)

采样电流，M0_OUT1_P电流流入M0_OUT1_N电流流出，从OUT中读取电压估计电流大小，

![image-20250220223958301](C:\Users\HXZP\AppData\Roaming\Typora\typora-user-images\image-20250220223958301.png)