
## Description

**TRMHv** is designed with a focus on using modern hardware technologies to provide new features to the reverse engineer's world. It operates on top of Windows by virtualizing an already running system using Intel VT-x and Intel PT. This project aims not to use any APIs and software debugging mechanisms, but instead, it uses Second Layer Page Table (a.k.a. Extended Page Table or EPT) extensively to monitor both kernel and user executions.
<p align="center"><a href="https://TRMHv.org/"><img align="center" width="600" height="500" src="https://raw.githubusercontent.com/TRMHv/graphics/master/Art%20Board/Artboard%201.png" alt="TRMHv project"></a></br>
</p>
TRMHv comes with features like hidden hooks, which are as fast as old inline hooks, but also stealth. It mimics hardware debug registers for (read & write) to a specific location, but this time entirely invisible for both Windows kernel and the programs, and of course, without any limitation in size or count!

Using TLB-splitting, and having features such as measuring code coverage and monitoring all mov(s) to/from memory by a function, makes TRMHv a unique VMM.

Although it has novel features, TRMHv tries to be as stealthy as possible. It doesn’t use any debugging APIs to debug Windows or any application, so classic anti-debugging methods won’t detect it. Also, it resists the exploitation of time delta methods (e.g., RDTSC/RDTSCP) to detect the presence of hypervisors, therefore making it much harder for applications, packers, protectors, malware, anti-cheat engines, etc. to discover the project.


## How does it work?

You can read about the internal design of TRMHv and its features in the [documentation](https://docs.TRMHv.org/design). Here's a top-level diagram that shows how TRMHv works:
</br>

<p align="center"><a href="https://TRMHv.org/"><img align="center" width="70%" height="100%" src="https://raw.githubusercontent.com/TRMHv/graphics/master/Diagrams/Diagram-hq-v1/Diagram_v1.jpg" alt="TRMHv Design"></a></br>
</p>
</br>

## Scripts
You can write your **[scripts](https://github.com/TRMHv/scripts)** to automate your debugging journey. **TRMHv** has a powerful, fast, and entirely kernel-side implemented [script engine](https://docs.TRMHv.org/commands/scripting-language).

## Contributing
Contributing to TRMHv is super appreciated. We have made a list of potential [tasks](https://github.com/TRMHv/TRMHv/blob/master/CONTRIBUTING.md#things-to-work-on) that you might be interested in contributing towards.

If you want to contribute to TRMHv, please read the [Contribution Guide](https://github.com/TRMHv/TRMHv/blob/master/CONTRIBUTING.md).


## License
**TRMHv**, and all its submodules and repos, unless a license is otherwise specified, are licensed under **GPLv3** LICENSE.

Dependencies are licensed by their own.
