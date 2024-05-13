program main;
type
    books = record
    title:array [0..1] of integer;
end;
var b:books;
function test(a:books):integer;
begin
    test:=a.title[0];
end;
begin
    b.title[0]:=1;
    write(b.title);
    write(test(b));
end.
