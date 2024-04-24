
## Description

**TRMHv** is designed with a focus on using modern hardware technologies to provide new features to the debuggers' world. It operates on top of Windows by virtualizing an already running system using Intel VT-x and Intel PT. This debugger aims not to use any APIs and software debugging mechanisms, but instead, it uses Second Layer Page Table (a.k.a. Extended Page Table or EPT) extensively to monitor both kernel and user executions.
<p align="center"><a href="https://TRMHv.org/"><img align="center" width="600" height="500" src="https://raw.githubusercontent.com/TRMHv/graphics/master/Art%20Board/Artboard%201.png" alt="TRMHv Debugger"></a></br>
</p>
TRMHv comes with features like hidden hooks, which are as fast as old inline hooks, but also stealth. It mimics hardware debug registers for (read & write) to a specific location, but this time entirely invisible for both Windows kernel and the programs, and of course, without any limitation in size or count!

Using TLB-splitting, and having features such as measuring code coverage and monitoring all mov(s) to/from memory by a function, makes TRMHv a unique debugger.

Although it has novel features, TRMHv tries to be as stealthy as possible. It doesn’t use any debugging APIs to debug Windows or any application, so classic anti-debugging methods won’t detect it. Also, it resists the exploitation of time delta methods (e.g., RDTSC/RDTSCP) to detect the presence of hypervisors, therefore making it much harder for applications, packers, protectors, malware, anti-cheat engines, etc. to discover the debugger.

## Build & Installation

