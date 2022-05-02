# rmit-eyes-arduino

Description: this is an IoT related project made by a group of students in RMIT University. the objective of the IoT stuture is to reduce Covid cases in the school by replacing a manual temperature checking with automatic temperature checking and automatic door

Components contain: Arduino Uno, MLX90614, HC-SR04, micro servo motor, a physical button

![](images/semi-design.png)

Brief ussage of each components: 
<li>MLX90614: To capture the temperature of the object; or in this case, body temperature</li>
<li>HC-SR04(Ultra Sensor): To detect the distance of the object and only record temperature data if only the object is in a certain distance</li>
<li>Micro servo: This is the automatic door that is control by the button</li>
<li>
Button: If pressed the micro servo will rotate 120 degree and if not, it goes back to 0 degree </li>

<p>library used: </p>
![](images/Libraries.png)

<p>Variables: </p>

![](images/variables.png)

<p>Setup:</p>

![](images/setup.png)

<p>Motor control Function:</p>

![](images/motorFunction.png)

<p>Calculate object distant with HC-SR04:</p>

![](images/ultraSonic.png)

<p>Return Temperature if the object is in the correct distance:</p>

![](images/printTemp.png)

<p>Loop function:</p>

![](images/loop.png)