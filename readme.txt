/*
===========================================================================================================
RS232 LED Lights Basics (Web Control)
===========================================================================================================
@package        RS232 LED Light (Web Control)
@copyright      Copyright (C) 2018. Benjamin Lu
@license        GNU General Public License v2 or later (http://www.gnu.org/licenses/gpl-2.0.html)
@author         Benjamin Lu (https://www.benjlu.com/)
===========================================================================================================
*/

/*
===========================================================================================================
Description
===========================================================================================================
This project deals with using RS232 as input to control the Web Interface to control LED Lights. 
===========================================================================================================
*/

/*
===========================================================================================================
Usage
===========================================================================================================
Please make sure that you have connected the correct LED with 220ohm register and pin to 3 as output. When uploaded, you will need to connect COM1 by using putty to read the information tht comes with this project. This will then initialize and give you an IP address that you can use to load the web page. Once the web page has loaded, it will asked you to enter 1 to turn on LED and 2 to turn off the LED. Please note that there's no right way to reload the page to make the LED to turn on and off. When you press 1 and enter, you will need to refresh the page so that the input that you enter will become active and the LED will turn off and press 2 to turn off. 
===========================================================================================================
*/