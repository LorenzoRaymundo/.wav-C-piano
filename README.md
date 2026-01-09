#🎹 .wav-C-piano
Code for the .wav exercise project of my 3rd grade class.

## What is consists of?
It consists of learning the basics of .wav file creation, meaning it's more approachable to the low level. I needed to create the header meta-data, and deal with the content of the audio reading raw bytes of data.

It basically contains 4 options:
1. Play the sample audio
2. Extract one determined part of the audio
3. Change the volume
4. Play piano with the keyboard (the coolest)

To play the piano, I made the program to generate all 7 musical notes trought a sine wave in a standard "la" reference frequency of 440hz. I also added a decayment euler equation to simulate the volume being lowered down to the 4sec of a string musical instrument like the piano.
