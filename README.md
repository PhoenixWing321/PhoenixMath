# Phoenix Wing C++ Math

- github url:
https://github.com/PhoenixWing321/PhoenixMath.git

# other modules
please clone ref to 3rdParty
same level folder with `PhoenixMath`


## clone
```

git clone --depth 1 https://github.com/PhoenixWing321/Catch2_Single.git
git clone --depth 1 https://gitlab.com/libeigen/eigen.git
git clone --depth 1 https://gitee.com/github-transport/glm.git
```

### for example 

set folder = `D:\3rdParty`
```
3rdParty
├──PhoenixMath
├──Catch2_Single 
├──eigen 
└──glm 
```
## cmake
```
# in common.cmake, use following path
${ROOT_DIR_3rdParty} 
${ROOT_DIR_3rdParty}/glm
${ROOT_DIR_3rdParty}/eigen
${ROOT_DIR_3rdParty}/Catch2_Single

```

# config
## config in windows
- copy `my.config.bak` to `my.config`
- modify `my.config`, set your own path
- run bldAll.ps1
- run export.ps1

## config in mac os
- to be done
