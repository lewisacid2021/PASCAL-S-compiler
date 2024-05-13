program main;
type
    books = record
    title:array [0..1] of integer;
end;
type
    stu=record
    bo:books;
end;
var b:books;c:stu;
function test(a:books):integer;
begin
    test:=a.title[0];
end;
begin
    b.title[0]:=1;
    c.bo.title[0]:=1;
    write(b.title[0]);
    write(test(b));
end.
