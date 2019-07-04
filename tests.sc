#!./build/StarCore*
# Test File
cout("[TEST]Hello World!\n");
if(true);
cout("[TEST]True PASS\n");
end;
if(false);
else;
cout("[TEST]Else PASS\n");
end;
a="[TEST]";
if(a.equals("[TEST]"));
cout("[TEST]Var PASS\n");
else;
cout("[TEST]Var Failed\n");
end;
n=0;
count=10000;
while(n.less(count));
cout("[TEST]While Loop:",n,"\r");
n=n.plus(1);
end;
if(n.equals(count));
cout("[TEST]While PASS       \n");
else;
cout("[TEST]While Failed:",n,"\n");
end;