# Address-Book-Managing-Program

本人大一下课设成果。一个通讯录管理的系统，能够维护通讯录的变更、转入学生的通讯信息的插入、转出学生的通讯信息的删除、通讯录的查询等功能，通讯录要求按照学号排序。

## 主要实现的功能包括： 

1、通讯录信息的录入：录入某班学生的通讯信息，并能够存储到文件中。

2、插入新同学信息：根据某个条件，例如，学号，将转入学生的信息插入到通讯录中。

3、删除调出同学信息：删除转出学生的通讯信息。

4、通讯录变更：根据某个条件，例如，学号，变更学生的通讯信息。

5、通讯录查询：根据某个条件，例如，学号，查询学生的详细通讯信息。 

此外实现了简单的键盘交互操作

## 各函数功能及原理：
Main:负责串联各函数功能。首先调用登录(Login)函数，返回登录成功后调用主菜单(Menu)函数。

Login:负责用户登录及存档创建。首先检测是否已经存在存档，如果不存在提示用户创建存档，并且设置密码，将密码存在存档的前100字节，并且以新存档登录，返回值为2。如果存在存档，提示用户输入密码。密码正确后返回1。

Getpassword:负责密码的输入，直接从键盘上读取字符，并且以*显示。然后存储到接收到的指针中。

Menu:负责打印出菜单，并且等待键盘操作。读取到键盘操作后，根据获取到的键值调用对应函数。

Add：负责添加新信息，追加在文件的末尾。一旦检测到用户输入*，则视为放弃输入，在不保存文件的情况下直接关闭文件。

Explore：负责展示已有的数据。先将文件的前100字节（密码）丢弃掉，然后以每100字节为单位将信息读取到结构数组中，直到文件结尾为止。最后输出所有信息。

Seek：负责查找相关信息。接收共有多少组数据以便程序停止，然后从键盘获取按键操作。每获取到一个按键就查找所有包含该按键对应字符的数据，并且显示出来。当读取到ESC键时退出。

Manage：负责文件的增删改查。打开文件，读取并打印出所有数据，从键盘读取按键操作。检测到上下键时将sel（用于控制光标的变量）+1，同时清空屏幕，重新打印。在输出过程中，当输出到排序（第几项）与sel相等的项前面会先打印出一个*，作为光标。由此可以实现用户使用上下键选择想要编辑的项目。当按下Enter键时，调用edit编辑第sel项数据，完成后排序并打印所有数据。当按下F1键时，调用seek。当按下Del键时，调用del删除第sel项，排序后重新打印。按下ESC键保存文件并返回主菜单。

Edit：负责条目的修改，接收需要修改项的指针，并且从键盘读取文字，将数据直接写入对应的地址。

Del:用于删除选定条目。将对应项的下一项覆盖到对应项上，并且所有数据向上移动1位，同时对dataexist（已有的数据量）-1。

Reset：删除已有存档并且重启存档。

Ranking:利用冒泡排序，将所有数据按学号顺序排列。
