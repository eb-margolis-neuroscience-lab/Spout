# SpoutAnalyze
A comprehensive application that works together with the SpoutCollect home cage drinking tracking device to analyze and visualize recorded data. The app is written in [`electron.js`](https://github.com/electron/electron) and runs as an independent executable. The app processes and summarizes the SpoutCollect data, output including visualing bout v time of day and estimated consumption volumes. The app also can generate reference calibrations to relate drinking duration to volume consumed.  
Graphics are generated using [`plotly.js`](https://plotly.com/javascript/), and can be saved as vector graphics. <br>

A link to the Spout journal article can be found here. (to be added)

## Example Workflow Video: Calibration Page
<img width="1087" alt="HomePage" src="https://user-images.githubusercontent.com/84408520/124176017-53b36e00-da7c-11eb-8b13-5c6027f33d80.png">

## Installing
To install **SpoutAnalyze**, go to the [`SpoutJS SourceForge Page`](https://sourceforge.net/u/ahberson/profile) and follow the instructions for your computer's platform. Apple, Windows, and Linux versions are downloadable.

## Getting Started
See the Spout device construction guide to get started collecting data.

### Analyze one file

### Analyze a group of files

### Generate a calibration curve
The calibration curve function enables consumed volumes to be estimated from the drinking durations detected. The last active calibration is automatically loaded when the app is launched and is used by the "analyze" functions. Calibrations can be exported and imported in case multiple calibration curves are required by a user. <br>

We recommend collecting data from at least 8 animals (or 16 bottles) for a calibration. <br>
