# ball-plate-system
 Cascade PID control and Image Processing

Made a cricket control system with K60, STM32 single-chip microcomputer, 6 axis motion processing module, camera and two servos.

K60 single-chip microcomputer is used for image processing and STM32 single-chip microcomputer is used for controling hardware.

Used cascade PID control include motor position as inner ring and angle as outer ring.

# 板球控制系统
关键词：串级PID控制、图像处理

基于K60、STM33单片机，六轴加速度传感器，摄像头，舵机等。

K60单片机用于图像处理，主要包括滤波、二值化、螺旋式搜索算法等。

STM32单片机用于卡尔曼滤波、控制电机等。

内环为电机位置环，外环为角度环
