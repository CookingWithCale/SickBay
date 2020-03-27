# [pandemic.cookbook](../)

### Contributing Guide

### C++ Style Guide

The style guide we're using is the Google C++ Style Guide that can be found at <https://google.github.io/styleguide/cppguide.html>.

### Easiest Way to Contribute

The easiest way for you to contribute is using an issue ticket at <https://github.com/KabukiStarship/sickbay/issues>. For the title, enter a one-sentence mission statement of what you want us to do. Then enter in the Description a more detailed Problem and Solution statement of what it is that you're contributing.

### Contributing with Git

**1.** Ensure the bug was not already reported by by reading the [Issues](https://github.com/abc_org/xyz_project/issues).

**2.** Open `/docs/bug_report_template.md` and copy it's contents to the clipboard.

**3.** Create an issue, paste the template into the Issue body and fill it out.

## Feature Requests

**1.** Same as the instructions for submitting a bug report except with using `/docs/feature_request.md`.

### Completing Issues

**1.** Clone the repo and create a branch for the IssueNuber:

```Console
git clone https://github.com/abc_org/xyz_project.git
cd Script2™
git checkout -b Issue123
```

**2.** Complete the issue with passing unit tests and submit the completed issue:

```Console
git add --all
git commit -m "module_id.Add feature XYZ. #123"
git push origin Issue123
```

**3.** Create a Pull Requesting using the `/docs/PULL_REQUEST_TEMPLATE.md`

**4.** Get others to inspect your changes and merge the branch to the master.

**5.** Merge the branch, complete another ticket, and delete the old branch.

```Console
git checkout -b Issue125
git add --all
git commit "module_id:Fix feature ABC. #125"
git branch -d Issue123
```
