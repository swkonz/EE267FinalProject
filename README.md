# EE 267 Final Project
- The following details the contents of this directory
- Virtual Reality Demo: A unity Scene constructed in order to allow a user to view a 3D medical model in virtual reality
- HoloLens Demo: a Unity scene to view and manipulate a 3D medical model in Augmented Reality using a Hololens device
- Pydicom: some short scripts for converting dicom medical imagery into alternative formats.

## Virtual Reality Demo
- The Virtual Reality Demo can be found in the folder /ee267finalcardboard
- This folder also contains the GoogleVR assets used directly in the project.
	- This folder can be opened in the Unity Hub as a new project
- The demo is also reliant on a VRduino setup and hardware consistent with the HW6 in our class.
	- The necessary code can be found in the /vrduino folder
	- Open the file "vrduino.ino" in the Arduino IDE editor, and upload to the VRduino
	- Verify the VRduino is sending orientation data using the Serial Monitor, then copy the port on the bottom left of the Arduino IDE.
	- Open the file ReadUSB.cs found in /ee267finalcardboard/Assets
		- Edit line 20 and replace the port name with the correct port open on your machine

- To run the demo, ensure that the VRduino is connected and running on the machine.
- Press "play" in the Unity Editor. This should bring up a game window.
- Move the game window to the HMD or desired display screen.
- Moving the VRduino will then cause the camera to rotate.
- Pressing the arrow keys will cause the camera to move around the scene.

-The following dependencies are required:
	- Unity 2018.3.14f1
		- Installed with the embedded Android Development JDK
	- VRDuino
		-Teensy loader

## Hololens Demo
- The hololens demo project is a Unity project which is larger than 100Mb, and thus cannot be stored on Github.
- We chose to revert to an earlier version of the Microsoft Hololens toolkit rather than the Mixed Reality Toolkit since there was seemingly better support for gesture input within unity scripts
- To run the unity project for the hololens, the following dependencies are required:
	- A Windows 10 machine
	- Unity 2017.4.28f1
		- Installed with the Windows Store .NET Scripting Backend package
		- Installed with the Windows Store IL2CPP Scritping Backend package
		- Installed with the Vuforia Augmented Reality Package
		- Can install everything by installing the Unity hub here: https://store.unity.com/download?ref=personal&_ga=2.39195626.833250537.1559902291-1018133056.1559902291
	- HoloToolkit 2017.4.1.0
	- Visual Studio 2017
	- Windows 10 SDK version 10.0.18362.0
		- All the required Microsoft tools can be downloaded from here: https://docs.microsoft.com/en-us/windows/mixed-reality/install-the-tools

- Running the Project:
	- Once all the dependencies are installed, you can run the project on a physical hololens device with the following:
		- Open file-> Build Settings. Make sure the target device is the hololens, build type is D3D, SDK and VS version are latest, Build and Run on is set to local machine, and development build is checked.
	- Once the settings are configured, hit build, and select a folder to build the project into.
	- Once the project is finished building, navigate to the build folder, and open the VS project solution in VS 2017
	- Set the build settings to 'Release', 'x86', and 'device'
	- With the hololens plugged in with a USB cable, go to the debug drop down and select 'start without debugging'. This will build the project, and upload it to the hololens.
	- The application is now available on the hololens, and you can unplug the device and use the app

## Pydicom
- Requires:
	- python 2.7.x
	- run `pip install -U pydicom`
- We used pydicom parse and anonymize data. Scripts are included


