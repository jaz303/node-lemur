# lemur

Nothing to see yet.

Lemur will one day grow up to be an audio/MIDI playback engine with accurate timing, oriented towards live performance.

## If you're feeling brave:

  * In `Audio MIDI Setup.app`, go to `Window > Show MIDI Window`
  * Double click `IAC Driver`
  * Create a port; call it whatever you like
  * Apply and quit app
  * [Download `AU Lab`](http://www.apple.com/uk/itunes/mastered-for-itunes/)
  * Run `AU Lab` and create a new project. Remember to disable the microphone input.
  * `Edit > Add Audio Unit Instrument...`
  * Select an instrument to add
  * Double click on the instrument's title on the newly-materialised channel strip
  * Click `Edit Thru Params...`
  * Select which MIDI channels you want the instrument to receive on
  * Inspect `test.js` in this repo to get a gist of how to send MIDI data to your new instrument