# Run CrowdNav from Scratch on Window 10   
## Install Git   
Download Git installer from [here](https://git-scm.com/downloads/win).   
## Install Visual Studio (C++ Compiler)   
1. Download Visual Studio Installer from [here](https://visualstudio.microsoft.com/zh-hant/downloads/) and then execute.   
2. Make sure to select at least the required options and packages according to the image below.
   
    ![image_b](https://github.com/user-attachments/assets/425e422d-470e-4346-a1d1-8b04db660cb6)


## Install Cmake    
Download Cmake Windows installer from [here](https://cmake.org/download/).
   
## Create Conda Environment   
1. Download Anaconda from [here](https://www.anaconda.com/download) and install.   
2. Create CowdNav environment (Python 3.6) and activate.
   
```
conda create -n crowd_nav_py36 python=3.6
```
```
conda activate crowd_nav_py36
```
   
## Install Python-RVO2 in Conda Environment   
1.  Install Cython, Cmake, and Make
   
```
pip install cython
```
```
pip install cmake
```
```
pip install make
```
2. Clone the Python-RVO2 Git repository.
   
```
git clone https://github.com/sybrenstuvel/Python-RVO2.git 
```
3. Open `cmake-gui.exe` . In "Where is the source code:", put the Python-RVO2 root folder (e.g. `C:/Users/user/Downloads/DRL/Python-RVO2-main` ). In "Where to build the binaries:", put something like `C:/Users/user/Downloads/DRL/Python-RVO2-main/build` , which will automatically create the `build` directory.
   
     ![image_k](https://github.com/user-attachments/assets/08cfa25f-3578-4eae-8817-bcb34b55a74c)

4. Click "Configure" on bottom left, click yes to accept to create the `build` directory, choose "Visual Studio 17 2022", "Use default native compilers". Click "Finish".
   
    ![image_w](https://github.com/user-attachments/assets/bcd2227c-5644-4951-b533-090c9eb32ffb)
    ![image_6](https://github.com/user-attachments/assets/9f54c825-9b28-45c7-9b72-6958bfb4f251)

5. Error occurs. Open Python-RVO2 root folder, edit `CMakeList.txt` and save it. Then click "Configure" again.   
    ![image_u](https://github.com/user-attachments/assets/47dd1a6a-c717-481c-93f9-5482ed8572d9)
    ![image](https://github.com/user-attachments/assets/92be699f-64a2-488c-bab3-05d6054952d9)
    ![image_f](https://github.com/user-attachments/assets/cfecafdd-77d5-4158-81d2-38dc4a87ce7a)

6. Click "Generate".   
7. Inside `build` directory, click `RVO.sln` to open it by Visual Studio.   
8. Select "Release" on the top.   
    ![image_x](https://github.com/user-attachments/assets/8aeb81d0-b93c-45c0-90d0-729f34392ed8)
   
9. Right clicking the `Solution 'RVO' (13 of 13 projects)` → Build Solution.   
    ![image_n](https://github.com/user-attachments/assets/08cb685d-5339-461a-a3d8-f0ccb21d9d20)

10. `RVO.lib` will be located in `build\src\Release` . Manually copy it to the Python-RVO2 root folder.   
11. Then, execute the python commands from the [Python-RVO2 README.md](https://github.com/sybrenstuvel/Python-RVO2?tab=readme-ov-file#python-bindings-for-optimal-reciprocal-collision-avoidance) in the root folder to finish the python installation.
   
```
cd C:/Users/user/Downloads/DRL/Python-RVO2-main
```
```
python setup.py build
```
```
python setup.py install
```
   
## Setup CrowdNav   
```
cd C:/Users/user/Downloads/DRL
```
```
git clone https://github.com/vita-epfl/CrowdNav.git 
```
> If you did not use Git commands to clone this repository, you may encounter one of the following errors when running train.py:   
> 
> ```
> git.exc.InvalidGitRepositoryError
> ```
> or   
> ```
>     raise ImportError(err) ImportError: Bad git executable. The git executable must be specified in one of the following ways:
>      - be included in your $PATH
>      - be set via $GIT_PYTHON_GIT_EXECUTABLE
>      - explicitly set via git.refresh()
> 
> All git commands will error until this is rectified.
> 
> This initial warning can be silenced or aggravated in the future by setting the
> $GIT_PYTHON_REFRESH environment variable. Use one of the following values:
>     - quiet|q|silence|s|none|n|0: for no warning or exception
>     - warn|w|warning|1: for a printed warning
>     - error|e|raise|r|2: for a raised exception
> 
> Example:
>     export GIT_PYTHON_REFRESH=quiet
> ```
```
cd CrowdNav
```
```
pip install -e .
```
## Run Example Code   
Start running example from [CrowdNav Github](https://github.com/vita-epfl/CrowdNav).   
> If the following error occurs, downgrade the version of the gym package.   
> 
> ```
> AssertionError: The environment must specify an action space. https://www.gymlibrary.dev/content/env
> ```
> ```
> pip install gym==0.18.0
> ```

## Reference   
- [Python-RVO2 Github](https://github.com/sybrenstuvel/Python-RVO2)   
- [CrowdNav Github](https://github.com/vita-epfl/CrowdNav)   
- [记录在Windows下安装RVO2-python包](https://juejin.cn/post/7297130301289332771)   
- [Stack Overflow - The CXX compiler identification is unknown](https://stackoverflow.com/questions/20632860/the-cxx-compiler-identification-is-unknown)   
- [Python-RVO2 Github Issuse - Build error Windows](https://github.com/sybrenstuvel/Python-RVO2/issues/22#issuecomment-1294446990)   
- [Stack Overflow - git executable not found with gitpython: "Bad git executable."](https://stackoverflow.com/questions/48399498/git-executable-not-found-with-gitpython-bad-git-executable)   
- [CrowdNav Github Issuse - train.py error](https://github.com/vita-epfl/CrowdNav/issues/15#issuecomment-562012680)   