You can download the latest compiled binary files from **[releases](https://github.com/TRMHv/TRMHv/releases)**; otherwise, if you want to build TRMHv, you should clone TRMHv with the `--recursive` flag.
```
git clone --recursive https://github.com/TRMHv/TRMHv.git
```
Please visit **[Build & Install](https://docs.TRMHv.org/getting-started/build-and-install)** and **[Quick Start](https://docs.TRMHv.org/getting-started/quick-start)** for a detailed explanation of how to start with **TRMHv**. You can also see the **[FAQ](https://docs.TRMHv.org/getting-started/faq)** for more information, or if you previously used other native debuggers like GDB, LLDB, or WinDbg, you could see the [command map](https://TRMHv.github.io/commands-map).

## Tutorials

The **[OpenSecurityTraining2's "Reversing with TRMHv (Dbg3301)"](https://ost2.fyi/Dbg3301)** tutorial is the recommended way to get started with and learn TRMHv, guiding you through the initial steps of using TRMHv, covering essential concepts, principles, debugging functionalities, along with practical examples and numerous reverse engineering methods that are unique to TRMHv.

If you're interested in understanding the internal design and architecture of hypervisors and TRMHv, you can read the [**Hypervisor From Scratch**](https://rayanfam.com/tutorials) tutorials.

## Publications

In case you use one of **TRMHv**'s components in your work, please consider citing our paper.

**1. [TRMHv: Reinventing Hardware-Assisted Debugging (CCS'22)](https://dl.acm.org/doi/abs/10.1145/3548606.3560649)** [[arXiv](https://arxiv.org/abs/2207.05676)]

```
@inproceedings{karvandi2022TRMHv,
  title={TRMHv: Reinventing Hardware-Assisted Debugging},
  author={Karvandi, Mohammad Sina and Gholamrezaei, MohammadHosein and Khalaj Monfared, Saleh and Meghdadizanjani, Soroush and Abbassi, Behrooz and Amini, Ali and Mortazavi, Reza and Gorgin, Saeid and Rahmati, Dara and Schwarz, Michael},
  booktitle={Proceedings of the 2022 ACM SIGSAC Conference on Computer and Communications Security},
  pages={1709--1723},
  year={2022}
}
```

You can also read [this article](https://research.TRMHv.org/debugger/kernel-debugger-design.html) as it describes the overall architecture, technical difficulties, design decisions, and internals of TRMHv Debugger, [this article](https://research.TRMHv.org/debugger/transparency.html) about our efforts on vm-exit transparency, and [this article](https://research.TRMHv.org/debugger/chasing-bugs.html) about chasing bugs within hypervisors. More articles, posts, and resources are available at the **[awesome](https://github.com/TRMHv/awesome)** repo, and in addition, the **[slides](https://github.com/TRMHv/slides)** repo provides presentation slides for further reference.

## Unique Features
### First Release (v0.1.0.0)
* Advanced Hypervisor-based Kernel Mode Debugger [<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging" target="_blank">link</a>][<a href="https://docs.TRMHv.org/getting-started/attach-to-TRMHv/debug" target="_blank">link</a>][<a href="https://docs.TRMHv.org/getting-started/attach-to-TRMHv/local-debugging" target="_blank">link</a>]
* Classic EPT Hook (Hidden Breakpoint) [<a href="https://docs.TRMHv.org/commands/extension-commands/epthook" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/features/vmm-module/design-of-epthook" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/hooking-any-function" target="_blank">link</a>]
* Inline EPT Hook (Inline Hook) [<a href="https://docs.TRMHv.org/commands/extension-commands/epthook2" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/features/vmm-module/design-of-epthook2" target="_blank">link</a>]
* Monitor Memory For R/W (Emulating Hardware Debug Registers Without Limitation) [<a href="https://docs.TRMHv.org/commands/extension-commands/monitor" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/features/vmm-module/design-of-monitor" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/monitoring-accesses-to-structures" target="_blank">link</a>]
* SYSCALL Hook (Disable EFER & Handle #UD) [<a href="https://docs.TRMHv.org/commands/extension-commands/syscall" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/features/vmm-module/design-of-syscall-and-sysret" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/intercepting-all-syscalls" target="_blank">link</a>]
* SYSRET Hook (Disable EFER & Handle #UD) [<a href="https://docs.TRMHv.org/commands/extension-commands/sysret" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/features/vmm-module/design-of-syscall-and-sysret" target="_blank">link</a>]
* CPUID Hook & Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/cpuid" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/triggering-special-instructions" target="_blank">link</a>]
* RDMSR Hook & Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/msrread" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/identifying-system-behavior" target="_blank">link</a>]
* WRMSR Hook & Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/msrwrite" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/identifying-system-behavior" target="_blank">link</a>]
* RDTSC/RDTSCP Hook & Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/tsc" target="_blank">link</a>]
* RDPMC Hook & Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/pmc" target="_blank">link</a>]
* VMCALL Hook & Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/vmcall" target="_blank">link</a>]
* Debug Registers Hook & Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/dr" target="_blank">link</a>]
* I/O Port (In Instruction) Hook & Monitor  [<a href="https://docs.TRMHv.org/commands/extension-commands/ioin" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/triggering-special-instructions" target="_blank">link</a>]
* I/O Port (Out Instruction) Hook & Monitor  [<a href="https://docs.TRMHv.org/commands/extension-commands/ioout" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/triggering-special-instructions" target="_blank">link</a>]
* MMIO Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/monitor" target="_blank">link</a>]
* Exception (IDT < 32) Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/exception" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/features/vmm-module/design-of-exception-and-interrupt" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/identifying-system-behavior" target="_blank">link</a>]
* External-Interrupt (IDT > 32) Monitor [<a href="https://docs.TRMHv.org/commands/extension-commands/interrupt" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/features/vmm-module/design-of-exception-and-interrupt" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/events/identifying-system-behavior" target="_blank">link</a>]
* Running Automated Scripts [<a href="https://docs.TRMHv.org/commands/scripting-language/debugger-script" target="_blank">link</a>]
* Transparent-mode (Anti-debugging and Anti-hypervisor Resistance) [<a href="https://docs.TRMHv.org/tips-and-tricks/considerations/transparent-mode" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/misc/defeating-anti-debug-and-anti-hypervisor-methods" target="_blank">link</a>]
* Running Custom Assembly In Both VMX-root, VMX non-root (Kernel & User) [<a href="https://docs.TRMHv.org/using-TRMHv/prerequisites/how-to-create-an-action" target="_blank">link</a>]
* Checking For Custom Conditions [<a href="https://docs.TRMHv.org/using-TRMHv/prerequisites/how-to-create-a-condition" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/debugger-internals/conditions" target="_blank">link</a>]
* Process-specific & Thread-specific Debugging [<a href="https://docs.TRMHv.org/commands/meta-commands/.process" target="_blank">link</a>][<a href="https://docs.TRMHv.org/commands/meta-commands/.thread" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/user-mode-debugging/examples/basics/switching-to-a-specific-process-or-thread" target="_blank">link</a>]
* VMX-root Compatible Message Tracing [<a href="https://docs.TRMHv.org/design/features/vmm-module/vmx-root-mode-compatible-message-tracing" target="_blank">link</a>]
* Powerful Kernel Side Scripting Engine [<a href="https://docs.TRMHv.org/commands/scripting-language" target="_blank">link</a>][<a href="https://docs.TRMHv.org/design/script-engine" target="_blank">link</a>]
* Support To Symbols (Parsing PDB Files) [<a href="https://docs.TRMHv.org/commands/meta-commands/.sympath" target="_blank">link</a>][<a href="https://docs.TRMHv.org/commands/meta-commands/.sym" target="_blank">link</a>]
* Mapping Data To Symbols & Create Structures, Enums From PDB Files [<a href="https://docs.TRMHv.org/commands/debugging-commands/dt" target="_blank">link</a>][<a href="https://docs.TRMHv.org/commands/debugging-commands/struct" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/basics/mapping-data-and-create-structures-and-enums-from-symbols" target="_blank">link</a>]
* Event Forwarding (#DFIR) [<a href="https://docs.TRMHv.org/tips-and-tricks/misc/event-forwarding" target="_blank">link</a>][<a href="https://docs.TRMHv.org/commands/debugging-commands/output" target="_blank">link</a>]
* Transparent Breakpoint Handler [<a href="https://docs.TRMHv.org/commands/debugging-commands/bp" target="_blank">link</a>][<a href="https://docs.TRMHv.org/using-TRMHv/kernel-mode-debugging/examples/basics/setting-breakpoints-and-stepping-instructions" target="_blank">link</a>]
* Various Custom Scripts [<a href="https://github.com/TRMHv/scripts" target="_blank">link</a>]

### Second Release (v0.2.0.0)
* TRMHv Software Development Kit (SDK) [<a href="https://docs.TRMHv.org/using-TRMHv/sdk" target="_blank">link</a>]

### Third Release (v0.3.0.0)
* Event Short-circuiting [<a href="https://docs.TRMHv.org/tips-and-tricks/misc/event-short-circuiting" target="_blank">link</a>][<a href="https://docs.TRMHv.org/commands/scripting-language/functions/events/event_sc" target="_blank">link</a>]
* Tracking records of function calls and return addresses [<a href="https://docs.TRMHv.org/commands/extension-commands/track" target="_blank">link</a>]
* Kernel-level Length Disassembler Engine (LDE) [<a href="https://docs.TRMHv.org/commands/scripting-language/functions/diassembler/disassemble_len" target="_blank">link</a>][<a href="https://docs.TRMHv.org/commands/scripting-language/functions/diassembler/disassemble_len32" target="_blank">link</a>]

### Fourth Release (v0.4.0.0)
* Memory Execution Monitor & Execution Blocking [<a href="https://docs.TRMHv.org/commands/extension-commands/monitor" target="_blank">link</a>]
* Custom Page-fault Injection [<a href="https://docs.TRMHv.org/commands/meta-commands/.pagein" target="_blank">link</a>]

### Fifth Release (v0.5.0.0)
* Different Event Calling Stages [<a href="https://docs.TRMHv.org/tips-and-tricks/misc/event-calling-stage" target="_blank">link</a>]

### Sixth Release (v0.6.0.0)
* Injecting Custom Interrupts/Exceptions/Faults [<a href="https://docs.TRMHv.org/commands/scripting-language/functions/events/event_inject" target="_blank">link</a>][<a href="https://docs.TRMHv.org/commands/scripting-language/functions/events/event_inject_error_code" target="_blank">link</a>]

### Seventh Release (v0.7.0.0)
* Instant events in the Debugger Mode [<a href="https://docs.TRMHv.org/tips-and-tricks/misc/instant-events" target="_blank">link</a>]

### Eighth Release (v0.8.0.0)
* Detect kernel-to-user and user-to-kernel transitions [<a href="https://docs.TRMHv.org/commands/extension-commands/mode" target="_blank">link</a>]

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
