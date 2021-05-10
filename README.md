# DaisySP Test VST

A VST plugin for prototyping projects based on the DaisySP library. I use the JUCE framework for the core VST functionality, however the purpose is to use DaisySP for all DSP in the same way that we do when writing code for the Daisy Seed microcontroller. Additionally a Reaper project is provided to help test the plugin (I use ReJJ's fantastic ReSpectrum, but it can be replaced with any spectrum analyser including the built-in one).

**Important**: The Visual Studio solution and projects have been manually modified to include the DaisySP library into the build process, **if you open the project in Projucer and modify things this will all be overwritten**. Proceed with caution, I have not found a satisafctory solution to this massive issue for the moment. Suggestions welcome.
