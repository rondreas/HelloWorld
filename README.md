# Hello CMake

Experiment to learn to use CMake when making Modo Plug ins.

To generate project files, using CMake GUI. Set the root of the kit as the source path and run configure. You will then have to set the LXSDK_PATH by browsing to where you've downloaded the lxsdk.

It is recommended to make out of source builds, so set the target build directory to ../build and generate the project.

Hopefully this should have created a project that will not only build the source for this plug-in but also the sdk.

Resulting plug-in should be in correct AutoScan folder no matter which architecture used to build or configuration, so building DEBUG will overwrite previous RELEASE builds.
