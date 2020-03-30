# [SickBay](../)

## Contributing Guide

### Code Style Guide

The style guide we're using is the ASCII C++ Style Guide, which is a modified version of the Google C++ Style Guide that can be found at <https://github.com/kabukistarship/script2/tree/master/style_guide>. We're going to just adapt this style guide for Python, and I'll probably end up make it's repo for the Style Guide but for right now they are too coupled to split up now.

### Easiest Way to Contribute

The easiest way for you to contribute is using a GitHub Issue Ticket at <https://github.com/KabukiStarship/sickbay/issues>. For the title, enter a one-sentence mission statement of what you want us to do. Then enter in the Description a more detailed Problem and Solution statement of what it is that you're contributing, if what you want us to do is not obvious from the Title Mission Statement. You can also copy and paste any code fixes and I can manually update it, but the contribution process is industry best practice and will be some what complicated for new users, but doable.

The easiest way to program the microcontroller is hands down the mbed online IDE at <https://ide.mbed.com>, they have a system where you the mbed board shows up as a drive in Windows and you can download the firmware to the drive to program it, but it can be frustrating so more advanced users who should read the Development Environment below.

## Development Environment

Our primary development is for mbed using Arduino pin outs to make porting to Arduino as simple as possible. mbed has an online IDE so there is no need to setup an IDE, we don't have a walk through for you but feel free to contribute one via a GitHub Issue ticket. We are in need of someone to take over the Arduino ports; we need all the hardware we can get our hands on.

**1.** Sign up for a GitHub account at <https://github.com>.

**2.** Download Git for your Operating System at <https://git-scm.com/>.

**3.** Learn the Git Revision Control System at <https://try.github.io>.

**4.** There are two repositories, one for the Pandemic Cookbook and another for the SickBay, which contains the design files. Fork both Git repositories (AKA repos) into your own account (See <https://try.github.io> for instructions on forking) so you can make and save changes and initiate Pull Requests to merge your contributions with the master branch. The repos are located at:

* <https://github.com/CookingWithCale/pandemic.cookbook>
* <https://github.com/KabukiStarship/sickbay>

**5** Clone the Cookbook repos:

```Bash
git clone https://github.com/CookingWithCale/pandemic.cookbook.git
git clone https://github.com/KabukiStarship/sickbay.git
```

**6.** Download and install the latest version of FreeCAD, a really nice free Solid modeling program, at <https://www.freecadweb.org/>.

**7.** Download and install mbed studio at <https://os.mbed.com/studio/>.

## Reporting Bugs

**1.** Ensure the bug was not already reported by by reading the [Issues](https://github.com/KabukiStarship/sickbay/issues).

**2.** Open `/docs/bug_report_template.md` and copy it's contents to the clipboard.

**3.** Create an issue, paste the template into the Issue body and fill it out.

### Feature Requests

**1.** Same as the instructions for submitting a bug report except with using `/docs/feature_request.md`.

### Completing Issues

**1.** Clone the repo and create a branch for the IssueNumber:

```BASH
git checkout -b Issue123
```

**1a.** If you already have cloned the repo, it's best to move the branch like this:

```Bash
git branch -m Issue123 Issue124
```

**2.** Complete the issue with passing unit tests and submit the completed issue:

```BASH
git add --all
git commit -m "module_id.Add feature XYZ. #123"
git push origin Issue123
```

**3.** Create a Pull Requesting using the `/docs/pull_request_template.md`

**4.** Get others to inspect your changes and merge the branch to the master.

**5.** Merge the branch with the master branch after it was been reviewed and delete the branch.

## License

Copyright 2020 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
