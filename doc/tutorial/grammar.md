# Grammar
��������Ҫ���﷨,��Ȼ����һ��ɢɳ  
~~Ȼ���ҵ�AST�﷨������û����~~  
�������һЩ�﷨  

#### ��任�з�
- ʹ�� '\n'    
- [x] [ʵ��](../../core/cmder_conf.cpp) Func str_to_map

����
```
    echo()
    var()
```

#### ���ʳ�Ա����
- ʹ�� '.'
- [x] [ʵ��](../../core/cmder.cpp) Func member_access

����
```
    builtin.var
    builtin.echo
```
#### ִ�к���
- ʹ�� '(' �� ')'
- �м��������
- [ ] [ʵ��](../../core/ast.cpp) class ast


����
```
    echo(string(Hello World))
    var(t,int(10))
```
### ���̿���
���̿��������Ե�����
#### ���
- ʹ�� if [not] else
- [ ] [ʵ��]()


����
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
#### ѭ��
- ʹ�� while [not]
- [ ] [ʵ��]()

����
```
    var(in,input().toInt())
    while(in > 0)
        echo(string("Loop "),string(in))
        var(in,in.minus(1))
```
*[Back](README.md)*