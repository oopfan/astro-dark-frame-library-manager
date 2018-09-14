# astro-dark-frame-library-manager
To achieve the finest astronomy images with a telescope and uncooled CMOS camera, astrophotographers need to match the temperature of Light frames and Dark frames. The solution presented here will minimize the impact of thermal noise in your final stack and thwart the effects of Raining Noise. Furthermore it will facilitate the creation of a Darks Library which will free your time under the stars to concentrate on the acquisition of Light frames.

## Calibration frames
The process of imaging a galaxy, nebula, or star cluster is complex. It usually requires an exposure from 15 minutes to several hours or even days depending on how faint the object is. Unfortunately we can not just take a single exposure and be done. A single exposure lasting one hour is likely to be washed-out, over-exposed, and devoid of detail. One reason is due to the build up of thermal energy in the camera's imaging sensor. Fortunately there is a solution. We can divide the total exposure time into small chunks. For example we can take a total of 120 exposures of 30 seconds each for an equivalent exposure of 1 hour. In this case the thermal energy is limited to the 30-second exposure.

Astrophotographers use software to stack the individual 30-second exposures to create the final one hour exposure. But for this to succeed we need to first subtract the thermal energy out of each 30-second exposure. That is the purpose of taking Calibration Frames. A particular type of calibration frame is a Dark frame. It is taken by covering the end of the telescope with a lens cap so that no light falls on the camera sensor. We then take a 30-second exposure but not just one, many. Some say to collect a minimum of 20, some say 50 or even 100. Actually, the more the better. The reason is due to electronic noise. Everything we do with the camera generates noise. Fortunately the nature of noise is that it is random, so the more Dark frames we take the less Dark noise is injected into the final, stacked image. Unfortunately, collecting 100 Dark frames is tedious and a monumental waste of good, clear skies. Wouldn't it be great to collect Dark frames when the skies were cloudy?

The amount of thermal energy is a function of time and temperature. As time or temperature increase so does the amount of thermal energy. In other words a 30-second Dark frame taken at 70 degrees Fahrenheit is not equivalent to a 30-second Dark frame at 69 degrees Fahrenheit. During the course of an imaging session the temperature may fall 10 degrees. Many astrophotographers capture Dark frames before taking Light frames (that is, taking off the lens cap and shooting the galaxy.) That works but subtracts too much thermal energy. Some astrophotographers capture Dark frames after taking Lights. This is bad practice which leads to noisy images and Raining Noise in severe cases. The best thing is to match the temperature of the Light frame with the temperature of the Darks.

## A Preview of what you can expect with temperature-matching
This is the Bubble Nebula (NGC 7635). It is comprised of 100x 50-second exposures for a total of 83 minutes. It was taken over two consecutive nights.

Lights:
* 70.5 degrees: 1 frame
* 71.0 degrees: 22 frames
* 71.5 degrees: 48 frames
* 72.0 degrees: 4 frames
* 72.5 degrees: 69 frames

Darks:
* 70.5 degrees: 113 frames
* 71.0 degrees: 69 frames
* 71.5 degrees: 94 frames
* 72.0 degrees: 96 frames
* 72.5 degrees: 96 frames

