program test(input,output);
const a=1; //整型常量
      b=3.0; //浮点型常量
      c='c'; //字符型常量
      blank=' '; //空格
var   d:integer; //整型变量
      e:real; //浮点型变量
      f:char; //字符型变量
      g:boolean; //布尔型变量
begin
    d:=6;
    e:=6.0;
    f:='f';
    g:=2>1;//不支持true常量，所以这么写
    writeln(a,blank,b,blank,c,blank,1,blank,1.0,blank,'y');
    write(a,blank,b,blank,c,blank,1,blank,1.0,blank,'y');
    writeln;
    writeln(g);
    writeln(a+b,blank,a*b,blank,g,blank,a>b,blank,c,blank,d,blank,e,blank,d<>e);
end.