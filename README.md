---
author:
- Benjamin Steenhoek
date: November 2018
title: ArmSim Technical Report
---

Introduction
============

This report is a feature description and user guide for ArmSim. It
describes build and run requirements, implementation details, and common
problems the user may encounter. ArmSim was built as the capstone of a
senior-year class project.

What is ArmSim?
---------------

ArmSim is a simulator of an ARM microprocessor. It can run programs that
use a subset of the ARM instruction set. Section
[2](#features) details a full
list of instructions and addressing modes. ArmSim can run user programs
via an operating system called ArmOS (Section
[7.6](#os)).

Features
========

![Screenshot of ArmSim running a
program.[]{label="fig:gui"}](gui.PNG)

GUI Overview
------------

-   Dissassembly Panel - Displays the instructions, in both encoded and
    assembly notation, before and after the instruction the Program
    Counter is currently pointing to.

-   Console - Input/Output panel to interact with the program's
    simulated memory-mapped I/O devices. (further described in Section
    [7.5](#io))

-   Loader - Offers inputs to load files and reset simulated memory.

-   Memory viewer - displays the data in simulated memory at a given
    location and the ASCII representation of each byte.

-   Various info panels - Display the condition flags, current processor
    mode, and values in all general-purpose registers.

-   Run Controls - Allows the user to control execution of the currently
    loaded program (Section [6.3](#guiguide){reference-type="ref"
    reference="guiguide"}).

-   Breakpoint window - Allows the user to add a breakpoint (Section
    [6.3](#guiguide)).

List of Features
----------------

The rest of this section is organized into A-, B-, and C-level features
-- these features were required in order to earn an A, B, or C on the
project, respectively.

### A-Level Features

-   Interrupt/Exception Handling

-   Run Program & Breakpoints

-   Unit Tests

-   Logging

### B-Level Features

-   Run/Stop Functionality

-   Trace and Reset Memory

-   Shortcuts (Section [6.2](#shortcuts)

-   Simulated memory-mapped I/O devices (Section
    [7.5](#io))

### C-Level Features

-   Run/Stop Functionality

-   Command-Line Options (Section [6.1](#cmd)

Software Prerequisites 
======================

This project was built for 64-bit Windows 10, using Qt 5.11 and the
MinGW compiler. The pre-built executable must be run on Windows 10. Qt
is a cross-platform framework, so ArmSim may be built on a machine
running Linux or Mac with Qt 5.11 and a C++ compiler compatible with Qt.

Build and Test
==============

To build ArmSim:

1.  Install the prerequisites (specified in Section
    [3](#prereq)).

2.  Open armsim.pro in the project root directory with Qt Creator.

3.  Select the Compiler Kit you want.

4.  Click Build.

To run ArmSim's unit tests:

1.  Install the prerequisites (specified in Section
    [3](#prereq)).

2.  Open armsim.pro in the project root directory with Qt Creator.

3.  Select the Compiler Kit you want.

4.  Select a unit test suite from the Run Configurations:

    -   barrelshiftertests

    -   computertests

    -   cputests

    -   instructiontests

    -   loadertests

    -   ramtests

5.  Click Run.

Configuration 
=============

ArmSim prints log messages during the course of the simulator's runtime.
The simulator does not allow the user to configure logging with a flag.
To **disable** log output, comment out lines 18-19 in (Figure
[\[fig:configfig\]](#fig:configfig){reference-type="ref"
reference="fig:configfig"}). To **redirect** log output to a file, use
file redirection when running ArmSim like so: .

``` 
        case QtDebugMsg:
            fprintf(stdout, "%s\n", msg.toStdString().c_str());
            fflush(stdout);
            break;
```

User Guide
==========

Use ArmSim by running the executable . The pre-built executable
(compiled for 64-bit Windows 10) is included here: .

Command-Line Options 
--------------------

Usage:

-   `--mem <bytes>`: Specifies the size of the simulated RAM. If this option is not
    specified, the default is .

-   `--load <filepath>`: Specifies the file to load into simulated RAM.

-   `--exec`: Requires a file to be specified with . Runs the specified file and
    shuts down ArmSim after execution has finished. If no file was
    specified with `--load`, then ArmSim runs normally.

-   `--traceall`: ArmSim does not trace program execution during exception
    processing by default. If `--traceall` is set, then ArmSim will trace program
    execution during exception processing.

Shortcuts
---------

-   `Ctrl+O`: Open a file to be loaded into simulated RAM.

-   `F5`: Run the simulator in its current state.

-   `F10`: Step forward once in the simulator.

-   `Ctrl+Q`: Stop the simulator if it is currently running.

-   `Ctrl+T`: Toggle trace on/off.

-   `Ctrl+R`: Reset the currently loaded program to its initial state.

-   `Ctrl+B`: Raise the Toggle Breakpoint window (Section
    [2](#features)).

![Screenshot of the ArmSim Run
Controls.[]{label="fig:runcontrols"}](runcontrols.PNG)

Run Controls 
------------

ArmSim allows the user to run an ARM executable in the ELF format and
displays information about the program's current state in simulated
memory. Figure [2](#fig:runcontrols) shows the ArmSim Run Controls.

1.  `Run`: Steps through the program until it reaches a halt instruction
    (Section [7.8](#halt)).

2.  `Step`: Performs one fetch-decode-execute loop, where the instruction
    executed is the one currently highlighted in the Disassembly Window.

3.  `Stop`: Stops execution after the current instruction is done executing.

4.  `Add Breakpoint`: Displays the Add Breakpoint window (Section
    [2](#features)).

5.  `Trace`: toggles tracing (Section [7.7](#tracing){reference-type="ref"
    reference="tracing"}) on the currently loaded program.

![Screenshot of the home page for the GNU GCC toolchain for
ARM.[]{label="fig:gcc"}](gcc.PNG)

Testing Files
-------------

ArmSim requires files to contain ARM instructions and to be in the ELF
format. These files can be built using the [GNU GCC toolchain for
ARM](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm). The
download page for the GCC toolchain is shown in Figure
[3](#fig:gcc) There is also a
special build script for convenience. To build a file for testing in
ArmSim:

1.  Download and install the [GNU GCC toolchain for
    ARM](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm) and
    make them accessible to the path.

2.  Download and unzip ArmOS (Section [7.6](#os){reference-type="ref"
    reference="os"}) and the make script from the [CPS 310 Github
    repository](https://github.com/sschaub/cps310/tree/master/tests/sim2/sim2tests).

3.  Run this command: (Replace with the name of your test program).

4.  The make script will include ArmOS, build the test file, and produce
    an executable and a disassembly/code listing file; for this example,
    the executable would be named and the code listing would be named .

5.  Note: To build test programs without linking ArmOS, use rather than
    .

Figure [4](#fig:makec) shows
the successful output after running on .

![Screenshot after running makec.cmd on program
test.c[]{label="fig:makec"}](makec.PNG)

Software Architecture
=====================

Multithreading
--------------

The ArmSim GUI runs in a main UI thread, and when the program is or ped
through, a separate thread is created for the computer to run until
completion. The button must quit this thread prematurely by setting a to
which holds a reference (denoted in Figure
[5](#fig:architecture)). Section [7.2](#mvc) explains why this design aligns with Model-View
Separation.

Model-View Separation 
---------------------

In Figure [5](#fig:architecture), any objects below the dotted line are
part of the Model and any objects above the line are part of the view.
ArmSim follows Model-View Separation because no classes in the Model
contain any references to any classes in the View. Three suspicious
areas come to mind, but are not violations of the principle:

-   : holds a reference to OOutputDevice(an Observer) rather than
    OutputDevice in order to preserve Model-View Separation.

-   : UI classes hold references to , but does not hold any references
    to any UI classes. is prematurely quit via a boolean pointer.

-   : Computer s QSet, but this data structure is implemented in many
    C++ general purpose libraries and can easily be replaced if Qt would
    be replaced with another framework.

Third-Party Libraries
---------------------

ArmSim uses Qt for all multithreading and UI implementation. Qt is a
cross-platform library and is available on Linux, Mac, and Windows.

Design Patterns
---------------

The Observer pattern can be seen in . This implementation does not
follow the traditional Observer pattern, but instead an abstract method
is overridden in the concrete class to send a QSignal to the UI. The
signal is a convenient, thread-safe way to notify the UI immediately of
an update in the Model.

![UML diagram of ArmSim's
architecture.[]{label="fig:architecture"}](uml.png)

Memory-Mapped I/O Devices 
-------------------------

ArmSim simulates a memory-mapped input/output device. If a byte is
written to address 0x100000, ArmSim does not store the byte in memory
and rather writes it to the Console through the (Section
[2](#features)). If a byte is
read from address 0x100001, ArmSim instead returns a character from an
internal queue maintained by ArmOS.

ArmOS 
-----

ArmOS is the name for an operating system written in ARM assembly and
designed for ArmSim. It includes a standard C library for input and
output and exception handlers so that programs can recieve keystrokes
from the simulator's GUI.

Tracing
-------

When Trace (Section [6.3](#guiguide)) is toggled on, ArmSim traces program output in
this format:

This trace is written to a file named for use in testing.

Halt
----

ArmSim treats a SWI 0x11 instruction as a directive to halt execution.
When this instruction is executed, the simulator stops running and
displays the current state of the program.

Bug Report
==========

The trace ArmSim produced matched the provided trace for all the files
provided: .

For quicksort.exe and mersenne.exe, ArmSim provided the expected output:

-   : Output all the constant numbers in in the correct order.

-   : Output prompt, took user input correctly, and printed five random
    numbers generated via the seed.

Appendices
==========

The following appendices are appended to the report: project journal,
git log, and source code listings.