![The Bubble Nebula with temperature matching](https://s3.amazonaws.com/oopfan-astrophotos/NGC_7635_Lum_100x50s_G100_BL20_TEMPMATCH.jpg)

Notice the creamy smoothness of the nebula and the darkness of space.

## And without temperature-matching

This is the Crescent Nebula (NGC 6888). It is comprised of 122x 45-second exposures.

175 Light frames collected between 11:17pm and 1:57am.

50 Dark frames collected in two batches: 25 frames from 10:35pm to 10:56pm, and 25 frames from 2:06am to 2:26am. They were combined into one master dark file. (This is an effective technique to average the effect of a steep temperature gradient.)

(I don't have a record of the beginning and ending temperature.)

![The Crescent Nebula without temperature matching](https://s3.amazonaws.com/oopfan-astrophotos/NGC_6888_Processed_Red_122x45s_G100_BL20_20180618_BMorgan.jpg)

Notice that the image is covered with tiny, faint speckles. Those are not stars. It is thermal noise that was injected into the image by not matching the temperature of the Lights and the Darks.

## Organizing your Dark frames
Here is how I organize them:
* Z:\
  * Astrophotography
    * Darks
      * Altair 290M
        * 50s_G100_BL20
          * temp_53.0F
          * temp_53.5F
          * temp_54.0F
          * temp_54.5F
          * temp_55.0F
          * etc...
        * 40s_G389_BL30
          * temp_53.0F
          * temp_53.5F
          * temp_54.0F
          * temp_54.5F
          * temp_55.0F
          * etc...

Notes:
* "Altair 290M" is the manufacturer and model of my camera.
* "50s_G100_BL20" is the exposure, gain, and black level settings. Notice that if you change any one of these then you need to collect a new set of Dark frames.

As far as the Library Manager application is concerned you just need to supply the *parent folder*, for example *Z:\Astrophotography\Darks\Altair290M\50s_G100_BL20* or *Z:\Astrophotography\Darks\Altair290M\40s_G389_BL30*. The application doesn't care how you organize your folders above that point. Also note that you do not need to pre-populate the *temp_xx.xF* folders. The application will lead you through that process.

## Organizing your Light frames
Here is how I organize them:
* Z:\
  * Astrophotography
    * NGC 7635
      * NGC_7635_Lum_50s_G100_BL20
        * temp_53.0F
        * temp_53.5F
        * temp_54.0F
        * temp_54.5F
        * temp_55.0F
        * etc...
    * NGC 7331
      * NGC_7331_Lum_50s_G100_BL20
        * temp_53.0F
        * temp_53.5F
        * temp_54.0F
        * temp_54.5F
        * temp_55.0F
        * etc...
      * NGC_7331_Red_50s_G100_BL20
        * temp_53.0F
        * temp_53.5F
        * temp_54.0F
        * temp_54.5F
        * temp_55.0F
        * etc...

The same Library Manager application can organize your Light frames as well as your Dark frames. Please refer to the section entitled *Organizing your Dark frames* for helpful information.

## A NodeJS application for efficiently organizing your Dark and Light frames
The application in this GitHub repository is invoked from the command line. This program is not terribly complex but it could benefit from a graphical user interface. It is written in JavaScript and thus needs NodeJS to run. (You cannot run it from the browser!)

To install NodeJS:
* Navigate to https://nodejs.org
* Download and install the current version.

To download the application code:
* Click on the "*Clone or Download*" button in GitHub.
* Select *Download ZIP*.
* Extract the ZIP. Choose any location you wish.
* Launch the Command Prompt (for Windows users) and change the directory to that location.
* Type "*npm install*" and press the Enter key. Wait a minute for all dependencies to load.
* Type "*node app.js --help*".

The application accepts three commands:
* *list-images* - Reads the input image directory and lists the file names and creation date.
* *list-temps* - Reads the temperature log file and lists the time and temperature.
* *organize* - For each image file in the input directory, looks up the temperature, and lists the shell command that will move the file into the appropriate temperature folder.
* Get help for any command by typing "*node app.js &lt;command&gt; --help*".

Commands require one or more options:
* *--in* - The path name of the input image file directory.
* *--out* - The path name of the parent output image file directory containing the child temperature directories.
* *--log* - The path name of the input temperature log file.

Up until now we have not spoken about the "*input image file directory*". It is the location where your image acquisition software (mine is [SharpCap](https://www.sharpcap.co.uk/)) stores image files. Generally speaking you will use a different computer, probably a laptop, to run the software with your telescope outdoors. At the end of the session you will likely download the files to your desktop machine where you will do image processing. Where you decide to put those files is your choice. "*--in*" must specify that path, for example:

*node app.js list-images --in="C:\SharpCap\2018-09-13\Capture\18_27_20"*

The "*--out*" option specifies the path to the output image file directory. If you are organizing Dark frames then you might say:

*--out="Z:\Astrophotography\Darks\Altair 290M\50s_G100_BL20"*

and if you are organizing Light frames then you might say:

*--out="Z:\Astrophotography\NGC 7635\NGC_7635_Lum_50s_G100_BL20"*

The "*--log*" option specifies the path to the temperature log file. This file is essential to the task of determining the name of the output temperature directory. For example:

*node app.js --list-temps --log="Z:\Astrophotography\temperaturelogs\temperaturelog-20180913.csv"*

The "*organize*" command takes all three options, for example:

*node app.js --organize --in="C:\SharpCap\2018-09-13\Capture\18_27_20" --out="Z:\Astrophotography\Darks\Altair 290M\50s_G100_BL20" --log="Z:\Astrophotography\temperaturelogs\temperaturelog-20180913.csv" > organize.bat*

Note that the order of the options is unimportant.

Also note that in the above example the standard output is redirected to a batch file. This batch file contains the actual shell commands to move the image files from the input directory to the output. If you do not redirect the output then it will go out to the console.

Depending on the *maturity* of your temperature folders some input image files may not move to the output if the temperature folder does not exist. The application will not create it for you (at least not in this version.) If this happens you will know it by observing the message "0 files moved" and by noting that the file still remains in the input directory. To remedy you need to create the appropriate temperature folder. You will know what the name should be by inspecting the output of the batch file. When completed rerun the batch file until all files are moved. Note that some files may never move if the temperature logger was not running at that time. The batch file will reflect this fact with a remark (REM).

Until you are confident with the operation of this application I recommend that you inspect the contents of the batch file before executing it. Also, make a copy of your files. The last thing you want is to lose them. I try my best to write bug-free code but I can not be liable for loss. Make sure you keep a copy of your input files on your laptop until you are confident with the result of the operation.

One last important point to make is this: Make sure to tell your acquisition software to prefix the image files with today's date since it may take several days to acquire 100+ Dark frames at a given temperature. You want to ensure that there are no name collisions. In [SharpCap](https://www.sharpcap.co.uk/) I can specify the *target*. At a minimum you should enter today's date, for example "*20180913*". I go further and say "*Darks_50s_G100_BL20_20180913*". It is up to you. You may want to follow a similar convention for Light frames, for example "*NGC_7635_Lum_50s_G100_BL20_20180904*".

## The format of the Temperature Log file
The temperature log file is expected to be a text file in comma-separated-value (CSV) format. Each line contains three values but only the first and the last are meaningful to this application:
* unixtime - The number of seconds elapsed since 00:00:00 Universal Coordinated Time (UTC) on January 1, 1970. This is the time at which the temperature was sampled.
* utc - This a text string representing the time in human readable form.
* temp - This is the temperature in Fahrenheit.

## Building a Temperature Logger using an Arduino Uno
The device that I use is the [Arduino Uno Rev3](https://store.arduino.cc/usa/arduino-uno-rev3/) with add-on products and libraries from [Adafruit](https://www.adafruit.com/). It is a self-contained unit with an SD card reader/writer for storing the temperature log file, an integrated real-time clock and coin cell battery backup, and a 1200maH LIPO battery and charger for stand-alone operation.

More information to follow.

## Using the Temperature Logger
More information to follow.

# My Kit
The cost of entry to this hobby is modest. Of course you can go crazy and spend tens of thousands of dollars but for me the total cost of what you see below is about $1500. Some people spend that much money on just the camera alone but my philosophy has always been "Do more with less."

![My Kit](https://s3.amazonaws.com/oopfan-astrophotos/My_Kit_WO71_20171207_Bmorgan.JPG)

Note that the small telescope with the red camera really is not necessary. You can do without it and save $200. The remaining camera is for imaging. It is monochrome (i.e. black-and-white.) The pancake-shaped wheel in front of it is loaded with filters on a carousel which enables me to capture in color. The mount and tripod is from a 50-year old Unitron telescope. It was a gift to me when I was a child. I added the motor last year to help with tracking stars. It allows me to take exposures up to 90 seconds in length.

# License
Copyright 2018 Brian D. Morgan

Permission to use, copy, modify, and/or distribute this software for any purpose with
or without fee is hereby granted, provided that the above copyright notice and this
permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
