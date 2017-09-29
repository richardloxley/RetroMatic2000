# RetroMatic2000

The "RetroMatic 2000" is a box I made (in part for the [Retro Challenge](http://www.retrochallenge.org/) in April 2017) to allow me to use my collection of 1980s computers with more modern accessories.

It comprises:

* a HD9800 RGB->VGA convertor board (a clone of the GBS8200)
* a scanline generator
* a Gotek floppy drive emulator (flashed with HxC firmware) with extra LCD display
* an Arduino to reprogram the HD9800 to accept 288p (non-interlaced) input
* an LCD and rotary encoder to control the Arduino and scanline generator via menus
* an additional rotary encoder to control the Gotek hardware (via the Arduino)

At the time of writing it is mostly finished, but the software is still a work in progress.  In particular the menus for controlling the scanline generator, and different modes on the HD9800, are incomplete.

The reprogramming of the TV5725 chip on the HD9800 is based on code from [mybook4/GBS_Control](https://github.com/mybook4/DigisparkSketches/tree/master/GBS_Control), which I believe was itself based on [dooklink/gbs-control](https://github.com/dooklink/gbs-control).

I haven't got full instructions for how to build one, but I documented the build extensively on my blog.  There should be enough information there (including circuit diagrams and board layouts) to follow along and build something similar.

__N.B. I found mistakes in my circuits as I went along and updated the diagrams in later blog posts.  Look for the circuit diagrams in the last few posts for the correct diagrams!!!__

Here are links to all the relevant blog posts:

[Retro Challenge 2017/04: my project summary](https://www.richardloxley.com/2017/04/01/retro-challenge-201704-my-project-summary/)

[RetroMatic 2000 update 1: video converter design](https://www.richardloxley.com/2017/04/01/retromatic-2000-update-1-video-converter-design/)

[RetroMatic 2000 update 2: HD9800 testing](https://www.richardloxley.com/2017/04/01/retromatic-2000-update-2-hd9800-testing/)

[RetroMatic 2000 update 3: reprogramming the TV5725](https://www.richardloxley.com/2017/04/01/retromatic-2000-update-3-reprogramming-the-tv5725/)

[RetroMatic 2000 update 4: video scanlines](https://www.richardloxley.com/2017/04/02/retromatic-2000-update-4-video-scanlines/)

[RetroMatic 2000 update 5: user interface ideas](https://www.richardloxley.com/2017/04/03/retromatic-2000-update-5-user-interface-ideas/)

[RetroMatic 2000 update 6: HxC floppy drive emulator](https://www.richardloxley.com/2017/04/04/retromatic-2000-update-6-hxc-floppy-drive-emulator/)

[RetroMatic 2000 update 7: more HxC testing](https://www.richardloxley.com/2017/04/04/retromatic-2000-update-7-more-hxc-testing/)

[RetroMatic 2000 update 8: Jumpers! In an Adventure with Floppy Cables!](https://www.richardloxley.com/2017/04/14/retromatic-2000-update-8-jumpers-in-an-adventure-with-floppy-cables/)

[RetroMatic 2000 update 9: treading water](https://www.richardloxley.com/2017/04/17/retromatic-2000-update-9-treading-water/)

[RetroMatic 2000 update 10: poorly HD9800 board](https://www.richardloxley.com/2017/04/20/retromatic-2000-update-10-poorly-hd9800-board/)

[RetroMatic 2000 update 11: user interface prototyping](https://www.richardloxley.com/2017/04/20/retromatic-2000-update-11-user-interface-prototyping/)

[RetroMatic 2000 update 12: power audit](https://www.richardloxley.com/2017/04/25/retromatic-2000-update-12-power-audit/)

[RetroMatic 2000 update 13: knobs!](https://www.richardloxley.com/2017/04/25/retromatic-2000-update-13-knobs/)

[RetroMatic 2000 update 14: HxC rotary encoder](https://www.richardloxley.com/2017/04/25/retromatic-2000-update-14-hxc-rotary-encoder/)

[RetroMatic 2000 update 15: sound effects](https://www.richardloxley.com/2017/04/28/retromatic-2000-update-15-sound-effects/)

[RetroMatic 2000 update 16: I’ve run out of pins on my Arduino!](https://www.richardloxley.com/2017/04/28/retromatic-2000-update-16-ive-run-out-of-pins-on-my-arduino/)

[RetroMatic 2000 update 17: final push, and prioritising](https://www.richardloxley.com/2017/04/29/retromatic-2000-update-17-final-push-and-prioritising/)

[RetroMatic 2000 update 18: metalwork and ball bearings!](https://www.richardloxley.com/2017/04/29/retromatic-2000-update-18-metalwork-and-ball-bearings/)

[RetroMatic 2000 update 19: soldering up the final circuit board](https://www.richardloxley.com/2017/04/30/retromatic-2000-update-19-soldering-up-the-final-circuit-board/)

[RetroMatic 2000 update 20: wrap up for the Retro Challenge](https://www.richardloxley.com/2017/04/30/retromatic-2000-update-20-wrap-up-for-the-retro-challenge/)

[RetroMatic 2000 update 21: fixing and debugging](https://www.richardloxley.com/2017/05/10/retromatic-2000-update-21-fixing-and-debugging/)

[RetroMatic 2000 update 22: making things permanent](https://www.richardloxley.com/2017/05/11/retromatic-2000-update-22-making-things-permanent/)

[RetroMatic 2000 update 23: finishing the case](https://www.richardloxley.com/2017/05/12/retromatic-2000-update-23-finishing-the-case/)

Feel free to contact me if you have any questions!
