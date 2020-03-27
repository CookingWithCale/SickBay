# [pandemic.cookbook](../)

### Contributing Guide

### C++ Style Guide

The style guide we're using is the Google C++ Style Guide that can be found at <https://google.github.io/styleguide/cppguide.html>.

### Easiest Way to Contribute

The easiest way for you to contribute is using an issue ticket at <https://github.com/KabukiStarship/sickbay/issues>. For the title, enter a one-sentence mission statement of what you want us to do. Then enter in the Description a more detailed Problem and Solution statement of what it is that you're contributing.

## Development Environment

Our primary development is for mbed using Arduino pin outs to make porting to Arduino as simple as possible. The mbed board we're using is the NUCLEO-L512RE, but any mbed board will work.

**1.** Learn the Git Revision Control System at <https://try.github.io> and sign up for a GitHub account at <https://github.com>.

**2.** There are two repositories, one for the Cookbook and another for the Sick Bay, which contains the design files. Fork both Git repositories (AKA repos) into your own account (See <https://try.github.io> for instructions on forking) so you can make and save changes and initiate Pull Requests to merge your contributions with the master branch. The repos are located at:

* <https://github.com/CookingWithCale/pandemic.cookbook>
* <https://github.com/KabukiStarship/sickbay>

**3** Clone the Cookbook repo using the command after you change MyGitHubAccountName to your GitHub account name you made in Step 1:

```Bash
git clone https://github.com/MyGitHubAccountName/pandemic.cookbook.git
git clone https://github.com/MyGitHubAccountName/sickbay.git
```

**3.** Download and install Visual Studio Code at <https://code.visualstudio.com>.

**4.** Open Visual Studio Code, and add the two Git repo folders you just cloned to your Workspace by clicking File then "Add folder to workspace..." then navigating to the pandemic.cookbook folder, and repeating for the sickbay folder.

**5.** Download and install FreeCAD at <https://www.freecadweb.org/>

## Reporting Bugs

**1.** Ensure the bug was not already reported by by reading the [Issues](https://github.com/abc_org/xyz_project/issues).

**2.** Open `/docs/bug_report_template.md` and copy it's contents to the clipboard.

**3.** Create an issue, paste the template into the Issue body and fill it out.

### Feature Requests

**1.** Same as the instructions for submitting a bug report except with using `/docs/feature_request.md`.

### Completing Issues

**1.** Clone the repo and create a branch for the IssueNuber:

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
