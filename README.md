# ChordRecogniser
A simple plugin that attempts to determine what chord a set of midi notes represents. Built using [iPlug2](https://github.com/iPlug2/iPlug2).
## Build Instructions
### XCode (macOS only)
Run `Dependencies/IPlug/download-iplug-sdks.sh` (see the [iPlug2 Wiki](https://github.com/iPlug2/iPlug2/wiki) for details on this script).

Open `Examples/ChordRecogniser/ChordRecogniser.xcworkspace` using XCode, and Build (cmd+b). 
### Other IDEs
Untested. The build instructions found in the [iPlug2 Wiki](https://github.com/iPlug2/iPlug2/wiki) should work.
## Usage Instructions
[Reaper](https://www.reaper.fm) is the suggested DAW to use this plugin in. On a new track, first add my ChordRecogniser plugin to the fx chain, then add your plugin that generates audio (from midi input). My plugin should not eat up the midi input that should be sent to your plugin. Other DAWs should have similar ways of chaining together plugins, but Reaper was the only DAW I used to test my plugin.
