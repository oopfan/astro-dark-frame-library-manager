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

## Building a Dark frame library
More information to follow.
