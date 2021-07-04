早期人类驯服haskell环境不完整记录_(:з)∠)_



## ghc

### 使用choco来安装ghc

vscode里的haskell插件只支持部分版本的ghc

```
choco install ghc --version=8.10.4
```

如果需要卸载之前安装的ghc，需要使用命令

```
choco uninstall ghc --version=x.x.x
```

似乎下面这个命令也可以把ghc设置为8.10.2，是vscode的haskell插件支持的版本（没试过

```
$ stack config set resolver lts-9
```

理论上也可以从ghc的官网下载，但不是很懂下载完应该怎么操作，所以还是选择了choco

### 验证ghc装好了没

查询ghc的版本

```
$ stack exec -- ghc --version
```

成功的话会显示

```
The Glorious Glasgow Haskell Compilation System, version 8.8.4
```

进入交互式的ghci

```
$ stack exec -- ghci
```

成功的话会显示

```
GHCi, version 8.8.3: https://www.haskell.org/ghc/  :? for help
Prelude> :q
Leaving GHCi.
```



## stack

使用brew来安装stack，再用stack来安装haskell（没理解错的话

```
brew install haskell-stack
```

用stack的时候需要翻墙，要配置代理或者镜像

### 配置代理：

```
$ export http_proxy=IP:PORT 
$ stack install
```

### 配置镜像：

需要修改sr文件夹下的config.yaml文件内容为：

```
###ADD THIS IF YOU LIVE IN CHINA
setup-info-locations: 
- "http://mirrors.tuna.tsinghua.edu.cn/stackage/stack-setup.yaml"
urls:
  latest-snapshot: http://mirrors.tuna.tsinghua.edu.cn/stackage/snapshots.json

package-indices:
  - download-prefix: http://mirrors.tuna.tsinghua.edu.cn/hackage/
    hackage-security:
        keyids:
        - 0a5c7ea47cd1b15f01f5f51a33adda7e655bc0f0b0615baa8e271f4c3351e21d
        - 1ea9ba32c526d1cc91ab5e5bd364ec5e9e8cb67179a471872f6e26f0ae773d42
        - 280b10153a522681163658cb49f632cde3f38d768b736ddbc901d99a1a772833
        - 2a96b1889dc221c17296fcc2bb34b908ca9734376f0f361660200935916ef201
        - 2c6c3627bd6c982990239487f1abd02e08a02e6cf16edb105a8012d444d870c3
        - 51f0161b906011b52c6613376b1ae937670da69322113a246a09f807c62f6921
        - 772e9f4c7db33d251d5c6e357199c819e569d130857dc225549b40845ff0890d
        - aa315286e6ad281ad61182235533c41e806e5a787e0b6d1e7eef3f09d137d2e9
        - fe331502606802feac15e514d9b9ea83fee8b6ffef71335479a2e68d84adc6b0
        key-threshold: 3
        ignore-expiry: no
```

如果修改sr文件夹里的yaml文件出现语法报错，修改的时候可参考官网的模板



## run in vscode

在自己选择的目录中用git bash新建stack项目。

如果直接在vscode中创建.hs文件，用haskell去运行，会出现ghc未安装的报错（虽然实际上ghc已经通过stack安装好了）

```
stack new my-project
cd my-project
stack setup
```

用命令行的方式打开vscode，否则依然可能出现vscode找不到ghc的问题

```
code .
```



## 有关链接

stack官网：https://docs.haskellstack.org/en/stable/README/