# Variable
变量是个好东西 是语言的基础  
该语言的变量是弱类型的

#### 怎样定义一个变量
在试图访问一个不存在的变量时,程序会在栈里创建一个类型为**void**的变量  
此时,就可以用  
```
    builtin.var
```
函数来修改它的值
例如
~~~
    builtin.var(avar,int(109))
~~~
#### 怎样使用一个变量
~~直接用就可以了~~  
例子
~~~
    builtin.echo(avar)
~~~


*[Back](README.md)*