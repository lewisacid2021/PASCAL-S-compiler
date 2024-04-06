# PASCAL-S to C Compiler

## 一键配置

### 安装依赖
``` shell
sudo apt-get update && sudo apt-get -y install gcc g++ gdb flex bison cmake git openssh-server
```
### 配置git
``` shell
git config --global user.name "Your name" 
git config --global user.email "Your email"
``` 
### 配置ssh key (直连可跳)
``` shell
ssh-keygen -t rsa
```
#### 一路回车确定
![alt text](/turtorial/image-1.png)
``` shell
cat ~/.ssh/id_rsa.pub
```
#### 复制显示内容
![alt text](/turtorial/image-2.png)
#### 进入Settings
![alt text](/turtorial/image-3.png)
#### 进入SSH and GPG keys
![alt text](/turtorial/image-4.png)
#### Add new SSH key
![alt text](/turtorial/image-5.png)
### clone仓库
``` shell
git clone git@github.com:lewisacid2021/PASCAL-S-compiler.git
# 直连执行 git clone https://github.com/lewisacid2021/PASCAL-S-compiler.git
```
### 进行初始化
``` shell
cd PASCAL-S-compiler
chmod +x init.sh
./init.sh
```



