# PokeMaze - Contributing Guide

- [Issues](#issues)
- [Pull Request - Guide](#pull-request-guide)
- [Environment setup](#environment-setup)
- [Documentation standard](#doc-standard)

## <a name="issues"></a> Issues

- If any problems or doubts occur while editing the project, create an [issue](https://github.com/williamniemiec/PokeMaze/issues) describing the problem / doubt.

## <a name="pull-request-guide"></a> Pull Request - Guide

### Branch
- If the changes made do not change the structure of the application or the way to use any functionality, use the current branch; otherwise, [creates a new branch](#new-branch) in the following format:

> If the current branch is `N.x`, the new branch should be called `(N + 1).x` (without parentheses), where N is a number

<b>Attention:</b> Do not make any changes using the `master` branch, as it will be the result of the merge with the latest version released.

### Tag
- Always create a tag before creating a pull request  
- Only create the tag at the end of your changes 
- only one tag per pull request must be created  
- Choose a different tag from the current tag. If the current tag is X.Y.Z, where X, Y and Z are numbers, [create a new tag](#new-tag) using the following criteria:  
  - If the changes made are minor, that is, small modifications that do not change the way of using a feature or even for bug fixes, create the tag `X.Y.(Z + 1)` (without parentheses) 
  - If new features are added, create the `X.(Y + 1).0` tag (without parentheses)
  - If the way of using one or more features is changed, or even if a feature is deleted, create a new branch with the name `(X + 1).x` and create a new tag with the name `(X + 1).0.0` (without parentheses) 
 
<b>Attention:</b> Tag creation should be `Annotated Tags` type.


- Released versions should be placed in the `dist/X.Y` directory, where X and Y are the released version numbers  
- Try whenever possible to add tests on each added feature. If a feature is edited, make sure the tests related to it continue to work.  
- Before adding a new functionality, it is recommended to create an issue describing the new functionality and a justification of why it would be useful to the application.

If the contribution is to correct a bug, the commit should be: `bug fix # xyzw`, where #xyzw is the issue id that quotes the bug. If not, the commit should be `bug fix <DESCRIPTION>`, where \<DESCRIPTION\> is a brief description of the bug that has been fixed.

### <a name="pull-request-submit"></a> Pull request submit
After making changes to the project, create a pull request with the project you have modified. Try to add a detailed description of what you changed from the original project. Avoid changing the structure of the project as much as possible to avoid breaking code. 


 <b> Attention: </b> Before making the pull request, make sure that:  
 * Edit `Makefile` fields:
	- `MAJOR_VERSION = X`
	- `VERSION = X.Y.Z`
	Where X, Y and Z are the numbers corresponding to the tag that will contain the changes made;  
 * Update `pom.xml` with new version;
 * Document the changes according to the [documentation standard mentioned above](#doc-standard);
 * Create a new [release](https://github.com/williamniemiec/PokeMaze/releases) with changelog.

## <a name="environment-setup"></a> Setting up development environment

#### Requirements
- Operating system: Windows
- Powershell
- MinGW version: [17.1+](https://nuwen.net/mingw.html)
- [Choco](https://chocolatey.org/install)

#### How to run
1. Go to project directory

2. Open CMD and type:

> make clean

> make

<b>Note:</b> A zip file will be automatically generated when executing `make` command.

## <a name="code-style"></a>Code style guide
The project uses the [code style recommended by CppCoreGuidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c-core-guidelines). Variable and functions naming use `snake_case`, and class names `CapitalCase`.

### Example
#### Good
<pre>
if (x == 2) 
{
	return "two";
}
else if (x == 3) 
{
	return "three"
}
</pre>

#### Bad
<pre>
if (x == 2) {
	return "two";
} else if (x == 3) {
	return "three"
}
</pre>

#### Bad
<pre>
if (x == 2) {
	return "two";
} 
else if (x == 3) {
	return "three"
}
</pre>
