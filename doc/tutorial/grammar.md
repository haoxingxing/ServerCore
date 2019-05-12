# Grammar
语言首先要有语法,不然就是一盘散沙  
~~然而我的AST语法分析还没有做~~  
这里给出一些语法  

#### 语句换行符
- 使用 '\n'    
- [x] [是否实现](../../core/cmder_conf.cpp) Func str_to_map

例如
```
    echo()
    var()
```

#### 访问成员函数
- 使用 '.'
- [x] [是否实现](../../core/cmder.cpp) Func member_access

例如
```
    builtin.var
    builtin.echo
```
#### 执行函数
- 使用 '(' 和 ')'
- 中间包含变量
- [ ] [是否实现](../../core/ast.cpp) class ast


例如
```
    echo(string(Hello World))
    var(t,int(10))
```
### 流程控制
流程控制是语言的中枢
#### 如果
- 使用 if [not] else
- [ ] [是否实现]()


例如
```
    var(in,input().toInt())
    if(in.bigger(10))
        echo(string("The number is bigger than ten"))
    else
        if (in.equals(10))
            echo(string("The number is the same as ten"))
        else
            echo(string("The number is smaller than ten"))

```
#### 循环
- 使用 while [not]
- [ ] [是否实现]()

例如
```
    var(in,input().toInt())
    while(in > 0)
        echo(string("Loop "),string(in))
        var(in,in.minus(1))
```
*[Back](README.md)*